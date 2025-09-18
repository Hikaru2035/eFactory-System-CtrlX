#pragma once

#include "variant.h"
#include "client.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* DLR_BULK;

//! @brief Create a bulk request
//! @param[in]  count           count of request in bulk request
//! @result created bulk request
DLR_BULK DLR_bulkCreate(size_t count);

//! @brief Delete a bulk request
//! @param[in]  bulk            request created with DLR_bulkCreate()
void DLR_bulkDelete(DLR_BULK bulk);

//! @brief Get count of entries in a bulk request
//! @param[in]  bulk            bulk request
//! @result Count of entries in a bulk request
size_t DLR_bulkGetCount(DLR_BULK bulk);

//! @brief Set requested address in a bulk request
//! @param[in]  bulk            bulk request
//! @param[in]  index           index to set
//! @param[in]  address         address to set
//! @result status of function call
DLR_RESULT DLR_bulkSetRequestAddress(DLR_BULK bulk, size_t index, char* address);

//! @brief Set requested data in a bulk request
//! @param[in]  bulk            bulk request
//! @param[in]  index           index to set
//! @param[in]  data            data to set
//! @result status of function call
DLR_RESULT DLR_bulkSetRequestData(DLR_BULK bulk, size_t index, DLR_VARIANT data);

//! @brief Get address in a bulk request
//! @param[in]  bulk            bulk request
//! @param[in]  index           index to get
//! @result address
char* DLR_bulkGetResponseAddress(DLR_BULK bulk, size_t index);

//! @brief Get data in a bulk request
//! @param[in]  bulk            bulk request
//! @param[in]  index           index to get
//! @result data
DLR_VARIANT DLR_bulkGetResponseData(DLR_BULK bulk, size_t index);

//! @brief Get timestamp in a bulk request
//! @param[in]  bulk            bulk request
//! @param[in]  index           index to get
//! @result timestamp
uint64_t DLR_bulkGetResponseTimestamp(DLR_BULK bulk, size_t index);

//! @brief Get result in a bulk request
//! @param[in]  bulk            bulk request
//! @param[in]  index           index to get
//! @result result
DLR_RESULT DLR_bulkGetResponseResult(DLR_BULK bulk, size_t index);

//! @brief Executes a synchronous bulk read request
//! @param[in]      client          client 
//! @param[in/out]  bulk            bulk request
//! @param[in]      token           optional token for the request
//! @result result of request
DLR_RESULT DLR_clientBulkReadSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);

//! @brief Executes a synchronous bulk write request
//! @param[in]      client          client 
//! @param[in/out]  bulk            bulk request
//! @param[in]      token           optional token for the request
//! @result result of request
DLR_RESULT DLR_clientBulkWriteSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);

//! @brief Executes a synchronous bulk create request
//! @param[in]      client          client 
//! @param[in/out]  bulk            bulk request
//! @param[in]      token           optional token for the request
//! @result result of request
DLR_RESULT DLR_clientBulkCreateSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);

//! @brief Executes a synchronous bulk delete request
//! @param[in]      client          client 
//! @param[in/out]  bulk            bulk request
//! @param[in]      token           optional token for the request
//! @result result of request
DLR_RESULT DLR_clientBulkDeleteSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);

//! @brief Executes a synchronous bulk browse request
//! @param[in]      client          client 
//! @param[in/out]  bulk            bulk request
//! @param[in]      token           optional token for the request
//! @result result of request
DLR_RESULT DLR_clientBulkBrowseSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);

//! @brief Executes a synchronous bulk metadata request
//! @param[in]      client          client 
//! @param[in/out]  bulk            bulk request
//! @param[in]      token           optional token for the request
//! @result result of request
DLR_RESULT DLR_clientBulkMetadataSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);

#ifdef __cplusplus
}
#endif
