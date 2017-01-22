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

#include "libspi.h"
#include "libassert.h"

#include <string.h>
#include "libspi_psoc_wrapper.h"

void libspi_psoc_default_start() __attribute__((weak));

void libspi_psoc_default_stop() __attribute__((weak));

void libspi_psoc_default_write(uint8_t data) __attribute__((weak));

uint8_t libspi_psoc_default_read() __attribute__((weak));

void libspi_init(spi_t* spi_dev)
{
    ASSERT_NOT_NULL(spi_dev);
    
    memset(spi_dev, 0, sizeof(spi_t));
}

void libspi_enable(spi_t* spi_dev, uint32_t enable)
{
    ASSERT_NOT_NULL(spi_dev);
    /* The SPI peripheral on the PSOC 4xxx is always on */
    (void)enable;
}

void libspi_start_transaction(spi_t* spi_dev)
{
    libspi_psoc_wrapper_t* wrapper = NULL;
    ASSERT_NOT_NULL(spi_dev);
    ASSERT_NOT_EQUAL(spi_dev->spi_transaction_counter, UINT32_MAX);
    
    if (0 == spi_dev->spi_transaction_counter)
    {
        if (0 == (spi_dev->spi_platform_flags & libspi_is_psoc_wrapper))
        {
            // Use default target
            libspi_psoc_default_start();
        }
        else
        {
            // Use wrapped target
            wrapper = (libspi_psoc_wrapper_t*)spi_dev->spi_addr;
        
            ASSERT_NOT_NULL(wrapper);
            
            wrapper->libspi_start();
        }
    }
    
    spi_dev->spi_transaction_counter += 1;
}

void libspi_stop_transaction(spi_t* spi_dev)
{
    libspi_psoc_wrapper_t* wrapper = NULL;
    ASSERT_NOT_NULL(spi_dev);
    ASSERT_NOT_EQUAL(spi_dev->spi_transaction_counter, 0);
    
    spi_dev->spi_transaction_counter -= 1;
    
    if (0 == spi_dev->spi_transaction_counter)
    {
        if (0 == (spi_dev->spi_platform_flags & libspi_is_psoc_wrapper))
        {
            // Use default target
            libspi_psoc_default_stop();
        }
        else
        {
            // Use wrapped target
            wrapper = (libspi_psoc_wrapper_t*)spi_dev->spi_addr;
        
            ASSERT_NOT_NULL(wrapper);
            
            wrapper->libspi_stop();
        }
    }
}

void libspi_write(spi_t* spi_dev, uint32_t data)
{
    libspi_psoc_wrapper_t* wrapper = NULL;
    ASSERT_NOT_NULL(spi_dev);
    ASSERT_NOT_EQUAL(spi_dev->spi_transaction_counter, 0);
    
    if (0 == (spi_dev->spi_platform_flags & libspi_is_psoc_wrapper))
    {
        // Use default target
        libspi_psoc_default_write((uint8_t)data);
    }
    else
    {
        // Use wrapped target
        wrapper = (libspi_psoc_wrapper_t*)spi_dev->spi_addr;
        
        ASSERT_NOT_NULL(wrapper);
        
        wrapper->libspi_write8((uint8_t)data);
    }
}

uint32_t libspi_read(spi_t* spi_dev)
{
    libspi_psoc_wrapper_t* wrapper = NULL;
    uint8_t data = 0;
    
    ASSERT_NOT_NULL(spi_dev);
    ASSERT_NOT_EQUAL(spi_dev->spi_transaction_counter, 0);
    
    if (0 == (spi_dev->spi_platform_flags & libspi_is_psoc_wrapper))
    {
        // Use default target
        data = libspi_psoc_default_read();
    }
    else
    {
        // Use wrapped target
        wrapper = (libspi_psoc_wrapper_t*)spi_dev->spi_addr;
        
        ASSERT_NOT_NULL(wrapper);
        
        data = wrapper->libspi_read8();
    }
    
    return data;
}



/* [] END OF FILE */
