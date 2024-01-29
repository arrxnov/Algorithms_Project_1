#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <chrono>

//****************************
//		FUNC POINTERS
//****************************

// The presence of function pointers allows us to change the 
// function being used to perform certain tasks while maintaining
// a smaller codebase for the quicksort function. Each function
// pointer points to one method whose impact we are 
// to measure. Their default values are given in the runSorts() function.

int* (*partition) (int* list, int* first, int* last);
int* (*pivot) (int* list, int* first, int* last);
void (*fillArray) (int* arr, int arrSize);

//****************************
//		    SWAP
//****************************

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
	int len = last - first;
	int half = len / 2;
	return first + half;
}

int* pivotMed3(int* arr, int* first, int* last)
{
	int x = *first;
	int y = *last;
	int z = arr[last - first];

	if ((x <= y && x >= z) || (x <= z && x >= y)) return first;
	else if ((y <= x && y >= x) || (y >= x && y <= z)) return last;
	else return &arr[last - first];
}

//*********************************
//		PARTITION FUNCTIONS
//*********************************

int* partitionTwoPointer(int* list, int* first, int* last)
{
	int* pivotPtr = pivot(list, first, last);
	int* lower = first;
	int* upper = last - 1;
	while (lower <= upper)
	{
		while (lower <= upper && *upper >= *pivotPtr) upper--;
		while (lower <= upper && *lower <= *pivotPtr) lower++;
		if (lower < upper) swap(list, lower, upper);
	}
	swap(list, lower, last);
	return lower;
}

int* partitionOnePointer(int* arr, int* first, int* last)
{
	int* pivotPtr = pivot(arr, first, last);
	int* lowPointer = first - 1;
	for (int* ptr = first; ptr < last; ptr++)
	{
		if (*ptr <= *pivotPtr)
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
	ofstream outFile;
	outFile.open("out.csv", ios_base::app);
	
	int* arr = new int[arrSize];
	
	fillArray(arr, arrSize);
	auto start = chrono::high_resolution_clock::now();
	quickSort(arr, arr, &arr[arrSize - 1]);
	auto finish = chrono::high_resolution_clock::now();
	auto quickSortNanoSeconds = chrono::duration_cast<chrono::nanoseconds>(finish - start);

	fillArray(arr, arrSize);
	start = chrono::high_resolution_clock::now();
	insertionSort(arr, arrSize);
	finish = chrono::high_resolution_clock::now();
	auto insertionSortNanoSeconds = chrono::duration_cast<chrono::nanoseconds>(finish - start);

	cout << arrSize << " elements " << endl;
	cout << "- Insertion Sort: " << insertionSortNanoSeconds.count() << " nanoseconds" << endl;
	cout << "- Quicksort: " << quickSortNanoSeconds.count() << " nanoseconds" << endl;

	int partmethod = (partition == &partitionTwoPointer) + 1;
	int fillmethod = (fillArray == &fillRand) ? 1 : (fillArray == &fillForward) + 2;
	int pivotmethod = (pivot == &pivotLast) ? 1 : (pivot == &pivotMedian) + 2;

	// ARRAYSIZE,QSTIME,ISTIME,PARTMETHOD,/*PIVMETHOD,*/FILLMETHOD
	outFile << arrSize << "," 
		<< quickSortNanoSeconds.count() << "," 
		<< insertionSortNanoSeconds.count() << ","
		<< partmethod << ","
		<< pivotmethod << ","
		<< fillmethod;
	outFile << endl;

	delete[] arr;
	outFile.close();
}

//*****************
//		MAIN
//*****************

int main(int argc, char** argv)
{
	using namespace std;
 
	partition = &partitionTwoPointer;
	pivot = &pivotLast;
	fillArray = &fillRand;
	for (int arrSize = 100; arrSize < 1000; arrSize++)
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

		//// Test all pivot functions
		//// Outside of these tests, we always use last := pivot
		//pivot = &pivotMedian;
		//done = false;
		//while (!done)
		//{
		//	runSorts(arrSize);
		//	if (pivot == &pivotMedian) pivot = &pivotMed3;
		//	else
		//	{
		//		pivot = &pivotLast;
		//		done = true;
		//	}
		//}

		// Test all data fill methods
		// Outside of these tests we always use randomized data
		fillArray = &fillReverse;
		done = false;
		while (!done)
		{
			runSorts(arrSize);
			if (fillArray == &fillReverse) fillArray = &fillForward;
			else
			{
				done = true;
				fillArray = &fillRand;
			}
		}
	}
	return 0;
}
