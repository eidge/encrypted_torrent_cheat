#include <iostream>
#include <fstream>
#include <map>

#include "bt_server.h"

using namespace std;



int main()
{
	const string tracker = "www.google.com";
	boost::asio::io_service io_service;
	CensorshipServer CS_BTNext(io_service, tracker);

	vector<char> request;
	vector<char> anwser;

	cout << "Censorship iniciado..." << endl;
	cout << "Tracker: " << tracker << endl << endl << "EidgeAre 2012" << endl << endl;

	int option = 0;

	switch(option){
		case 0:{ //YES/NO Censor type:
			while(true)
			{
				string resposta;

				cout << "A aguardar request... ";
				request = CS_BTNext.get_request();
				cout << "request recebido." << endl << string(request.begin(), request.end()); //DEV
				cout << request.size() << endl;

				//Ask if user wants to send the request
				do{
					cout << "Reencaminho request para o tracker? (s/n)" << endl;
					cin >> resposta;
				}while(resposta[0] != 's' && resposta[0] != 'S' && resposta[0] != 'n' && resposta[0] != 'N');

				if(resposta[0] == 's' || resposta[0] == 'S')
					cout << CS_BTNext.send_request(request) << endl;
				else{
					CS_BTNext.close_sockets();
					continue;
				}

				anwser = CS_BTNext.get_anwser();
				cout << string(anwser.begin(), anwser.end());

				cout << CS_BTNext.send_anwser(anwser) << endl;
			}
		}
		case 1:{ //Automatic redirection, but save requests and answers:
			//File Description -> "size_t bytes_writen | size_t (request/answer/etc) | actual_data"
			fstream output_file;
			output_file.open("data.bin", ios::out | ios::binary | ios::trunc);
			const size_t REQUEST_TYPE = 0;
			const size_t ANWSER_TYPE = 0;
			while(true){
				 
				if(output_file.bad()){
					cerr << "Bad output file.\n";
					break;
					}

				//Get request
				cout << "A aguardar request... ";
				request = CS_BTNext.get_request();
				cout << "request recebido.\n";

					//Hold size info
					size_t bytes_to_write = request.size()*sizeof(request.at(0));
					const size_t size_of_size_t = sizeof(size_t);
					const size_t size_of_char = sizeof(request.at(0));
				
					//Writing request to disk:
					//Add number of bytes writen and content type
					output_file.write(reinterpret_cast<const char*>(&REQUEST_TYPE), (size_of_size_t));
					output_file.write(reinterpret_cast<char*>(&bytes_to_write), (size_of_size_t));
					for(size_t i = 0; i != request.size(); ++i){
						output_file.write(reinterpret_cast<char*>(&request.at(i)), size_of_char);
						}
				
				//Send request, get anwser and send it back:
				CS_BTNext.send_request(request);
				anwser = CS_BTNext.get_anwser();

					//Writing request to disk:
					bytes_to_write = anwser.size()*sizeof(request.at(0));
					output_file.write(reinterpret_cast<const char*>(&ANWSER_TYPE), (size_of_size_t));
					output_file.write(reinterpret_cast<char*>(&bytes_to_write), (size_of_size_t));
					for(size_t i = 0; i != anwser.size(); ++i){
						output_file.write(reinterpret_cast<char*>(&anwser.at(i)), size_of_char);
						}
					output_file.flush();

				CS_BTNext.send_anwser(anwser);
				
				}
			output_file.close();
			}
		case 2:{
			 //saveable anwsers that can be resent
			map<string, vector<char> > anwser_map;
			map<string, vector<char> >::iterator i;
			string a_name;
			while(true){
				//Get request
				cout << "A aguardar request... ";
				request = CS_BTNext.get_request();
				cout << "request recebido.\n";
				
				//if there's an anwser saved, then let the user choose which one to send:
				if(!anwser_map.empty()){
					while(1){
						cout << "Enter the anwser name (Type \"auto\", to get an answer from the server): ";
						cin >> a_name;

						if(a_name == "auto"){
							CS_BTNext.send_request(request);
							anwser = CS_BTNext.get_anwser();

							cout << "Should I save the anwser? ";
							cin >> a_name;

							if(a_name.at(0) == 'y' || a_name.at(0) == 'Y'){
								cout << "Enter a name to save the anwser: ";
								cin >> a_name;

								anwser_map[a_name] = anwser;
								cout << "Anwser \"" << a_name << "\" saved." << endl;
								}
							else{
								cout << "Anwser was not saved!" << endl;
								}

							break;
							}	

						if((i = anwser_map.find(a_name)) != anwser_map.end()){
							anwser = i->second;
							break;
							}
						else{
							cout << "Request not found";
							continue;
							}
						}
					}
				else{
					CS_BTNext.send_request(request);
					anwser = CS_BTNext.get_anwser();

					cout << "Should I save the anwser? ";
					cin >> a_name;

					if(a_name.at(0) == 'y' || a_name.at(0) == 'Y'){
						cout << "Enter a name to save the anwser: ";
						cin >> a_name;

						anwser_map[a_name] = anwser;
						cout << "Anwser \"" << a_name << "\" saved." << endl;
						}
					else{
						cout << "Anwser was not saved!" << endl;
						}
					}
				
				CS_BTNext.send_anwser(anwser);
				
				}
	}}
	return 0;
}
