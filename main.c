#include "stm32f4xx.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "stdbool.h"

//Ayni öncelik seviyesi olan 2 görev arasinda geçis.


bool KEY=1;

static void ledBir(void *params);
static void ledIki(void *params);
void gpio_Ayar(void);

TaskHandle_t task1=NULL;
TaskHandle_t task2=NULL;

void gpio_Ayar()
{


  //D12 Ayarlari
	RCC->AHB1ENR |=1<<3;  //D Clock Aktif.
	
	GPIOD->MODER  = 0x05000000; //Output modu
	GPIOD->OTYPER = 0x00000000; //Push-Pull
	GPIOD->OSPEEDR =0x0A000000; //Yuksek hiz
	GPIOD->BSRR =1<<28; //D12 low
	GPIOD->BSRR =1<<29; //D13 low
	
}

 void ledBir(void *params)
{
		for(;;)
	{
		if(KEY)
		{
		KEY=0;
		GPIOD->BSRR =1<<12; //D12 low
		GPIOD->BSRR =1<<13; //D13 low
		vTaskDelay(1000);
		KEY=1;
	  taskYIELD();
		
		
		}
		

	}
}

 void ledIki(void *params)
{
	for(;;)
	{
   if(KEY)
		{
		KEY=0;
		GPIOD->BSRR =1<<28; //D12 low
		GPIOD->BSRR =1<<29; //D13 low
		vTaskDelay(1000);
		KEY=1;
	  taskYIELD();
		
		
		}
		
	}

}

int main()
{
	
	SystemCoreClockUpdate();
	gpio_Ayar();
	xTaskCreate(ledBir,"GorevA",configMINIMAL_STACK_SIZE,NULL,3,&task1);//&task1
	xTaskCreate(ledIki,"GorevB",configMINIMAL_STACK_SIZE,NULL,3,&task2);//&task2
  vTaskStartScheduler();
	

while(1)
{

}
}
/*

Ayni öncelikte yapilacak.
if(KEY)
		{
		KEY=0;
		GPIOD->BSRR =1<<28; //D12 low
		GPIOD->BSRR =1<<29; //D13 low
		vTaskDelay(1000);
		KEY=1;
	  taskYIELD();
		
		
		}
*/
