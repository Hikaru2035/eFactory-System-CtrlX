//! common
DL_ENUM_VALUE(DL_OK, 0x00000000)                        //! function call succeeded
DL_ENUM_VALUE(DL_OK_NO_CONTENT, 0x00000001)             //! function call succeeded with no content
DL_ENUM_VALUE(DL_OK_WITH_ERRORS, 0x00000002)            //! request was completed successfully but some parts have errors
DL_ENUM_VALUE(DL_FAILED, 0x80000001)                    //! only allowed for temporary use - define matching error code

//! application
DL_ENUM_VALUE(DL_INVALID_ADDRESS, 0x80010001)           //! address not found, address invalid (browse of this node not possible, write -> address not valid)
DL_ENUM_VALUE(DL_UNSUPPORTED, 0x80010002)               //! function not implemented (eg. onread is called but not readable)
DL_ENUM_VALUE(DL_OUT_OF_MEMORY, 0x80010003)             //! out of memory or resources (RAM, sockets, handles, disk space ...).
DL_ENUM_VALUE(DL_LIMIT_MIN, 0x80010004)                 //! the minimum of a limitation is exceeded.
DL_ENUM_VALUE(DL_LIMIT_MAX, 0x80010005)                 //! the maximum of a limitation is exceeded.
DL_ENUM_VALUE(DL_TYPE_MISMATCH, 0x80010006)             //! wrong flatbuffer type, wrong data type
DL_ENUM_VALUE(DL_SIZE_MISMATCH, 0x80010007)             //! size mismatch, present size doesn't match requested size.
DL_ENUM_VALUE(DL_INVALID_FLOATINGPOINT, 0x80010009)     //! invalid floating point number.
DL_ENUM_VALUE(DL_INVALID_HANDLE, 0x8001000A)            //! invalid handle argument or NULL pointer argument.
DL_ENUM_VALUE(DL_INVALID_OPERATION_MODE, 0x8001000B)    //! not accessible due to invalid operation mode (write not possible)
DL_ENUM_VALUE(DL_INVALID_CONFIGURATION, 0x8001000C)     //! mismatch of this value with other configured values
DL_ENUM_VALUE(DL_INVALID_VALUE, 0x8001000D)             //! invalid value / invalid argument
DL_ENUM_VALUE(DL_SUBMODULE_FAILURE, 0x8001000E)         //! error in submodule
DL_ENUM_VALUE(DL_TIMEOUT, 0x8001000F)                   //! request timeout
DL_ENUM_VALUE(DL_ALREADY_EXISTS, 0x80010010)            //! create: resource already exists
DL_ENUM_VALUE(DL_CREATION_FAILED, 0x80010011)           //! error during creation
DL_ENUM_VALUE(DL_VERSION_MISMATCH, 0x80010012)          //! version conflict
DL_ENUM_VALUE(DL_DEPRECATED, 0x80010013)                //! deprecated - function not longer supported
DL_ENUM_VALUE(DL_PERMISSION_DENIED, 0x80010014)         //! request declined due to missing permission rights
DL_ENUM_VALUE(DL_NOT_INITIALIZED, 0x80010015)           //! object not initialized yet
DL_ENUM_VALUE(DL_MISSING_ARGUMENT, 0x80010016)          //! missing argument (eg. missing argument in fbs)
DL_ENUM_VALUE(DL_TOO_MANY_ARGUMENTS, 0x80010017)        //! to many argument
DL_ENUM_VALUE(DL_RESOURCE_UNAVAILABLE, 0x80010018)      //! resource unavailable
DL_ENUM_VALUE(DL_COMMUNICATION_ERROR, 0x80010019)       //! low level communication error occurred
DL_ENUM_VALUE(DL_TOO_MANY_OPERATIONS, 0x8001001A)       //! request can't be handled due to too many operations
DL_ENUM_VALUE(DL_WOULD_BLOCK, 0x8001001B)               //! request would block, you have called a synchronous function in a callback from a asynchronous function

//! communication
DL_ENUM_VALUE(DL_COMM_PROTOCOL_ERROR, 0x80020001)       //! internal protocol error
DL_ENUM_VALUE(DL_COMM_INVALID_HEADER, 0x80020002)       //! internal header mismatch

//! client
DL_ENUM_VALUE(DL_CLIENT_NOT_CONNECTED, 0x80030001)      //! client not connected

//! provider
DL_ENUM_VALUE(DL_PROVIDER_RESET_TIMEOUT, 0x80040001)    //! resets keepalive timer for the current asynchronous request
DL_ENUM_VALUE(DL_PROVIDER_UPDATE_TIMEOUT, 0x80040002)   //! update maximum keepalive time for the current asynchronous request
DL_ENUM_VALUE(DL_PROVIDER_SUB_HANDLING, 0x80040003)     //! use default subscription handling of provider

//! broker

//! realtime related error codes
DL_ENUM_VALUE(DL_RT_NOTOPEN, 0x80060001)                //! not open
DL_ENUM_VALUE(DL_RT_INVALIDOBJECT, 0x80060002)          //! invalid object 
DL_ENUM_VALUE(DL_RT_WRONGREVISON, 0x80060003)           //! wrong memory revision
DL_ENUM_VALUE(DL_RT_NOVALIDDATA, 0x80060004)            //! no valid data 
DL_ENUM_VALUE(DL_RT_MEMORYLOCKED, 0x80060005)           //! memory already locked
DL_ENUM_VALUE(DL_RT_INVALIDMEMORYMAP, 0x80060006)       //! invalid memory map
DL_ENUM_VALUE(DL_RT_INVALID_RETAIN, 0x80060007)         //! invalid memory map
DL_ENUM_VALUE(DL_RT_INTERNAL_ERROR, 0x80060008)         //! internal RT error
DL_ENUM_VALUE(DL_RT_MALLOC_FAILED, 0x80060009)          //! allocation of shared memory failed - datalayer-shm connected?
DL_ENUM_VALUE(DL_RT_WOULD_BLOCK, 0x8006000A)            //! beginAccess would block because there are no data

DL_ENUM_VALUE(DL_SEC_NOTOKEN, 0x80070001)               //! no token found
DL_ENUM_VALUE(DL_SEC_INVALIDSESSION, 0x80070002)        //! token not valid (session not found)
DL_ENUM_VALUE(DL_SEC_INVALIDTOKENCONTENT, 0x80070003)   //! token has wrong content
DL_ENUM_VALUE(DL_SEC_UNAUTHORIZED, 0x80070004)          //! unauthorized
DL_ENUM_VALUE(DL_SEC_PAYMENT_REQUIRED, 0x80070005)      //! payment required
