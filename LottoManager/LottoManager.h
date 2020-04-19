#ifndef __LOTTO_MANAGER__
#define __LOTTO_MANAGER__

#include "define.h"

typedef struct _lotto
{
	int index;
	
	int number[6];
	int bonus;
	ull bitNumber;

	int sum;
	ull status;
	ull key;
	int numOfOddNum;
	int numOfPrimeNum;

	int countOfPastRanks[6];
	
	bool deleteFlag;
}LOTTO;


void showLottoNumber(int index);
void showLottoNumber(LOTTO Lotto);

bool isLottoWinningNumber(LOTTO Lotto);
bool isMySuckNumber(LOTTO Lotto);

ull makeKey(LOTTO Lotto);
ull makeBitNumber(LOTTO Lotto);
int makeSum(LOTTO Lotto);
int countOddNumber(LOTTO Lotto);

void makeStatisticsInfo(LOTTO& Lotto);

void getAllNumber();
void deleteNumber();

//연속된 숫자 6개, 5개, ..., 2개
bool checkConsecutive6(LOTTO Lotto);
bool checkConsecutive5(LOTTO Lotto);
bool checkConsecutive4(LOTTO Lotto);
bool checkConsecutive3(LOTTO Lotto);
bool checkConsecutive2(LOTTO Lotto);

//등차수열 확인
bool checkDiff(LOTTO Lotto, int diff);
bool checkDifferentialSequence(LOTTO Lotto);

void setMustNumber(int* number, int size);
bool isMustNumber(LOTTO Lotto);
void setWrongNumber(int* number, int size);
bool isWrongNumber(LOTTO Lotto);

#endif 
