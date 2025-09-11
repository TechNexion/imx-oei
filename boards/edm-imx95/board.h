/*
 * Copyright 2023-2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BOARD_H
#define BOARD_H

#include "fsl_common.h"
#include "pin_mux.h"
#include "config_board.h"

/*!
 * @addtogroup BRD_OEI_EDM_IMX95
 * @{
 *
 * @file
 * @brief
 *
 * Header file containing the board API.
 */

/*******************************************************************************
 * Types
 ******************************************************************************/

/*!
 * Debug UART configuration info
 */
typedef struct
{
    LPUART_Type *const base;  /*!< LPUART base pointer */
    uint32_t clockId;         /*!< Clock ID */
    uint32_t baud;            /*!< Baud rate */
    uint8_t inst;             /*!< Instance number */
} board_uart_config_t;


/*******************************************************************************
 * BOARD_ID1   BOARD_ID0
 *     1            1       16G LPDDR5
 *     1            0       8G LPDDR5
 *     0            1       4G LPDDR5
 ******************************************************************************/
enum {
	LPDDR5_16GB = 0x3,
	LPDDR5_8GB = 0x2,
	LPDDR5_4GB = 0x1,
	LPDDR5_UNKNOWN = 0xf,
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

/*! Init hardware */
void BOARD_InitHardware(void);

/*! Init clocks */
void BOARD_InitClocks(void);

/*!
 * Get a device clock debug UART info.
 *
 * This function returns the UART info for the UART used for SM
 * debug.
 *
 * @return Returns the debug UART config info.
 */
const board_uart_config_t *BOARD_GetDebugUart(void);

/*! Init the debug UART */
void BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** @} */

#endif /* BOARD_H */
