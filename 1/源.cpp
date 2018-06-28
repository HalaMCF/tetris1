#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace std;
using socket_ptr = boost::shared_ptr<boost::asio::ip::tcp::socket>;
int m = 0;
void session(socket_ptr sock)
{
	auto ep = sock->local_endpoint();
	char data[10]="";
	boost::system::error_code ec;
	size_t len;
	
	while (true)
	{
		len = sock->read_some(boost::asio::buffer(data), ec);
		if (ec)
		{
			cout << boost::system::system_error(ec).what() << endl;
			break;
		}
		len = sock->write_some(boost::asio::buffer(data), ec);
		if (ec)
		{
			cout << boost::system::system_error(ec).what() << endl;
			break;
		}
	}
	cout << ep.address().to_string() << "close" << endl;
}
int main(int argc, const char* argv[])
{
	boost::asio::io_service io_service;
	tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 666);
	boost::asio::ip::tcp::acceptor apt(io_service, endpoint);
	while (true)
	{
		if (m < 2)
		{
			socket_ptr sock(new boost::asio::ip::tcp::socket(io_service));
			apt.accept(*sock);
			auto ep = sock->local_endpoint();
			cout << ep.address().to_string() << "connect" << endl;
			m = m + 1;
			if (m == 2)
			{
				boost::thread(boost::bind(session, sock));
			}
		}
	}
}