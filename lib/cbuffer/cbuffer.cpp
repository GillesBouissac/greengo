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
#include <stdio.h>
#include "cbuffer.hpp"

#define min(a,b) ((a)<(b)?(a):(b))

void CircularBufferInit(CircularBuffer* buffer) {
    buffer->idx = 0;
    buffer->count = 0;
    for (int i=0; i<BUFFER_SIZE; i++) {
        buffer->values[i] = 0;
    }
}

bool CircularBufferEmpty(CircularBuffer* buffer) {
    return buffer->count == 0;
}

void CircularBufferAdd(CircularBuffer* buffer, ulong value) {
    buffer->idx = (buffer->idx + 1) % BUFFER_SIZE;
    buffer->count = min(buffer->count+1, BUFFER_SIZE);
    buffer->values[buffer->idx] = value;
}

ulong CircularBufferAverage(CircularBuffer* buffer) {
    if (buffer->count == 0) return 0;
    int idx = buffer->idx;
    ulong sum = 0;
    for (int i = 0; i < buffer->count; i++) {
        sum += buffer->values[idx];
        idx = (idx - 1 + BUFFER_SIZE) % BUFFER_SIZE;
    }
    return sum / buffer->count;
}

ulong CircularBufferGet(CircularBuffer* buffer, int index) {
    if (index < 0 || index >= buffer->count) return 0;
    int idx = (buffer->idx - buffer->count + 1 + index + BUFFER_SIZE) % BUFFER_SIZE;
    return buffer->values[idx];
}
