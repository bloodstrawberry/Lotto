#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>

#include "LottoManager.h"
#include "StatisticsManager.h"

using namespace std;

int NumOfWinLotto;
LOTTO LottoWinningNumber[10000];
map<ull, bool> MapLottoWinningNumber;

int NumOfSuckLotto;
LOTTO MySuckNumber[10000];
map<ull, bool> MapMySuckNumber;

LOTTO AllLottoNumber[NUM_OF_ALLCASE + 10];

void showLottoNumber(int index)
{
	printf("%4d] ", index + 1);
	for (int k = 0; k < 7;k++)
		printf("%2d ", LottoWinningNumber[index].number[k]);
	putchar('\n');
}

void showLottoNumber(LOTTO Lotto)
{
	for (int k = 0; k < 7;k++)
		printf("%2d ", Lotto.number[k]);
	putchar('\n');
}

bool isLottoWinningNumber(LOTTO Lotto)
{
	return MapLottoWinningNumber.count(Lotto.key);
}

bool isMySuckNumber(LOTTO Lotto)
{
	return MapMySuckNumber.count(Lotto.key);
}



ull makeKey(LOTTO Lotto)
{
	return Lotto.number[0] * 10000000000ull + Lotto.number[1] * 100000000ull + Lotto.number[2] * 1000000ull 
		+ Lotto.number[3] * 10000ull + Lotto.number[4] * 100ull + Lotto.number[5];
}

void getAllNumber()
{
	int a, b, c, d, e, f;

	int cnt = 0;
	for (a = 1; a <= 40;a++)
		for (b = a + 1; b <= 41;b++)
			for (c = b + 1; c <= 42;c++)
				for (d = c + 1; d <= 43;d++)
					for (e = d + 1; e <= 44;e++)
						for (f = e + 1; f <= 45;f++)
						{
							AllLottoNumber[cnt].number[0] = a;
							AllLottoNumber[cnt].number[1] = b;
							AllLottoNumber[cnt].number[2] = c;
							AllLottoNumber[cnt].number[3] = d;
							AllLottoNumber[cnt].number[4] = e;
							AllLottoNumber[cnt].number[5] = f;
							cnt++;
						}


	//for (int i = 0; i < NUM_OF_ALLCASE;i++) showLottoNumber(AllLottoNumber[i]);
}

//void printMap()
//{
//	map<ull, bool>::iterator iter;
//	for (iter = m.begin(); iter != m.end(); ++iter)
//		cout << "(" << (*iter).first << "," << (*iter).second << ")" << " ";
//	cout << endl;
//}