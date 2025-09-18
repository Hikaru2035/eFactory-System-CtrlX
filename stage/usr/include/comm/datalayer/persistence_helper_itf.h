#pragma once

// ---------------------------------------------------------------------------
//! @file       persistence_helper.h
//! @author     DC-AE/ESW2
//! @copyright  Bosch Rexroth Corporation http://www.boschrexroth.com
//! @version    1.0.0
//! @date       2019
// ---------------------------------------------------------------------------
//! This file is part of the persistence library
//! for other bundles for C.
// ---------------------------------------------------------------------------


//!  @par List of available functions in persistence helper interface. 
//! <TABLE>
//! <TR><TH>           Function                                         </TH><TH> Interface version </TH></TR>
//! <TR><TD id="st_e"> @ref saveDataType                                </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataTypeaddress                         </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataaddress                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveJson                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadData                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataType                                </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataaddress                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadJson                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFile                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFiles                                   </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDirectory                               </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFile                                    </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFiles                                   </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDirectory                               </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFile                                  </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFiles                                 </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteDirectory                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref directoryExists                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref fileExists                                  </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref getRootPath                                 </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref getLastError                                </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectory                             </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectoryRegex                        </TD><TD> 0.0.1             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataType2                               </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataTypeaddress2                        </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDataaddress2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveJson2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadData2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataType2                               </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDataaddress2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFile2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveFiles2                                  </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref saveDirectory2                              </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFile2                                   </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadFiles2                                  </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref loadDirectory2                              </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFile2                                 </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteFiles2                                </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref deleteDirectory2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref directoryExists2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref fileExists2                                 </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectory2                            </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref browseDirectoryRegex2                       </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref getAbsolutePath                             </TD><TD> 0.1.0             </TD></TR>
//! <TR><TD id="st_e"> @ref persistNvram                                </TD><TD> 0.2.0             </TD></TR>
//! <TR><TD id="st_e"> @ref getPersistenceHeader                        </TD><TD> 0.3.0             </TD></TR>
//! </TABLE>
//!

// ---------------------------------------------------------------------------
// Include Files
// ---------------------------------------------------------------------------
#include <map>
#include "datalayer.h"

// ---------------------------------------------------------------------------
// Declaration of symbolic constants
// ---------------------------------------------------------------------------

