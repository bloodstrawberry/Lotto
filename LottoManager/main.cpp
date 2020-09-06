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
#include "PensionManager.h"
#include "ReactManager.h"		  


using namespace std;

extern int NumOfWinLotto;
extern int NumOfSuckLotto;
extern LOTTO LottoWinningNumber[];
extern unsigned long long seed;
extern int SHUFFLE;
extern int NumOfWinPension;
extern PENSION PensionWinningNumber[10000];

LOTTO testLotto;

extern int sortPension[1000000];
extern int MySuckPensionNumber[1000000];

#define F_PENSIO

int main()
{
	srand(time(NULL)); 
	seed = rand();

#ifdef F_PENSION
	//suck number 정렬하기 앞글자만 따서 check 하기 
	getPensionWinningNumber();
	getMyPensionSuckNumber();
	pensionSort();

	int pick = 929876;
	if (sortPension[pick] || MySuckPensionNumber[pick]) printf("no way!! %d %d %d\n", pick, sortPension[pick], MySuckPensionNumber[pick]);


	//for (int i = 1; i <= NumOfWinPension;i++) showPensionNumber(PensionWinningNumber[i]);
#else


	/* ---------------------- Input ---------------------- */
	
	getLottoWinningNumber(); //당첨 번호 
	getMySuckNumber(); //실패한 나의 번호
	getNumbers(); //hot, cold, except

	/* ---------------------- Statistics ---------------------- */

	setStatistics(728, 928);
	setLatestStatistics(50);
	statistics();

	/* ---------------------- PickUp ---------------------- */
	int mNumber[] = { 3, 14, 37 }; 
	int msize = sizeof(mNumber) / sizeof(int);
	setMustNumber(mNumber, msize);

	int wNumber[] = {
		35, //완제수
		38, //혜성
		44, //홍표
		10, //도건
		13, //김돤
		18, //옥형
		9, 5, // 9월 5일
		27, //927회
		6, //이전 보너스
		
		24, // YES 24 ...

		1, 2,

		9,17,21,26,34,38, // 김돤 수
	};


	int wsize = sizeof(wNumber) / sizeof(int);
	setWrongNumber(wNumber, wsize);

	setPastRank2(0, 0);
	setPastRank3(0, 0);
	setPastRank4(0, 2);	
	
	setMustEvenNumber(6, 5);
	setPrimeNumber(1, 3);

	setHotNumber(1, 5);
	setColdNumber(1, 5);
	setOneNumber(1, 3);

	setColor(4, 4);

	int mColor[] = { PURPLE, }; // YELLOW, BLUE, RED, PURPLE, GREEN
	int csize = sizeof(mColor) / sizeof(int);
	setMustColor(mColor, csize);

	setACNumber(8, 9);
	setNextNumber(1, 1);

	set_Jump_Cons2_Cons22_Cons3(NO_CARE, NEED, DELETE, DELETE);



	SHUFFLE = 1;
	getAllNumber(); //Fileter. -> 이월된 번호 통계...해서...음....

	latestAnalysis(false);
	latestAnalysis(true);
#endif

#if 01
	makeJson();
#endif

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