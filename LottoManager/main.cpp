#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#include "LottoManager.h"
#include "FileManager.h"
#include "StatisticsManager.h"


using namespace std;

extern int NumOfWinLotto;
extern int NumOfSuckLotto;
extern LOTTO LottoWinningNumber[];
extern unsigned long long seed;
extern int SHUFFLE;
LOTTO testLotto;



int main()
{
	srand(time(NULL)); 
	seed = rand();

	/* ---------------------- Input ---------------------- */
	
	getLottoWinningNumber(); //당첨 번호 
	getMySuckNumber(); //실패한 나의 번호
	getNumbers(); //hot, cold, except

	/* ---------------------- Statistics ---------------------- */

	setStatistics(817, 917);
	statistics();

	/* ---------------------- PickUp ---------------------- */
	int mNumber[] = { 23 };
	int msize = sizeof(mNumber) / sizeof(int);
	setMustNumber(mNumber, msize);

	int wNumber[] = { 1,2,3,4,7,16,21,22,26,27,34,39};
	int wsize = sizeof(wNumber) / sizeof(int);
	setWrongNumber(wNumber, wsize);

	setPrimeNumber(1, 3);
	setMustEvenNumber(3, 4);
	setPastRank2(0, 0);
	setPastRank3(0, 0);
	setPastRank4(1, 1);

	setHotNumber(1, 4);
	setColdNumber(1, 4);
	setOneNumber(2,2);

	setACNumber(8, 8);



	SHUFFLE = 1;
	getAllNumber(); //Fileter. -> 이월된 번호 통계...해서...음....


	


	return 0;














	showAllPastLottoResult(4);
	return 0;

	//연속된 2자리 번호
	findAllConsecutiveNumbers();
	showConsecutiveNumbers();

	//1칸 점프 번호
	findAllJumpNumbers();
	showJumpNumbers();

	/* -------------------------------------------------------- */

	/* -------------------- Pick up Number -------------------- */

	getAllNumber();
	//delete
	//shuffle...?


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

	
	//MAP으로 check realnum sucknum 관리하기.

	printf("NumOfWinLotto %d\n", NumOfWinLotto);
	printf("NumOfSuckLotto %d\n", NumOfSuckLotto);

	printf("%d\n", isLottoWinningNumber(testLotto));
	printf("%d\n", isMySuckNumber(testLotto));

	showPastLottoResult(testLotto, 3);

	return 0;
}