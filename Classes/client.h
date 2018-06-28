#pragma once
#include "cocos2d.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include"Remote.h"
using boost::asio::ip::tcp;
using namespace std;
extern int i;
class Client : public cocos2d::Node
{
public: 
	static Client* create()
	{
		Client *sprite = new Client();
		if (sprite)
		{
			sprite->autorelease();
			sprite->runClient();

			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	void runClient()
	{
		thread t(&Client::client, this);
		t.detach();
	}
	int client(void)
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket sock(io_service);
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 666);
		sock.async_connect(ep, [](const boost::system::error_code &error)
		{
			if (error)
			{
				return ;
			}
		});
		io_service.run();
		char* data[10];
		data[0] = const_cast<char*>("a");
		boost::system::error_code ec;
		size_t len;
		while (true)
		{
			len = sock.write_some(boost::asio::buffer(data), ec);

			len = sock.read_some(boost::asio::buffer(data), ec);
			if (data[0] == "a")
			{
				i = 1;
			}
		}
		return 0;

	}
};

