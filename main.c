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

float cal_voltage(int n, float VB, float VBFLT_n);
int main(void);

/*バッテリ電圧フィルター処理値計算関数*/
float cal_voltage(int n, float VB, float VBFLT_n)
{
	float CFVBFLT = 0.5; //バッテリ電圧フィルタリング係数
	float VBFLT_n_1; //(n-1)回目バッテリ電圧フィルター処理値
	
	
	/*システム起動直後の値(=初回バッテリ電圧)*/
	if (n == 0)
	{
		VB = 0;
		VBFLT_n_1 = 0;
	}
	else
	{
		VBFLT_n_1 = VBFLT_n;
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


int main(void)
{
	int num_case = 5; //ケース数
	int num_step = 10; //ステップ数
	int i; //ステップ数カウンター
	int j; //ケース数カウンター
	
	float VB[5] = {24.4, 24.5, 12.2, 50, -10}; //各ケースのバッテリ電圧
	float VBFLT[5][10]; //バッテリ電圧フィルター処理値配列[ケース][ステップ]
	
	for (j = 0; j < num_case; j ++)
	{	
		/*0回目バッテリ電圧フィルター処理値算出*/
		i == 0;
		VBFLT[j][i] = cal_voltage(i, VB[j], VBFLT[j][i]);
		
		/*ステップj回目バッテリ電圧フィルター処理値順次に算出*/
		for (i = 1; i < num_step; i ++)
		{
			VBFLT[j][i] = cal_voltage(i, VB[j], VBFLT[j][i-1]);
		}
	}
	
	/*define minUnit testing*/
	float test_case1[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.209375, 24.3046875, 24.35234375}; //テストケース1
	float test_case2[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.209375, 24.3046875, 24.35234375}; //テストケース2
	float test_case3[10] = {0, 6.1, 9.15, 10.675, 11.4375, 11.81875, 12.009375, 12.1046875, 12.15234375, 12.17617188}; //テストケース3
	float test_case4[10] = {0, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4}; //テストケース4
	float test_case5[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //テストケース5
	
	static char *cal_voltage_case1()
	{
	        i = 0
	        mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[1][i]) == test_case1[i]);
		return 0;
		
		for (i = 1; i < num_step; i ++)
		{
		        mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[1][i-1]) == test_case1[i]);
			return 0;
		}
	}

	static char *cal_voltage_case2()
	{
	        i = 0
                mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[2][i]) == test_case2[i]);
		
		for (i = 1; i < num_step; i ++)
		{
		        mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[2][i-1]) == test_case2[i]);
			return 0;
		}
	}

	static char *cal_voltage_case3()
	{
	       i = 0
	       mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[3][i]) == test_case3[i]);
	       return 0;
		
	       for (i = 1; i < num_step; i ++)
	       {
		        mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[3][i-1]) == test_case3[i]);
			return 0;
	       }
	}
	
	static char *cal_voltage_case4()
	{
	       i = 0
	       mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[4][i]) == test_case4[i]);
	       return 0;
		
	       for (i = 1; i < num_step; i ++)
	       {
		       mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[4][i-1]) == test_case4[i]);
		       return 0;
	       }
	}
	
	static char *cal_voltage_case5()
	{
	       i = 0
	       mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[5][i]) == test_case5[i]);
	       return 0;
	
	       for (i = 1; i < num_step; i ++)
	       {
		      mu_assert("error voltage value !", cal_voltage(i, VB[i], VBFLT[5][i-1]) == test_case5[i]);
		      return 0;
	       }
	}
	
	static char * all_tests() //テストを実施する関数
	{    
	        mu_run_test(cal_voltage_case1);
                mu_run_test(cal_voltage_case2);
		mu_run_test(cal_voltage_case3);
		mu_run_test(cal_voltage_case4);
		mu_run_test(cal_voltage_case5);
                return 0;
	}

	/*run minUnit testing*/
	char s[255]={0};

        int a=1;
        char *result = all_tests();
        if (result != 0) 
	{
	        sprintf(s, "%s\n",result);
	}
        else
	{
	        sprintf(s, "ALL OK! \n");
	}
	
        /* printf("test num: %d\n",tests_run); */
        return result != 0;

	
}