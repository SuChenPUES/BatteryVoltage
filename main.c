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

/*�o�b�e���d���t�B���^�[�����l�v�Z�֐�*/
float cal_voltage(int n, float VB, float VBFLT_n)
{
	float CFVBFLT = 0.5; //�o�b�e���d���t�B���^�����O�W��
	float VBFLT_n_1; //(n-1)��ڃo�b�e���d���t�B���^�[�����l
	
	
	/*�V�X�e���N������̒l(=����o�b�e���d��)*/
	if (n == 0)
	{
		VB = 0;
		VBFLT_n_1 = 0;
	}
	else
	{
		VBFLT_n_1 = VBFLT_n;
	}
	
	/*���͂�ڕW�͈͂ɏC��*/
	if (VB < 0)
	{
		VB = 0;
	}
	else if (VB > 24.4)
	{
		VB = 24.4;
	}
	
	/*�o�b�e���d���t�B���^�[�����l�v�Z*/
	VBFLT_n = VB * CFVBFLT + VBFLT_n_1 * (1 - CFVBFLT);
	
	/*�o�͂�ڕW�͈͂ɏC��*/
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
	int num_case = 5; //�P�[�X��
	int num_step = 10; //�X�e�b�v��
	int i; //�X�e�b�v���J�E���^�[
	int j; //�P�[�X���J�E���^�[
	
	float VB[5] = {24.4, 24.5, 12.2, 50, -10}; //�e�P�[�X�̃o�b�e���d��
	float VBFLT[5][10]; //�o�b�e���d���t�B���^�[�����l�z��[�P�[�X][�X�e�b�v]
	
	for (j = 0; j < num_case; j ++)
	{	
		/*0��ڃo�b�e���d���t�B���^�[�����l�Z�o*/
		i == 0;
		VBFLT[j][i] = cal_voltage(i, VB[j], VBFLT[j][i]);
		
		/*�X�e�b�vj��ڃo�b�e���d���t�B���^�[�����l�����ɎZ�o*/
		for (i = 1; i < num_step; i ++)
		{
			VBFLT[j][i] = cal_voltage(i, VB[j], VBFLT[j][i-1]);
		}
	}
	
	/*define minUnit testing*/
	float test_case1[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.209375, 24.3046875, 24.35234375}; //�e�X�g�P�[�X1
	float test_case2[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.209375, 24.3046875, 24.35234375}; //�e�X�g�P�[�X2
	float test_case3[10] = {0, 6.1, 9.15, 10.675, 11.4375, 11.81875, 12.009375, 12.1046875, 12.15234375, 12.17617188}; //�e�X�g�P�[�X3
	float test_case4[10] = {0, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4}; //�e�X�g�P�[�X4
	float test_case5[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //�e�X�g�P�[�X5
	
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
	
	static char * all_tests() //�e�X�g�����{����֐�
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