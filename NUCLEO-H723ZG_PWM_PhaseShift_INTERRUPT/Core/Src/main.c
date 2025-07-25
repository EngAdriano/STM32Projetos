
#include "main.h"
#include "tim.h"

volatile uint8_t apply_new_phase = 0;
volatile uint32_t phase_ticks = 0;

void SetPhaseShiftPercent(float percent)
{
    if (percent < 0.f) percent = 0.f;
    if (percent > 100.f) percent = 100.f;
    uint32_t arr = TIM8->ARR + 1;
    phase_ticks = (uint32_t)((percent / 100.f) * arr);
    apply_new_phase = 1;
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_TIM1_Init();
    MX_TIM8_Init();

    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);

    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);

    HAL_Delay(2000);
    SetPhaseShiftPercent(25.f);

    while (1)
    {
        HAL_Delay(5000);
        float next = (rand() % 101);
        SetPhaseShiftPercent(next);
    }
}
