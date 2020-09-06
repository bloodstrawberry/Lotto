#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>


#include "StatisticsManager.h"
#include "ReactManager.h"

using namespace std;
//statistic
extern int NumOfWinLotto;
extern LOTTO LottoWinningNumber[];



void makeLottoWinningNumberJson()
{
	ofstream fout;
	fout.open("LottoWinningNumber.json");
	
	fout << "[" << endl;

	char buff[100];
	//0에 대한 처리 하기.

	printf("%d\n", NumOfWinLotto);
	for (int i = NumOfWinLotto - 5; i <= NumOfWinLotto; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		fout << "    {" << endl;
		sprintf(buff, "      \"day\": \"%4d-%02d-%02d\"", lotto.mtime.year, lotto.mtime.month, lotto.mtime.day);
		fout << buff;
		fout << "," << endl;
		sprintf(buff, "      \"number\": [%d,%d,%d,%d,%d,%d]", lotto.number[0], lotto.number[1], lotto.number[2], lotto.number[3], lotto.number[4], lotto.number[5]);
		fout << buff;
		fout << "," << endl;
		sprintf(buff, "      \"bonus\": \"%d\"", lotto.bonus);
		fout << buff << endl;
		fout << "    }";
		
		if (i != NumOfWinLotto) fout << "," << endl;
		else fout << endl;
	}

	fout << "]" << endl;
	
	fout.close();
}

void makeJson()
{
	printf("* make LottoWinningNumber.json\n");
	makeLottoWinningNumberJson();
	printf("* End LottoWinningNumber.json\n");
}