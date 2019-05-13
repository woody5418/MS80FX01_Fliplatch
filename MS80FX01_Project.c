#include "syscfg.h"


#define _XTAL_FREQ 		4000000
#define u16         unsigned int
#define u8          unsigned char

#define  OUTPUT     PA2
#define  INPUT      PA5
#define  INHIGH     PA4
#define  INLOW      PA3

u8 flag_0=1;
u8 flag_F=0;

void Delay_xms(unsigned int x);//����ʱx����
void Input_INPUT(void);
void Input_INLOW(void);
void Input_INHIGH(void);
void key_Scan(void);
//======================Subroutine=======================
void Device_Memory_Init(void)
{
    OPTION = 0b00000000; //BIT7:���������� 0=���� 1=�ر�
    OSCCON = 0B01010000; //BIT6~BIT4:�����ڲ���Ƶ��ѡ�� 4MHz
    WDTCON = 0B00001000;//BIT4~BIT1:���Ź���λʱ��512ms��bit0--1=������0=�ر�
}
/*******************************************************************************
 * ��������IOPort_Init
 * ����  ��GPIO���ú���
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����(��1��)
 ******************************************************************************/
void IOPort_Init(void)
{
    //TRISA ����������� PA3ֻ����������
    TRISA0=0;//0=�����1=����
    TRISA1=0;//0=�����1=����
    TRISA2=0;//0=�����1=����
    TRISA4=1;//0=�����1=����
    TRISA5=1;//0=�����1=����
    //WPUA ������������Ҫ��Ҫ���� �ȿ���option��PAPUʹ��������
    WPUA0=0;//1=ʹ��������0=��ֹ����
    WPUA1=0;//1=ʹ��������0=��ֹ����
    WPUA2=0;//1=ʹ��������0=��ֹ����
    WPUA4=0;//1=ʹ��������0=��ֹ����
    WPUA5=0;//1=ʹ��������0=��ֹ����

}
// ������
void main(void)
{
    Device_Memory_Init();
    IOPort_Init();
    OUTPUT=0;
    while(1) {
        key_Scan();
    }
}
/*******************************************************************************
 * ��������Input_PA1
 * ����  ������keyɨ�躯��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����(Ϊ��ת��)
 ******************************************************************************/
void Input_INPUT(void)
{
    /*if(flag_0 == 0)
    	OUTPUT=1;
    if(flag_0 == 1)
    	OUTPUT=0;
    */
    if(INPUT == 0) {
        Delay_xms(10);
        if(INPUT == 1) {
            if(flag_0 == 0) {
                OUTPUT=0;
                flag_0=1;
            } else {
                OUTPUT=1;
                flag_0=0;
            }
            return;
        }
    }
}
/*******************************************************************************
 * ��������Input_PA1
 * ����  ������keyɨ�躯��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����(��0��)
 ******************************************************************************/
void Input_INHIGH(void)
{
    if(INHIGH != 0) {
        Delay_xms(10);
        if(INHIGH != 0) {
            flag_F=1;
            if(INLOW != 0)
                OUTPUT=0;
            else
                OUTPUT=1;
        }
    }
}

/*******************************************************************************
 * ��������Input_INLOW
 * ����  ������keyɨ�躯��
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����(��1��)
 ******************************************************************************/
void Input_INLOW(void)
{
    if(INLOW != 0) {
        Delay_xms(10);
        if(INLOW != 0) {
            flag_F=1;
            if(INLOW != 0)
                OUTPUT=0;
            else
                OUTPUT=1;
        }
    }
}


void key_Scan(void)
{
    //if(flag_F == 0)
    Input_INPUT();
    Input_INHIGH();
    Input_INLOW();
}

////////////////////////////////////////////////
void Delay_xms(unsigned int x)  //����ʱx����
{
    unsigned int i;
    for(i=0; i<x; i++) {
        __delay_ms(1);
        //CLRWDT();
    }
}

