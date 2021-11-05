// Server_DGRAM.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>  
#include <winsock2.h>
#include <windows.h>
#include <string>
#include "Forms.h"
#pragma comment (lib, "Ws2_32.lib")  
using namespace std;
#define SRV_PORT 1234    
int main() {
    ClientForm in;
    ServerForm out;
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
    {
        cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
        return -1;
    }
    SOCKET s;
    sockaddr_in sin, from_sin;
    int from_len = sizeof(from_sin);
    s = socket(AF_INET, SOCK_DGRAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(SRV_PORT);
    bind(s, (sockaddr*)&sin, sizeof(sin));
        while (1) {
            recvfrom(s, (char*)&in, sizeof(ClientForm), 0, (sockaddr*)&from_sin, &from_len);
            if (in.grant < 0) break;
            if (in.grant > 2000) out.grant = GRANT_TYPE_INCREASED;
            else if (in.grant > 0) out.grant = GRANT_TYPE_NORMAL;
            else out.grant = GRANT_TYPE_ZERO;
            sendto(s, (char*)&out, sizeof(ServerForm), 0,(sockaddr*)&from_sin, from_len);
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
