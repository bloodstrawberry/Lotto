#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>
#include <fstream>

#include "FileManager.h"
#include "StatisticsManager.h"
#include "LottoManager.h"
#include "PensionManager.h"

using namespace std;

extern int START_NUM;
extern int END_NUM;

extern int NumOfWinLotto;
extern LOTTO LottoWinningNumber[];
extern map<ull, bool> MapLottoWinningNumber;

extern int NumOfSuckLotto;
extern LOTTO MySuckNumber[];
extern map<ull, bool> MapMySuckNumber;

extern int NumOfHotNumber;
extern int HotNumber[50];
 
extern int NumOfColdNumber;
extern int ColdNumber[50];
 

extern int NumOfOneNumber;
extern int OneNumber[50];

extern int NumOfWinPension;
extern PENSION PensionWinningNumber[10000];
extern int NumOfSuckPension;
extern int MySuckPensionNumber[1000000];



void getPensionWinningNumber()
{
	FILE *fp = fopen(PENSION_WINNING_NUMBER, "r");
	if (fp == NULL)
	{
		printf("Wrong Input : %s\n", PENSION_WINNING_NUMBER);
		exit(1);
	}

	int n1, n2, n3, n4, n5, n6, bs;

	for(int i = 1; i<=461;i++)
	{
		PensionWinningNumber[i].index = i;
		fscanf(fp, "%d", &PensionWinningNumber[i].date);
		fscanf(fp, "%d", &PensionWinningNumber[i].pClass[0]);
		fscanf(fp, "%d", &PensionWinningNumber[i].pClass[1]);
		
		for (int k = 0; k < 13;k++)
			fscanf(fp, "%d", &PensionWinningNumber[i].numbers[k]);
	}

	NumOfWinPension = 461;
	while (fscanf(fp, "%d", &n1) != EOF)
	{
		NumOfWinPension++;
		PensionWinningNumber[NumOfWinPension].index = NumOfWinPension;

		PensionWinningNumber[NumOfWinPension].date = n1;
		fscanf(fp, "%d", &PensionWinningNumber[NumOfWinPension].pClass[0]);
		fscanf(fp, "%d", &PensionWinningNumber[NumOfWinPension].numbers[0]);
		fscanf(fp, "%d", &PensionWinningNumber[NumOfWinPension].bonus);

	}

	for (int i = 1; i <= NumOfWinPension;i++)
	{
		if (isPensionWinningNumber(PensionWinningNumber[i], 0))
			printf("PensionNumber is Already Pension Number!!! index %d\n", i);
	}

	putchar('\n');

	fclose(fp);
}

void getMyPensionSuckNumber()
{
	FILE *fp = fopen(MY_SUCK_PENSION_NUMBER, "r");
	if (fp == NULL)
	{
		printf("Wrong Input : %s\n", MY_SUCK_PENSION_NUMBER);
		exit(1);
	}

	int n1;
	while (fscanf(fp, "%d", &n1) != EOF)
	{
		NumOfSuckPension++;
		if (MySuckPensionNumber[n1])
		{
			printf("this is already Suck Pension Number!!! %d\n", n1);
			exit(1);
		}
		
		if (isPensionWinningNumber(n1, 1)) printf("MySuckNumber is Pension Number!!! %d, prize %d\n", n1, 1);
		if (isPensionWinningNumber(n1, 2)) printf("MySuckNumber is Pension Number!!! %d, prize %d\n", n1, 2);
		if (isPensionWinningNumber(n1, 3)) printf("MySuckNumber is Pension Number!!! %d, prize %d\n", n1, 3);

		MySuckPensionNumber[n1] = 1;
	}

	fclose(fp);


	ofstream fout;
	fout.open("MySuckPensionNumber.txt");
	char buff[20];
	for (int i = 1; i < 1000000;i++)
	{
		if (MySuckPensionNumber[i])
		{
			sprintf(buff, "%6d\n", i);
			fout << buff;
		}
	}

	putchar('\n');

	fout.close();
}


