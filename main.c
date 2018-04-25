/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :Mon, Oct 24, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/

#include <stdlib.h>
#include "iodefine.h"

float cal_voltage(int n,float VB,float VBFLT_n_1);
void main(void);

/*バッテリ電圧フィルター処理値計算関数*/
float cal_voltage(int n,float VB,float VBFLT_n_1)
{
	float CFVBFLT = 0.5;/*バッテリ電圧フィルタリング係数*/
        float VBFLT_n;/*バッテリ電圧フィルター処理値*/
	
	
	/*システム起動直後の値(=初回バッテリ電圧)*/
	if (n == 0)
	{
		VBFLT_n_1 = VB;
	}
	
	/*バッテリ電圧フィルター処理値計算*/
	VBFLT_n = VB * CFVBFLT + VBFLT_n_1 * (1 - CFVBFLT);
	
	/*期待値を目標範囲に修正*/
	if (VBFLT_n < 0)
	{
		VBFLT_n = 0;
	}
	else if (VBFLT_n > 24.4)
	{
		VBFLT_n = 24.4;
	}
	
	return VBFLT_n;
	
}

void main(void)
{
	int num_case = 5;/*ケース数*/
	int n = 10;/*ステップ数*/
	int i;
	int j;
	
	float VBFLT_n_1;
	float VB[5] = {24.4,24.5,12.2,50,-10};/*各ケースのバッテリ電圧*/
	float VBFLT[5][10];/*バッテリ電圧フィルター処理値配列[ケース][ステップ]*/
	
	for (j = 0;j < num_case;j ++)
	{	
		for (i = 0; i < n;i ++)
		{
			VBFLT[j][i] = cal_voltage(i,VB[j],VBFLT_n_1);/*i回目バッテリ電圧フィルター処理値算出*/
			VBFLT_n_1 = VBFLT[j][i];/*i回目バッテリ電圧フィルター処理値保存して次回に(i-1)回目の値として使用*/
		}
	}
	
	

}