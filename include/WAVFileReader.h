#ifndef __wav_file_reader_h__
#define __wav_file_reader_h__

#include <SPIFFS.h>
#include <FS.h>
#include "SampleSource.h"

class WAVFileReader : public SampleSource
{
private:
    int m_num_channels;
    int m_sample_rate;
    File m_file;
    bool m_circulation;

public:
    WAVFileReader(const char *file_name);
    ~WAVFileReader();
    uint32_t sampleRate() { return m_sample_rate; }
    int getFrames(Frame_t *frames, int number_frames);
};

#endif