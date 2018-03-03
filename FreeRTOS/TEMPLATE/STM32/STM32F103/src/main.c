
#include "stm32f10x.h"

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
}
