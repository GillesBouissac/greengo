
typedef unsigned long   ulong;
typedef unsigned int    uint;

#define HISTORY_DEPTH   10
typedef struct {
    int idx;   // next idx
    int count; // total count of values read
    ulong values[HISTORY_DEPTH];
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


ulong analogReadSmooth(int pin, CircularBuffer* history);
ulong resampleAnalogInput(int pin, CircularBuffer* history);
uint updatePumpRpm(bool is_on);
uint updateLedBlinking(bool is_on);
void printvals(uint a,uint b,uint c);
void resampleAnalogInputs();

