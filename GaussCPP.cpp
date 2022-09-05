// GaussCPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int N;
    cout << "Order" << endl;
    cin >> N;
    vector<vector<double>> allb;
    vector<vector<double>> all;
    vector<double> column;
    double x;
    for (int j = 0; j < N; j++) {
        cout << "Row " + j << endl;
        for (int i = 0; i < N; i++) {
            cout << "Column " + i << endl;
            cin >> x;
            column.push_back(x);
        }
        cout << "Free elem" << endl;
        cin >> x;
        column.push_back(x);
        all.push_back(column);
        column.clear();
    }
    allb.push_back(column);
    vector<vector<double>>::iterator supit = allb.begin();
    for (int i = 0; i < N; i++) {
        if (supit->at(i) != 0) {
            supit++;
            for (; supit != allb.end(); supit++) {
                if (supit->at(i) == 0) {
                    swap(*supit, allb.at(i));
                    supit = allb.begin() + i;
                    break;
                }
            }
            cout << "Unsolvable" << endl;
            return 0;
        }
        vector<double> sample = *supit;
        vector<double>::iterator it = sample.begin() + i;
        double denom = sample.at(i);
        for (; supit != allb.end(); supit++) {
            double upper = supit->at(i);
             for (vector<double>::iterator col = supit->begin() + i; col!=supit->end(); it++, col++) {
                 *col = ( (*col) - (upper / denom) * (*it));
             }
         }
        for (vector<vector<double>>::iterator testit = allb.begin(); testit != allb.end(); testit++) {
            for (vector<double>::iterator col = testit->begin(); col != supit->end(); col++)
                cout << *it;
            cout << endl;
        }
    }
    std::cout << "Hello World!\n";
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
