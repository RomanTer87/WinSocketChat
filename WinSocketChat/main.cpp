#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include"ServerSocket.h"
#include"ClientSocket.h"

void main()
{
	setlocale(LC_ALL, "");
	//CONST INT SIZE_NAME = 32;
	//CHAR sz_username[SIZE_NAME] = "Server";

	int nChoice;
	int port = 22000;
	string ipAddress;
	char recieveMessage[MAXSTRLEN]{};
	char sendMessage[MAXSTRLEN]{};
	cout << "1. Start server" << endl;
	cout << "2. Connect to server" << endl;
	cout << "3. Exit" << endl;
	cin >> nChoice;
	switch (nChoice)
	{
	case 1:
	{
		ServerSocket server;
		cout << "Starting server" << endl;
		server.StartHosting(port);
		while (true)
		{
			//cout << "Waiting..." << endl;
			server.RecieveData(recieveMessage, MAXSTRLEN);
			if (strstr(sendMessage, "bye"))
			{
				server.AcceptClient();
			}
			cout/* << "Recieved: "*/ << recieveMessage << endl;
			server.SendDataMessage();
			if (strstr(recieveMessage, "bye"))break;
		}
	}
		break;
	case 2:
	{
		string username;
		ipAddress = "127.0.0.1";
		//cout << "Enter IP address: "; cin >> ipAddress;
		cout << "Enter username: "; cin >> username;
		ClientSocket client = username;
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			ZeroMemory(sendMessage, sizeof(sendMessage));
			ZeroMemory(recieveMessage, sizeof(recieveMessage));
			strcpy(sendMessage, client.SendDataMessage());
			if (strstr(sendMessage, "bye"))break;
			//cout << "Waiting" << endl;
			client.RecieveData(recieveMessage, MAXSTRLEN);
			cout/* << "Recieved: "*/ << recieveMessage << endl;
			if (strstr(recieveMessage, "bye"))break;
		}
		client.CloseConnection();
	}
	break;
	}
}