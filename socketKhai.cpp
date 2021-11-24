#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<fstream>
#include<string>
#include <winsock2.h>
#include"socketKhai.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

//A function to send map to other player
void SendFile(SOCKET socket, const char* filePath) {
	//get file size
	ifstream file(filePath, ios::binary);
	file.seekg(0, ios::end);
	unsigned int fileSize = file.tellg();
	file.close();

	//get the file
	char* fileBuffer = new char[fileSize + 1];
	file.open(filePath, ios::binary);
	file.seekg(0, ios::beg);
	file.read(fileBuffer, fileSize);
	fileBuffer[fileSize] = 0;
	file.close();
	//cout << fileSize << endl;
	send(socket, fileBuffer, fileSize + 1, 0);

	delete[] fileBuffer;
}

//A function to get map from other player
void ReceiveFile(SOCKET socket, const char* filePath)
{
	int count=0;
	char* buffer = new char[1024];
	memset(buffer, 0, 1024);
	recv(socket, buffer, 1024, 0);
	for (int i = 0; i < 1024; i++)
		if (buffer[i] != 0) count++;
		else break;
	char* buffer2 = new char[count + 1];
	strcpy_s(buffer2, count+1, buffer);
	//cout << buffer << endl;
	ofstream out(filePath, ios::binary);
	if (out.is_open())
	{
		out.write(buffer2, count);
		delete[] buffer;
		delete[] buffer2;
	}
}

void PrintFile(const char* filePath) {
	ifstream file(filePath, ios::binary);
	file.seekg(0, ios::end);
	unsigned int fileSize = file.tellg();
	file.close();
	cout << fileSize << endl;
	//get the file
	char* fileBuffer = new char[fileSize + 1];
	file.open(filePath, ios::binary);
	file.seekg(0, ios::beg);
	file.read(fileBuffer, fileSize);
	cout << fileBuffer << endl;
	delete[] fileBuffer;
}

//A function to send cordinate(x,y) to other player
void SendCord(SOCKET socket, int x, int y) { 
	char buff[3];
	std::string str = "";
	str.push_back(48 + x);
	str.push_back(48 + y);
	strcpy(buff, str.c_str());
	send(socket, buff, 3, 0);
}

//A function to get cordinate(x,y) from other player
void ReceiveCord(SOCKET socket, int& x, int& y) {
	char buff[3];
	recv(socket, buff, 3, 0);
	x = (int)buff[0] - 48;
	y = (int)buff[1] - 48;
}

//A function to get IP of player 1 - server
std::string GetIP() {
	std::string IP;
	cout << "\n\nPLEASE ENTER YOUR RIVAL - SERVER IP ADDRESS: ";
	cin.ignore(100, '\n');
	getline(cin, IP);
	return IP;
}