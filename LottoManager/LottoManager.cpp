#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LottoManager.h"

int NumOfWinLotto;
LOTTO LottoWinningNumber[10000];

int NumOfSuckLotto;
LOTTO MySuckNumber[10000];

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

bool isMySuckNumber(LOTTO Lotto)
{
	for (int i = 0; i < NumOfSuckLotto;i++)
	{
		int check;
		check =
			(Lotto.number[0] == MySuckNumber[i].number[0])
			&& (Lotto.number[1] == MySuckNumber[i].number[1])
			&& (Lotto.number[2] == MySuckNumber[i].number[2])
			&& (Lotto.number[3] == MySuckNumber[i].number[3])
			&& (Lotto.number[4] == MySuckNumber[i].number[4])
			&& (Lotto.number[5] == MySuckNumber[i].number[5]);

		if (check) return true;
	}

	return false;
}