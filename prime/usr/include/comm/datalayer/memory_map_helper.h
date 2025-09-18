#pragma once

#include "datalayer.h"
#include "memory_map_generated.h"
#include <map>

//! Namespace for datalayer
namespace comm {
namespace datalayer {
DATALAYER_VERSION_NAMESPACE

//! Helper class for providers
class MemoryMapHelper
{
public:
  static bool equalTypes(const std::string type1, VariantType type2)
  {
    return toVariantType(type1) == type2;
  }

  static VariantType toVariantType(std::string type)
  {
    static std::map<std::string, VariantType> mapTypes = {
      {TYPE_DL_BOOL8, VariantType::BOOL8},
      {TYPE_DL_INT8, VariantType::INT8},
      {TYPE_DL_UINT8, VariantType::UINT8},
      {TYPE_DL_INT16, VariantType::INT16},
      {TYPE_DL_UINT16, VariantType::UINT16},
      {TYPE_DL_INT32, VariantType::INT32},
      {TYPE_DL_UINT32, VariantType::UINT32},
      {TYPE_DL_INT64, VariantType::INT64},
      {TYPE_DL_UINT64,  VariantType::UINT64},
      {TYPE_DL_FLOAT32, VariantType::FLOAT32},
      {TYPE_DL_FLOAT64, VariantType::FLOAT64},
    
      {TYPE_DL_STRING, VariantType::STRING },
      {TYPE_DL_ARRAY_OF_BOOL8, VariantType::ARRAY_OF_BOOL8 },
      {TYPE_DL_ARRAY_OF_INT8, VariantType::ARRAY_OF_INT8 },
      {TYPE_DL_ARRAY_OF_UINT8, VariantType::ARRAY_OF_UINT8 },
      {TYPE_DL_ARRAY_OF_INT16, VariantType::ARRAY_OF_INT16 },
      {TYPE_DL_ARRAY_OF_UINT16, VariantType::ARRAY_OF_UINT16 },
      {TYPE_DL_ARRAY_OF_INT32, VariantType::ARRAY_OF_INT32 },
      {TYPE_DL_ARRAY_OF_UINT32, VariantType::ARRAY_OF_UINT32 },
      {TYPE_DL_ARRAY_OF_INT64, VariantType::ARRAY_OF_INT64 },
      {TYPE_DL_ARRAY_OF_UINT64, VariantType::ARRAY_OF_UINT64 },
      {TYPE_DL_ARRAY_OF_FLOAT32, VariantType::ARRAY_OF_FLOAT32 },
      {TYPE_DL_ARRAY_OF_FLOAT64, VariantType::ARRAY_OF_FLOAT64 },
      {TYPE_DL_ARRAY_OF_STRING,  VariantType::ARRAY_OF_STRING },
      {TYPE_DL_RAW, VariantType::RAW },
      {TYPE_DL_TIMESTAMP,  VariantType::TIMESTAMP },
      {TYPE_DL_ARRAY_OF_TIMESTAMP,  VariantType::ARRAY_OF_TIMESTAMP },
      {TYPE_DL_EMPTY,  VariantType::EMPTY },

      {TYPE_PLC_BIT, VariantType::BOOL8 },
      {TYPE_PLC_BOOL, VariantType::BOOL8 },
      {TYPE_PLC_BYTE, VariantType::UINT8 },
      {TYPE_PLC_WORD, VariantType::UINT16 },
      {TYPE_PLC_DWORD, VariantType::UINT32 },
      {TYPE_PLC_LWORD, VariantType::UINT64 },
      {TYPE_PLC_SINT, VariantType::INT8 },
      {TYPE_PLC_USINT, VariantType::UINT8 },
      {TYPE_PLC_INT, VariantType::INT16 },
      {TYPE_PLC_UINT, VariantType::UINT16 },
      {TYPE_PLC_DINT, VariantType::INT32 },
      {TYPE_PLC_UDINT, VariantType::UINT32 },
      {TYPE_PLC_LINT, VariantType::INT64 },
      {TYPE_PLC_ULINT, VariantType::UINT64 },
      {TYPE_PLC_REAL, VariantType::FLOAT32 },
      {TYPE_PLC_LREAL, VariantType::FLOAT64 },
      {TYPE_PLC_STRING, VariantType::STRING },
      {TYPE_PLC_WSTRING, VariantType::RAW },
      {TYPE_PLC_TIME, VariantType::RAW },
      {TYPE_PLC_TIME_OF_DAY, VariantType::RAW },
      {TYPE_PLC_DATE, VariantType::RAW },
      {TYPE_PLC_DATE_AND_TIME, VariantType::RAW },
      {TYPE_PLC_LTIME, VariantType::RAW },

      {TYPE_PLC_ARRAY_OF_BYTE,  VariantType::ARRAY_OF_UINT8 },
      {TYPE_PLC_ARRAY_OF_WORD,  VariantType::ARRAY_OF_UINT16 },
      {TYPE_PLC_ARRAY_OF_DWORD, VariantType::ARRAY_OF_UINT32 },
      {TYPE_PLC_ARRAY_OF_LWORD, VariantType::ARRAY_OF_UINT64 },
      {TYPE_PLC_ARRAY_OF_SINT,  VariantType::ARRAY_OF_INT8 },
      {TYPE_PLC_ARRAY_OF_USINT, VariantType::ARRAY_OF_UINT8 },
      {TYPE_PLC_ARRAY_OF_INT,   VariantType::ARRAY_OF_INT16 },
      {TYPE_PLC_ARRAY_OF_UINT,  VariantType::ARRAY_OF_UINT16 },
      {TYPE_PLC_ARRAY_OF_DINT,  VariantType::ARRAY_OF_INT32 },
      {TYPE_PLC_ARRAY_OF_UDINT, VariantType::ARRAY_OF_UINT32 },
      {TYPE_PLC_ARRAY_OF_LINT,  VariantType::ARRAY_OF_INT64 },
      {TYPE_PLC_ARRAY_OF_ULINT, VariantType::ARRAY_OF_UINT64 },
      {TYPE_PLC_ARRAY_OF_REAL,  VariantType::ARRAY_OF_FLOAT32 },
      {TYPE_PLC_ARRAY_OF_LREAL, VariantType::ARRAY_OF_FLOAT64 },
    };

    auto found = mapTypes.find(type);
    if (found == mapTypes.end())
    {
      return VariantType::UNKNOWN;
    }
    return found->second;
  }

