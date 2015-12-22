//
// reference_counted.cpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "asio.hpp"
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using asio::ip::tcp;

// A reference-counted non-modifiable buffer class.
class shared_const_buffer
{
public:
  // Construct from a std::string.
  explicit shared_const_buffer(const std::string& data)
    : data_(new std::vector<char>(data.begin(), data.end())),
      buffer_(asio::buffer(*data_))
  {
  }

  // Implement the ConstBufferSequence requirements.
  typedef asio::const_buffer value_type;
  typedef const asio::const_buffer* const_iterator;
  const asio::const_buffer* begin() const { return &buffer_; }
  const asio::const_buffer* end() const { return &buffer_ + 1; }

private:
  std::shared_ptr<std::vector<char> > data_;
  asio::const_buffer buffer_;
};

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
  }

  void start()
  {
	do_receive_reactor();
    //do_write();
  }

private:

  void do_receive() {
	  //auto p = std::make_shared<std::string>("I love u very much!");
      std::time_t now = std::time(0);
	  auto p = std::make_shared<std::string>(std::string(std::to_string(now)));
	  //std::shared_ptr<char> p(new char[100]);
      auto self(shared_from_this());
	  socket_.async_receive(asio::buffer(buffer), [this, p, self](std::error_code ec, std::size_t length) {
	    if(!ec) {
			std::cout << "read length = " << length << ", content: " << buffer[0] << std::endl;
			do_write();
		}
		else {
			std::cout << "error when reading: " << ec.message() << std::endl;
		}
	  });

  }

  void do_receive_reactor() {
	  socket_.non_blocking(true);
      auto self(shared_from_this());
	  socket_.async_read_some(asio::null_buffers(), [this, self](std::error_code ec, std::size_t length) {
		if (!ec) {
		  std::cout << "begin to read" << std::endl;
		  int len = socket_.read_some(asio::buffer(buffer));
		  std::cout << "read length = " << len << ", content: " << buffer[0] << std::endl;
		}
		else {
		   std::cout << "error when reading: " << ec.message() << std::endl;
		}
	  });
  }

  void do_write()
  {
    std::time_t now = std::time(0);
    //shared_const_buffer buffer(std::ctime(&now));
	//std::shared_ptr<std::string> p(new std::string(std::to_string(now)));
	auto p = std::make_shared<std::string>(std::string(std::to_string(now)));

    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(*p),
        [this, self, p](std::error_code ec, std::size_t length)
        {
			do_receive();
        });
  }

  // The socket used to communicate with the client.
  tcp::socket socket_;
  std::array<char, 512> buffer;
};

class server
{
public:
  server(asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service)
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](std::error_code ec)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket_))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  tcp::socket socket_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: reference_counted <port>\n";
      return 1;
    }

    asio::io_service io_service;

    server s(io_service, std::atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
