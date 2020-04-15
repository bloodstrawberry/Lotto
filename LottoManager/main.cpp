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

extern unsigned long long seed;

LOTTO testLotto;

int main()
{
	srand(time(NULL)); 
	seed = rand();

	/* ---------------------- Statistics ---------------------- */

	getLottoWinningNumber(); //��÷ ��ȣ 
	getMySuckNumber(); //������ ���� ��ȣ

	//���ӵ� 2�ڸ� ��ȣ
	findAllConsecutiveNumbers();
	showConsecutiveNumbers();

	//1ĭ ���� ��ȣ
	findAllJumpNumbers();
	showJumpNumbers();

	/* -------------------------------------------------------- */

	/* -------------------- Pick up Number -------------------- */

	getAllNumber();
	//delete
	//shuffle...?

	// pick up ---------------------------------------------------
	int mNumber[] = { 42,43 };
	int msize = sizeof(mNumber) / sizeof(int);
	setMustNumber(mNumber, msize);

	int wNumber[] = { 1,2,3,4,5,10,11,9,16, 24, 8 };
	int wsize = sizeof(wNumber) / sizeof(int);
	setWrongNumber(wNumber, wsize);

	//pick
	//pick up and statistics

	/* -------------------------------------------------------- */
	return 0;
	//----------------------========================================

	//8 19 20 27 42 45
	testLotto.number[0] = 6;
	testLotto.number[1] = 12;
	testLotto.number[2] = 17;
	testLotto.number[3] = 19;
	testLotto.number[4] = 34;
	testLotto.number[5] = 37;
	testLotto.key = makeKey(testLotto);

	
	//MAP���� check realnum sucknum �����ϱ�.

	printf("NumOfWinLotto %d\n", NumOfWinLotto);
	printf("NumOfSuckLotto %d\n", NumOfSuckLotto);

	printf("%d\n", isLottoWinningNumber(testLotto));
	printf("%d\n", isMySuckNumber(testLotto));

	showPastLottoResult(testLotto, 3);

	return 0;
}