  static const std::string& toVariantString(VariantType type)
  {
    static std::map<VariantType, std::string> mapTypes = {
      {VariantType::BOOL8,   TYPE_DL_BOOL8 },
      {VariantType::INT8,    TYPE_DL_INT8 },
      {VariantType::UINT8,   TYPE_DL_UINT8 },
      {VariantType::INT16,   TYPE_DL_INT16 },
      {VariantType::UINT16,  TYPE_DL_UINT16 },
      {VariantType::INT32,   TYPE_DL_INT32 },
      {VariantType::UINT32,  TYPE_DL_UINT32 },
      {VariantType::INT64,   TYPE_DL_INT64 },
      {VariantType::UINT64,  TYPE_DL_UINT64 },
      {VariantType::FLOAT32, TYPE_DL_FLOAT32 },
      {VariantType::FLOAT64, TYPE_DL_FLOAT64 },
      {VariantType::STRING,  TYPE_DL_STRING },

      {VariantType::ARRAY_OF_BOOL8,      TYPE_DL_ARRAY_OF_BOOL8 },
      {VariantType::ARRAY_OF_INT8,       TYPE_DL_ARRAY_OF_INT8 },
      {VariantType::ARRAY_OF_UINT8,      TYPE_DL_ARRAY_OF_UINT8 },
      {VariantType::ARRAY_OF_INT16,      TYPE_DL_ARRAY_OF_INT16 },
      {VariantType::ARRAY_OF_UINT16,     TYPE_DL_ARRAY_OF_UINT16 },
      {VariantType::ARRAY_OF_INT32,      TYPE_DL_ARRAY_OF_INT32 },
      {VariantType::ARRAY_OF_UINT32,     TYPE_DL_ARRAY_OF_UINT32 },
      {VariantType::ARRAY_OF_INT64,      TYPE_DL_ARRAY_OF_INT64 },
      {VariantType::ARRAY_OF_UINT64,     TYPE_DL_ARRAY_OF_UINT64 },
      {VariantType::ARRAY_OF_FLOAT32,    TYPE_DL_ARRAY_OF_FLOAT32 },
      {VariantType::ARRAY_OF_FLOAT64,    TYPE_DL_ARRAY_OF_FLOAT64 },
      {VariantType::ARRAY_OF_STRING,     TYPE_DL_ARRAY_OF_STRING },
      {VariantType::RAW,                 TYPE_DL_RAW },
      {VariantType::TIMESTAMP,           TYPE_DL_TIMESTAMP },
      {VariantType::ARRAY_OF_TIMESTAMP,  TYPE_DL_ARRAY_OF_TIMESTAMP },
      {VariantType::EMPTY,               TYPE_DL_EMPTY },
    };

    auto found = mapTypes.find(type);
    if (found == mapTypes.end())
    {
      return TYPE_DL_UNKNOWN;
    }
    return found->second;
  }
};

}
}
}
