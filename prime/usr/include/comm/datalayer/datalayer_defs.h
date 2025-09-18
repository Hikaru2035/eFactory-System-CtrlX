#pragma once

#include "datalayer_version.h"
#include <stdint.h>
#include <string.h>


#ifndef DATALAYER_NAMESPACE
#define DATALAYER_XSTR(s) DATALAYER_STR(s)
#define DATALAYER_STR(s) #s

#define IDATALAYER_VERSION_MAJOR_STR DATALAYER_XSTR(IDATALAYER_VERSION_MAJOR)
#define IDATALAYER_VERSION_MINOR_STR DATALAYER_XSTR(IDATALAYER_VERSION_MINOR)
#define IDATALAYER_VERSION_PATCH_STR DATALAYER_XSTR(IDATALAYER_VERSION_PATCH)

#define DATALAYER_VERSION_CONCAT_EX(major,minor,patch)  v ## major ## _ ## minor ## _ ## patch
#define DATALAYER_VERSION_CONCAT(major,minor,patch) DATALAYER_VERSION_CONCAT_EX(major,minor,patch)
#define DATALAYER_VERSION_NAMESPACE inline namespace DATALAYER_VERSION_CONCAT(IDATALAYER_VERSION_MAJOR, IDATALAYER_VERSION_MINOR, IDATALAYER_VERSION_PATCH) {
#endif

//! Namespace for datalayer
namespace comm {
namespace datalayer {


//! Result data type for all function calls
struct DlResult
{

#include "c/datalayer_facility.h"

  // additional error codes can be added if they are useable for all components
  enum Value : uint32_t
  {
#define DL_ENUM_VALUE(id,value) id = value,
#include "c/datalayer_error_codes.h"
#undef DL_ENUM_VALUE
  };

  Value value;

  DlResult() = default;
  constexpr DlResult(Value result) : value(result) {}
  constexpr DlResult(uint32_t result) : value(static_cast<Value>(result)) {}
  
  friend inline bool operator==(const DlResult& lhs, const DlResult& rhs) {
    return lhs.value == rhs.value;
  }

  friend inline bool operator!=(const DlResult& lhs, const DlResult& rhs) {
    return lhs.value != rhs.value;
  }

  const char* toString() const 
  {
    switch (static_cast<uint32_t>(value))
    {
#define DL_ENUM_VALUE(id,value)    case Value::id: return (#id);
#include "c/datalayer_error_codes.h"
#undef DL_ENUM_VALUE
      default: return("unknown");
    }
  }
};

//! Return whether status code is an error status code
//! @param[in]  status     Status code
//! @return true if status code is an error status code
inline bool STATUS_FAILED(DlResult status)
{
  return (static_cast<uint32_t>(status.value) & (1 << 31));
}

//! Return whether status code is a successfull status code
//! @param[in]  status     Status code
//! @return true if status code is a successfull status code
inline bool STATUS_SUCCEEDED(DlResult status)
{
  return !STATUS_FAILED(status);
}

#if defined(_MSC_VER)
//! @brief save string cat (will not overwrite the destination)
//! @param[in]   dest pointer to the null-terminated byte string to append to
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   destSize the size of the destination buffer
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX).
inline int32_t stringcat_s(char* dest, size_t destSize, const char* src)
{
  return strncat_s(dest, destSize, src, _TRUNCATE);
}

//! @brief save string copy (will not overwrite the destination)
//! @param[in]   dest pointer to the character array to copy to
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   copyCount  maximum number of characters to copy
//! @param[in]   destSize the size of the destination buffer 
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX) and may clobber the rest of the destination array with unspecified values.
inline int32_t stringcpy_s(char* dest, size_t destSize, const char* src, size_t copyCount)
{
  return strncpy_s(dest, destSize, src, copyCount);
}
#else
//! @brief save string cat (will not overwrite the destination)
//! @param[in]   dest pointer to the null-terminated byte string to append to
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   destSize the size of the destination buffer
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX).
inline int32_t stringcat_s(char* dest, size_t destSize, const char* src)
{
  strncat(dest, src, destSize - strlen(dest) - 1);
  return 0;
}

//! @brief save string copy (will not overwrite the destination)
//! @param[in]   dest pointer to the character array to copy to
//! @param[in]   destSize the size of the destination buffer 
//! @param[in]   src    pointer to the character array to copy from
//! @param[in]   copyCount  maximum number of characters to copy
//! @return returns zero on success, returns non-zero on error. Also, on error, writes zero to dest[0] (unless dest is a null pointer or destsz is zero or greater than RSIZE_MAX) and may clobber the rest of the destination array with unspecified values.
inline int32_t stringcpy_s(char* dest, size_t destSize, const char* src, size_t copyCount)
{
  if (destSize < (copyCount + 1)) {
    copyCount = destSize;
  }
  strncpy(dest, src, copyCount);
  return 0;
}
#endif // _MSC_VER

}
}
