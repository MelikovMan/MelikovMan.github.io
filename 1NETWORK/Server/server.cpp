// server.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//REPLACE ALL D:\\PUBLIC_DATA WITH C:\\Users\\s0160098\\Desktop

#include <iostream>
#include "cliservrep.h"
#include <fstream>
#include <string>
#include <Windows.h>
int main()
{
    setlocale(LC_ALL, "rus");
    std::ifstream f;
    ClientForm in;
    ServerForm out;
    std::ofstream fo;
    f.open("D:\\PUBLIC_DATA\\ServInfo.txt", std::ios::binary | std::ios::ate);
    int old_pos = f.tellg();
    f.close();
    while (in.lastname != "end") {
        std::cout << "Ожидаем ввод..." << std::endl;
        f.open("D:\\PUBLIC_DATA\\ServInfo.txt", std::ios::binary | std::ios::ate);
        while (old_pos >= f.tellg()) {
            Sleep(100);
            f.seekg(0, std::ios::end);
        }
        f.seekg(old_pos, std::ios::beg);
        f.read((char*)&in, sizeof(in));
        old_pos = f.tellg();
        f.close();
        std::cout << "A reading..." << std::endl;
        if (in.lastname != "end") {
            out.lastname = in.lastname;
            out.id = in.id;
            if (in.grant > 2000) out.grant = GRANT_TYPE_INCREASED;
            else if (in.grant > 0) out.grant = GRANT_TYPE_NORMAL;
            else out.grant = GRANT_TYPE_ZERO;
            do {
                fo.open("D:\\PUBLIC_DATA\\CliInfo.txt", std::ios::binary | std::ios::app);
                if (fo) {
                    fo.write((char*)&out, sizeof(out));
                    fo.close();
                    std::cout << "Message sent!" << std::endl;
                }
                else {
                    std::cout << "Can't open file!" << std::endl;
                }
            } while (!fo);
        }
    }
    std::cout << "End of program";
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
