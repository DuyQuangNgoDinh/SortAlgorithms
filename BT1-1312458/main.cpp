#include "sortAlgo.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

// khởi tạo một mảng có n phần tử, mỗi phần tử từ 0 đến 99
void initArray(int* a, int n){
	srand(time(NULL));
	for(int i = 0; i < n; i++)
		a[i] = rand() % 100;
}
 // xuất mảng ra màn hình
void outArray(int* a, int n){
	cout << n << endl;
	cout << a[0];
	for(int i = 1; i < n; i++)
		cout << " " << a[i];
	cout << endl;
}

// copy từ mảng a sang mảng b, n là số lượng phần tử của mảng
void copyArray(int* a, int* b, int n){
	for(int i = 0; i < n; i++)
		b[i] = a[i];
}

// tính thời gian thực hiện thuật toán sắp xếp
void timeCount(int* a, int n, void (*algorithm)(int*, int)){
	clock_t t = clock();
	algorithm(a, n);
	t = clock() - t;
	cout << "Thoi gian thuc hien: "<< t << "(milisec)\n";
}

int main(){
	//ofstream outdev("input1000.txt", ios::out);
	int n = 1000;
	int* a = new int[n];
	int* b = new int[n];
	if(a == NULL || b == NULL) return 0;
	initArray(a, n);

	// Thuc hien cac giai thuat sort
	
	// Selection Sort
	copyArray(a, b, n);
	cout << "Giai thuat Selection Sort\n";
	timeCount(b, n, SelectionSort);
	cout << "--------------------------\n";
	
	// Bubble Sort
	copyArray(a, b, n);
	cout << "Giai thuat Bubble Sort\n";
	timeCount(b, n, BubbleSort);
	cout << "--------------------------\n";
	
	// Shaker Sort
	copyArray(a, b, n);
	cout << "Giai thuat Shaker Sort\n";
	timeCount(b, n, ShakerSort);
	cout << "--------------------------\n";
	
	// Quick Sort
	copyArray(a, b, n);
	cout << "Giai thuat Quick Sort\n";
	timeCount(b, n, QuickSort);
	cout << "--------------------------\n";
	
	// Radix Sort
	copyArray(a, b, n);
	cout << "Giai thuat Radix Sort\n";
	timeCount(b, n, RadixSort_1);
	
	delete[] a;
	delete[] b;
	return 0;
}