#pragma once

#include <cstdlib>

using byte = unsigned char;

/*! Default (and also a sample) class of Memory strategy */
class MemoryHeapStrategy
{
public:

  /*! Allocate memory method
   * \param[in] Amount amount of bytes to allocate
   * \returns pointer on allocated memory
   */
  byte * alloc(size_t Amount)
  {
    return (byte *)malloc(Amount);
  }

  /*! Decallocate memory method
   * \param[in] Data pointer on allocated data
   */
  void dealloc(byte *Data)
  {
    free(Data);
  }
};