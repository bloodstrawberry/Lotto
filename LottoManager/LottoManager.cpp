#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>

#include "LottoManager.h"

using namespace std;

int NumOfWinLotto;
LOTTO LottoWinningNumber[10000];
map<ull, bool> MapLottoWinningNumber;

int NumOfSuckLotto;
LOTTO MySuckNumber[10000];
map<ull, bool> MapMySuckNumber;

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



//void printMap()
//{
//	map<ull, bool>::iterator iter;
//	for (iter = m.begin(); iter != m.end(); ++iter)
//		cout << "(" << (*iter).first << "," << (*iter).second << ")" << " ";
//	cout << endl;
//}