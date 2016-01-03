//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <thread>
#include <cstring>
#include <iostream>
#include "asio.hpp"

using asio::ip::tcp;

enum { max_length = 1024 };

class SS: public std::enable_shared_from_this<SS> {
private:
	tcp::socket _socket;
	char reply[10240];
	asio::streambuf response_;
public:	
	SS(tcp::socket s): _socket(std::move(s)) {
	}

	void f() {
		auto p(shared_from_this());
		using namespace std;
		cout << "fuck" << endl;
		//_socket.open(tcp::v4());
		_socket.async_read_some(asio::buffer(reply, 100),
			[p, this](std::error_code ec, std::size_t len) {
				using namespace std;
				cout << ec << " " << len << endl;
				std::cout.write(reply, len);
		});
		/*asio::async_read(_socket, asio::buffer(reply, 10240), [this, p](std::error_code ec, std::size_t len) {
			using namespace std;
			cout << ec << " " << len << endl;
		});*/

		/*int len = asio::read(_socket, asio::buffer(reply, 10));
    	std::cout.write(reply, len);*/
	}
};

void f(tcp::socket s) {
	std::shared_ptr<SS> ss(new SS(std::move(s)));
	ss->f();
}

int main(int argc, char* argv[])
{
  char reply[max_length];
  size_t reply_length = 0;
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    asio::io_service io_service;
	asio::io_service::work work(io_service);

    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);
    asio::connect(s, resolver.resolve({argv[1], argv[2]}));

    std::cout << "Enter message: ";
    char request[max_length];
    std::cin.getline(request, max_length);
	strcpy(request, "GET /index.html\r\n");
    size_t request_length = std::strlen(request);
    asio::write(s, asio::buffer(request, request_length));

	std::thread t(f, std::move(s));
	/*std::shared_ptr<SS> ss(new SS(std::move(s)));
	ss->f();*/
	io_service.run();
	//work.run();
	//std::thread t2 = std::thread([&]() { io_service.run(); });
	//io_service.run();
	t.join();
	//t2.join();

    /*reply_length = asio::read(s,
        asio::buffer(reply, 1000));
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";*/

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
	std::cout.write(reply,reply_length - 1);
  }

  return 0;
}
