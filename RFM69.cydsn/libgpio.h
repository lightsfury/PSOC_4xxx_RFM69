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

#ifndef libgpio_h_
#define libgpio_h_

#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

typedef struct gpio_t
{
    union
    {
        uint32_t gpio_id;
        uintptr_t gpio_addr;
    };
} gpio_t;

enum libgpio_mode
{
    libgpio_mode_disable = 0,
    libgpio_mode_enable = 1
};

enum libgpio_pin_direction
{
    libgpio_pin_direction_in = 0,
    libgpio_pin_direction_out = 1
};

enum libgpio_pin_state
{
    libgpio_pin_state_low = 0,
    libgpio_pin_state_high = 1
};

/**
    Initialize a gpio_t structure to the default state.
**/
void libgpio_init(gpio_t* gpio_bank);

/**
    Enable or disable a GPIO pin.
    @param enable Disable when 0, enable otherwise.
**/
void libgpio_enable_pin(gpio_t* gpio_bank, uint32_t gpio_pin_mask,
                        uint32_t enable);

/**
    Set a GPio pin as input or output.
    @param direction Input when 0, output when 1. Undefined otherwise.
**/
void libgpio_set_pin_direction(gpio_t* gpio_bank, uint32_t gpio_pin_number,
                               uint32_t direction);

/**
    Read data from a GPIO pin.
    @return Return @link libgpio_pin_state_high; when positive logic high, @link libgpio_pin_state_low; otherwise.
**/
uint32_t libgpio_read_pin(gpio_t* gpio_bank, uint32_t gpio_pin_number);

/**
    Set the positive logic state of a GPIO pin.
    @param state Logic low when 0, logic high otherwise.
**/
void libgpio_write_pin(gpio_t* gpio_bank, uint32_t gpio_pin_number,
                       uint32_t state);

#if __cplusplus
};
#endif

#endif // libgpio_h_

/* [] END OF FILE */
