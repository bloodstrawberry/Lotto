#ifndef __STATISTICS_MANAGER__
#define __STATISTICS_MANAGER__

#include "define.h"
#include "LottoManager.h"

void showPastLottoResult(LOTTO Lotto, int offset);
void showBinary_long(ull n);

//연속된 숫자 6개, 5개, ..., 2개
bool checkConsecutive6(LOTTO Lotto);
bool checkConsecutive5(LOTTO Lotto);
bool checkConsecutive4(LOTTO Lotto);
bool checkConsecutive3(LOTTO Lotto);
bool checkConsecutive2(LOTTO Lotto);
#endif
