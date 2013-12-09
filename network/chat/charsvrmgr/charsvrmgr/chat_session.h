#pragma once
#include "chat_message.hpp"
#include "chat_participant.h"
#include "chat_room.h"

//程序不认识人，它只认识一个一个连接，所以一个连接就代表着一个人
//在聊天室环境下，一个session就是一个成员的加入

class chat_session
	:public chat_participant,
     public boost::enable_shared_from_this<chat_session>
{
public:	
	 chat_session(boost::asio::io_service& io_service, chat_room& room)
    : socket_(io_service),
      room_(room)
  {
  }
	virtual ~chat_session(void);
	tcp::socket& socket();
	void start(); //会话开始，准备从客户那读取消息
	void deliver(const chat_message& msg);  //向服务的客户发送消息
	void deliver_group(const chat_message& msg); //去掉不能实例化抽象类，做什么用保留
	void handle_read_header(const boost::system::error_code& error);
	void handle_read_body(const boost::system::error_code& error);
	void handle_write(const boost::system::error_code& error);
	
private:
  tcp::socket socket_;
  chat_room& room_;
  chat_message read_msg_;
  //为什么写数据时需要一个队列，而读数据时不需要？
  //因为可能存在需要人同时向一个人发送消息，而一个无论它如何发送消息
  //也可能一条条发送，所有没有并行的可能
  chat_message_queue write_msgs_;
};
typedef boost::shared_ptr<chat_session> chat_session_ptr;
