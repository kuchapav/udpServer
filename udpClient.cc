#include "udpClient.h"

udpClient::udpClient(boost::asio::io_service& io_service_, const char *host_) 
	: host(host),
	  resolver(io_service_),
	  query(boost::asio::ip::udp::v4(), host, "client"),
	  receiver_endpoint(*resolver.resolve(query)),
	  socket(io_service_)
{
	socket.open(boost::asio::ip::udp::v4());
}

udpClient::~udpClient()
{
	
}

void udpClient::send(std::tuple<unsigned long, unsigned long, imr::STrackedObject> data)
{
	boost::array<std::tuple<unsigned long, unsigned long, imr::STrackedObject>, 1> send_buf  = {{ data }};
	socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
}