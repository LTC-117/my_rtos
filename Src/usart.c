#include "usart.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_usart.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f103xb.h"

#include <stdint.h>


/* USART1_CK -> PA8*/
/* USART1_TX -> PA9 */
/* USART1_RX -> PA10 */
/* USART1_CTS -> PA11 */
/* USART1_RTS -> PA12 */


#define SYS_FREQ        16000000
#define USART_BR        115200


static uint32_t usart_compute_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
    return (periph_clk + (baudrate / 2U)) / baudrate;
}


void usart_tx_rx_init(void)
{
    /* ---------- Initializing GPIO pins ---------- */
    // Init tx pin (PA9)
    GPIO_InitTypeDef usart1_tx = {
        .Pin = GPIO_PIN_9,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM
    };

    // Init rx pin (PA10)
    GPIO_InitTypeDef usart1_rx = {
        .Pin = GPIO_PIN_10,
        .Mode = GPIO_MODE_AF_INPUT,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM
    };

    HAL_GPIO_Init(GPIOA, &usart1_tx);
    HAL_GPIO_Init(GPIOA, &usart1_rx);

    __HAL_RCC_USART1_CLK_ENABLE();

    /* ---------- Configuring USART1 ---------- */

    // USART1 Handle
    USART_InitTypeDef usart_driver = {
        .BaudRate = 115200,
        .WordLength = USART_WORDLENGTH_8B,
        .StopBits = USART_STOPBITS_1,
        .Parity = USART_PARITY_NONE,
        .Mode = USART_MODE_TX_RX,
    };

    USART_HandleTypeDef usart1 = {
        .Instance = USART1,
        .Init = usart_driver,
    };

    HAL_USART_Init(&usart1);
}
