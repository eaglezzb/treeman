#include "StdAfx.h"
#include "chat_session.h"

chat_session::~chat_session(void)
{
}

  tcp::socket& chat_session::socket()
  {
    return socket_;
  }
void chat_session::start()
{
room_.join(shared_from_this());
//async_read是事件处理一个机制，使用回调函数从而实现事件处理器方法
//本示例大量采用这个机制，也就是异步机制
//通过回调函数可以形成一个事件链，即在回调函数中设置一个新的事件与新回调函数
boost::asio::async_read(socket_,
	boost::asio::buffer(read_msg_.data(), chat_message::header_length),
	boost::bind(&chat_session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
  }
void chat_session::deliver(const chat_message& msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
	//OutputDebugStringA(write_msgs_.front().data());
    if (!write_in_progress)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(write_msgs_.front().data(),
            write_msgs_.front().length()),
          boost::bind(&chat_session::handle_write, shared_from_this(),
            boost::asio::placeholders::error));
    }
  }

  void chat_session::handle_read_header(const boost::system::error_code& error)
  {
    if (!error && read_msg_.decode_header())
    {
      boost::asio::async_read(socket_,
          boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
          boost::bind(&chat_session::handle_read_body, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      room_.leave(shared_from_this());
    }
  }

  void chat_session::handle_read_body(const boost::system::error_code& error)
  {
    if (!error)
    {
		std::string szbody= read_msg_.data();
		left(szbody);
		if( szbody.compare("41234") == 0)
		{
			set_checked();
		}
      room_.deliver(read_msg_);
      boost::asio::async_read(socket_,
          boost::asio::buffer(read_msg_.data(), chat_message::header_length),
          boost::bind(&chat_session::handle_read_header, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      room_.leave(shared_from_this());
    }
  }

  void chat_session::handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      write_msgs_.pop_front();
      if (!write_msgs_.empty())
      {
        boost::asio::async_write(socket_,
            boost::asio::buffer(write_msgs_.front().data(),
              write_msgs_.front().length()),
            boost::bind(&chat_session::handle_write, shared_from_this(),
              boost::asio::placeholders::error));
      }
    }
    else
    {
      room_.leave(shared_from_this());
    }
  }
 void chat_session::deliver_group(const chat_message& msg)
  {	
  }