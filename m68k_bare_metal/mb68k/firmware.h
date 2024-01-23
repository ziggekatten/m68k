/**
 * @author (c) Mats Brorson ()
 *             2023-2024, Sweden
 *
 * @brief Base firmware header for the BroCom m68k homebrew computer used to initialize
 * hardware and set up firmware stuff for parsing commands
 *
 *
 * @license The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef MB68K_FIRMWARE_H_
#define MB68K_FIRMWARE_H_

#include <stdint.h>
/* Struct used for serial data stuff*/
typedef struct serialstruct{
    char buf[65];  // One extra byte for '\0'
    uint8_t idx;
} serialstruct;

extern const char *prompt;
/* Prototype for function called by evt using enum: ioports */
void serialhandler(char);

#endif
