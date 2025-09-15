/*
 * user_led.c
 *
 *  Created on: Apr 22, 2025
 *      Author: 24116
 */

#include <user_rgb.h>
#include "tim.h"
#include "stdlib.h"

#define Code0 30
#define Code1 60
#define CodeReset 0
static uint16_t yellow[]={
Code1,Code1,Code1,Code1,Code1,Code1,Code1,Code1,//G
Code1,Code1,Code1,Code1,Code1,Code1,Code1,Code1,//R
Code0,Code0,Code0,Code0,Code0,Code0,Code0,Code0,//B
CodeReset
                     };
static uint16_t Blue[]={
Code0,Code0,Code0,Code0,Code0,Code0,Code0,Code0,//G
Code0,Code0,Code0,Code0,Code0,Code0,Code0,Code0,//R
Code1,Code1,Code1,Code1,Code1,Code1,Code1,Code1,//B
CodeReset
                     };

RGB_Color_TypeDef table[16] =
{
   {254,67,101},
   {76,0,10},
   {249,15,173},
   {128,0,32},
   {158,46,36},
   {184,206,142},
   {227,23,13},
   {178,34,34},
   {255,99,71},
   {99,38,18},
   {255,97,0},
   {21,161,201},
   {56,94,15},
   {50,205,50},
   {160,32,240},
    {218,60,90}
};
 //这些是好看的颜色
const RGB_Color_TypeDef color1 = {254,67,101};
//const RGB_Color_TypeDef color2 = {76,0,10};
//const RGB_Color_TypeDef color3 = {249,15,173};
//const RGB_Color_TypeDef color4 = {128,0,32};
//const RGB_Color_TypeDef color5 = {158,46,36};
//const RGB_Color_TypeDef color6 = {184,206,142};
//const RGB_Color_TypeDef color7 = {227,23,13};
//const RGB_Color_TypeDef color8 = {178,34,34};
//const RGB_Color_TypeDef color9 = {255,99,71};
//const RGB_Color_TypeDef color10 ={99,38,18};
//const RGB_Color_TypeDef color11= {255,97,0};
//const RGB_Color_TypeDef color12= {21,161,201};
//const RGB_Color_TypeDef color13= {56,94,15};
//const RGB_Color_TypeDef color14= {50,205,50};
//const RGB_Color_TypeDef color15= {160,32,240};
//const RGB_Color_TypeDef color16= {218,60,90};


/*二维数组存放最终PWM输出数组，每一行24个数据代表一个LED，最后一行24个0用于复位*/
static uint16_t Pixel_Buf[Pixel_NUM+1][24];

/*
功能：最后一行装在24个0，输出24个周期占空比为0的PWM波，作为最后reset延时，这里总时长为24*1.25=37.5us > 24us(要求大于24us)
//如果出现无法复位的情况，只需要在增加数组Pixel_Buf[Pixel_NUM+1][24]的行数，并改写Reset_Load即可，这里不做演示了，
*/
 void Reset_Load(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[Pixel_NUM][i] = 0;

	}
}

/*
功能：发送数组Pixel_Buf[Pixel_NUM+1][24]内的数据，发送的数据被存储到定时器1通道1的CCR寄存器，用于控制PWM占空比
参数：(&htim1)定时器1，(TIM_CHANNEL_1)通道1，((uint32_t *)Pixel_Buf)待发送数组，
			(Pixel_NUM+1)*24)发送个数，数组行列相乘
*/
  void RGB_SendArray(void)
{
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)Pixel_Buf,(Pixel_NUM+1)*24);
}


 //刷新WS2812B灯板显示函数
 void RGB_Flush(void)
{
    Reset_Load();     //复位
    RGB_SendArray();  //发送数据


}
/*
功能：设定单个RGB LED的颜色，把结构体中RGB的24BIT转换为0码和1码
参数：LedId为LED序号，Color：定义的颜色结构体
*/
void RGB_SetOne_Color(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i;
	if(LedId > Pixel_NUM)return; //avoid overflow 防止写入ID大于LED总数
	//这里是对 Pixel_Buf[LedId][i]写入一个周期内高电平的持续时间（或者说时PWM的占空比寄存器CCR1），
	for(i=0;i<8;i++) Pixel_Buf[LedId][i]   = ( ((Color.G/5) & (1 << (7 -i)))? (CODE_1):CODE_0 );//数组某一行0~7转化存放G
	for(i=8;i<16;i++) Pixel_Buf[LedId][i]  = ( ((Color.R/5) & (1 << (15-i)))? (CODE_1):CODE_0 );//数组某一行8~15转化存放R
	for(i=16;i<24;i++) Pixel_Buf[LedId][i] = ( ((Color.B/5) & (1 << (23-i)))? (CODE_1):CODE_0 );//数组某一行16~23转化存放B
}

