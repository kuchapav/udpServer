#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <boost/array.hpp>
#include <tuple>
#include "tracked_object.h"

class udpClient
{
public:
	udpClient(boost::asio::io_service& io_service, const std::string host);
	~udpClient(void);
	void send(std::tuple<unsigned long, unsigned long, imr::STrackedObject> data);

private:
	const std::string host;
	boost::asio::ip::udp::resolver resolver;
    boost::asio::ip::udp::resolver::query query;
    boost::asio::ip::udp::endpoint receiver_endpoint;
	boost::asio::ip::udp::socket socket;
};


#endif // UDPCLIENT_H