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
