// ServerChat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <winsock2.h>
#include <windows.h>
#include <string>
#include "MessageForms.h"
#pragma comment (lib, "Ws2_32.lib") 
#pragma warning(disable: 4996)
#pragma pack(push, 1)
using namespace std;
map <string, SOCKET> clientList;
char nick[1024];
const string welcomemsg = "Welcome to the chat! Please, input your username.";
const string debugwelcomemsg = "Username is already taken. Try again";
DWORD WINAPI handleMessages(LPVOID name) {
    string curname = ((char*)name);
    SOCKET cursock = clientList.find(curname)->second;
    MessageForm *message;
    bool leave = 0;
    int size = 0;
    MSG_TYPE msgtype = MSG_TYPE_NULL;
    while (!leave) {
        recv(cursock, (char*)&msgtype, sizeof(msgtype), 0);
        char buffalo[8046];
        int len = recv(cursock, buffalo, sizeof(buffalo), 0);
        buffalo[len] = '\0';
        message = (MessageForm*)&buffalo[0];
        map <string, SOCKET>::iterator it;
        string msg;
        switch (msgtype) {
        case MSG_TYPE_ALL:
            msg = string(message->nick) + ": " + string(message->msgbody);
            for (it = clientList.begin(); it != clientList.end(); it++)
                send(it->second, msg.c_str(), msg.length(), 0);
            break;
        case MSG_TYPE_PRIVATE:
            it = clientList.find(message->target_nick);
            if (it == clientList.end()) {
                msg = "Invalid nickname!";
                send(cursock, msg.c_str(), msg.length(), 0);
            }
            else {
                msg = "Private msg from " + string(message->nick) + ": " + string(message->msgbody);
                send(it->second, msg.c_str(), msg.length(), 0);
            }
            break;
        case MSG_TYPE_LEAVE:
            msg = "TERMINATION";
            send(cursock, msg.c_str(), msg.length(), 0);
            leave = true;
            break;
        case MSG_TYPE_TEST:
            msg = "TEST";
            send(cursock, msg.c_str(), msg.length(), 0);
            break;
        case MSG_TYPE_NULL:
        default:
            msg = "Invalid request header!";
            send(cursock, msg.c_str(), msg.length(),0);
        }
    }
    string leavemsg = curname + " left the chat";
    clientList.erase(curname);
    for(map <string, SOCKET>::iterator lit=clientList.begin();lit!=clientList.end();lit++)
        send(lit->second, leavemsg.c_str(), leavemsg.length(), 0);
    closesocket(cursock);
    return 0;
}
DWORD WINAPI handleNewClient(LPVOID socket) {
    SOCKET sock = ((SOCKET*)socket)[0];
    send(sock, welcomemsg.c_str(), welcomemsg.length(),0);
    bool sameName;
    string nNick;
    do {
        int len = recv(sock, nick, sizeof(nick), 0);
        nick[len] = '\0';
        string tempNick = nick;
        sameName = clientList.find(tempNick) != clientList.end();
        send(sock, (char*)&sameName, sizeof(sameName), 0);
        if (sameName)  send(sock, debugwelcomemsg.c_str(), debugwelcomemsg.size(), 0);
    } while (sameName);
    nNick = nick;
    clientList[nNick] = sock;
    CreateThread(NULL, NULL, handleMessages, &nick, NULL, NULL);
    string welcomemsg = nNick + " joined the chat!";
    for (map <string, SOCKET>::iterator wit = clientList.begin(); wit != clientList.end(); wit++) {
        send(wit->second, welcomemsg.c_str(), welcomemsg.length(), 0);
    }
    return 0;
}
int main()
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    WSAStartup(DLLVersion, &wsaData);
    sockaddr_in addr;
    int addrsize = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(2000);
    addr.sin_family = AF_INET;
    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, NULL);
    bind(listen_socket, (SOCKADDR*)&addr, addrsize);
    listen(listen_socket, SOMAXCONN);
    SOCKET client_socket;
    while (true) {
        client_socket = accept(listen_socket, (SOCKADDR*)&addr, &addrsize);
        CreateThread(NULL, NULL, handleNewClient, &client_socket, NULL, NULL);
    }
    return 0;
}

