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

#include <stdio.h>
#include "iodefine.h"
#include "minunit.h"

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
		VB = 0;
		VBFLT_n_1 = 0;
	}
	
	/*入力を目標範囲に修正*/
	if (VB < 0)
	{
		VB = 0;
	}
	else if (VB > 24.4)
	{
		VB = 24.4;
	}
	
	/*バッテリ電圧フィルター処理値計算*/
	VBFLT_n = VB * CFVBFLT + VBFLT_n_1 * (1 - CFVBFLT);
	
	/*出力を目標範囲に修正*/
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
	
	float VBFLT_n_1;/*(n-1)回目バッテリ電圧フィルター処理値*/
	float VB[5] = {24.4,24.5,12.2,50,-10};/*各ケースのバッテリ電圧*/
	float VBFLT[5][10];/*バッテリ電圧フィルター処理値配列[ケース][ステップ]*/
	
	float test_case1[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.209375, 24.3046875, 24.35234375}; /*テストケース1*/
	
	for (j = 0;j < num_case;j ++)
	{	
		for (i = 0; i < n;i ++)
		{
			VBFLT[j][i] = cal_voltage(i,VB[j],VBFLT_n_1);/*i回目バッテリ電圧フィルター処理値算出*/
			VBFLT_n_1 = VBFLT[j][i];/*i回目バッテリ電圧フィルター処理値を保存して次回に(i-1)回目の値として使用*/
		}
	}
	
	/*minUnit testing*/
	static char *cal_voltage_case1()
	{
		for (i = 0;i < n;i ++)
		{
		    mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT_n_1) == test_case1[i]);
	
		}
	}

}