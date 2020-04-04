#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "FileManager.h"

extern int NumOfWinLotto;
extern int NumOfSuckLotto;

int main()
{
	getLottoWinningNumber(); //당첨 번호 
	getMySuckNumber(); //실패한 나의 번호

	//MAP으로 check realnum sucknum 관리하기.

	printf("NumOfWinLotto %d\n", NumOfWinLotto);
	printf("NumOfSuckLotto %d\n", NumOfSuckLotto);

	return 0;
}