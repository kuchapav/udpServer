//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>

#include "position.h"

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), argv[1], "daytime");
    udp::endpoint receiver_endpoint = *resolver.resolve(query);

    udp::socket socket(io_service);
    socket.open(udp::v4());

    position pos;
    imr::STrackedObject trackedObj;
    trackedObj.valid = true;
    trackedObj.x = 1;
    trackedObj.y = 2;
    trackedObj.z = 3;
    trackedObj.pitch = 0.14;
    trackedObj.roll = 0.27;
    trackedObj.yaw = 0.39;
    trackedObj.pixel_ratio = 15.1267;
    trackedObj.bw_ratio = 55.653;

    pos.trackedObj = trackedObj;
    pos.x = 9;
    pos.y = 8;
    pos.z = 7;
    pos.pitch = 0.66;
    pos.roll = 0.55;
    pos.yaw = 0.44;
    
    boost::array<position, 1> send_buf  = {{ pos }};
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(recv_buf), sender_endpoint);

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}