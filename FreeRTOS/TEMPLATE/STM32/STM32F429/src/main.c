
#include "stm32f4xx.h"
			
#include "FreeRTOS.h"
#include "task.h"

static void prvSetupHardware(void);

int main(void) {

	// Hardware configuration
	prvSetupHardware();

	// Creating tasks
	// ..
	// ..

	// Start the scheduler
	vTaskStartScheduler(); // should never return

	// Will only get here if there was not enough heap space

	while(1);

	return 0;
}

static void prvSetupHardware(void)
{
	// It's place to hardware configuration, like e.g. clock external source

	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	RCC_WaitForHSEStartUp(); // while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != SET );

	RCC_PLLConfig(RCC_PLLSource_HSE,8,360,2,8);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET );

	FLASH_PrefetchBufferCmd(ENABLE);
	FLASH_SetLatency(FLASH_Latency_5 );

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while( RCC_GetSYSCLKSource() != 0x08 );

	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_PCLK2Config(RCC_HCLK_Div2);
}
