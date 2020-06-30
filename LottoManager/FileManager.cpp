#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>

#include "FileManager.h"
#include "StatisticsManager.h"
#include "LottoManager.h"

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
