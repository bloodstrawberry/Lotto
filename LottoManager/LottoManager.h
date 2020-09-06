#ifndef __LOTTO_MANAGER__
#define __LOTTO_MANAGER__

#include "define.h"

typedef struct _MYTIME
{
	int year;
	int month;
	int day;
}MYTIME;

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

	//this is for Filter
	int hot;
	int cold;
	int one;

	int numOfHot;
	int numOfCold;
	int numOfOne;
	
	int AC;

	int countOfPastRanks[6];
	int countOfColor;
	int countOfColorBonus;

	MYTIME mtime;
}LOTTO;

bool Filter(LOTTO& Lotto);

void showLottoNumber(int index);
void showLottoNumber(LOTTO& Lotto);

bool isLottoWinningNumber(LOTTO& Lotto);
bool isMySuckNumber(LOTTO& Lotto);

ull makeKey(LOTTO& Lotto);
ull makeBitNumber(LOTTO& Lotto);
int makeSum(LOTTO& Lotto);
int countOddNumber(LOTTO& Lotto);
int countPrimeNumber(LOTTO& Lotto);

void makeStatisticsInfo(LOTTO& Lotto);

void getAllNumber();
void deleteNumber();

//연속된 숫자 6개, 5개, ..., 2개
bool checkConsecutive6(LOTTO& Lotto);
bool checkConsecutive5(LOTTO& Lotto);
bool checkConsecutive4(LOTTO& Lotto);
bool checkConsecutive3(LOTTO& Lotto);
bool checkConsecutive2(LOTTO& Lotto);
bool checkConsecutive2_2(LOTTO& Lotto); //연속된 숫자 2개 x2

//등차수열 확인
bool checkDiff(LOTTO& Lotto, int diff);
bool checkDifferentialSequence(LOTTO& Lotto);

void setMustNumber(int* number, int size);
bool isMustNumber(LOTTO& Lotto);
void setWrongNumber(int* number, int size);
bool isWrongNumber(LOTTO& Lotto);

void setPrimeNumber(int under, int upper);
void setMustEvenNumber(int under, int even);

void setMustColor(int* color, int size);

void setPastRank2(int under, int upper);
void setPastRank3(int under, int upper);
void setPastRank4(int under, int upper);

void setHotNumber(int under, int upper);
void setColdNumber(int under, int upper);
void setOneNumber(int under, int upper);

void setACNumber(int under, int upper);
void setColor(int under, int upper);

void setNextNumber(int under, int upper);

void set_Jump_Cons2_Cons22_Cons3(int jump, int cons, int cons22, int cons3);

#endif 
