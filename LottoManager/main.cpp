#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "FileManager.h"

extern int NumOfWinLotto;
extern int NumOfSuckLotto;

int main()
{
	getLottoWinningNumber(); //��÷ ��ȣ 
	getMySuckNumber(); //������ ���� ��ȣ

	//MAP���� check realnum sucknum �����ϱ�.

	printf("NumOfWinLotto %d\n", NumOfWinLotto);
	printf("NumOfSuckLotto %d\n", NumOfSuckLotto);

	return 0;
}