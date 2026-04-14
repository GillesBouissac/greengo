/*
 * Copyright (c) 2026 Gilles Bouissac
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef cbuffer_hpp
#define cbuffer_hpp

#include "greengo_common.hpp"

#define BUFFER_SIZE   10
typedef struct {
    int idx;   // next idx
    int count; // total count of values read
    ulong values[BUFFER_SIZE];
} CircularBuffer;


/// @brief Initialises a CircularBuffer structure, setting all values to 0 and count to 0
/// @param buffer Buffer to reset
void CircularBufferInit(CircularBuffer* buffer);

/// @brief Checks if a CircularBuffer is empty
/// @param buffer Buffer to check
bool CircularBufferEmpty(CircularBuffer* buffer);

/// @brief Adds an element to the CircularBuffer
/// @param buffer Buffer to add element to
/// @param value Value to add
void CircularBufferAdd(CircularBuffer* buffer, ulong value);

/// @brief Computes the average of values in the CircularBuffer
/// @param buffer Buffer to average
/// @return The average value
ulong CircularBufferAverage(CircularBuffer* buffer);

/// @brief Gets the element at the specified index (0 = oldest)
/// @param buffer Buffer to get from
/// @param index Index of the element (0 to count-1)
/// @return The value at the index, or 0 if index out of range
ulong CircularBufferGet(CircularBuffer* buffer, int index);

#endif /* cbuffer_hpp */
