
#include "stm32f4_hal.h"
#include "stm32f4_hal_lowlevel.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_cryp.h"

UART_HandleTypeDef UartHandle;

uint8_t hw_key[16];
static CRYP_HandleTypeDef cryp;

void platform_init(void)
{
	//HAL_Init();

#ifdef USE_INTERNAL_CLK
     RCC_OscInitTypeDef RCC_OscInitStruct;
     RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
     RCC_OscInitStruct.HSEState       = RCC_HSE_OFF;
     RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
     RCC_OscInitStruct.PLL.PLLSource  = RCC_PLL_NONE;
     HAL_RCC_OscConfig(&RCC_OscInitStruct);

     RCC_ClkInitTypeDef RCC_ClkInitStruct;
     RCC_ClkInitStruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
     RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_HSI;
     RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
     RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
     RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
     uint32_t flash_latency = 0;
     HAL_RCC_ClockConfig(&RCC_ClkInitStruct, flash_latency);
#else
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSEState       = RCC_HSE_BYPASS;
	RCC_OscInitStruct.HSIState       = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLSource  = RCC_PLL_NONE;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_ClkInitStruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_HSE;
	RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_ACR_LATENCY_5WS);
#endif
}

void init_uart(void)
{
	GPIO_InitTypeDef GpioInit;
	GpioInit.Pin       = GPIO_PIN_9 | GPIO_PIN_10;
	GpioInit.Mode      = GPIO_MODE_AF_PP;
	GpioInit.Pull      = GPIO_PULLUP;
	GpioInit.Speed     = GPIO_SPEED_FREQ_HIGH;
	GpioInit.Alternate = GPIO_AF7_USART1;
	__GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &GpioInit);

	UartHandle.Instance        = USART1;
	UartHandle.Init.BaudRate   = 38400;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	__USART1_CLK_ENABLE();
	HAL_UART_Init(&UartHandle);
}

void trigger_setup(void)
{
	GPIO_InitTypeDef GpioInit;
	GpioInit.Pin       = GPIO_PIN_12;
	GpioInit.Mode      = GPIO_MODE_OUTPUT_PP;
	GpioInit.Pull      = GPIO_NOPULL;
	GpioInit.Speed     = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GpioInit);
}

void trigger_high(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, SET);
}

void trigger_low(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);
}

char getch(void)
{
	uint8_t d;
	while (HAL_UART_Receive(&UartHandle, &d, 1, 5000) != HAL_OK);
	return d;
}

void putch(char c)
{
	uint8_t d  = c;
	HAL_UART_Transmit(&UartHandle,  &d, 1, 5000);
}

void HW_AES128_Init(void)
{
	cryp.Instance = CRYP;
	cryp.Init.DataType = CRYP_DATATYPE_8B;
	cryp.Init.KeySize = CRYP_KEYSIZE_128B;
	cryp.Init.pKey = hw_key;
  HW_AES128_LoadKey(hw_key);
  __HAL_RCC_CRYP_CLK_ENABLE();
	HAL_CRYP_Init(&cryp);
}

void HW_AES128_LoadKey(uint8_t* key)
{
	for(int i = 0; i < 16; i++)
	{
		cryp.Init.pKey[i] = key[i];
	}
}

void HW_AES128_Enc(uint8_t* pt)
{
	HAL_CRYP_Init(&cryp);
  HAL_CRYP_AESECB_Encrypt(&cryp, pt, 16, pt, 1000);
}

void HW_AES128_Dec(uint8_t *pt)
{
     HAL_CRYP_Init(&cryp);
     HAL_CRYP_AESECB_Decrypt(&cryp, pt, 16, pt, 1000);
}
