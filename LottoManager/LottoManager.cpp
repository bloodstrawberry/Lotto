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

ull makeBitNumber(LOTTO Lotto)
{
	return (1ull << Lotto.number[0]) | (1ull << Lotto.number[1]) | (1ull << Lotto.number[2]) | (1ull << Lotto.number[3]) | (1ull << Lotto.number[4]) | (1ull << Lotto.number[5]);
}

int makeSum(LOTTO Lotto)
{
	return Lotto.number[0] + Lotto.number[1] + Lotto.number[2] + Lotto.number[3] + Lotto.number[4] + Lotto.number[5];
}

void makeStatisticsInfo(LOTTO& Lotto)
{
	Lotto.key = makeKey(Lotto);
	Lotto.bitNumber = makeBitNumber(Lotto);
	Lotto.sum = makeSum(Lotto);
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
							makeKey(AllLottoNumber[cnt]);
							cnt++;
						}


	//for (int i = 0; i < NUM_OF_ALLCASE;i++) showLottoNumber(AllLottoNumber[i]);
}


void deleteNumber()
{
	//총 개수에서 몇개가 빠지는지 세기 [삭제 수 / 전체 수에서 삭제 수]
	//delete flag로 관리 후 마지막에 한꺼번에 삭제.

	//연속된 2 ~ 6자리 수 삭제
	//등차수열 삭제 차수 2 ~ 8 삭제
	//짝수가 6개인 경우
	//짝수가 5개인 경우
	//짝수가 4개인 경우
	//짝수가 3개인 경우
	//짝수가 2개인 경우
	//짝수가 1개인 경우
	//짝수가 0개인 경우
	//이미 로또 번호인 경우
	//SuckNumber 삭제
	//모두 소수인 경우 삭제

	//
	
}

bool checkConsecutive6(LOTTO Lotto)
{
	if (Lotto.number[5] - Lotto.number[0] == 5) return 1;
	return 0;
}

bool checkConsecutive5(LOTTO Lotto)
{
	if (Lotto.number[4] - Lotto.number[0] == 4
		|| Lotto.number[5] - Lotto.number[1] == 4) return 1;
	return 0;
}

bool checkConsecutive4(LOTTO Lotto)
{
	if (Lotto.number[3] - Lotto.number[0] == 3
		|| Lotto.number[4] - Lotto.number[1] == 3
		|| Lotto.number[5] - Lotto.number[2] == 3) return 1;
	return 0;
}

bool checkConsecutive3(LOTTO Lotto)
{
	if (Lotto.number[2] - Lotto.number[0] == 2
		|| Lotto.number[3] - Lotto.number[1] == 2
		|| Lotto.number[4] - Lotto.number[2] == 2
		|| Lotto.number[5] - Lotto.number[3] == 2) return 1;
	return 0;
}

bool checkConsecutive2(LOTTO Lotto)
{
	if (Lotto.number[1] - Lotto.number[0] == 1
		|| Lotto.number[2] - Lotto.number[1] == 1
		|| Lotto.number[3] - Lotto.number[2] == 1
		|| Lotto.number[4] - Lotto.number[3] == 1
		|| Lotto.number[5] - Lotto.number[4] == 1) return 1;
	return 0;
}

bool checkDiff(LOTTO Lotto, int diff)
{
	for (int i = 1; i < 6;i++)
		if (Lotto.number[i] - Lotto.number[i - 1] != diff) return false;

	return true;
}

bool checkDifferentialSequence(LOTTO Lotto)
{
	for (int diff = 2; diff <= 8;diff++)
	{
		if (checkDiff(Lotto, diff)) return true;
	}

	return false;
}

int mustNumber[50];
int mustSize;
void setMustNumber(int* number, int size)
{
	mustSize = size;
	for (int i = 0; i < size;i++)
		mustNumber[number[i]] = 1;
}

bool isMustNumber(LOTTO Lotto)
{
	int cnt = 0;
	for (int i = 0; i < 6;i++)
		if (mustNumber[Lotto.number[i]]) cnt++;

	if (cnt == mustSize) return true;
	return false;
}

int wrongNumber[50];
int wrongSize;
void setWrongNumber(int* number, int size)
{
	wrongSize = size;
	for (int i = 0; i < size;i++)
		wrongNumber[number[i]] = 1;
}

bool isWrongNumber(LOTTO Lotto)
{
	int cnt = 0;
	for (int i = 0; i < 6;i++)
		if (wrongNumber[Lotto.number[i]]) return true;

	return false;
}

//void printMap()
//{
//	map<ull, bool>::iterator iter;
//	for (iter = m.begin(); iter != m.end(); ++iter)
//		cout << "(" << (*iter).first << "," << (*iter).second << ")" << " ";
//	cout << endl;
//}

