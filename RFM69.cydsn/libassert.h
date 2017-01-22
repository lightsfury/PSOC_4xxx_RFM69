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

#ifndef libassert_h_
#define libassert_h_

#ifdef __cplusplus
extern "C" {
#endif

void assert_handler(const char* filename, int line_number,
                    const char* user_message);

#ifdef __cplusplus
};
#endif

#define RAISE_ASSERT() assert_handler(__FILE__, __LINE__, __FUNCTION__)
#define RAISE_ASSERT_WITH_MESSAGE(msg) assert_handler(__FILE__, __LINE__, msg)

#define ASSERT(expr) { if ( ( expr ) ) { RAISE_ASSERT(); } }
//#define ASSERT_NOT_NULL(ptr) { if ( ( ptr ) == 0 ) { RAISE_ASSERT(); } }
//#define ASSERT_NOT_EQUAL(n1, n2) { if ( ( n1 ) == ( n2 ) ) { RAISE_ASSERT(); } }
#define ASSERT_NOT_NULL(ptr) ASSERT( ( ( ptr ) == 0 ) )
#define ASSERT_NOT_EQUAL(n1, n2) ASSERT( ( ( n1 ) == ( n2 ) ) )
    
#endif // libassert_h_

/* [] END OF FILE */
