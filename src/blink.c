#include "stm32f10x.h"
#include <stdint.h>

void Delay(volatile uint32_t count)
{
    for (; count != 0; count--)
        ;
}

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    while (1)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
        Delay(500000);

        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        Delay(500000);
    }
}
