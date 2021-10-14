// cliservrepo.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//REPLACE ALL D:\\PUBLIC_DATA WITH C:\\Users\\s0160098\\Desktop

#include <iostream>
#include "cliservrep.h"
#include <fstream>
#include <string>
#include <windows.h>
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
    while (h != NULL) {
        Data* r = p;
        p = p->next;
        delete r;
    }
}
void print(Data* h) {
    for (Data* p = h; h != NULL; p = p->next)
        std::cout << p->lastname << std::endl;
}
Data* head = new Data();
Data* tail;
int main()
{
    head->prev = NULL;
    head->next = NULL;
    head->lastname = " ";
    tail = head;
    setlocale(LC_ALL, "rus");
    std::ofstream f1;
    std::string name;
    int sala;
    ServerForm in;
    ClientForm out;
    in.lastname = "/";
    std::ifstream fiid("D:\\PUBLIC_DATA\\ClientId.txt");
    if (fiid.tellg() != 0) fiid >> out.id;
    else out.id = 0;
    fiid.close();
    std::ofstream foid("D:\\PUBLIC_DATA\\ClientId.txt");
    int o = out.id;
    (o < 128) ? foid << ++o << std::endl : foid << 0 << std::endl;
    foid.close();
    std::cout << out.id << std::endl;
    std::ifstream fi("D:\\PUBLIC_DATA\\CliInfo.txt", std::ios::binary | std::ios::ate);
    int old_pos = fi.tellg();
    fi.close();
    std::cout << "Ввести имя студента(Или end для прекращения)" << std::endl;
    std::cin >> name;
    std::cout << "Введите размер его стипендии: " << std::endl;
    std::cin >> sala;
    while (name != "end") {
        out.grant = sala;
        out.lastname = name;
        do {
            f1.open("D:\\PUBLIC_DATA\\ServInfo.txt", std::ios::binary | std::fstream::out | std::ios::app);
            if (f1) {
                f1.write((char*)&out, sizeof(out));
                f1.close();
                std::cout << "Message sent!" << std::endl;
            }
        } while (!f1);
        f1.close();
        std::cout << "Expecting package..." << std::endl;
        fi.open("D:\\PUBLIC_DATA\\CliInfo.txt", std::ios::binary | std::ios::ate);
        do {
            while (old_pos >= fi.tellg()) {
                Sleep(100);
                fi.seekg(0, std::ios::end);
            }
            fi.seekg(old_pos, std::ios::beg);
            fi.read((char*)&in, sizeof(in));
            old_pos = fi.tellg();
        } while(in.id != out.id);
        fi.close();
        std::cout << "Package received!" << std::endl;
        switch (in.grant) {
        case GRANT_TYPE_INCREASED:
            std::cout << "Last name: " << in.lastname << " Grand level: increased" << std::endl;
            break;
        case GRANT_TYPE_NORMAL:
            std::cout << "Last name: " << in.lastname << " Grand level: normal" << std::endl;
            break;
        case GRANT_TYPE_ZERO:
            append(tail, in.lastname);
            break;
        }
        std::cout << "Ввести имя студента(Или end для прекращения)" << std::endl;
        std::cin >> name;
        std::cout << "Введите размер его стипендии: " << std::endl;
        std::cin >> sala;
    }
    print(head);
    Sleep(5000);
    deleteData(head);
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
