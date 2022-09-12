// RotationMethod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
void printMatrix(vector<vector<double>> mat) {
    cout << "_________________________" << endl;
    for (vector<vector<double>>::iterator testit = mat.begin(); testit != mat.end(); testit++) {
        for (vector<double>::iterator c = testit->begin(); c != testit->end(); c++) {
            if (c + 1 == testit->end()) cout << "|";
            cout << *c << "    ";
        }
        cout << endl;
    }
    cout << "_________________________" << endl;
    cout << endl;
}
void rotationMethod(vector<double>::iterator first, vector<double>::iterator current) {
    double norm = sqrt(pow(*first, 2) + pow(*current, 2));
    double m1 = (*first) / norm;
    double m2 = (*current) / norm;
}
int main()
{
    int N;
    cout << "Order: " << endl;  // Выбор порядка квадратной матрицы
    cin >> N;
    vector<vector<double>> allb;
    vector<vector<double>> all;
    vector<double> row;
    double x;
    for (int j = 0; j < N; j++) {            // Ввод строки матрицы Ab
        cout << "Row" << endl;
        for (int i = 0; i < N; i++) {    // Ввод элементов j строки матрицы А
            cin >> x;
            row.push_back(x);
        }
        cout << "Free elem" << endl;
        cin >> x;                       //Ввод свободного элемента j
        row.push_back(x);
        allb.push_back(row);
        row.clear();
    }
    copy(allb.begin(), allb.end(), back_inserter(all)); // копия оригинала матрицы в all
    vector<vector<double>>::iterator supit;
    for (int i = 0; i < N; i++) {                 // цикл приведения матрицы к верхнетреугольному виду
        supit = allb.begin() + i;                 // выбирается i строка
        if (supit->at(i) == 0) {                  // Если aii ноль, то ищем строку > i с ненулевым элементом aii
            supit++;
            bool cont = 1;
            for (; supit != allb.end() && cont; supit++) {
                if (supit->at(i) != 0) {         // Если такая строка найдена, меняем ее местами с i строкой
                    swap(*supit, allb.at(i));
                    supit = allb.begin() + i;
                    cont = 0;
                    break;
                }
            }
            if (cont) {                         //Если такая строка не найдена, то в матрице лиюо есть нулевой столбец, либо в результате преобразований
                                                //получилась нулевая строка, следовательно ! решения не существует                            
                cout << "Unsolvable" << endl;
                return 0;
            }
        }
        vector<double> sample = *supit;                   //sample - строка-вычитаемое
        vector<double>::iterator it = sample.begin() + i;
        supit++;
        for (; supit != allb.end(); supit++) {            //цикл всех строк >i по индексу                 //выбор числителя
            it = sample.begin() + i;

        }// выбор i столбца i строки для обхода строки начиная с i столбца
    }
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
