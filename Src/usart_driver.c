#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_usart.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f103xb.h"
#include <stdint.h>
#include "mystring.h"

#include "usart_driver.h"


USART_HandleTypeDef usart_tx_rx_init(USART_TypeDef *usart_module, uint32_t baud_rate)
{
    if (usart_module != USART1 &&
        usart_module != USART2 &&
        usart_module != USART3) {
            Error_Handler();
    }

    /* ---------- Initializing GPIO pins ---------- */

    uint32_t usart_tx_pin =
        (usart_module == USART1)
        ? GPIO_PIN_9  :
        (usart_module == USART2)
        ? GPIO_PIN_2  :
        (usart_module == USART3) // USART3 uses GPIOB, not GPIOA like 1 and 2.
        ? GPIO_PIN_10 :
        0;

    uint32_t usart_rx_pin =
        (usart_module == USART1)
        ? GPIO_PIN_10 :
        (usart_module == USART2)
        ? GPIO_PIN_3  :
        (usart_module == USART3) // USART3 uses GPIOB, not GPIOA like 1 and 2.
        ? GPIO_PIN_11 :
        0;

    // Init tx pin (PA9)
    GPIO_InitTypeDef usart_tx = {
        .Pin = usart_tx_pin,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM
    };

    // Init rx pin (PA10)
    GPIO_InitTypeDef usart_rx = {
        .Pin = usart_rx_pin,
        .Mode = GPIO_MODE_AF_INPUT,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM
    };

    if (usart_module == USART1 || usart_module == USART2) {
        HAL_GPIO_Init(GPIOA, &usart_tx);
        HAL_GPIO_Init(GPIOA, &usart_rx);
    } else {
        HAL_GPIO_Init(GPIOB, &usart_tx);
        HAL_GPIO_Init(GPIOB, &usart_rx);
    }

    __HAL_RCC_USART1_CLK_ENABLE();

    /* ---------- Configuring USART1 ---------- */

    // USART1 Handle
    USART_InitTypeDef usart_driver = {
        .BaudRate = baud_rate,
        .WordLength = USART_WORDLENGTH_8B,
        .StopBits = USART_STOPBITS_1,
        .Parity = USART_PARITY_NONE,
        .Mode = USART_MODE_TX_RX,
    };

    USART_HandleTypeDef husart = {
        .Instance = usart_module,
        .Init = usart_driver,
    };

    if (HAL_USART_Init(&husart) != HAL_OK) {
        Error_Handler();
    }

    return husart;
}


void usart_write(USART_HandleTypeDef *husart, char *message)
{
    HAL_USART_Transmit(husart, (uint8_t *)message, mystrlen(message), HAL_MAX_DELAY);
}
