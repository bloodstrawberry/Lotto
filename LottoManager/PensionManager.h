#ifndef __PENSION_MANAGER__
#define __PENSION_MANAGER__

#include "define.h"

typedef struct _pension
{
	int index;
	int pClass[2];
	int numbers[14]; // 1�� 1�� 2�� 2�� 2�� 2�� 3�� 4�� 5�� 6�� 6�� 7�� 7��
	
	int bonus;

	int date;

} PENSION;

void showPensionNumber(PENSION pension);

bool isPensionWinningNumber(int number, int rank);
bool isPensionWinningNumber(PENSION p, int rank);

void pensionSort();


#endif 
