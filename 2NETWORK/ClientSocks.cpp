﻿ // CLIENT TCP
#include <iostream>  
#define _WINSOCK_DEPRECATED_NO_WARNINGS  
// подавление предупреждений библиотеки winsock2
#include <winsock2.h>
#include <string>
#include <windows.h>
#include "Forms.h"
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996)  // подавление предупреждения 4996
using namespace std;
#define SRV_HOST "localhost"  
#define SRV_PORT 1234
#define CLNT_PORT 1235  
struct Data {
    std::string lastname;
    Data* next;
    Data* prev;
};
void append(Data*& t, std::string s) {
    Data* r = new Data();
    r->next = NULL;
    r->lastname = s;
    r->prev = t;
    t->next = r;
    t = r;
}
void deleteData(Data* h) {
    Data* p = h;
    while (p != NULL) {
        Data* r = p;
        p = p->next;
        delete r;
    }
}
void print(Data* h) {
    std::cout << "Printing start" << std::endl;
    for (Data* p = h; p != NULL; p = p->next)
        std::cout << p->lastname << std::endl;
}
Data* head = new Data();
Data* tail;
int main() {
    head->prev = NULL;
    head->next = NULL;
    head->lastname = " ";
    tail = head;
    setlocale(LC_ALL, "rus");
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
        cout << "Error WSAStartup \n" << WSAGetLastError();  // Ошибка!
        return -1;
    }
    SOCKET s;
    ClientForm out;
    ServerForm in;
    hostent* hp;
    sockaddr_in clnt_sin, srv_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    clnt_sin.sin_family = AF_INET;
    clnt_sin.sin_addr.s_addr = 0; //Подставляет порт текущего компьютера
    clnt_sin.sin_port = htons(CLNT_PORT);///переписывает значекние под формат сети.
    bind(s, (sockaddr*)&clnt_sin, sizeof(clnt_sin));
    hp = gethostbyname(SRV_HOST);
    srv_sin.sin_port = htons(SRV_PORT);
    srv_sin.sin_family = AF_INET;
    ((unsigned long*)&srv_sin.sin_addr)[0] =
        ((unsigned long**)hp->h_addr_list)[0][0];
    connect(s, (sockaddr*)&srv_sin, sizeof(srv_sin));
    string name;
    std::cout << "Ввести имя студента(Или end для прекращения)" << std::endl;
    getline(cin, name);
    while (name!="end") {
        std::cout << "Введите размер его стипендии: " << std::endl;
        std::cin >> out.grant;
        send(s, (char*)&out, sizeof(ClientForm), 0);
        recv(s, (char*)&in, sizeof(ServerForm), 0);
        switch (in.grant) {
        case GRANT_TYPE_INCREASED:
            std::cout << "Last name: " << name << " Grand level: increased" << std::endl;
            break;
        case GRANT_TYPE_NORMAL:
            std::cout << "Last name: " << name << " Grand level: normal" << std::endl;
            break;
        case GRANT_TYPE_ZERO:
            append(tail, name);
            break;
        default:
            std::cout << "Invalid type!" << std::endl;
            Sleep(3000);
            return -1;
        }
        cin.get();
        std::cout << "Ввести имя студента(Или end для прекращения)" << std::endl;
        getline(cin, name);
    }
    out.grant = -1;
    send(s, (char*)&out, sizeof(ClientForm), 0);
    cout << "exit to infinity" << endl;
    cin.get();
    Data* h = head;
    head = head->next;
    delete h;
    print(head);
    Sleep(2000);
    deleteData(head);
    closesocket(s);
    WSACleanup();
    return 0;
}