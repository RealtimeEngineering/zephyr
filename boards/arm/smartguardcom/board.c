/*
 * Copyright (c) 2021 RealTime Engineering AG
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <soc.h>
#include <stm32h7xx_hal_gpio.h>

static int board_smartguardcom_init(const struct device *dev)
{
	ARG_UNUSED(dev);
//	LL_GPIO_InitTypeDef     GPIO_InitStruct;
//
//	/* Workaround to release ethernet reset line */
//	GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
//	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
//	LL_GPIO_Init(GPIOE, &GPIO_InitStruct);
//	LL_GPIO_SetOutputPin(GPIOE,LL_GPIO_PIN_12);
//	/* Workaround to release Wifi reset line */
//	GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
//	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
//	LL_GPIO_Init(GPIOE, &GPIO_InitStruct);
//	LL_GPIO_SetOutputPin(GPIOE,LL_GPIO_PIN_4);
//	/* Workaround to set error LED */
//	GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
//	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
//	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//	LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_8);

	GPIO_InitTypeDef     GPIO_InitStruct;
	/* Workaround to set error LED */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	//GPIO_InitStruct.Alternate = GPIO_AF_0;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);

	return 0;
}

SYS_INIT(board_smartguardcom_init, PRE_KERNEL_2,
	 CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
