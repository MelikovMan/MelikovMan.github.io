#include <mpi.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
using namespace std;
void gnomeSort(int* a, int n) {
	int i = 1;
	int j = 2;
	while (i < n) {
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
void merge(int* a, int* b, int l, int m, int r) {
	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;
	while ((h <= m) && (j <= r)) {
		if (a[h] <= a[j]) {
			b[i] = a[h];
			h++;
		}
		else {
			b[i] = a[j];
			j++;
		}
		i++;
	}
	if (m < h) {
		for (k = j; k <= r; k++) {
			b[i] = a[k];
			i++;
		}
	}
	else {
		for (k = h; k <= m; k++) {
			b[i] = a[k];
			i++;
		}
	}

	for (k = l; k <= r; k++) {
		a[k] = b[k];
	}
}

void mergeSort(int* a, int* b, int l, int r) {
	int m;
	if (l < r) {
		m = (l + r) / 2;
		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);
	}
}
int main(int argc, char** argv) {
	int i, j, k, l;
	double start, stop;
	int* a, * b, * c, * buffer, * ans, * displace;
	int* sendprocs, * recvprocs;
	int size = 25000;
	int rank, numprocs, line;
	srand(time(0));
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	line = size / numprocs;
	//cout << "Input size:" << endl;
	//cin >> size;
	/*displace = new int[numprocs];
	sendprocs = new int[numprocs];
	recvprocs = new int[numprocs];
	for (int i = 0; i < numprocs; i++) {
		sendprocs[i] = line;
		recvprocs[i] = line;
		displace[i] = i*line;
	}
	*/
	buffer = new int[line];
	//ans = new int(line);
	start = MPI_Wtime();
	a = new int[size];
	b = new int[size];
	if (rank == 0) {
		for (int i = 0; i < size; i++) a[i] = rand() % 20;
	}
	MPI_Scatter(a, line, MPI_INT, buffer, line, MPI_INT, 0, MPI_COMM_WORLD);
	gnomeSort(buffer, line);
	MPI_Gather(buffer, line, MPI_INT, b, line, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		if (numprocs > 1) {
			c = new int[size];
			mergeSort(b, c, 0, size - 1);
			stop = MPI_Wtime();
			cout << stop - start << endl;
			for (int i = 0; i < size; i++) cout << c[i] << " ";
			delete[] c;
		}
		else {
			stop = MPI_Wtime();
			cout << stop - start << endl;
			for (int i = 0; i < size; i++) cout << b[i] << " ";
		}
	}
	delete[] b;
	delete[] a;
	delete[] buffer;
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}