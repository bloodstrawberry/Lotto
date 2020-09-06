#ifndef __PENSION_MANAGER__
#define __PENSION_MANAGER__

#include "define.h"

typedef struct _pension
{
	int index;
	int pClass[2];
	int numbers[14]; // 1등 1등 2등 2등 2등 2등 3등 4등 5등 6등 6등 7등 7등
	
	int bonus;

	int date;

} PENSION;

void showPensionNumber(PENSION pension);

bool isPensionWinningNumber(int number, int rank);
bool isPensionWinningNumber(PENSION p, int rank);

void pensionSort();


#endif 
