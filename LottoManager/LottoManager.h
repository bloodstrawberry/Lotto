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

}LOTTO;


void showLottoNumber(int index);
void showLottoNumber(LOTTO Lotto);

bool isLottoWinningNumber(LOTTO Lotto);
bool isMySuckNumber(LOTTO Lotto);

ull makeKey(LOTTO Lotto);
ull makeBitNumber(LOTTO Lotto);
int makeSum(LOTTO Lotto);
void makeStatisticsInfo(LOTTO& Lotto);

void getAllNumber();


#endif 
