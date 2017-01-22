/*******************************************************************************
 * Copyright 2017 Robert J Beam
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
*******************************************************************************/

#ifndef libspi_h_
#define libspi_h_
    
#include "libgpio.h"
    
#ifdef __cplusplus
extern "C" {
#endif

typedef struct spi_t
{
    union
    {
        uint32_t spi_id;
        uintptr_t spi_addr;
    };
    /* Platform specific flags */
    uint32_t spi_platform_flags;
    /* Include nSS GPIO information for
     * platforms that need it (i.e. STM32)
     */
    gpio_t* spi_nss_gpio_bank;
    uint32_t spi_nss_gpio_pin_number;
    
    uint32_t spi_transaction_counter;
    
#ifndef libspi_no_soft_buffers
    /* SPI soft-buffers */
    uint8_t spi_tx_buffer[16];
    uint8_t spi_rx_buffer[16];
    uint8_t spi_tx_buffer_index;
    uint8_t spi_rx_buffer_index;
#endif
} spi_t;

enum libspi_mode
{
    libspi_mode_disable = 0,
    libspi_mode_enable = 1
};

/**
    Initialize an spi_t structure to the default state.
**/
void libspi_init(spi_t* spi_dev);

/**
    Enable/Disable an SPI device.
    @param enable Disable when 0, enable otherwise.
**/
void libspi_enable(spi_t* spi_dev, uint32_t enable);

/**
    Increment the transaction counter.
    Assert the nSS signal (peripheral or GPIO) when counter becomes greater than 0.
**/
void libspi_start_transaction(spi_t* spi_dev);

/**
    Decrement the transaction counter.
    Deassert the nSS signal when counter becomes equal to 0.
**/
void libspi_stop_transaction(spi_t* spi_dev);

/**
    Enqueue @p data; onto the SPI transmit FIFO.
    @note Platforms should leverage hardware FIFOs when available.
**/
void libspi_write(spi_t* spi_dev, uint32_t data);

/**
    Dequeue data from the SPI receive FIFO.
    @note Platforms should leverage hardware FIFOs when available.
**/
uint32_t libspi_read(spi_t* spi_dev);

#ifdef __cplusplus
};
#endif

#endif // libspi_h_

/* [] END OF FILE */
