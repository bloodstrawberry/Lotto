//당첨된 번호 분석용 cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>

#include "StatisticsManager.h"

using namespace std;
//statistic
extern int NumOfWinLotto;
extern LOTTO LottoWinningNumber[];

int START_NUMBER = 524;
int END_NUMBER;

int CONSECUTIVE_NUMBERS[7][50];
int JUMP_NUMBERS[7][50];

int primeNumber[] = { 0,
						0,1,1,0,1,0,1,0,0,0,
						1,0,1,0,0,0,1,0,1,0,
						0,0,1,0,0,0,0,0,1,0,
						1,0,0,0,0,0,1,0,0,0,
						1,0,1,0,0,0,1,0,0,0, };

unsigned long long seed = 5; // seed can be changed
unsigned int random(void)
{
	return ((unsigned int)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

void showPastLottoResult(LOTTO Lotto, int offset)
{
	int RANK[] = { 6, 6, 6, 5, 4, 3, 1 };

	for (int i = 1; i <= NumOfWinLotto;i++)
	{
		int cnt, bonus, rank;
		int table[50] = { 0 };

		cnt = bonus = 0;

		for (int k = 0; k < 6;k++) table[LottoWinningNumber[i].number[k]] = 1;
		for (int k = 0; k < 6;k++) cnt += table[Lotto.number[k]];

		for (int k = 0; k < 6;k++)
		{
			if (Lotto.number[k] == LottoWinningNumber[i].bonus)
			{
				bonus = 1;
				break;
			}
		}

		rank = RANK[cnt];
		if (rank == 3 && bonus == 1) rank = 2;

		if (rank <= offset)
		{
			printf("round %4d]   ", i);
			showLottoNumber(LottoWinningNumber[i]);
			printf("rank  %4d]   ", rank);
			for (int k = 0; k < 6;k++)
			{
				if (table[Lotto.number[k]]) printf("[%d] ", Lotto.number[k]);
				else printf("%d ", Lotto.number[k]);
			}
			printf("\n=================================\n");
		}

	}

}

void showAllPastLottoResult(int offset)
{
	int i;
	for (i = 1; i <= NumOfWinLotto;i++)
		showPastLottoResult(LottoWinningNumber[i], offset);
}

void showBinary_long(ull n)
{
	ull mask = 1ull << 63;
	for (int i = 0; i < 64;i++)
	{
		printf("%d ", (n & mask) == mask);
		mask >>= 1;
	}
	putchar('\n');
}

void findConsecutiveNumbers(int lottoNum)
{
	int i;
	LOTTO& Lotto = LottoWinningNumber[lottoNum];

	for (i = 0; i < 5;i++)
	{
		if (Lotto.number[i + 1] - Lotto.number[i] == 1)
		{
			//printf("%d] %d %d\n", lottoNum + 1, Lotto.number[i], Lotto.number[i + 1]);
			CONSECUTIVE_NUMBERS[2][Lotto.number[i]]++;
		}
	}
}

void findAllConsecutiveNumbers()
{
	// 2연속 번호만 check.
	int lottoNum;
	for (lottoNum = START_NUMBER; lottoNum <= NumOfWinLotto;lottoNum++)
	{
		findConsecutiveNumbers(lottoNum);
	}
}

void showConsecutiveNumbers()
{
	printf("\n================ show consecutivenumbers ==============\n");

	int index[50] = { 0 };
	int value[50] = { 0 };

	for (int i = 0; i < 50;i++) index[i] = i;
	for (int i = 0; i < 50;i++) value[i] = CONSECUTIVE_NUMBERS[2][i];

	for (int i = 0; i < 49;i++)
	{
		for (int k = i + 1; k < 50;k++)
		{
			if (value[i] > value[k]) continue;

			int tmp = value[i];
			value[i] = value[k];
			value[k] = tmp;

			tmp = index[i];
			index[i] = index[k];
			index[k] = tmp;
		}
	}

	for (int i = 0; i < 45;i++)
		if(index[i] <= 45) printf("%d, %d] : %d\n", index[i], index[i] + 1, value[i]);
}

void findJumpNumbers(int lottoNum)
{
	int i;
	LOTTO& Lotto = LottoWinningNumber[lottoNum];

	for (i = 0; i < 5;i++)
	{
		if (Lotto.number[i + 1] - Lotto.number[i] == 2)
		{
			//printf("%d] %d %d\n", lottoNum + 1, Lotto.number[i], Lotto.number[i + 1]);
			JUMP_NUMBERS[2][Lotto.number[i]]++;
		}
	}
}

void findAllJumpNumbers()
{
	int lottoNum;
	for (lottoNum = START_NUMBER; lottoNum <= NumOfWinLotto;lottoNum++)
	{
		findJumpNumbers(lottoNum);
	}
}

void showJumpNumbers()
{
	//for (int i = 1; i <= 44;i++) 
	//if(consecutive_numbers[2][i]) printf("%d, %d] : %d\n", i, i+1, consecutive_numbers[2][i]);
	printf("\n================ show jump number ==============\n");
	int index[50] = { 0 };
	int value[50] = { 0 };

	for (int i = 0; i < 50;i++) index[i] = i;
	for (int i = 0; i < 50;i++) value[i] = JUMP_NUMBERS[2][i];

	for (int i = 0; i < 49;i++)
	{
		for (int k = i + 1; k < 50;k++)
		{
			if (value[i] > value[k]) continue;

			int tmp = value[i];
			value[i] = value[k];
			value[k] = tmp;

			tmp = index[i];
			index[i] = index[k];
			index[k] = tmp;
		}
	}

	for (int i = 0; i < 45;i++)
		printf("%d, %d] : %d\n", index[i], index[i] + 2, value[i]);
}

bool isPrime(int num)
{
	return primeNumber[num];
}