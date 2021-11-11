// HTTPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>  
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <WS2tcpip.h>
#include <sstream>
#pragma comment (lib, "Ws2_32.lib")  
using namespace std;
#define SRV_PORT 80    
int main() {
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
	{
		cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
		return -1;
	}
	SOCKET s, s_new;
	int from_len;
	char buf[1024];
	sockaddr_in sin, from_sin;
	s = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SRV_PORT);
	bind(s, (sockaddr*)&sin, sizeof(sin));
	std::stringstream response, response_body;
	listen(s, SOMAXCONN);
	while (1) {
		from_len = sizeof(from_sin);
		s_new = accept(s, (sockaddr*)&from_sin, &from_len);
		cout << "new connected client! " << endl;
		while (1) {
			int result = recv(s_new, buf, sizeof(buf), 0);
			if (result == 0) break;
			buf[result] = '\0';
			response_body << "<title> HTTP SERV </title>" << endl <<
				"<h1>Test page</h1>" << endl <<
				"<p> body </p>" << endl <<
				"<h2>Request headers</h2>" << endl <<
				"<pre>" << buf << "</pre>";
		}
		cout << "client is lost";
		closesocket(s_new);
	}
	return 0;
}
