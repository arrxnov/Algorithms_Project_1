#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <chrono>

void swap(int* list, int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int* partition(int* list, int* first, int* last)
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

void quickSort(int* list, int *first, int *last)
{
	if (first < last)
	{
		int* mid = partition(list, first, last);
		quickSort(list, first, mid - 1);
		quickSort(list, mid + 1, last);
	}
}

int main(int argc, char** argv)
{
	using namespace std;

	ofstream outputFile;
	outputFile.open("output.csv");
	srand(time(0));
	int arr[100];
	for (int i = 0; i < 100; i++) arr[i] = rand();
	for (int i = 0; i < 100; i++) cout << arr[i] << endl;

	auto start = chrono::high_resolution_clock::now();

	quickSort(arr, arr, &arr[99]);
	// Sort array
	cout << "-----BREAK-----" << endl;
	auto finish = chrono::high_resolution_clock::now();

	for (int i = 0; i < 100; i++) cout << arr[i] << endl;

	return 0;
}
