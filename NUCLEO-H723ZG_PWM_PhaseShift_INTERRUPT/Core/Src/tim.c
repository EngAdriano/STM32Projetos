
#include "tim.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim8;

void MX_TIM1_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 72 - 1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 2000 - 1;
    HAL_TIM_OC_Init(&htim1);

    sConfigOC.OCMode = TIM_OCMODE_TIMING;
    sConfigOC.Pulse = htim1.Init.Period / 4;
    HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_OC2REF;
    HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
}

void MX_TIM8_Init(void)
{
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim8.Instance = TIM8;
    htim8.Init.Prescaler = 72 - 1;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 2000 - 1;
    HAL_TIM_PWM_Init(&htim8);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = htim8.Init.Period / 2;
    HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1);

    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
    sSlaveConfig.InputTrigger = TIM_TS_ITR0;
    HAL_TIM_SlaveConfigSynchronization(&htim8, &sSlaveConfig);
}
