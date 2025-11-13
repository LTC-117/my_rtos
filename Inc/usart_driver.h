#ifndef __USART_DRIVER_H__
#define __USART_DRIVER_H__


#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_usart.h"


USART_HandleTypeDef usart_tx_rx_init(USART_TypeDef *usart_module, uint32_t baud_rate);
void usart_write(USART_HandleTypeDef *huart, char *message);


#endif
