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
		int result = recv(s_new, buf, sizeof(buf), 0);
		if (result == 0) break;
		buf[result] = '\0';
		response_body << "<title> HTTP SERV </title>" << endl <<
		"<h1>Test page</h1>" << endl <<
		"<p> body </p>" << endl <<
		"<h2>Request headers</h2>" << endl <<
		"<pre>" << buf << "</pre>";
		response << "HTTP/1.1 200 OK \r\n" << "Version: HTTP/1.1\r\n"
		<< "Content-Type: text/html; charset=utf-8;\r\n" <<
		"Content-Length: " << response_body.str().length() <<
		"\r\n\r\n" << response_body.str();
		send(s_new, response.str().c_str(), response.str().length(), 0);
		cout << "client is lost";
		response.str("");
		response_body.str("");
		closesocket(s_new);
	}
	closesocket(s);
	WSACleanup();
	return 0;
}