void getLottoWinningNumber()
{
	FILE *fp = fopen(LOTTO_WINNING_NUMBER, "r");
	if (fp == NULL)
	{
		printf("Wrong Input : %s\n", LOTTO_WINNING_NUMBER);
		exit(1);
	}

	int n1, n2, n3, n4, n5, n6, bs;
	while (fscanf(fp, "%d", &n1) != EOF)
	{
		NumOfWinLotto++;

		fscanf(fp, "%d", &n2);fscanf(fp, "%d", &n3);fscanf(fp, "%d", &n4);
		fscanf(fp, "%d", &n5);fscanf(fp, "%d", &n6);fscanf(fp, "%d", &bs);

		LottoWinningNumber[NumOfWinLotto].index     = NumOfWinLotto;
		LottoWinningNumber[NumOfWinLotto].number[0] = n1;
		LottoWinningNumber[NumOfWinLotto].number[1] = n2;
		LottoWinningNumber[NumOfWinLotto].number[2] = n3;
		LottoWinningNumber[NumOfWinLotto].number[3] = n4;
		LottoWinningNumber[NumOfWinLotto].number[4] = n5;
		LottoWinningNumber[NumOfWinLotto].number[5] = n6;
		LottoWinningNumber[NumOfWinLotto].bonus     = bs;

		makeStatisticsInfo(LottoWinningNumber[NumOfWinLotto]);
		MapLottoWinningNumber[LottoWinningNumber[NumOfWinLotto].key] = true;
		//printf("%lld\n", LottoWinningNumber[NumOfWinLotto].key);
		//showLottoNumber(LottoWinningNumber[NumOfWinLotto]);
		//showBinary_long(LottoWinningNumber[NumOfWinLotto].bitNumber);
	}

	fclose(fp);
}

void getMySuckNumber()
{
	FILE *fp = fopen(MY_SUCK_NUMBER, "r");
	if (fp == NULL)
	{
		printf("Wrong Input : %s\n", MY_SUCK_NUMBER);
		exit(1);
	}

	int n1, n2, n3, n4, n5, n6;
	while (fscanf(fp, "%d", &n1) != EOF)
	{
		NumOfSuckLotto++;

		fscanf(fp, "%d", &n2);fscanf(fp, "%d", &n3);fscanf(fp, "%d", &n4);
		fscanf(fp, "%d", &n5);fscanf(fp, "%d", &n6);

		MySuckNumber[NumOfSuckLotto].index = NumOfSuckLotto;
		MySuckNumber[NumOfSuckLotto].number[0] = n1;
		MySuckNumber[NumOfSuckLotto].number[1] = n2;
		MySuckNumber[NumOfSuckLotto].number[2] = n3;
		MySuckNumber[NumOfSuckLotto].number[3] = n4;
		MySuckNumber[NumOfSuckLotto].number[4] = n5;
		MySuckNumber[NumOfSuckLotto].number[5] = n6;
		makeStatisticsInfo(MySuckNumber[NumOfSuckLotto]);

		//printf("%lld\n", MySuckNumber[NumOfSuckLotto].key);
		//showLottoNumber(MySuckNumber[NumOfSuckLotto]);
		
		if (!(n1 < n2 && n2 < n3 && n3 < n4 && n4 < n5 && n5 < n6))
		{
			printf("Wrong Suck Number !! %d %d %d %d %d %d\n", n1, n2, n3, n4, n5, n6);
			exit(1);
		}

		if (isMySuckNumber(MySuckNumber[NumOfSuckLotto]))
		{
			printf("this is already Suck Number!!!\n");
			showLottoNumber(MySuckNumber[NumOfSuckLotto]);
			exit(1);
		}

		if (isLottoWinningNumber(MySuckNumber[NumOfSuckLotto]))
		{
			printf("MySuckNumber is LottoNumber!!!\n");
			showLottoNumber(MySuckNumber[NumOfSuckLotto]);
			exit(1);
		}

		MapMySuckNumber[MySuckNumber[NumOfSuckLotto].key] = true;
	}

	//for (int i = 1; i <= NumOfSuckLotto;i++)
		//showLottoNumber(MySuckNumber[i]);

	fclose(fp);




}

void getNumber(const char* fileName, int Numbers[], int count)
{
	FILE *fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		printf("Wrong Input : %s\n", fileName);
		exit(1);
	}

	count = 0;


	int n1;
	while (fscanf(fp, "%d", &n1) != EOF)
	{
		count++;
		Numbers[n1] = 1;
	}

	fclose(fp);
}

void getNumbers()
{
	getNumber("HotNumber.txt", HotNumber, NumOfHotNumber);
	getNumber("ColdNumber.txt", ColdNumber, NumOfColdNumber);
	getNumber("OneNumber.txt", OneNumber, NumOfOneNumber);

	printf("Hot :\n");
	for (int i = 1; i <= 45; i++)
		if (HotNumber[i]) printf("%d ", i);
	putchar('\n');

	printf("Cold :\n");
	for (int i = 1; i <= 45; i++)
		if (ColdNumber[i]) printf("%d ", i);
	putchar('\n');

	printf("One :\n");
	for (int i = 1; i <= 45; i++)
		if (OneNumber[i]) printf("%d ", i);
	putchar('\n');

}
