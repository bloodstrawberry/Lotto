#ifndef __LOTTO_MANAGER__
#define __LOTTO_MANAGER__

#include "define.h"

typedef struct _lotto
{
	int index;
	int number[6];
	int bonus;

	ull status;

}LOTTO;

void showLottoNumber(int index);
void showLottoNumber(LOTTO Lotto);

bool isMySuckNumber(LOTTO Lotto);



#endif 
