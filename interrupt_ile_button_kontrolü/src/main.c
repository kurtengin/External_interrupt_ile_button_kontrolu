

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t buttondurum;

GPIO_InitTypeDef GPIOInitstructure;
EXTI_InitTypeDef EXTIInitstructure;
NVIC_InitTypeDef NVICInitstructure;

void gpioConfig(){
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//led
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //button
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); //EXTI

	//LED
	
	GPIOInitstructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIOInitstructure.GPIO_OType=GPIO_OType_PP;
	GPIOInitstructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIOInitstructure.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15;
	GPIOInitstructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIOInitstructure);

	//BUTTON

	GPIOInitstructure.GPIO_Mode=GPIO_Mode_IN;
	GPIOInitstructure.GPIO_OType=GPIO_OType_PP;
	GPIOInitstructure.GPIO_Pin=GPIO_Pin_0;
	GPIOInitstructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIOInitstructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIOInitstructure);

	//EXTI

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);

	EXTIInitstructure.EXTI_Line=EXTI_Line0;
	EXTIInitstructure.EXTI_LineCmd=ENABLE;
	EXTIInitstructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTIInitstructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTIInitstructure);

	//NVIC CONFÝG
	
	NVICInitstructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVICInitstructure.NVIC_IRQChannelCmd=ENABLE;
	NVICInitstructure.NVIC_IRQChannelPreemptionPriority=0xFF;
	NVICInitstructure.NVIC_IRQChannelSubPriority=0x00;
	NVIC_Init(&NVICInitstructure);
}

void delay(uint32_t time){

	while(time--);

}

void EXTI0_IRQHandler(void){

	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{

		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_14 | GPIO_Pin_15);
		delay(16800000);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}

}

int main(void)
{

	gpioConfig();
	GPIO_ResetBits(GPIOD, GPIO_Pin_All);
	
	while(1)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_All);

	}
	
}
	
	
	
/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
