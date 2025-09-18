#pragma once
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum DLR_MEMORYTYPE
  {
    MemoryType_Unknown = 0,
    MemoryType_Input = 1,
    MemoryType_Output = 2,
    MemoryType_SharedRetain = 3,
    MemoryType_Shared = 4,
  }DLR_MEMORYTYPE;

  typedef void* DLR_OWNER;

  //! Begin access to rt memory. After this call you can alter data returned in data.
  //! @param[in]  owner      Owner of the memory
  //! @param[out] data       Return pointer to the data
  //! @param[in]  revision   Revision number of the data (matching with memory map)
  //! @result status of function call
  DLR_RESULT DLR_ownerBeginAccess(DLR_OWNER owner, uint8_t** data, uint32_t revision);

  //! End access to rt memory.
  //! @param[in]  owner      Owner of the memory
  //! @result status of function call
  DLR_RESULT DLR_ownerEndAccess(DLR_OWNER owner);

  //! Get size of memory
  //! @param[in]  owner      Owner of the memory
  //! @param[out] sizeBytes  Size of memory in bytes
  //! @result status of function call
  DLR_RESULT DLR_ownerGetSize(DLR_OWNER owner, size_t* sizeBytes);

  //! Get type of memory
  //! @param[in]  owner      Owner of the memory
  //! @param[out] type       Type of memory in bytes
  //! @result status of function call
  DLR_RESULT DLR_ownerGetType(DLR_OWNER owner, DLR_MEMORYTYPE* type);

  //! Get memory map
  //! @param[in]  owner      Owner of the memory
  //! @param[out] memMap     Memory map
  //! @result status of function call
  DLR_RESULT DLR_ownerGetMemoryMap(DLR_OWNER owner, DLR_VARIANT memoryMap);

  //! Set memory map of own memory
  //! @param[in]  owner      Owner of the memory
  //! @param[in]  memMap     Memory map
  //! @result status of function call
  DLR_RESULT DLR_ownerSetMemoryMap(DLR_OWNER owner, DLR_VARIANT memoryMap);

#ifdef __cplusplus
}
#endif
