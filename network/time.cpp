/*
	Eagle:
	study asio
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	boost::asio::io_service ios;
	boost::asio::deadline_timer(ios, boost::posix_time::seconds(5));
	t.wait();
	std::cout<<"Hello Asio";
	return 0;
}