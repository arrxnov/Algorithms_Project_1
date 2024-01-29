#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <chrono>

//**************************
//		FUNC POINTERS
//**************************

int* (*partition) (int* list, int* first, int* last);
int* (*pivot) (int* list, int* first, int* last);
void (*fillArray) (int* arr, int arrSize);

void swap(int* list, int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

//****************************
//		FILL FUNCTIONS
//****************************

void fillRand(int* arr, int arrSize)
{
	srand(time(0));
	for (int i = 0; i < arrSize; i++) arr[i] = rand();
}

void fillReverse(int* arr, int arrSize)
{
	for (int i = 0; i < arrSize; i++) arr[i] = arrSize - i;
}

void fillForward(int* arr, int arrSize)
{
	for (int i = 0; i < arrSize; i++) arr[i] = i;
}

//****************************
//		PIVOT FUNCTIONS 
//****************************

int* pivotLast(int* arr, int* first, int* last) { return last; }

int* pivotMedian(int* arr, int* first, int* last)
{
	// Finish
}

int* pivotMed3(int* arr, int* first, int* last)
{
	// Finish
}

//*********************************
//		PARTITION FUNCTIONS
//*********************************

int* partitionTwoPointer(int* list, int* first, int* last)
{
	int* pivot = last;
	int* lower = first;
	int* upper = last - 1;
	while (lower <= upper)
	{
		while (lower <= upper && *upper >= *pivot) upper--;
		while (lower <= upper && *lower <= *pivot) lower++;
		if (lower < upper) swap(list, lower, upper);
	}
	swap(list, lower, last);
	return lower;
}

int* partitionOnePointer(int* arr, int* first, int* last)
{
	int* pivot = last;
	int* lowPointer = first - 1;
	for (int* ptr = first; ptr < last; ptr++)
	{
		if (*ptr <= *pivot)
		{
			lowPointer++;
			swap(arr, lowPointer, ptr);
		}
	}
	lowPointer++;
	swap(arr, lowPointer, last);
	return lowPointer;
}

//*****************************
//		SORT FUNCTIONS
//*****************************

void quickSort(int* list, int *first, int *last)
{
	if (first < last)
	{
		int* mid = partition(list, first, last);
		quickSort(list, first, mid - 1);
		quickSort(list, mid + 1, last);
	}
}

void insertionSort(int* list, int len)
{
	int key;
	for (int j = 1; j < len; j++)
	{
		key = list[j];
		int i = j - 1;
		while (i >= 0 && list[i] > key)
		{
			list[i + 1] = list[i];
			i--;
		}
		list[i + 1] = key;
	}
}

void runSorts(int arrSize)
{
	using namespace std;
	
	int* arr = new int[arrSize];

	fillArray(arr, arrSize);

	auto start = chrono::system_clock::now();
	quickSort(arr, arr, &arr[arrSize - 1]);
	auto finish = chrono::system_clock::now();
	auto quickSortNanoSeconds = chrono::duration_cast<chrono::nanoseconds>(finish - start);

	auto start = chrono::system_clock::now();
	insertionSort(arr, arrSize);
	auto finish = chrono::system_clock::now();
	auto insertionSortNanoSeconds = chrono::duration_cast<chrono::nanoseconds>(finish - start);

	cout << "[+] Insertion Sort: " << insertionSortNanoSeconds.count() << " nanoseconds" << endl;
	cout << "[+] Quicksort: " << quickSortNanoSeconds.count() << " nanoseconds" << endl;

	delete[] arr;
}

//*****************
//		MAIN
//*****************

int main(int argc, char** argv)
{
	using namespace std;
 
	partition = &partitionTwoPointer;
	for (int arrSize = 100; arrSize < 10000; arrSize++)
	{
		// Test all partition functions
		// Outside of these tests, we always use two-pointer
		bool done = false;
		while (!done)
		{
			runSorts(arrSize);
			if (partition == &partitionTwoPointer) partition = &partitionOnePointer;
			else
			{
				done = true;
				partition = &partitionTwoPointer; 
			}
		}

		// Test all pivot functions
		// Outside of these tests, we always use last := pivot
		done = false;
		while (!done)
		{
			runSorts(arrSize);
			if (pivot == &pivotLast) pivot = &pivotMedian;
			else if (pivot == &pivotMedian) pivot = &pivotMed3;
			else
			{
				pivot = &pivotLast;
				done = true;
			}
		}

		// Test all data fill methods
		// Outside of these tests we always use randomized data
		done = false;
		while (!done)
		{
			runSorts(arrSize);
			if (fillArray == &fillRand) fillArray = &fillReverse;
			else if (fillArray == &fillReverse) fillArray = &fillForward;
			else
			{
				done = true;
				fillArray = &fillRand;
			}
		}
	}

	return 0;
}
