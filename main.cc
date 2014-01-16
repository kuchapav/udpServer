#include "tracked_object.h"
#include "udpClient.h"

int main(int argc, char const *argv[])
{
	try
  	{
    	if (argc != 2)
    	{
      		std::cerr << "Usage: main <host>" << std::endl;
      		return 1;
    	}

    	boost::asio::io_service io_service;
    	udpClient my_client(io_service, argv[1]);

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
	    
	    unsigned long id = 111111;
	    unsigned long time = 123456;

	    std::tuple<unsigned long, unsigned long, imr::STrackedObject> sendData = std::make_tuple(id, time, trackedObj);

	    my_client.send(sendData);
  	}
  	
  	catch (std::exception& e)
  	{
    	std::cerr << e.what() << std::endl;
  	}

  	return 0;
}