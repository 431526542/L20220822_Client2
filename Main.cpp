#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include<WinSock2.h>
#include<string>


#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData WseData;

	WSAStartup(MAKEWORD(2, 2), &WseData);


	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerSOCKAddr;
	memset(&ServerSOCKAddr, 0, sizeof(SOCKADDR_IN));
	ServerSOCKAddr.sin_family = PF_INET;
	ServerSOCKAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSOCKAddr.sin_port = htons(3000);//htons 서로다른 pc의 cpu가 달라 byte order to network byte order로 한다.
	connect(ServerSocket, (SOCKADDR*)&ServerSOCKAddr, sizeof(SOCKADDR_IN));
	
	//내가 푼 문제
	/*
	for (int i = 0; i < 3; ++i)
	{
		char Buffer[1024] = { 0, };
		int RecvBytes = recv(ServerSocket, Buffer, sizeof(Buffer) - 1, 0);

		cout << Buffer << endl;
		string sBuffer = Buffer;
		int Sum = 0;
		if (sBuffer.find('+') != string::npos)
		{
			size_t pos = sBuffer.rfind('+');
			string fir = sBuffer.substr(0, pos);
			string sed = sBuffer.substr(pos + 1);
			Sum = stoi(fir) + stoi(sed);
		}
		else if (sBuffer.find('-') != string::npos)
		{
			size_t pos = sBuffer.rfind('-');
			string fir = sBuffer.substr(0, pos);
			string sed = sBuffer.substr(pos + 1);
			Sum = stoi(fir) - stoi(sed);
		}
		else if (sBuffer.find('*') != string::npos)
		{
			size_t pos = sBuffer.rfind('*');
			string fir = sBuffer.substr(0, pos);
			string sed = sBuffer.substr(pos + 1);
			Sum = stoi(fir) * stoi(sed);
		}
		else if (sBuffer.find('/') != string::npos)
		{
			size_t pos = sBuffer.rfind('/');
			string fir = sBuffer.substr(0, pos);
			string sed = sBuffer.substr(pos + 1);
			Sum = stoi(fir) / stoi(sed);
		}

		string tmp = to_string(Sum);
		char const* num_char = tmp.c_str();

		int SendBytes = send(ServerSocket, num_char, RecvBytes, 0);
	}
	*/

	//강사님 풀이
	char Buffer[1024] = { 0, };
	recv(ServerSocket, Buffer, sizeof(Buffer) - 1, 0);

	cout << Buffer << endl;

	string Message = Buffer;

	cout << Message << endl;

	int Result = 0;
	if (Message.find('+') != string::npos)
	{
		string First = Message.substr(0, Message.find('+'));
		string Second = Message.substr(Message.find('+') + 1, Message.length() + Message.find('+'));
		cout << First << "+" << Second << endl;
		Result = stoi(First) + stoi(Second);
	}
	else if (Message.find('-') != string::npos)
	{
		string First = Message.substr(0, Message.find('-'));
		string Second = Message.substr(Message.find('-') + 1, Message.length() - Message.find('-'));
		cout << First << "-" << Second << endl;
		Result = stoi(First) - stoi(Second);
	}
	else if (Message.find('*') != string::npos)
	{
		string First = Message.substr(0, Message.find('*'));
		string Second = Message.substr(Message.find('*') + 1, Message.length() * Message.find('*'));	
		cout << First << "*" << Second << endl;
		Result = stoi(First) * stoi(Second);
	}
	else if (Message.find('/') != string::npos)
	{
		string First = Message.substr(0, Message.find('/'));
		string Second = Message.substr(Message.find('/') + 1, Message.length() / Message.find('/'));
		cout << First << "/" << Second << endl;
		Result = stoi(First) / stoi(Second);
	}

	cout << Result << endl;

	string ResultString = to_string(Result);

	int SendBytes = send(ServerSocket, ResultString.c_str(), ResultString.length(), 0);
	if (SendBytes <= 0)
	{
		cout << "fail send : " << GetLastError() << endl;
		exit(-1);
	}

	recv(ServerSocket, Buffer, sizeof(Buffer) - 1, 0);

	cout << "Answer : " << Buffer << endl;

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}