/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __XMC4500_CONF_H
#define __XMC4500_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Comment the line below to disable peripheral header file inclusion */

#include "XMC4000_misc.h"  /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

#include "xmc_common.h"
#include "xmc_scu.h"
#include "xmc_gpio.h"
#include "xmc_dma.h"
#include "xmc_i2c.h"
#include "xmc_uart.h"
#include "xmc_spi.h"
#include "xmc_ccu4.h"
#include "xmc_ccu8.h"
#include "xmc_flash.h"
#include "xmc_vadc.h"

typedef enum
{
  Bit_RESET = 0,
  Bit_SET
}BitAction;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __XMC4500_CONF_H */
