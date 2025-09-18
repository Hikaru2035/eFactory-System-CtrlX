#pragma once

#include "client.h"
#include "provider.h"
#include "user.h"
#include "owner.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void *DLR_FACTORY;

  //! Creates a client for accessing data of the system
  //! @param[in] factory    Reference to the factory
  //! @param[in] remote     Remote address of the data layer
  //! @return Client
  DLR_CLIENT DLR_factoryCreateClient(DLR_FACTORY factory, const char* remote);

  //! Creates a provider to provide data to the datalayer
  //! @param[in] factory    Reference to the factory
  //! @param[in] remote     Remote address of the data layer
  //! @return Provider
  DLR_PROVIDER DLR_factoryCreateProvider(DLR_FACTORY factory, const char* remote);

  //! Opens datalayer rt memory
  //! @param[in]  factory    Reference to the factory
  //! @param[out] user       Created user
  //! @param[in]  addr       Address of the RT memory
  //! @return Provider
  DLR_RESULT DLR_factoryOpenMemory(DLR_FACTORY factory, DLR_USER *user, const char* addr);

  //! Closes datalayer rt memory
  //! @param[in] factory    Reference to the factory
  //! @param[in] user       User to close
  DLR_RESULT DLR_factoryCloseMemory(DLR_FACTORY factory, DLR_USER user);

  //! Create datalayer rt memory
  //! @param[in]  factory    Reference to the factory
  //! @param[out] owner      Created user
  //! @param[in]  addr       Address of the RT memory
  //! @param[in]  provider   Provider to use for memory
  //! @param[in]  sizeBytes  Size of the memory
  //! @param[in]  type       Type of the memory
  DLR_RESULT DLR_factoryCreateMemorySync(DLR_FACTORY factory, DLR_OWNER* owner, const char* addr, DLR_PROVIDER provider, size_t sizeBytes, DLR_MEMORYTYPE type);

  //! Delete datalayer rt memory
  //! @param[in]  factory    Reference to the factory
  //! @param[out] owner      Owner to delete
  DLR_RESULT DLR_factoryDeleteMemorySync(DLR_FACTORY factory, DLR_OWNER owner);

#ifdef __cplusplus
}
#endif
