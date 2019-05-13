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

void Delay_xms(unsigned int x);//死延时x毫秒
void Input_INPUT(void);
void Input_INLOW(void);
void Input_INHIGH(void);
void key_Scan(void);
//======================Subroutine=======================
void Device_Memory_Init(void)
{
    OPTION = 0b00000000; //BIT7:开启总上拉 0=开启 1=关闭
    OSCCON = 0B01010000; //BIT6~BIT4:设置内部振荡频率选择 4MHz
    WDTCON = 0B00001000;//BIT4~BIT1:看门狗复位时间512ms，bit0--1=开启，0=关闭
}
/*******************************************************************************
 * 函数名：IOPort_Init
 * 描述  ：GPIO配置函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用(置1端)
 ******************************************************************************/
void IOPort_Init(void)
{
    //TRISA 配置输入输出 PA3只做输入引脚
    TRISA0=0;//0=输出，1=输入
    TRISA1=0;//0=输出，1=输入
    TRISA2=0;//0=输出，1=输入
    TRISA4=1;//0=输出，1=输入
    TRISA5=1;//0=输出，1=输入
    //WPUA 配置输入引脚要不要上拉 先开启option的PAPU使能总上拉
    WPUA0=0;//1=使能上拉，0=禁止上拉
    WPUA1=0;//1=使能上拉，0=禁止上拉
    WPUA2=0;//1=使能上拉，0=禁止上拉
    WPUA4=0;//1=使能上拉，0=禁止上拉
    WPUA5=0;//1=使能上拉，0=禁止上拉

}
// 主函数
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
 * 函数名：Input_PA1
 * 描述  ：配置key扫描函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用(为翻转端)
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
 * 函数名：Input_PA1
 * 描述  ：配置key扫描函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用(置0端)
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
 * 函数名：Input_INLOW
 * 描述  ：配置key扫描函数
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用(置1端)
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
void Delay_xms(unsigned int x)  //死延时x毫秒
{
    unsigned int i;
    for(i=0; i<x; i++) {
        __delay_ms(1);
        //CLRWDT();
    }
}

