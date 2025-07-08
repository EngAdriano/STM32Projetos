
#include "main.h"
#include "tim.h"
#include "gpio.h"

void SystemClock_Config(void);
void Delay_us(uint32_t us);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();

  // Configura PWM com: freq = 20kHz, dead time = 5us, fase = 25%
  PWMPhaseShift_Init(20000, 5, 25);

  while (1) {
    // Loop principal
  }
}

void PWMPhaseShift_Init(uint32_t freq_hz, uint32_t deadtime_us, uint8_t fase_percentual) {
  uint32_t timer_clk = 96000000;
  uint32_t arr = (timer_clk / freq_hz) - 1;
  uint32_t ccr = (arr + 1) / 2;

  TIM1->ARR = arr;
  TIM1->CCR1 = ccr;
  TIM1->BDTR = (TIM1->BDTR & ~TIM_BDTR_DTG_Msk) | ((deadtime_us * 96) & TIM_BDTR_DTG_Msk);
  TIM1->BDTR |= TIM_BDTR_MOE;

  TIM8->ARR = arr;
  TIM8->CCR1 = ccr;
  TIM8->BDTR = (TIM8->BDTR & ~TIM_BDTR_DTG_Msk) | ((deadtime_us * 96) & TIM_BDTR_DTG_Msk);
  TIM8->BDTR |= TIM_BDTR_MOE;

  // Inicia Par A (TIM1)
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

  // Fase
  uint32_t periodo_us = 1000000 / freq_hz;
  uint32_t fase_us = (periodo_us * fase_percentual) / 100;
  Delay_us(fase_us);

  // Inicia Par B (TIM8)
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim8, TIM_CHANNEL_1);
}

void Delay_us(uint32_t us) {
  uint32_t start = DWT->CYCCNT;
  uint32_t ticks = us * (SystemCoreClock / 1000000);
  while ((DWT->CYCCNT - start) < ticks);
}
