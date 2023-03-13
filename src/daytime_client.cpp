//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try // try block to catch usage exceptions
  {
    if (argc != 2) // if the number of arguments is not 2
    {
      std::cerr << "Usage: client <host>" << std::endl; // print the correct usage format
      return 1;
    }

    boost::asio::io_context io_context; // create an io_context object

    tcp::resolver resolver(io_context); // create a resolver for current io_context
    tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime"); // resolve the given IP (host) with the service name "daytime", save as an endpoint

    tcp::socket socket(io_context); // create a socket object
    boost::asio::connect(socket, endpoints); // connect our socket to the host resolved in the endpoints variable

    while(true) // loop to read data from the server
    {
      boost::array<char, 128> buf; // create a buffer
      boost::system::error_code error; // create an error_code object

      size_t len = socket.read_some(boost::asio::buffer(buf), error); // read data coming through socket connection, store in buf var, save nr. of received bytes as len (integer)

      if (error == boost::asio::error::eof) // if the connection is closed
        break; // Connection closed cleanly by peer.
      else if (error) // if there is an actual error
        throw boost::system::system_error(error); // "throw"/print the given error that occured

      std::cout.write(buf.data(), len); // print the data
    }
  }
  catch (std::exception& e) // catch any exceptions
  {
    std::cerr << e.what() << std::endl; // print the error message
  }

  return 0;
}