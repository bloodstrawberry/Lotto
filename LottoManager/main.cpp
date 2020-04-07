#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>

#include "LottoManager.h"
#include "FileManager.h"
#include "StatisticsManager.h"

using namespace std;

extern int NumOfWinLotto;
extern int NumOfSuckLotto;

//40 41 42 43 44 45

LOTTO testLotto;

int main()
{
	getAllNumber();
	return 0;

	//8 19 20 27 42 45
	testLotto.number[0] = 6;
	testLotto.number[1] = 12;
	testLotto.number[2] = 17;
	testLotto.number[3] = 19;
	testLotto.number[4] = 34;
	testLotto.number[5] = 37;
	testLotto.key = makeKey(testLotto);

	getLottoWinningNumber(); //��÷ ��ȣ 
	getMySuckNumber(); //������ ���� ��ȣ

	//MAP���� check realnum sucknum �����ϱ�.

	printf("NumOfWinLotto %d\n", NumOfWinLotto);
	printf("NumOfSuckLotto %d\n", NumOfSuckLotto);

	printf("%d\n", isLottoWinningNumber(testLotto));
	printf("%d\n", isMySuckNumber(testLotto));

	showPastLottoResult(testLotto, 3);

	return 0;
}