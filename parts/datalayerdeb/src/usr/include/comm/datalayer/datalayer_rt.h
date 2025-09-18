#pragma once
#include "datalayer_defs.h"
#include "memory_generated.h"
#include "memory_map_generated.h"
#include "datalayer_types.h"
#include "variant.h"

namespace comm
{
namespace datalayer
{

#define DL_RT_CHECK_REVISION            (uint8_t*)(0x0000C0EC)   //! Magic for only check revision in rt_user->beginAccess()
#define DL_RT_NON_BLOCKING              (uint8_t*)(0x0000A0EC)   //! Magic for non blocking rt->beginAccess() - returns DL_RT_WOULD_BLOCK in case of blocking

//! Memory Owner interface
//! All member functions are real time capable
class IMemoryOwner {
public:
  IMemoryOwner() = default;
  virtual ~IMemoryOwner() = default;

  //! Begin access to rt memory. After this call you can alter data returned in data.
  //! @param[out] data      Return pointer to the data
  //! @param[in]  revision  Revision number of the data (matching with memory map)
  //! @result status of function call
  virtual DlResult beginAccess(uint8_t*& data, uint32_t revision) = 0;

  //! End access to rt memory.
  //! @result status of function call
  virtual DlResult endAccess() = 0;

  //! Get size of memory
  //! @param[out] sizeBytes   Size of memory in bytes
  //! @result status of function call
  virtual DlResult getSize(size_t& sizeBytes) const = 0;

  //! Get type of memory
  //! @param[out] type   Type of memory in bytes
  //! @result status of function call
  virtual DlResult getType(MemoryType& type) const = 0;

  //! Get memory map
  //! @param[out] memMap   Memory map
  //! @result status of function call
  virtual DlResult getMemoryMap(Variant &memMap) = 0;

  //! Set memory map of own memory
  //! @param[in] memMap   Memory map
  //! @result status of function call
  virtual DlResult setMemoryMap(const Variant &memoryMap) = 0;
};

//! Memory User interface
//! all member functions are real time capable
class IMemoryUser {
public:
  IMemoryUser() = default;
  virtual ~IMemoryUser() = default;

  //! Begin access to rt memory. After this call you can alter data returned in data.
  //! @param[out] data     Return pointer to the data
  //! @param[in]  revision Revision number of the data (matching with memory map)
  //! @result status of function call
  virtual DlResult beginAccess(uint8_t*& data, uint32_t revision) = 0;

  //! End access to rt memory.
  //! @result status of function call
  virtual DlResult endAccess() = 0;

  //! Get size of memory
  //! @param[out] sizeBytes   Size of memory in bytes
  //! @result status of function call
  virtual DlResult getSize(size_t& sizeBytes) = 0;

  //! Get type of memory
  //! @param[out] type   Type of memory in bytes
  //! @result status of function call
  virtual DlResult getType(MemoryType& type) = 0;

  //! Get memory map
  //! @param[out] memMap   Memory map. It contains revision number for beginAccess.
  //! @result status of function call
  virtual DlResult getMemoryMap(Variant &memMap) = 0;
};

}
}
