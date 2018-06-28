#pragma once
#include "cocos2d.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace std;
extern int i;
using socket_ptr = boost::shared_ptr<boost::asio::ip::tcp::socket>;
class Server : public cocos2d::Node
{
public:
	static Server* create(void)
	{
		Server *sprite = new Server();
		if (sprite)
		{
			sprite->autorelease();
			sprite->RunServer();

			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	void RunServer(void)
	{
		thread t(&Server::server, this);
		t.detach();
	}

	int server(void)
	{
		try
		{
			boost::asio::io_service io_service;
			tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 666);
			boost::asio::ip::tcp::acceptor apt(io_service, endpoint);
			int m = 0;
			while (true)
			{
				if (m < 2)
				{
					socket_ptr sock(new boost::asio::ip::tcp::socket(io_service));
					apt.accept(*sock);
					m = m + 1;
					i = 0;
				}
				else if (m == 2)
				{
					i = 1;
					break;
				}
			}
		}
		catch (exception& e)
		{
			cerr << "Exception: " << e.what() << "\n";
		}

		return 0;
	}

};

