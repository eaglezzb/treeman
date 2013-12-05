#include "stdafx.h"
#include "chat_server.h"

chat_server::~chat_server(void)
{
}

  void chat_server::start_accept()
  {
	  //创建一个新的session，让它接受新的连接
    chat_session_ptr new_session(new chat_session(io_service_, room_));
	 //接受新的连接，在socket上
    acceptor_.async_accept(new_session->socket(), boost::bind(&chat_server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void chat_server::handle_accept(chat_session_ptr session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      session->start();
    }

    start_accept();
  }