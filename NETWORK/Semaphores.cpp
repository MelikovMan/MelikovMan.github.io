// Semaphores.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
using namespace std;
HANDLE hSemaphore;
HANDLE TD1, TD2, TD3;
int a[5];
DWORD WINAPI TR1(LPVOID pr) {
    cout << "tr1 launched" << endl;
    while (WaitForSingleObject(hSemaphore, 1) != WAIT_OBJECT_0)
        cout << "tr1 timeout" << endl;
    cout << "tr1 signalled" << endl;
    Sleep(10000);
    ReleaseSemaphore(hSemaphore, 1, NULL);
    cout << "tr1 releases semaphore" << endl;
    CloseHandle(TD1);
    return 0;
}
DWORD WINAPI tr2(LPVOID pr) {
    cout << "tr2 launched" << endl;
    while (WaitForSingleObject(hSemaphore, 1) != WAIT_OBJECT_0)
        cout << "tr2 timeout" << endl;
    cout << "tr2 signalled" << endl;
    Sleep(1000);
    ReleaseSemaphore(hSemaphore, 1, NULL);
    cout << "tr2 releases semaphore" << endl;
    CloseHandle(TD2);
    return 0;
}
DWORD WINAPI tr3(LPVOID pr) {
    cout << "tr3 launched" << endl;
    while (WaitForSingleObject(hSemaphore, 1) != WAIT_OBJECT_0)
        cout << "tr3 timeout" << endl;
    cout << "tr3 signalled" << endl;
    Sleep(1000);
    ReleaseSemaphore(hSemaphore, 1, NULL);
    cout << "tr3 releases semaphore" << endl;
    CloseHandle(TD3);
    return 0;
}
int main()
{
    DWORD thID;
    hSemaphore = CreateSemaphore(NULL, 2, 2, NULL);
    TD1 = CreateThread(NULL, NULL, TR1, NULL, NULL, NULL);
    TD2 = CreateThread(NULL, NULL, tr2, NULL, NULL, NULL);
    TD3 = CreateThread(NULL, NULL, tr3, NULL, NULL, NULL);
    Sleep(10000);
    cin.get();
    CloseHandle(hSemaphore);
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
