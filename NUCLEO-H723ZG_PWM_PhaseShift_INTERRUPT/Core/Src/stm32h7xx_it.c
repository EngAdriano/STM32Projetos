
#include "main.h"

extern TIM_HandleTypeDef htim1;

void TIM1_UP_IRQHandler(void)
{
    if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_UPDATE))
    {
        __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);
        extern uint8_t apply_new_phase;
        extern uint32_t phase_ticks;
        if (apply_new_phase)
        {
            TIM8->CNT = phase_ticks;
            apply_new_phase = 0;
        }
    }
}
