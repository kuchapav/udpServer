#include "tracked_object.h"
#include "udpClient.h"

int main(int argc, char const *argv[])
{
	try
  	{

    	boost::asio::io_service io_service;

      const std::string host = argc > 1 ? std::string(argv[1]) : "localhost";
      
    	udpClient my_client(io_service, host);

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