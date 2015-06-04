#include "sortAlgo.h"
#include <stdio.h>
#include <malloc.h>
#define BASE 10
#define M 500

// swap the value of two elements
void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

/* ----------------------------- Selection Sort ----------------------------- */
void SelectionSort(int* a, int n){
	int imin;
	for(int i = 0; i < n - 1; i++){
		imin = i;
		for(int j = i + 1; j < n; j++){
			if(a[imin] > a[j])
				imin = j;
		}
		swap(a[i], a[imin]);
	}
}

/* ----------------------------- Bubble Sort ----------------------------- */
void BubbleSort(int* a, int n){
	for(int i = 0; i < n - 1; i++){
		for(int j = n - 1; j > i; j--){
			if(a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
		}
	}
}

/* ----------------------------- Shaker Sort ----------------------------- */
void ShakerSort(int* a, int n){
	int left, right, j, k;
	left = 1;
	right = n - 1;
	k = n - 1;
	do {
		for(j = right; j >= left; j--)
			if(a[j - 1] > a[j]){
				swap(a[j], a[j - 1]);
				k = j;
			}
		left = k + 1;
		for(j = left; j <= right; j++)
			if(a[j - 1] > a[j]){
				swap(a[j], a[j - 1]);
				k = j;
			}
		right = k - 1;
	} while(left <= right);
}

/* ----------------------------- Quick Sort ----------------------------- */
void quick_sort(int* a, int left, int right){
	int x = a[(left + right) / 2];
	int i = left, j = right;
	do{
		while(a[i] < x) i++;
		while(a[j] > x) j--;
		if(i <= j){
			swap(a[i], a[j]);
			i++;
			j--;
		}
	} while(i <= j);
	if(left < j) quick_sort(a, left, j);
	if(right > i) quick_sort(a, i, right);
}

void QuickSort(int* a, int n){
	quick_sort(a, 0, n - 1);
}

/* ----------------------------- Radix Sort (1) ----------------------------- */
void RadixSort_1(int* a, int n){
	int i, m = a[0], exp = 1;
	int* b = new int[n];
	if(b == NULL) return;
	//Get the greatest value in the array a and assign it to m
	for (i = 1; i < n; i++)
		if(a[i] > m)
			m = a[i];

	//Loop until exp is bigger than the largest number
	while(m / exp > 0){
		int bucket[BASE] = {0};
		//Count the number of keys that will go into each bucket
		for(i = 0; i < n; i++)
			bucket[(a[i] / exp) % BASE]++;

		//Add the count of the previous buckets to acquire the indexes after the end of each bucket location in the array
		for(i = 1; i < BASE; i++)
		  bucket[i] += bucket[i - 1];

		//Starting at the end of the list, get the index corresponding to the a[i]'s key, decrement it, and use it to place a[i] into array b.
		for(i = n - 1; i >= 0; i--)
			b[--bucket[(a[i] / exp) % BASE]] = a[i];
 
		//Copy array b to array a
		for(i = 0; i < n; i++)
			a[i] = b[i];
 
		//Multiply exp by the BASE to get the next group of keys
		exp *= BASE;
	}
	delete[] b;
}

/* ----------------------------- Binary Insertion Sort ----------------------------- */
void BinaryInsertionSort(int* a, int n){
	int i, j, left, right, mid, x;
	for(i = 1; i < n; i++){
		x = a[i];
		left = 0;
		right = i - 1;
		while(left <= right){
			mid = (left + right) / 2;
			if(x < a[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}
		for(j = i - 1; j >= left; j--)
			a[j + 1] = a[j];
		a[left] = x;
	}
}

/* ----------------------------- Merge Sort ----------------------------- */
void merge(int* a, int* b, int na, int nb, int* c){ // gộp hai mảng có thứ tự thành 1 mảng có thứ tự
	int n = na + nb;
	int* temp = new int[n];
	int i, j, z = 0;
	i = j = 0;
	while(i < na && j < nb){
		temp[z++] = (a[i] < b[j])?a[i++]:b[j++];
	}
	while(j < nb){
		temp[z++] = b[j++];
	}
	while(i < na){
		temp[z++] = a[i++];
	}
	for(int x = 0; x < n; x++){
		c[x] = temp[x];
	}
	delete[] temp;
}

void MergeSort(int* a, int n){
	if(n == 1) return;
	int* a1 = a;
	int n1 = n/2;
	int n2 = n - n1;
	int* a2 = a + n1;
	MergeSort(a1, n1);
	MergeSort(a2, n2);
	merge(a1, a2, n1, n2, a);
}

/* ----------------------------- Heap Sort ----------------------------- */
void shift(int* a, int l, int r){ // hiệu chỉnh a[l] ... a[r] thành Heap
	int x, i, j;
	i = l;
	j = 2 * i + 1;
	x = a[i];
	while(j <= r){
		if(j < r)
			if(a[j] < a[j + 1])
				j++;
		if(a[j] < x) return;
		else{
			a[i] = a[j];
			i = j;
			j = 2 * i + 1;
			a[i] = x;
		}
	}
}

void createHeap(int* a, int n){
	int l;
	l = n / 2 - 1;
	while(l >= 0){
		shift(a, l, n - 1);
		l--;
	}
}

void HeapSort(int* a, int n){
	int r;
	createHeap(a, n); // xây dựng Heap
	r = n - 1;
	while(r > 0){
		swap(a[0], a[r]);
		r--;
		if(r > 0) shift(a, 0, r);
	}
}

/* ----------------------------- Radix Sort (2) ----------------------------- */
// tạo cấu trúc lưu số trong lô và số lượng số trong lô
struct lo{
	int* data;
	int size;
};

int findMax(int* a, int n){
	if(n == 0) return -1;
	int m = a[0];
	for(int i = 1; i < n; i++)
		if(m < a[i]) m = a[i];
	return m;
}

void initBucket(lo* bucket){
	for(int i = 0; i < BASE; i++){
		//free(bucket[i].data);
		bucket[i].data = NULL;
		bucket[i].size = 0;
	}
}

void RadixSort_2(int* a, int n){
	// find max value in the array a
	int m = findMax(a, n);
	int exp = 1;
	// create BASE bucket
	lo* bucket = (lo*)calloc(BASE, sizeof(lo));
	// loop until exp is bigger than the largest number
	int i, j;
	while(m / exp > 0){
		// khởi tạo các lô trống
		initBucket(bucket);
		for(i = 0; i < n; i++){
			int place = (a[i] / exp) % BASE;
			if(bucket[place].data != NULL)
				bucket[place].data = (int*)realloc(bucket[place].data, (bucket[place].size + 1) * sizeof(int));
			else
				bucket[place].data = (int*)calloc(1, sizeof(int));
			bucket[place].data[bucket[place].size++] = a[i];
		}
		int z = 0;
		for(i = 0; i < BASE; i++){
			for(j = 0; j < bucket[i].size; j++){
				int tmp = bucket[i].data[j];
				a[z++] = bucket[i].data[j];
			}
			free(bucket[i].data);
		}
		exp += 1;
	}
	
	free(bucket);
}

/* ----------------------------- Flash Sort ----------------------------- */
// tìm min max trong mảng, gán vào tham chiếu min max truyền vào
void findMinMax(int* a, int size, int &min, int &max){
	min = max = a[0];
	for(int i = 1; i < size; i++)
		if(min > a[i])
			min = a[i];
		else
			if(max < a[i]) max = a[i];
}

// phân lớp các phần tử trong mảng
void classify(int* a, int size, int* &L, int min, int max){
	L = new int[M];
	for(int i = 0; i < M; i++)
		L[i] = 0;

	size_t k;
	for(int i = 0; i < size; i++){
		int tmp = a[i];
		k = (M - 1) * ((a[i] - min) / (double)(max - min));
		L[k]++;
	}

	L[0] = L[0] - 1;
	for(k = 1; k < M; k++)
		L[k] += L[k - 1];

	int count = 1;
	int i = 0;
	k = M - 1;
	while(count <= M){
		while (i > L[k]){
			i++;
			k = (M - 1) * ((a[i] - min) / (double)(max - min));
		}
		int x = a[i];
		while(i <= L[k]){
			k = (M - 1) * ((x - min) / (double)(max - min));
			int y = a[L[k]];
			a[L[k]] = x;
			x = y;
			L[k]--;
			count++;
		}
	}
}

// dùng thuật toán insertion sort để sắp xếp mỗi phân lớp
void fsort(int* a, int* &L){
	for(int k = 1; k < M; k++){
		for(int i = L[k] - 1; i > L[k - 1]; i--)
			if(a[i] > a[i + 1]){
				int t = a[i];
				int j = i;
				while(t > a[j + 1]){
					a[j] = a[j + 1];
					j++;
				}
				a[j] = t;
			}
	}
}

// Thuật toán flashSort
void FlashSort(int* a, int n){
	int max, min;
	findMinMax(a, n, min, max);
	
	int* L = NULL;
	
	// phân lớp các phần tử
	classify(a, n, L, min, max);

	// sắp xếp từng phân lớp
	fsort(a, L);
	delete[] L;
}