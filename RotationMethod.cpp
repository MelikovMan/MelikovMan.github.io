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
void rotationMethod(vector<double>::iterator first, vector<double>::iterator current, vector<double>::iterator firste, vector<double>::iterator currente) {
    double norm = sqrt(pow(*first, 2) + pow(*current, 2));
    double c1 = (*first) / norm;
    double s1 = (*current) / norm;
    double a1, a2;
    for (; first != firste && current != currente; first++, current++) {
        a1 = *first;
        a2 = *current;
        *first = ((c1 * a1) + s1 * a2);
        *current = ((-s1) * (a1) + c1 * (a2));
    }
}
int main()
{
    int N;
    cout << "Order: " << endl;  // Выбор порядка квадратной матрицы
    cin >> N;
    vector<vector<double>> allb;
    vector<vector<double>> all;
    vector<double> row;
    vector<double> solution (N, 0);
    vector<double> b;
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
        vector<double>::iterator cur = supit->begin() + i;
        for (; supit != allb.end(); supit++) {            //цикл всех строк >i по индексу                 //выбор числителя
            it = sample.begin() + i;
            cur = supit->begin() + i;
            rotationMethod(it, cur, sample.end(), supit->end());
        }
        printMatrix(allb);
    }
    for (int i = N - 1; i >= 0; i--) {
        double intersum = 0;
        for (int j = 0; j < N; j++) {
            intersum += allb.at(i).at(j) * solution.at(j);
        }
        solution.at(i) = (allb.at(i).at(N) - intersum) / (allb.at(i).at(i));
    }
    cout << "Solution: " << endl;
    for (vector<double>::iterator it = solution.begin(); it != solution.end(); it++) {
        cout << "|" << *it << "|" << endl;
    }
    vector<double> deltas;
    cout << "Deltas: " << endl;
    for (int r = 0; r < N; r++) { //Расчет погрешности
        double ts = 0;
        for (int c = 0; c < N; c++) ts += all.at(r).at(c) * solution.at(c);
        deltas.push_back(ts - all.at(r).at(N));
        cout << "| " << deltas.at(r) << " |" << endl;
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
