#pragma once
#include "variant.h"
#include "owner.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void* DLR_USER;

  //! Begin access to rt memory. After this call you can alter data returned in data.
  //! @param[out] data     Return pointer to the data
  //! @param[in]  revision Revision number of the data (matching with memory map)
  //! @result status of function call
  DLR_RESULT DLR_userBeginAccess(DLR_USER user, uint8_t** data, uint32_t revision);

  //! End access to rt memory.
  //! @result status of function call
  DLR_RESULT DLR_userEndAccess(DLR_USER user);

  //! Get size of memory
  //! @param[out] sizeBytes   Size of memory in bytes
  //! @result status of function call
  DLR_RESULT DLR_userGetSize(DLR_USER user, size_t* sizeBytes);

  //! Get type of memory
  //! @param[out] type   Type of memory in bytes
  //! @result status of function call
  DLR_RESULT DLR_userGetType(DLR_USER user, DLR_MEMORYTYPE* type);

  //! Get memory map
  //! @param[out] memMap   Memory map. It contains revision number for beginAccess.
  //! @result status of function call
  DLR_RESULT DLR_userGetMemoryMap(DLR_USER user, DLR_VARIANT memoryMap);

#ifdef __cplusplus
}
#endif
