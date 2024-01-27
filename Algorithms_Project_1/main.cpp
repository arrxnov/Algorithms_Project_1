#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <chrono>

void swap(int* list, int x, int y)
{
	// Had a harder time following pcode here.
}

int partition(int* list, int first, int last)
{
	int pivot = list[last];
	int lower = first;
	int upper = last - 1;
	while (lower <= upper)
	{
		while (lower <= upper && list[upper] >= pivot) upper--;
		while (lower <= upper && list[lower] <= pivot) lower++;
		if (lower < upper) swap(list, lower, upper);
	}
	swap(list, lower, last);
	return lower;
}

void insertionSort(int* list, int len)
{
	int temp;
	for (int i = 1; i < len; i++)
	{
		temp = list[i];
		int j = i - 1;
		while (j and list[j] > temp)
		{
			list[j + 1] = list[j];
			j--;
		}
	}
}

void quickSort(int* list, int first, int last)
{
	if (first < last)
	{
		int mid = /*partition(list, first, last)*/0;
		quickSort(list, first, mid - 1);
		quickSort(list, mid + 1, last);
	}
}

int main(int argc, char** argv)
{
	using namespace std;

	ofstream outputFile;
	outputFile.open("output.csv");

	auto start = std::chrono::high_resolution_clock::now();

	// Algorithm operation

	auto finish = std::chrono::high_resolution_clock::now();

	return 0;
}
