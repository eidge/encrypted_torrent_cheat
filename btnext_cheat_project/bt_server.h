#ifndef BT_SERVER
#define BT_SERVER

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <string>
#include <vector>

class CensorshipServer
{
	private:
		typedef boost::asio::ip::tcp tcp;
		
		const std::string _tracker;

		tcp::socket BTNextSocket;
		boost::system::error_code BTError;
		bool BTNextBad;

		tcp::socket TrackerSocket;
		boost::system::error_code TrackerError;
		bool TrackerBad;

		//Will listen on port 80 and assign connections to BTNextSocket
		boost::asio::ip::tcp::acceptor Listen80;

		tcp::resolver resolver;
		tcp::resolver::iterator endpoint_iterator;

		

	public:
		CensorshipServer(boost::asio::io_service &io_service, const std::string &tracker):
			BTNextSocket(io_service), TrackerSocket(io_service), resolver(io_service), 
			Listen80(io_service, tcp::endpoint(tcp::v4(), 80)),
			BTNextBad(false), TrackerBad(false), _tracker(tracker) {	//Resolve the tracker adress
																		tcp::resolver::query query(_tracker, "80");
																		endpoint_iterator = resolver.resolve(query);
																	}
		virtual ~CensorshipServer() {}

		std::vector<char> get_request();
		size_t send_request(const std::vector<char> &request);

		std::vector<char> get_anwser();
		size_t send_anwser(const std::vector<char> &anwser);
			
		bool BT_is_good(){return !BTNextBad;}
		bool Tracker_is_good(){return !TrackerBad;}

		void close_sockets() 
			{BTNextSocket.close(BTError); TrackerSocket.close(TrackerError);
			if(BTError || TrackerError) std::cerr << "Error socket.close()" << std::endl;}
};

#endif