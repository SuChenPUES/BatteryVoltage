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

/*�o�b�e���d���t�B���^�[�����l�v�Z�֐�*/
float cal_voltage(int n,float VB,float VBFLT_n_1)
{
	float CFVBFLT = 0.5;/*�o�b�e���d���t�B���^�����O�W��*/
        float VBFLT_n;/*�o�b�e���d���t�B���^�[�����l*/
	
	
	/*�V�X�e���N������̒l(=����o�b�e���d��)*/
	if (n == 0)
	{
		VB = 0;
		VBFLT_n_1 = 0;
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

void main(void)
{
	int num_case = 5;/*�P�[�X��*/
	int n = 10;/*�X�e�b�v��*/
	int i;
	int j;
	
	float VBFLT_n_1;/*(n-1)��ڃo�b�e���d���t�B���^�[�����l*/
	float VB[5] = {24.4,24.5,12.2,50,-10};/*�e�P�[�X�̃o�b�e���d��*/
	float VBFLT[5][10];/*�o�b�e���d���t�B���^�[�����l�z��[�P�[�X][�X�e�b�v]*/
	
	float test_case1[10] = {0, 12.2, 18.3, 21.35, 22.875, 23.6375, 24.01875, 24.209375, 24.3046875, 24.35234375}; /*�e�X�g�P�[�X1*/
	
	for (j = 0;j < num_case;j ++)
	{	
		for (i = 0; i < n;i ++)
		{
			VBFLT[j][i] = cal_voltage(i,VB[j],VBFLT_n_1);/*i��ڃo�b�e���d���t�B���^�[�����l�Z�o*/
			VBFLT_n_1 = VBFLT[j][i];/*i��ڃo�b�e���d���t�B���^�[�����l��ۑ����Ď����(i-1)��ڂ̒l�Ƃ��Ďg�p*/
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