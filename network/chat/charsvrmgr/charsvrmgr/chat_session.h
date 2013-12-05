#pragma once
#include "chat_message.hpp"
#include "chat_participant.h"
#include "chat_room.h"
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
	 void start();
	 void deliver(const chat_message& msg);
	 void handle_read_header(const boost::system::error_code& error);
	 void handle_read_body(const boost::system::error_code& error);
	 void handle_write(const boost::system::error_code& error);
	
private:
  tcp::socket socket_;
  chat_room& room_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};
typedef boost::shared_ptr<chat_session> chat_session_ptr;
