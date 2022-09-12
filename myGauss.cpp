// myGauss.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
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
        vector<double>::iterator it = sample.begin() + i; // выбор i столбца i строки для обхода строки начиная с i столбца
        double denom = sample.at(i);                      // выбор знаменателя
        supit++;
        for (; supit != allb.end(); supit++) {            //цикл всех строк >i по индексу
            double numen = supit->at(i);                  //выбор числителя
            it = sample.begin() + i;
            for (vector<double>::iterator col = supit->begin() + i; col != supit->end(); it++, col++) { //цикл вычитания из строк строки i
                *col = ((*col) - (numen / denom) * (*it));                                             
            }
        }
        printMatrix(allb);
    }
    vector<vector<double>>::reverse_iterator rsupit = allb.rbegin();
    for (int k = 1; k!=N && rsupit != allb.rend(); rsupit++,k++) { //приведение верхнетреугольной матрицы к диагональной
        double freethis = rsupit->back(); // Выбор свободного члена N-k строки
        double denom = rsupit->at(N - k); // Знаменатель
        for (vector<vector<double>>::reverse_iterator trsupit = rsupit + 1; trsupit != allb.rend(); trsupit++) { // Цикл прохода предыдущих строк
            double numen = trsupit->at(N-k); // Числитель
            trsupit->at(N - k) = 0; //Зануление всех элементов N-k столбца предыдущих строк
            trsupit->back() = (trsupit->back() - (numen / denom) * (freethis));  // Вычисление свободных членов
        }
        printMatrix(allb);
    }
    vector<double> solution;
    cout << "Solution: " << endl;
    for (int t = 0; t < N; t++) {
        solution.push_back(allb.at(t).at(N) / allb.at(t).at(t)); //Решение (Через диагональную матрицу)
        cout << "| " << solution.at(t) << " |" << endl; //Вывод решения
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
