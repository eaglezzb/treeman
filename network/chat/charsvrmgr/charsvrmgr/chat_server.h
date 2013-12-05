#pragma once
#include "chat_session.h"
#include "chat_room.h"

//它只做一件事，就是等待客户端连接；当客户端连接时，新建一个session
//然后把实际操作事务交给这个session，接着继续等待客户端连接。
class chat_server
{
public:
	chat_server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
		:io_service_(io_service),acceptor_(io_service, endpoint)
		{
			start_accept();
		}
	virtual ~chat_server(void);
	void start_accept();
    void handle_accept(chat_session_ptr session, const boost::system::error_code& error);
private:
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;