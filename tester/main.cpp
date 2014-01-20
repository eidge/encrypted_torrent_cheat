#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
	map<string, int> map1;
	
	map1[string("hello")] = 2;
	cout << map1.find("hello2")->first;
	
	
	//FILE TEST
	//ifstream file("data.bin");

	//size_t type = 3;
	//size_t bytes = 3;

	//vector<char> vec;

	//file.read(reinterpret_cast<char*>(&type), sizeof(type));
	//file.read(reinterpret_cast<char*>(&bytes), sizeof(bytes));
	//
	//cout << type << endl << bytes << endl << endl;
	//END FILE TEST

	getchar();
	return 0;
}