//! @brief Interface version of the persistence bundle interface
#define PERSISTENCE_C_INTERFACE_VERSION                   "2.0.0"
//! @brief Consumer range of the persistence bundle interface
#define PERSISTENCE_C_INTERFACE_DEFAULT_CONSUMER_RANGE    "[2.0.0,3.0.0)"
//! @brief Name of the persistence bundle interface
#define PERSISTENCE_C_INTERFACE_NAME                      "com.boschrexroth.comm.datalayer.persistence"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum PersistenceErrorCodes
  {
    PERSISTENCE_DIAG_OK = 0,                  //! everything is okay
    PERSISTENCE_DIAG_ERR_GENERATE_JSON,       //! failed to generate json (maybe wrong data or type?)
    PERSISTENCE_DIAG_ERR_PARSE_JSON,          //! failed to parse json (maybe wrong type?)
    PERSISTENCE_DIAG_ERR_NO_VALID_DIRECTORY,  //! no valid directory found
    PERSISTENCE_DIAG_ERR_NO_VALID_HEADER,     //! no valid header found in json file
    PERSISTENCE_DIAG_ERR_BFBS_NOT_SET,        //! bfbs path in json file missing
    PERSISTENCE_DIAG_ERR_BFBS_NOT_VALID,      //! file is no valid bfbs
    PERSISTENCE_DIAG_ERR_INVAL_TYPENAME,      //! type name is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_TYPEADDR,      //! type address is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_DATAADDR,      //! data address is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_PATH,          //! path is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_JSON,          //! json string is not valid (maybe empty string?)
    PERSISTENCE_DIAG_ERR_INVAL_FILES,         //! files are not valid (maybe empty list?)
    PERSISTENCE_DIAG_ERR_MKDIR,               //! error during directory create
    PERSISTENCE_DIAG_ERR_FILE_WRITE,          //! error write into a file 
    PERSISTENCE_DIAG_ERR_FILE_OPEN,           //! error opening a file
    PERSISTENCE_DIAG_ERR_FILE_DELETE,         //! error file delete
    PERSISTENCE_DIAG_ERR_FILE_NOT_EXISTS,     //! the given file doesn't exist
    PERSISTENCE_DIAG_ERR_DIR_NOT_EXISTS,      //! the given directory doesn't exist
    PERSISTENCE_DIAG_ERR_DIR_COPY,            //! error during directory copy
    PERSISTENCE_DIAG_ERR_DIR_DELETE,          //! error during directory delete
    PERSISTENCE_DIAG_ERR_SET_PERMISSIONS,     //! unable to set permissions
    PERSISTENCE_DIAG_ERR_DL_READ,             //! error returned from datalayer read
    PERSISTENCE_DIAG_ERR_DL_WRITE,            //! error returned from datalayer write
    PERSISTENCE_DIAG_ERR_DL_METADATA,         //! error returned from datalayer read metadata
    PERSISTENCE_DIAG_ERR_FIND_FILE,           //! find of file failed
    PERSISTENCE_DIAG_ERR_EVALUATE_PATH,       //! can't evaluate path
    PERSISTENCE_DIAG_ERR_NO_REGEX,            //! not a valid regular expression
    PERSISTENCE_DIAG_ERR_EXCEPTION,           //! c++ exception occurred
    PERSISTENCE_DIAG_ERR_VARINAT_TYPE         //! type of variant is invalid
  }PersistenceErrorCodes;

  typedef struct PersistenceDetailDiag
  {
    PersistenceErrorCodes errorCode;          //! persistence helper specific error code
    comm::datalayer::DlResult dlResult;       //! datalayer result
    std::uint32_t errNbr;                     //! errno if available
    std::string detailDiag;                   //! detailed diagnosis text
  }PersistenceDetailDiag;

  //! @brief This is the interface for the persistence helper for other bundles for commands from C.
  //! For detailed documentation see 'persistence_helper.h'.
  typedef struct PersistenceHelperItf
  {
    void *handle;

    //! @brief Save data to active configuration
    //! @param[in]  handle    handle to persistence helper
    //! @param[in]  data      data to save
    //! @param[in]  type      flatbuffer type
    //! @param[in]  typeName  name of type
    //! @param[in]  path      path to store file relative to active configuration
    //! @result status of function call
    std::uint32_t(*saveDataType)(const void* handle, const ::comm::datalayer::Variant& data, const ::comm::datalayer::Variant& type, const std::string& typeName, const std::string& path);

    //! @brief Save data to active configuration (datatype is read from datalayer address)
    //! @param[in]  handle      handle to persistence helper
    //! @param[in]  data        data to save
    //! @param[in]  typeAddress datalayer address to get type
    //! @param[in]  path        path to store file relative to active configuration
    //! @result status of function call
    std::uint32_t(*saveDataTypeaddress)(const void* handle, const ::comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path);

    //! @brief Save data to active configuration  (data and datatype is read from datalayer address)
    //! @param[in]  handle      handle to persistence helper
    //! @param[in]  dataAddress datalayer address to get data
    //! @param[in]  path        path to store file
    //! @result status of function call
    std::uint32_t(*saveDataaddress)(const void* handle, const std::string& dataAddress, const std::string& path);

    //! @brief Save Json string to active configuration
    //! @param[in]  handle      handle to persistence helper
    //! @param[in]  jsonString  json string to store
    //! @param[in]  path        path to store file
    //! @result status of function call
    std::uint32_t(*saveJson)(const void* handle, const std::string& jsonString, const std::string& path);

    //! @brief Loads from a saved json file into flatbuffer data and flatbuffer type.
    //! The loaded file has to be a valid persistence helper json file.
    //! To restore the data the argument type is used.
    //! This method is called within c interface function 'loadData'.
    //! @param[in]  handle    handle to persistence helper
    //! @param[in]  path      path to load file from relative to active configuration
    //! @param[in]  type      flatbuffer type
    //! @param[out] data      flatbuffer data
    //! @return               Success or error
    std::uint32_t(*loadData)(const void* handle, const std::string& path, const ::comm::datalayer::Variant& type, ::comm::datalayer::Variant& data);

    //! @brief Load data from active configuration
    //! @param[in]  handle    handle to persistence helper
    //! @param[in]  path      path to load file from relative to active configuration
    //! @param[out] data      data
    //! @param[out] type      flatbuffer type
    //! @result status of function call
    std::uint32_t(*loadDataType)(const void* handle, const std::string& path, ::comm::datalayer::Variant& data, ::comm::datalayer::Variant& type);

    //! @brief Load data from active configuration and writes it to datalayer address
    //! @param[in]  handle      handle to persistence helper
    //! @param[in]  path        path to load file from relative to active configuration
    //! @param[in]  dataAddress datalayer address to write data
    //! @result status of function call
    std::uint32_t(*loadDataaddress)(const void* handle, const std::string& path, const std::string& dataAddress);

    //! @brief Load Json from file from active configuration
    //! @param[in]  handle      handle to persistence helper
    //! @param[in]  path        path to load file from relative to active configuration
    //! @param[in]  jsonString  json string read from file
    //! @result status of function call
    std::uint32_t(*loadJson)(const void* handle, const std::string& path, std::string& jsonString);

    //! @brief Save file to active configuration
    //! @param[in]  handle            handle to persistence helper
    //! @param[in]  destinationPath   destination path to store file relative to active configuration
    //! @param[in]  sourcePath        source path of file
    //! @result status of function call
    std::uint32_t(*saveFile)(const void* handle, const std::string& destinationPath, const std::string& sourcePath);

    //! @brief Save files to active configuration
    //! @param[in]  handle  handle to persistence helper
    //! @param[in]  files   map for with destination files (key) and source files (value)
    //! @result status of function call
    std::uint32_t(*saveFiles)(const void* handle, const std::map<std::string, std::string>& files);

    //! @brief Save Directory to active configuration
    //! @param[in]  handle                handle to persistence helper
    //! @param[in]  destinationDirectory  destination store directory
    //! @param[in]  sourceDirectory       source directory
    //! @result status of function call
    std::uint32_t(*saveDirectory)(const void* handle, const std::string& destinationDirectory, const std::string& sourceDirectory);

    //! @brief Loads a file from source relative to active configuration into destination.
    //! @param[in]  handle            handle to persistence helper
    //! @param[in]  destinationPath   path to store file 
    //! @param[in]  sourcePath        path to to get file from relative to active configuration
    //! @result status of function call
    std::uint32_t(*loadFile)(const void* handle, const std::string& destinationPath, const std::string& sourcePath);

    //! @brief Loads a files from source relative to active configuration into destination.
    //! @param[in]  handle  handle to persistence helper
    //! @param[in]  files   map including the files to save (key = destinationPath, value = sourcePath)
    //! @result status of function call
    std::uint32_t(*loadFiles)(const void* handle, const std::map<std::string, std::string>& files);

    //! @brief Loads a source directory relative to active configuration into a destination directory.
    //! @param[in]  handle                 handle to persistence helper
    //! @param[in]  destinationDirectory   destination directory
    //! @param[in]  sourceDirectory        source directory  relative to active configuration
    //! @result status of function call
    std::uint32_t(*loadDirectory)(const void* handle, const std::string& destinationDirectory, const std::string& sourceDirectory);

    //! @brief Delete file in active configuration
    //! @param[in]  handle  handle to persistence helper
    //! @param[in]  path    file to delete relative to active configuration
    //! @result status of function call
    std::uint32_t(*deleteFile)(const void* handle, const std::string& path);

    //! @brief Delete files in active configuration
    //! @param[in]  handle  handle to persistence helper
    //! @param[in]  paths   files to delete relative to active configuration
    //! @result status of function call
    std::uint32_t(*deleteFiles)(const void* handle, const std::vector<std::string>& paths);

    //! @brief Delete directory in active configuration
    //! @param[in]  handle     handle to persistence helper
    //! @param[in]  directory  directory to delete relative to active configuration
    //! @result status of function call
    std::uint32_t(*deleteDirectory)(const void* handle, const std::string& directory);

    //! @briefChecks if a directory exists.
    //! @param[in]  handle      handle to persistence helper
    //! @param[in]  directory   directory to check relative to active configuration
    //! @return                 'true' if directory exists
    bool(*directoryExists)(const void* handle, const std::string& directory);

    //! @brief Checks if a file exists.
    //! @param[in]  handle handle to persistence helper
    //! @param[in]  path   file to check relative to active configuration
    //! @return            'true' if file exists
    bool(*fileExists)(const void* handle, const std::string& path);

    //! @brief Get root path of active configuration
    //! @param[in]  handle      handle to persistence helper
    //! @param[in]  rootPath    root path where all files are persisted
    //! @result status of function call
    std::uint32_t(*getRootPath)(const void* handle, std::string& rootPath);

    //! @brief Get detail of last error
    //! @param[in]  diagnosis   detail diagnosis of last error
    //! @result status of function call
    std::uint32_t(*getLastError)(const void* handle, PersistenceDetailDiag& diagnosis);

    //! @brief Browse directory
    //! @param[in]  handle                  handle to persistence helper
    //! @param[in]  directory               Directory to browse relative to active configuration
    //! @param[in]  includeDirecotries      include directories
    //! @param[out] files                   list of found files in directory
    //! @return                             Success or error
    std::uint32_t(*browseDirectory)(const void* handle, const std::string& directory, bool includeDirecotries, std::vector<std::string>& files);

    //! @brief Browse directory with regular expressions
    //! @param[in]  handle                  handle to persistence helper
    //! @param[in]  directory               Directory to browse relative to active configuration
    //! @param[in]  includeDirecotries      subdirectories are found as well
    //! @param[in]  regularExpression       string representing a regular expression
    //! @param[out] files                   list of found files in directory
    //! @return                             Success or error
    std::uint32_t(*browseDirectoryRegex)(const void* handle, const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files);

    //! @brief This method saves flatbuffer data into a given path.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref saveDataType(const void* handle, const comm::datalayer::Variant& data, const comm::datalayer::Variant& type, const std::string& typeName, const std::string& path) const "saveDataType".
    std::uint32_t(*saveDataType2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const ::comm::datalayer::Variant& data, const ::comm::datalayer::Variant& type, const std::string& typeName, const std::string& path);

    //! @brief This method saves flatbuffer data into a given path.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref saveDataTypeaddress(const void* handle, const comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path) const "saveDataTypeaddress".
    std::uint32_t(*saveDataTypeaddress2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const ::comm::datalayer::Variant& data, const std::string& typeAddress, const std::string& path);

    //! @brief This method saves flatbuffer data into a given path.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref saveDataaddress(const void* handle, const std::string& dataAddress, const std::string& path) const "saveDataaddress".
    std::uint32_t(*saveDataaddress2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& dataAddress, const std::string& path);

    //! @brief This method saves a json string as it is into a given path.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref saveJson(const void* handle, const std::string& jsonString, const std::string& path) const "saveJson".
    std::uint32_t(*saveJson2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& jsonString, const std::string& path);

    //! @brief This method loads from a saved json file into flatbuffer data and flatbuffer type.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadData(const void* handle, const std::string& path, const comm::datalayer::Variant& type, comm::datalayer::Variant& data) const "loadData".
    std::uint32_t(*loadData2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, const ::comm::datalayer::Variant& type, ::comm::datalayer::Variant& data);

    //! @brief This method loads from a saved json file into flatbuffer data and flatbuffer type.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadDataType(const void* handle, const std::string& path, comm::datalayer::Variant& data, comm::datalayer::Variant& type) const "loadDataType".
    std::uint32_t(*loadDataType2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, ::comm::datalayer::Variant& data, ::comm::datalayer::Variant& type);

    //! @brief This method loads from a saved json file and writes the data via datalayer.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadDataaddress(const void* handle, const std::string& path, const std::string& dataAddress) const "loadDataaddress".
    std::uint32_t(*loadDataaddress2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, const std::string& dataAddress);

    //! @brief This method loads from a saved json file and returns the data as json string.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadJson(const void* handle, const std::string& path, std::string& jsonString) const "loadJson".
    std::uint32_t(*loadJson2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, std::string& jsonString);

    //! @brief This method saves a file from source into destination.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref saveFile(const void* handle, const std::string& destinationPath, const std::string& sourcePath) const "saveFile".
    std::uint32_t(*saveFile2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationPath, const std::string& sourcePath);

    //! @brief This method saves files from source into destination.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref saveFiles(const void* handle, const std::map<std::string, std::string>& files) const "saveFile".
    std::uint32_t(*saveFiles2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::map<std::string, std::string>& files);

    //! @brief This method copies a source directory into destination.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref saveDirectory(const void* handle, const std::string& destinationDirectory, const std::string& sourceDirectory) const "saveDirectory".
    std::uint32_t(*saveDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationDirectory, const std::string& sourceDirectory);

    //! @brief This method loads a file from source into destination.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadFile(const void* handle, const std::string& destinationPath, const std::string& sourcePath) const "loadFile".
    std::uint32_t(*loadFile2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationPath, const std::string& sourcePath);

    //! @brief This method loads a files from source into destination.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadFiles(const void* handle, const std::map<std::string, std::string>& files) const "loadFiles".
    std::uint32_t(*loadFiles2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::map<std::string, std::string>& files);

    //! @brief This method loads a source directory into a destination directory.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadDirectory(const void* handle, const std::string& destinationDirectory, const std::string& sourceDirectory) const "loadDirectory".
    std::uint32_t(*loadDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& destinationDirectory, const std::string& sourceDirectory);

    //! @brief This method deletes a file.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref deleteFile(const void* handle, const std::string& path) const "deleteFile".
    std::uint32_t(*deleteFile2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path);

    //! @brief This method loads a files from source into destination.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadFiles(const void* handle, const std::map<std::string, std::string>& files) const "deleteFiles".
    std::uint32_t(*deleteFiles2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::vector<std::string>& paths);

    //! @brief This method loads a source directory into a destination directory.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref loadDirectory(const void* handle, const std::string& destinationDirectory, const std::string& sourceDirectory) const "deleteDirectory".
    std::uint32_t(*deleteDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory);

    //! @brief This method checks if a directory exists.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref directoryExists(const void* handle, const std::string& directory) const "directoryExists".
    bool(*directoryExists2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory);

    //! @brief This method checks if a file exists.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref fileExists(const void* handle, const std::string& path) const "fileExists".
    bool(*fileExists2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path);

    //! @brief This method browses a directory and returns the containing files.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref browseDirectory(const void* handle, const std::string& directory, bool includeDirecotries, std::vector<std::string>& files) const "browseDirectory".
    std::uint32_t(*browseDirectory2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory, bool includeDirecotries, std::vector<std::string>& files);

    //! @brief This method browses a directory and returns the files matching a regular expression.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! For method documentation see \ref browseDirectory(const void* handle, const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files) const "browseDirectory".
    std::uint32_t(*browseDirectoryRegex2)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& directory, bool includeDirecotries, const std::string& regularExpression, std::vector<std::string>& files);

    //! @brief This method returns the resulting absolute path based on the arguments.
    //! For description of 'persistenceParam' see \ref persistenceParam. 
    //! @param[in]  handle                  handle to persistence helper
    //! @param[in]  persistenceParam        variant of type persistence param, including the configuration path
    //! @param[in]  path                    path to the configuration
    //! @param[out] absolutePath            the resulting absolute path
    //! @return                             Success or error
    std::uint32_t(*getAbsolutePath)(const void* handle, const ::comm::datalayer::Variant& persistenceParam, const std::string& path, std::string& absolutePath);

    //! @brief This method starts persist NVRam to hardware. You should call this function at the end of your cycle that uses NVRAM. Persistance of
    //! NVRam is done after this call in hardware and took about 1,5ms
    //! @return                             Success or error
    std::uint32_t(*persistNvram)(const void* handle);

    //! @brief This method returns the values of the persistence header.
    //! This method is called within c interface function 'getPersistenceHeader'.
    //! @param[in]  handle                  handle to persistence helper
    //! @param[in]  path                    path to the file to get the persistence header from
    //! @param[out] bfbsPath                the path to the bfbs file
    //! @param[out] persistenceVersion      the version of the persistence helper
    //! @return                             Success or error
    std::uint32_t(*getPersistenceHeader)(const void* handle, const std::string& path, std::string& bfbsPath, std::string& persistenceVersion);

    void *reserved[100];
  } PersistenceHelperItf;

#ifdef __cplusplus
}
#endif
