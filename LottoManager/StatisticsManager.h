#ifndef __STATISTICS_MANAGER__
#define __STATISTICS_MANAGER__

#include "define.h"
#include "LottoManager.h"

void showPastLottoResult(LOTTO Lotto, int offset);
void showBinary_long(ull n);

//���ӵ� ���� 6��, 5��, ..., 2��
bool checkConsecutive6(LOTTO Lotto);
bool checkConsecutive5(LOTTO Lotto);
bool checkConsecutive4(LOTTO Lotto);
bool checkConsecutive3(LOTTO Lotto);
bool checkConsecutive2(LOTTO Lotto);
#endif
