#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>

#include "LottoManager.h"
#include "FileManager.h"

using namespace std;

extern int NumOfWinLotto;
extern int NumOfSuckLotto;

//40 41 42 43 44 45

LOTTO testLotto;

int main()
{
	//8 19 20 27 42 45
	testLotto.number[0] = 1;
	testLotto.number[1] = 4;
	testLotto.number[2] = 10;
	testLotto.number[3] = 12;
	testLotto.number[4] = 28;
	testLotto.number[5] = 45;
	testLotto.key = makeKey(testLotto);

	getLottoWinningNumber(); //당첨 번호 
	getMySuckNumber(); //실패한 나의 번호

	//MAP으로 check realnum sucknum 관리하기.

	printf("NumOfWinLotto %d\n", NumOfWinLotto);
	printf("NumOfSuckLotto %d\n", NumOfSuckLotto);

	printf("%d\n", isLottoWinningNumber(testLotto));
	printf("%d\n", isMySuckNumber(testLotto));


	return 0;
}