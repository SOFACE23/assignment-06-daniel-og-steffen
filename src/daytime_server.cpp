//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp; 

std::string make_daytime_string() // function to create a string with the current date and time
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0); // get the current time stored as time_t
  // in ctime func you can pass a reference to a time_t var, and have the function return a string format of the time
  return ctime(&now); // return the current time as a string
}

int main()
{
  try // try block to catch any exceptions
  {
    boost::asio::io_context io_context; // create an io_context object

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13)); // create an acceptor object and open it to an IPV4 endpoint on port 13 

    while (true) // loop to accept connections
    {
      tcp::socket socket(io_context); // create a tcp socket object for current io context
      acceptor.accept(socket); // accept an incoming connection

      std::string message = make_daytime_string(); // create a string with the current date and time

      boost::system::error_code ignored_error; // create a dummy error_code object for next func 
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error); // write the data to the connected socket
    }
  }
  catch (std::exception &e) // catch any exceptions
  {
    std::cerr << e.what() << std::endl; // print the error message
  }

  return 0;
}