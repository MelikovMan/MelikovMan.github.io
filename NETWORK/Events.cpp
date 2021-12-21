// Events.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
using namespace std;
HANDLE hEvent1,hEvent2;
int a[5];
DWORD WINAPI tr(LPVOID pr) {
    int i;
    int num = 0;
    while (1) {
        WaitForSingleObject(hEvent2, INFINITE);
        for (i = 0; i < 5; i++)
            a[i] = num;
        SetEvent(hEvent1);
        num++;
    }
    return 0;
}
int main()
{
    DWORD thID;
    hEvent1 = CreateEvent(NULL, false, true, NULL);
    hEvent2 = CreateEvent(NULL, false, false, NULL);

    CreateThread(NULL, NULL, tr, NULL, NULL, &thID);
    while (1) {
        WaitForSingleObject(hEvent1, INFINITE);
        for (int i = 0; i < 5; i++)
            cout << "" << a[i];
        cout << endl;
        SetEvent(hEvent2);
        cin.get();
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
