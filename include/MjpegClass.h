#ifndef _MJPEGCLASS_H_
#define _MJPEGCLASS_H_

#pragma GCC optimize("O3")

#define READ_BUFFER_SIZE 4096

#include <esp_heap_caps.h>
#include "lvgl.h"
#include "tjpgdClass.h"
#include "ui.h"

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class MjpegClass
{
public:
  bool setup(const char *fileName, uint8_t *mjpeg_buf, LGFX_Device *tft, bool multiTask, int32_t tftWidth, int32_t tftHeight)
  {
    _fileName = fileName;
    _input_op_result = lv_fs_open(&_input, fileName, LV_FS_MODE_RD);
    if (_input_op_result != LV_FS_RES_OK)
    {
      ESP_LOGE("setup", "Unable to open video file! Result was lv_fs_res_t:: %d", _input_op_result);
      return false;
    }

    _mjpeg_buf = mjpeg_buf;
    _tft = tft;
    _multiTask = multiTask;

    _mjpeg_buf_offset = 0;
    _inputindex = 0;
    _remain = 0;

    _tft_width = tftWidth;
    _tft_height = tftHeight;

    _read_buf = (uint8_t *)malloc(READ_BUFFER_SIZE);
    if (!_read_buf)
    {
      ESP_LOGE("setup", "Read Buffer allocate failed!");
      return false;
    }

    _out_buf = (uint8_t *)heap_caps_malloc(_tft_width * 16 * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    if (!_out_buf)
    {
      ESP_LOGE("setup", "Jpeg codec out buffer malloc failed!");
      return false;
    }

    if (_multiTask)
    {
      _jdec.multitask_begin();
    }

    _is_file_picture = isFilePicture();
    _is_file_read = false;
    _is_file_drawn = false;

    _ready = true;

    return true;
  }

  bool readMjpegBuf()
  {
    if (_is_file_picture && _is_file_read)
    {
      return true;
    }

    if (_inputindex == 0)
    {
      _input_op_result = lv_fs_read(&_input, _read_buf, READ_BUFFER_SIZE, &_buf_read);
      if (_input_op_result != LV_FS_RES_OK)
      {
        return false;
      }

      _inputindex += _buf_read;
    }
    _mjpeg_buf_offset = 0;
    int i = 3;
    bool found_FFD9 = false;
    if (_buf_read > 0)
    {
      i = 3;
      while ((_buf_read > 0) && (!found_FFD9))
      {
        if ((_mjpeg_buf_offset > 0) && (_mjpeg_buf[_mjpeg_buf_offset - 1] == 0xFF) && (_read_buf[0] == 0xD9)) // JPEG trailer
        {
          found_FFD9 = true;
        }
        else
        {
          while ((i < _buf_read) && (!found_FFD9))
          {
            if ((_read_buf[i] == 0xFF) && (_read_buf[i + 1] == 0xD9)) // JPEG trailer
            {
              found_FFD9 = true;
              ++i;
            }
            ++i;
          }
        }

        // Serial.printf("i: %d\n", i);
        memcpy(_mjpeg_buf + _mjpeg_buf_offset, _read_buf, i);
        _mjpeg_buf_offset += i;
        size_t o = _buf_read - i;
        if (o > 0)
        {
          // Serial.printf("o: %d\n", o);
          memcpy(_read_buf, _read_buf + i, o);
          // _buf_read = _input.read(_read_buf + o, READ_BUFFER_SIZE - o);
          lv_fs_read(&_input, _read_buf + o, READ_BUFFER_SIZE - o, &_buf_read);
          _inputindex += _buf_read;
          _buf_read += o;
          // Serial.printf("_buf_read: %d\n", _buf_read);
        }
        else
        {
          // _buf_read = _input.read(_read_buf, READ_BUFFER_SIZE);
          lv_fs_read(&_input, _read_buf, READ_BUFFER_SIZE, &_buf_read);
          _inputindex += _buf_read;
        }
        i = 0;
      }
      if (found_FFD9)
      {
        _is_file_read = true;
        return true;
      }
    }

    return false;
  }

  bool drawJpg()
  {
    if (_is_file_picture && _is_file_drawn)
    {
      return true;
    }

    _fileindex = 0;
    _remain = _mjpeg_buf_offset;

    TJpgD::JRESULT jres = _jdec.prepare(jpgRead, this);
    if (jres != TJpgD::JDR_OK)
    {
      ESP_LOGE("drawJpg", "prepare failed! %d", jres);
      return false;
    }

    _out_width = std::min<int32_t>(_jdec.width, _tft_width);
    _jpg_x = (_tft_width - _jdec.width) >> 1;
    if (0 > _jpg_x)
    {
      _off_x = -_jpg_x;
      _jpg_x = 0;
    }
    else
    {
      _off_x = 0;
    }
    _out_height = std::min<int32_t>(_jdec.height, _tft_height);
    _jpg_y = (_tft_height - _jdec.height) >> 1;
    if (0 > _jpg_y)
    {
      _off_y = -_jpg_y;
      _jpg_y = 0;
    }
    else
    {
      _off_y = 0;
    }

    if (_multiTask)
    {
      jres = _jdec.decomp_multitask(jpgWrite16, jpgWriteRow);
    }
    else
    {
      jres = _jdec.decomp(jpgWrite16, jpgWriteRow);
    }

    if (jres != TJpgD::JDR_OK)
    {
      ESP_LOGE("drawJpg", "decomp failed! %d", jres);
      return false;
    }

    _is_file_drawn = true;
    return true;
  }

  bool reload()
  {
    if (_is_file_picture)
    {
      return true;
    }

    lv_fs_seek(&_input, 0, LV_FS_SEEK_SET);
    _inputindex = 0;
    return true;
  }

  bool switchFile(const char *fileName)
  {
    _fileName = fileName;
    lv_fs_close(&_input);
    _input_op_result = lv_fs_open(&_input, fileName, LV_FS_MODE_RD);
    if (_input_op_result != LV_FS_RES_OK)
    {
      ESP_LOGE("switchFile", "Unable to open video file!");
      return false;
    }

    _inputindex = 0;

    _is_file_picture = isFilePicture();
    _is_file_read = false;
    _is_file_drawn = false;

    return true;
  }

  bool ready()
  {
    return _ready;
  }

  void pause()
  {
    _jdec.pause_multitask();
    _ready = false;
  }

  void resume()
  {
    _jdec.resume_multitask();
    _ready = true;
  }

private:
  String _fileName;
  lv_fs_file_t _input;
  lv_fs_res_t _input_op_result;
  uint8_t *_read_buf;
  uint8_t *_mjpeg_buf;
  int32_t _mjpeg_buf_offset = 0;

  /* For jpg pictures */
  bool _is_file_picture = false;
  bool _is_file_read = false;
  bool _is_file_drawn = false;

  /* Status Flag */
  bool _ready = false;

  LGFX_Device *_tft;
  bool _multiTask;
  uint8_t *_out_buf;
  TJpgD _jdec;

  int32_t _inputindex = 0;
  uint32_t _buf_read;
  int32_t _remain = 0;
  uint32_t _fileindex;

  int32_t _tft_width;
  int32_t _tft_height;
  int32_t _out_width;
  int32_t _out_height;
  int32_t _off_x;
  int32_t _off_y;
  int32_t _jpg_x;
  int32_t _jpg_y;

  bool isFilePicture()
  {
    return _fileName.endsWith(".jpg") || _fileName.endsWith(".jpeg");
  }

  static uint32_t jpgRead(TJpgD *jdec, uint8_t *buf, uint32_t len)
  {
    MjpegClass *me = (MjpegClass *)jdec->device;
    if (len > me->_remain)
      len = me->_remain;
    if (buf)
    {
      memcpy(buf, (const uint8_t *)me->_mjpeg_buf + me->_fileindex, len);
    }
    me->_fileindex += len;
    me->_remain -= len;
    return len;
  }

  // for 16bit color panel
  static uint32_t jpgWrite16(TJpgD *jdec, void *bitmap, TJpgD::JRECT *rect)
  {
    MjpegClass *me = (MjpegClass *)jdec->device;

    uint16_t *dst = (uint16_t *)me->_out_buf;

    uint_fast16_t x = rect->left;
    uint_fast16_t y = rect->top;
    uint_fast16_t w = rect->right + 1 - x;
    uint_fast16_t h = rect->bottom + 1 - y;
    uint_fast16_t outWidth = me->_out_width;
    uint_fast16_t outHeight = me->_out_height;
    uint8_t *src = (uint8_t *)bitmap;
    uint_fast16_t oL = 0, oR = 0;

    if (rect->right < me->_off_x)
      return 1;
    if (x >= (me->_off_x + outWidth))
      return 1;
    if (rect->bottom < me->_off_y)
      return 1;
    if (y >= (me->_off_y + outHeight))
      return 1;

    if (me->_off_y > y)
    {
      uint_fast16_t linesToSkip = me->_off_y - y;
      src += linesToSkip * w * 3;
      h -= linesToSkip;
    }

    if (me->_off_x > x)
    {
      oL = me->_off_x - x;
    }
    if (rect->right >= (me->_off_x + outWidth))
    {
      oR = (rect->right + 1) - (me->_off_x + outWidth);
    }

    int_fast16_t line = (w - (oL + oR));
    dst += oL + x - me->_off_x;
    src += oL * 3;
    do
    {
      int i = 0;
      do
      {
        uint_fast8_t r8 = src[i * 3 + 0] & 0xF8;
        uint_fast8_t g8 = src[i * 3 + 1];
        uint_fast8_t b5 = src[i * 3 + 2] >> 3;
        r8 |= g8 >> 5;
        g8 &= 0x1C;
        b5 = (g8 << 3) + b5;
        dst[i] = r8 | b5 << 8;
      } while (++i != line);
      dst += outWidth;
      src += w * 3;
    } while (--h);

    return 1;
  }

  static uint32_t jpgWriteRow(TJpgD *jdec, uint32_t y, uint32_t h)
  {
    MjpegClass *me = (MjpegClass *)jdec->device;

    if (y == 0)
    {
      me->_tft->setAddrWindow(me->_jpg_x, me->_jpg_y, jdec->width, jdec->height);
    }

    me->_tft->pushPixelsDMA((uint16_t *)me->_out_buf, me->_out_width * h);

    return 1;
  }
};

#endif // _MJPEGCLASS_H_