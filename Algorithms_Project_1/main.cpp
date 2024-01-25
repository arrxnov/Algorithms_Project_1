#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "main.h"

void insertionSort(int* list, int len)
{
	int temp;
	for (int i = 1; i < len; i++) // position in list to insert into
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

int main(int argc, char** argv)
{
	using namespace std;

	ofstream outputFile;
	outputFile.open("output.csv");

	return 0;
}
