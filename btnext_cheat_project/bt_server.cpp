#include "bt_server.h"
#include <iostream>
using namespace std;

vector<char> CensorshipServer::get_request()
{
	//Wait for connection and accept
	Listen80.accept(BTNextSocket, BTError);
	
	std::vector<char> request(200000);//get me 195kb of memory to hold my data
	
	size_t bytes_received = BTNextSocket.read_some(boost::asio::buffer(request, 200000), BTError);
	
	if(BTError){
		BTNextBad = true;
		}
	else{ //In case there is a retry, flag is reseted
		BTNextBad = false;
		}
	

	return vector<char>(request.begin(), request.begin() + bytes_received);
}

size_t CensorshipServer::send_request(const vector<char> &request)
{
	boost::asio::connect(TrackerSocket, endpoint_iterator, TrackerError);

	if(TrackerError){
		TrackerBad = true;
		return 0;
		}
	else{
		TrackerBad = false;
		}

	size_t bytes_sent = TrackerSocket.write_some(boost::asio::buffer(request, request.size()), TrackerError);

	if(bytes_sent < request.size())
		TrackerBad = true;

	return bytes_sent;
}

vector<char> CensorshipServer::get_anwser()
{
	vector<char> anwser(200000);
	
	size_t bytes_received = TrackerSocket.read_some(boost::asio::buffer(anwser,200000), TrackerError);

	if(TrackerError == boost::asio::error::eof)//Server closed the connection
		TrackerBad = false;
	else
		TrackerBad = true;

	return vector<char>(anwser.begin(), anwser.begin() + bytes_received);
}

size_t CensorshipServer::send_anwser(const std::vector<char> &anwser)
{
	size_t bytes_sent = boost::asio::write(BTNextSocket, boost::asio::buffer(anwser), BTError);

	BTNextSocket.close(BTError);

	if(BTError)
		BTNextBad = true;
	else
		BTNextBad = false;

	return bytes_sent;
}