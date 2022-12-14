#ifndef _SAMPLE_SOURCE_H_
#define _SAMPLE_SOURCE_H_

#include <Arduino.h>

typedef struct
{
    // uint16_t left;
    // uint16_t right;

    // Frame data
    uint64_t data;
} Frame_t;

/**
 * Base class for our sample generators
 **/
class SampleSource
{
public:
    virtual ~SampleSource(){};
    virtual uint32_t sampleRate() = 0;
    // This should fill the samples buffer with the specified number of frames
    // A frame contains a LEFT and a RIGHT sample. Each sample should be signed 16 bits
    virtual int getFrames(Frame_t *frames, int number_frames) = 0;
    bool valid() { return isValid; }
protected:
    bool isValid = false;
};

#endif