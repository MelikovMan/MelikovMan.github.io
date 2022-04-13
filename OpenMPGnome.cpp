// OpenMPGnome.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>
using namespace std;
void gnomePart(int* a, int n, int beg, int end) {
    int i = beg + 1;
    int j = beg + 2;
    while (i <= end) {
        if (a[i] > a[i - 1]) {
            i = j;
            j++;
        }
        else {
            swap(a[i], a[i - 1]);
            i--;
            if (i == 0) {
                i = j;
                j++;
            }
        }
    }
}
int main()
{
    int n, t;
    cin >> n;
    cin >> t;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand()%100;
    }
    double t1 = omp_get_wtime();
    int size = 0;
    if (t > 1) {
        if (t > n) size = 1;
        else size = (int)n / t;
        #pragma omp parallel num_threads(t) firstprivate(n) shared(arr,size)
        {
            #pragma for schedule(dynamic)
            for (int i = 1; i <= t; i++) {
                if (i == t) gnomePart(arr, n, (i - 1) * size, n - 1);
                else gnomePart(arr, n, (i - 1) * size, i * size);
            }
        }
    }
    gnomePart(arr, n, 0, n - 1);
    double t2 = omp_get_wtime();
    cout << "Time: " << t2 - t1 << endl;
    for (int j = 0; j < n; j++) cout << arr[j] << " ";
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
