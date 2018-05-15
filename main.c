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

float cal_voltage(float VB);
int main(int argc, char **argv);

/*�o�b�e���d���t�B���^�[�����l�v�Z�֐�*/
float cal_voltage(float VB)
{
	float CFVBFLT = 0.5; //�o�b�e���d���t�B���^�����O�W��
	static float VBFLT_n_1 = 0; //(n-1)��ڃo�b�e���d���t�B���^�[�����l
	float VBFLT_n; //(n)��ڃo�b�e���d���t�B���^�[�����l

	/*���͂�ڕW�͈͂ɏC��*/
	if (VB < 1e-7)
	{
		VB = 0;
	}
	else if ((VB -24.4) > 1e-7)
	{
		VB = 24.4;
	}
	
	/*�V�e�X�g�֐��ɓ��鎞VBFLT_n_1������*/
	if (VB == 0)
	{
		VBFLT_n_1 = 0;
	}

	/*�o�b�e���d���t�B���^�[�����l�v�Z*/
	VBFLT_n = VB * CFVBFLT + VBFLT_n_1 * (1 - CFVBFLT);
	
	/*�o�͂�ڕW�͈͂ɏC��*/
	if (VBFLT_n < 1e-7)
	{
		VBFLT_n = 0;
	}
	else if ((VBFLT_n - 24.4) > 1e-7)
	{
		VBFLT_n = 24.4;
	}
	
	/*(n-1)��ڃo�b�e���d���t�B���^�[�����l�ۑ�*/
	VBFLT_n_1 = VBFLT_n;
	
	return VBFLT_n;
	
}

/*define minUnit testing*/
int tests_run = 5; //�e�X�g�P�[�X��
int num_step = 10; //�X�e�b�v��

static char *cal_voltage_case1()
{
	float VB1[10] = {0, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4, 24.4}; //�P�[�X�̃o�b�e���d������
	float test_case1[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.20938, 24.30469, 24.35234}; //�P�[�X�̃o�b�e���d���t�B���^�[�����l�̊��Ғl
	
	int i;
	
	for (i = 0; i < num_step; i ++)
	{
		mu_assert("error voltage value(case1) !", abs(cal_voltage(VB1[i]) - test_case1[i]) <= 1e-7);
	}
	
	return 0;
}

static char *cal_voltage_case2()
{
	float VB2[10] = {0, 24.5, 24.5, 24.5, 24.5, 24.5, 24.5, 24.5, 24.5, 24.5};
	float test_case2[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.20938, 24.30469, 24.35234};
	
	int i;
	
	for (i = 0; i < num_step; i ++)
	{
		mu_assert("error voltage value(case2) !", abs(cal_voltage(VB2[i]) - test_case2[i]) <= 1e-7);
	}
	
	return 0;
}

static char *cal_voltage_case3()
{
	float VB3[10] = {0, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2, 12.2};
	float test_case3[10] = {0, 6.1, 9.15, 10.675, 11.4375, 11.81875, 12.00938, 12.10469, 12.15234, 12.17617};
	
	int i;
	
	for (i = 0; i < num_step; i ++)
	{
		mu_assert("error voltage value(case3) !", abs(cal_voltage(VB3[i]) - test_case3[i]) <= 1e-7);
	}
	
	return 0;
}

static char *cal_voltage_case4()
{
	float VB4[10] = {0, 50, 50, 50, 50, 50, 50, 50, 50, 50};
	float test_case4[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.20938, 24.30469, 24.35234};
	
	int i;
	
	for (i = 0; i < num_step; i ++)
	{
		mu_assert("error voltage value(case4) !", abs(cal_voltage(VB4[i]) - test_case4[i]) <= 1e-7);
	}
	
	return 0;
}

static char *cal_voltage_case5()
{
	float VB5[10] = {0, -10, -10, -10, -10, -10, -10, -10, -10, -10};
	float test_case5[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	int i;
	
	for (i = 0; i < num_step; i ++)
	{
		mu_assert("error voltage value(case5) !", abs(cal_voltage(VB5[i]) - test_case5[i]) <= 1e-7);
	}
	
	return 0;
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


int main(int argc, char **argv)
{
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
	
        printf("test num: %d\n",tests_run);
        return result != 0;

}