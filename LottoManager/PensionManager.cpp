#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

#include "PensionManager.h"
#include "StatisticsManager.h"

using namespace std;


int NumOfWinPension;
PENSION PensionWinningNumber[10000];
int NumOfSuckPension;
int MySuckPensionNumber[1000000];

int sortPension[1000000];


void showPensionNumber(PENSION pension)
{
	if (pension.index > PENSION520)
	{
		printf("%d %d %d %d\n", pension.index, pension.date, pension.numbers[0], pension.bonus);

		return;
	}

	printf("%d %d %d ", pension.date, pension.pClass[0], pension.pClass[1]);
	for (int k = 0; k < 13;k++)
		printf("%d ", pension.numbers[k]);
	putchar('\n');

}

bool isPensionWinningNumber(int number, int rank)
{
	int st, ed;
	if (rank == 1) st = 0, ed = 1;
	else if (rank == 2) st = 2, ed = 5;
	else if (rank == 3) st = 6, ed = 7;
	else st = 0, ed = 6;

	for (int i = 1; i <= NumOfWinPension;i++)
	{
		PENSION& p = PensionWinningNumber[i];

		for (int k = st; k < ed;k++)
			if (number == p.numbers[k]) return true;
	}

	return false;
}

bool isPensionWinningNumber(PENSION p, int rank)
{
	int st, ed;
	
	for (int i = 1; i <= NumOfWinPension;i++)
	{
		if (i == p.index) continue;

		PENSION& p2 = PensionWinningNumber[i];

		for (int k = 0; k < 7;k++)
		{
			for (int j = 0; j < 7;j++)
				if (p.numbers[k] == p2.numbers[j] && (p.numbers[k] + p2.numbers[j] != 0)) return true;

			if ((p.bonus != 0) && p.bonus == p2.numbers[k]) return true;
		}
	}

	return false;
}


void pensionSort()
{
	ofstream fout;
	fout.open("PensionSort.txt");
	char buff[20];
	
	for (int i = 1; i <= NumOfWinPension;i++)
	{
		PENSION& p = PensionWinningNumber[i];

		for (int k = 0; k < 7;k++)
		{
			if (p.numbers[k] == 0) continue;
			sortPension[p.numbers[k]]++;
			if (sortPension[p.numbers[k]] >= 2) printf("this Pension Number is duplicated! [%d] [%d]\n", p.numbers[k], sortPension[p.numbers[k]]);
		}
		if (p.bonus == 0) continue;
		sortPension[p.bonus]++;
		if (sortPension[p.bonus] >= 2) printf("this Pension Number is duplicated! [%d] [%d]\n", p.bonus, sortPension[p.bonus]);

	}
	
	
	for (int i = 1; i < 1000000;i++)
	{
		if (sortPension[i])
		{
			sprintf(buff, "%6d %d\n", i, sortPension[i]);
			fout << buff;
		}
	}

	putchar('\n');
	fout.close();
}