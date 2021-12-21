// ClientChat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
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
DWORD WINAPI ClientThread(LPVOID socket) {
    SOCKET sock = ((SOCKET*)socket)[0];
    char msg[4096];
    while (1) {
        int len = recv(sock, msg, sizeof(msg), 0);
        msg[len] = '\0';
        if (string(msg) == "TERMINATION") break;
        cout << msg << endl;
    }
    return 0;
}
MSG_TYPE parseType(string s) {
    if (s == "leave")
        return MSG_TYPE_LEAVE;
    if (s == "private")
        return MSG_TYPE_PRIVATE;
    if (s == "all")
        return MSG_TYPE_ALL;
    return MSG_TYPE_NULL;
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
    SOCKET clientsock = socket(AF_INET, SOCK_STREAM, NULL);
    connect(clientsock, (SOCKADDR*)&addr, sizeof(addr));
    char wlcbuf[1024];
    int buflen = recv(clientsock, wlcbuf, sizeof(wlcbuf), 0);
    wlcbuf[buflen] = '\0';
    cout << wlcbuf<< endl;
    string name = "";
    string target_name="";
    boolean name_taken = false;
    do {
        getline(cin, name);
        send(clientsock, name.c_str(), name.length(), 0);
        recv(clientsock, (char*)&name_taken, sizeof(bool), 0);
        if (name_taken) {
            buflen = recv(clientsock, wlcbuf, sizeof(wlcbuf), 0);
            wlcbuf[buflen] = '\0';
            cout << wlcbuf << endl;
        }
    } while (name_taken);
    CreateThread(NULL, NULL, ClientThread, &clientsock, NULL, NULL);
    string chatmessage = "";
    MSG_TYPE msgtype = MSG_TYPE_NULL;
    do {
        getline(cin, chatmessage);
        string s = chatmessage;
        size_t pos = s.find('/');
        if (pos == string::npos) {
            msgtype = MSG_TYPE_ALL;
        }
        else {
            s.erase(0, pos + 1);
            pos = s.find(' ');
            string typestring = s.substr(0, pos);
            msgtype = parseType(typestring);
            s.erase(0, pos+1);
            pos = s.find(' ');
            if (msgtype == MSG_TYPE_PRIVATE) {
                target_name = s.substr(0, pos);
                s.erase(0, pos + 1);
                pos = s.find(' ');
            }     
        }
        char buffer[sizeof(MessageForm)];
        MessageForm *pForm = (MessageForm*)&buffer[0];
        strncpy(pForm->nick, name.c_str(), 1024);
        strncpy(pForm->target_nick, target_name.c_str(), 1024);
        strncpy(pForm->msgbody, s.c_str(), 1024);
        send(clientsock, (char*)&msgtype, sizeof(MSG_TYPE), 0);
        send(clientsock, buffer, sizeof(buffer), 0);
        Sleep(100);
    } while (msgtype!=MSG_TYPE_LEAVE);
    if (SOCKET_ERROR == closesocket(clientsock)) {
        cout << WSAGetLastError();
        return -1;
    }
    WSACleanup();
    return 0;
}

