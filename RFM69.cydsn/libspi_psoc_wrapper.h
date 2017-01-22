/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef libspi_psoc_wrapper_h_
#define libspi_psoc_wrapper_h_

#include <stdint.h>
    
#include "libspi.h"
    
#define libspi_is_psoc_wrapper  0x8000

typedef struct libspi_psoc_wrapper
{
    void (*libspi_start)(void);
    void (*libspi_stop)(void);
    uint8_t (*libspi_read8)(void);
    void (*libspi_write8)(uint8_t);
} libspi_psoc_wrapper_t;

#ifdef __cplusplus
extern "C" {
#endif

void libspi_create_psoc(spi_t* psoc_dev,
                        void (*start)(void),
                        void (*stop)(void),
                        uint8_t (*read)(void),
                        void (*write)(uint8_t));

#ifdef __cplusplus
};
#endif

#endif // libspi_psoc_wrapper_h_

/* [] END OF FILE */
