#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "main.h"

void insertionSort(int* list, int len)
{
	int temp;
	for (int i = 0; i < len; i++) // position in list to insert into
	{
		temp = list[i];
		int j = i;
		while (j > 0)
		{
			if (temp <= list[j])
			{
				list[j + 1] = list[j];
			}
			else
			{
				list[j + 1] = temp;
			}
			j--;
		}
	}
}

int main(int argc, char** argv)
{
	using namespace std;

	ofstream outputFile;
	outputFile.open("output.csv");
}
