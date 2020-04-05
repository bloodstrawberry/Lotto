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
		LottoWinningNumber[NumOfWinLotto].key = makeKey(LottoWinningNumber[NumOfWinLotto]);
		MapLottoWinningNumber[LottoWinningNumber[NumOfWinLotto].key] = true;
		//printf("%lld\n", LottoWinningNumber[NumOfWinLotto].key);
		//showLottoNumber(LottoWinningNumber[NumOfWinLotto]);
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
		MySuckNumber[NumOfSuckLotto].key = makeKey(MySuckNumber[NumOfSuckLotto]);
		

		//printf("%lld\n", MySuckNumber[NumOfSuckLotto].key);
		//showLottoNumber(MySuckNumber[NumOfSuckLotto]);
		
		if (isMySuckNumber(MySuckNumber[NumOfSuckLotto]))
		{
			printf("this is already Suck Number!!!\n");
			showLottoNumber(MySuckNumber[NumOfSuckLotto]);
			exit(1);
		}

		MapMySuckNumber[MySuckNumber[NumOfSuckLotto].key] = true;
	}

	fclose(fp);
}

