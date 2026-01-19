/*
 * Copyright 2023-2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "clock.h"
#include "oei.h"
#include "board.h"
#include "fsl_lpuart.h"
#include "fsl_ccm.h"
#include "fsl_clock.h"
#include "fsl_rgpio.h"

#ifdef SUPPORT_MULTI_DDR
extern char __data_start__ [];
extern char __data_size__ [];
extern char __data_load_start__ [];

void ddr_conf_init(void);
#endif

#if defined(DEBUG)
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Debug UART base pointer list */
static LPUART_Type *const s_uartBases[] = LPUART_BASE_PTRS;

/* Debug UART clock list */
static uint32_t const s_uartClks[] =
{
    0U,
    CLOCK_ROOT_LPUART1,
    CLOCK_ROOT_LPUART2,
    CLOCK_ROOT_LPUART3,
    CLOCK_ROOT_LPUART4,
    CLOCK_ROOT_LPUART5,
    CLOCK_ROOT_LPUART6,
    CLOCK_ROOT_LPUART7,
    CLOCK_ROOT_LPUART8
};

/* Debug UART configuration info */
static board_uart_config_t const s_uartConfig =
{
    .base = s_uartBases[BOARD_DEBUG_UART_INSTANCE],
    .clockId = s_uartClks[BOARD_DEBUG_UART_INSTANCE],
    .baud = BOARD_DEBUG_UART_BAUDRATE,
    .inst = BOARD_DEBUG_UART_INSTANCE
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*--------------------------------------------------------------------------*/
/* Return the debug UART info                                               */
/*--------------------------------------------------------------------------*/
const board_uart_config_t *BOARD_GetDebugUart(void)
{
    return &s_uartConfig;
}

/*--------------------------------------------------------------------------*/
/* Initialize debug console                                                 */
/*--------------------------------------------------------------------------*/
void BOARD_InitDebugConsole(void)
{
    if (s_uartConfig.base != NULL)
    {
#if 0
        uint64_t rate = CCM_RootGetRate(s_uartConfig.clockId);
#else
        uint64_t rate = 24000000;
#endif

        /* Configure debug UART */
        lpuart_config_t lpuart_config;
        LPUART_GetDefaultConfig(&lpuart_config);
        lpuart_config.baudRate_Bps = s_uartConfig.baud;
        lpuart_config.rxFifoWatermark = ((uint8_t)
            FSL_FEATURE_LPUART_FIFO_SIZEn(s_uartConfig.base)) - 1U;
        lpuart_config.txFifoWatermark = ((uint8_t)
            FSL_FEATURE_LPUART_FIFO_SIZEn(s_uartConfig.base)) - 1U;
        lpuart_config.enableTx = true;
        lpuart_config.enableRx = true;
        (void) LPUART_Init(s_uartConfig.base, &lpuart_config,
            (uint32_t) rate & 0xFFFFFFFFU);
    }
}
#endif /* DEBUG */

#ifdef SUPPORT_MULTI_DDR
static void _memcpy(void *dest, const void *src, size_t n)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;

    for (size_t i = 0; i < n; i++)
    {
        d[i] = s[i];
    }
}


static void _copy_data(void)
{
    if (&__data_start__[0] != &__data_load_start__[0])
    {
        _memcpy(__data_start__, __data_load_start__, (size_t) __data_size__);
    }
}
#endif

static void BOARD_DetectDDR(void)
{
    uint8_t ddrcode = 0;
    /* Initialize GPIOs for DRAM detection */
    rgpio_pin_config_t gpioConfig =
    {
        kRGPIO_DigitalInput,
        0U
    };

    RGPIO_PinInit(GPIO1, 8U, &gpioConfig);
    RGPIO_PinInit(GPIO1, 9U, &gpioConfig);

    uint8_t GPIO1_IO_BIT8_value = RGPIO_ReadPinInput(GPIO1, 8U);
    uint8_t GPIO1_IO_BIT9_value = RGPIO_ReadPinInput(GPIO1, 9U);

    ddrcode = GPIO1_IO_BIT8_value | (GPIO1_IO_BIT9_value << 1);

    switch (ddrcode)
    {
        case LPDDR5_4GB:
            printf("DDR Type: LPDDR5_4GB\n");
            break;
        case LPDDR5_8GB:
            printf("DDR Type: LPDDR5_8GB\n");
            break;
        case LPDDR5_16GB:
            printf("DDR Type: LPDDR5_16GB\n");
            break;
        default:
            printf("DDR Type: LPDDR5_UNKNOWN\n");
    }
#ifdef DDR_CONFIG_STR
    printf("Build-time DDR Config: %s\n", DDR_CONFIG_STR);
#endif
    Write32(OCRAM_NON_SECURE_BASE_ADDR, ddrcode);
}

/*--------------------------------------------------------------------------*/
/* Initialize board                                                         */
/*--------------------------------------------------------------------------*/
void BOARD_InitHardware(void)
{

#ifdef SUPPORT_MULTI_DDR
    _copy_data();
#endif

    Clock_Init();

#if defined(DEBUG)
    BOARD_InitPins();
    BOARD_InitDebugConsole();
#endif

    BOARD_DetectDDR();

#ifdef SUPPORT_MULTI_DDR
    ddr_conf_init();
#endif

}
