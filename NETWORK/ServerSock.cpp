// ServerSock.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>  
#include <winsock2.h>
#include <windows.h>
#include <string>
#include "Forms.h"
CRITICAL_SECTION cs;
#pragma comment (lib, "Ws2_32.lib")  
using namespace std;
#define SRV_PORT 1234    
void inline printClient(int client) {
    cout << "Amount of clients is:" << client << endl;
}
int nclient = 0;
DWORD WINAPI handleClient(LPVOID client_socket) {
    ClientForm in;
    ServerForm out;
    SOCKET sock;
    sock = ((SOCKET*)client_socket)[0];
    while (1) {
        EnterCriticalSection(&cs);
        recv(sock, (char*)&in, sizeof(ClientForm), 0);
        if (in.grant < 0) break;
        if (in.grant > 2000) out.grant = GRANT_TYPE_INCREASED;
        else if (in.grant > 0) out.grant = GRANT_TYPE_NORMAL;
        else out.grant = GRANT_TYPE_ZERO;
        send(sock, (char*)&out, sizeof(ServerForm), 0);
        LeaveCriticalSection(&cs);
    }
    cout << "client is lost";
    nclient--;
    printClient(nclient);
    closesocket(sock);
    return 0;
}
int main() {
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
    {
        cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
        return -1;
    }
    SOCKET s, s_new;
    int from_len;
    sockaddr_in sin, from_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(SRV_PORT);
    bind(s, (sockaddr*)&sin, sizeof(sin));
    string msg, msg1;
    listen(s, SOMAXCONN);
    InitializeCriticalSection(&cs);
    while (1) {
        from_len = sizeof(from_sin);
        s_new = accept(s, (sockaddr*)&from_sin, &from_len);
        cout << "new connected client! " << endl;
        nclient++;
        printClient(nclient);
        CreateThread(NULL, NULL, handleClient, &s_new, NULL, NULL);
        /*while (1) {
            recv(s_new, (char*)&in, sizeof(ClientForm), 0);
            if (in.grant < 0) break;
            if (in.grant > 2000) out.grant = GRANT_TYPE_INCREASED;
            else if (in.grant > 0) out.grant = GRANT_TYPE_NORMAL;
            else out.grant = GRANT_TYPE_ZERO;
            send(s_new, (char*)&out, sizeof(ServerForm), 0);
        }
        */
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
