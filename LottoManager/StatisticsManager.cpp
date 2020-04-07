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

int START_NUM;
int END_NUM;

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