//调用RGB_SetOne_Color函数，完成对多个LED的颜色设置。
void RGB_SetMore_Color(uint8_t head, uint8_t heal,RGB_Color_TypeDef color)
{
    uint8_t i=0;
    for(i=head;i<=heal;i++)
    {
        RGB_SetOne_Color(i,color) ;
    }
}
void ASSI_Set_Black(void)
{
	 for(int j=0;j<Pixel_NUM;j++)
	    {
	    	for(int i=0;i<24;i++)
	    		{
	    			Pixel_Buf[j][i] = Code0;

	    		}
	    }
	 RGB_Flush();
}
void ASSI_Set_Blue(void)
{

	for(int j=0;j<Pixel_NUM;j++)
	    {
	    	for(int i=0;i<8;i++)
	    		{
	    			Pixel_Buf[j][i] = Code0;

	    		}
	    	for(int i=8;i<16;i++)
	    		{
	    		    			Pixel_Buf[j][i] = Code1;

	    		}
	    	for(int i=16;i<24;i++)
	    	{
	    		Pixel_Buf[j][i] = Code0;
	    	}
	    }
	 RGB_Flush();

}
void ASSI_Set_Yellow(void)
{

	for(int j=0;j<Pixel_NUM;j++)
	    {

	    	for(int i=0;i<8;i++)
	    		{
	    			Pixel_Buf[j][i] = Code1;

	    		}
	    	for(int i=8;i<16;i++)
	    	{
	    		Pixel_Buf[j][i] = Code0;
	    	}
	    	for(int i=16;i<24;i++)
	    	{
	    		    		Pixel_Buf[j][i] = Code1;
	    	}
	    }
	 RGB_Flush();

}
void ASSI_OFF(void)//无人系统指示灯熄灭
{
	 blink_enabled=0;
	 ASSI_Set_Black();

}

void ASSI_Blue_Stable(void)//无人系统指示灯 蓝灯常亮
{__disable_irq();
	   blink_enabled=0;
	   ASSI_Set_Blue();
	   __enable_irq();
}
void ASSI_Blue_Blink(void)//无人系统指示灯  蓝灯闪烁
{
	blink_enabled=1;
}
void ASSI_Yellow_Stable(void)//无人系统指示灯 黄灯常亮
{__disable_irq();
	    blink_enabled=0;
	    ASSI_Set_Yellow();
	    __enable_irq();
}
void ASSI_Yellow_Blink(void)//无人系统指示灯  黄灯闪烁
{
	blink_enabled=2;
}
//TIM中断的重写
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)//控制ASSI闪烁
	{
		if(blink_enabled==1)//蓝灯闪烁
		{
			led_state ^= 1;
		    if(led_state)
		    {
		    	 ASSI_Set_Blue();
		    }
		    if(!led_state)
		    {
		    	 ASSI_Set_Black();
		    }

		}
		if(blink_enabled==2)//黄灯闪烁
		{
		    led_state ^= 1;
		    if(led_state)
		   	 {
		   		  ASSI_Set_Yellow();
		     }
		    if(!led_state)
		     {
		   		  ASSI_Set_Black();
		     }
		}
	}
	if(htim->Instance == TIM4)//发送CAN消息
	{
		if(AS_State==AS_Emergency)
		{
			CAN_Send_AS_Emergency();
		}
		if(EBS_Able_State==EBS_Disable)
		{
			CAN_Send_EBS_Disable();
		}
	}
}
void WS2812_Update(void){
	static uint16_t data[]={
			Code1,Code1,Code1,Code1,Code1,Code1,Code1,Code1,//G
			Code0,Code0,Code0,Code0,Code0,Code0,Code0,Code0,//B
			Code1,Code1,Code1,Code1,Code1,Code1,Code1,Code1,//R
			CodeReset
                     };
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)data, sizeof(data)/sizeof(uint16_t));

}
