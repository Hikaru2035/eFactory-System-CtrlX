#pragma once
#include "datalayer.h"
#include "flatbuffers_celix.h"
#include "flatbuffer_json.h"
#include "persistence_helper.h"
#include "compliance_checker.h"

namespace common {
namespace log {
namespace trace {
  class IRegistrationRealTime3;
}
namespace diagnosis {
  class IRegistration4;
}
}}

//! Namespace for datalayer
namespace comm {
namespace datalayer {

enum class BindNode { FRONTEND_TCP, BACKEND_TCP, FRONTEND_IPC, BACKEND_IPC, FRONTEND_INPROC, BACKEND_INPROC, IPC_PATH, NO_SAVE };
class Factory;
class Broker;
class RealtimeBroker;
class FlatbufferJson;
class PersistenceHelper;
class ComplianceChecker;
class RTDebug;
class LoadSaveProvider;
class WatchlistProvider;
class ServerSettingsProvider;
class UtilFlatcProvider;
class UtilFlatcGeneratedProvider;
class ZipFileProvider;

namespace remote{
  class C2CMain;
}

//! DatalayerSystem which includes a broker
class DatalayerSystem
{
public:
  //! Constructor
  //! @param[in] ipcPath  Path in file system for interprocess communication - use empty string for automatic detection
  //!                     Leave empty for auto 
  //! @return none
  DatalayerSystem(std::string ipcPath = "");
  ~DatalayerSystem();

  //! Returns the factory to create clients and provider for the datalayer
  //! @return Factory
  IDataLayerFactory3* factory();

  //! Returns the factory to create clients and provider for the datalayer
  //! @return Factory
  IDataLayerFactory4* factory4();

  //! Returns the factory to create clients and provider for the datalayer
  //! @return Factory
  IDataLayerFactory5* factory5();

  //! Returns converter between JSON and Variant
  //! @return Converter between JSON and Variant
  IFlatbufferJson* jsonConverter();

  //! Returns persistence helper
  //! @return persistence helper
  PersistenceHelper* persistenceHelper();

  //! Returns compliance checker
  //! @return compliance checker
  ComplianceChecker* complianceChecker();

  //! Returns datalayer c interface
  //! @return datalayer c interface
  DatalayerCItf* datalayerCInterface();

  //! Returns flatbuffers c interface
  //! @return flatbuffers c interface
  FlatbuffersCItf* flatbuffersCInterface();

  //! Start the datalayer (broker)
  void start(bool boStartBroker = true);

  //! Stop the datalayer (broker)
  //! returns false if there is a client or provider active
  bool stop(bool boForceProviderStop = false);

  std::string getBrokerBindNode(BindNode type);

  void setRTParallelClientAsDefault(bool value);

  void setBfbsPath(std::string path);;

  void setServerKeypair(const std::string& publicKey, const std::string& privateKey);
  std::string getServerPublicKey();
  std::string getServerPrivateKey();

  //! By default key is requested using HTTPS from remote control.
  //! This function sets the public key of the remote control.
  //! @param[in] key     Remote TCP server public key
  //! @return none
  DlResult setRemotePublicKey(const std::string& key);

  //! By default token is fetched from deviceadmin using HTTPS from remote control.
  //! This function sets the token of the remote control.
  //! @param[in] key     Remote TCP server public key
  //! @return none
  DlResult setRemoteToken(const std::string& token);

  DlResult setDebugAddress(const std::string& address);

  DlResult persistNvram();

  DlResult enableTrace(bool boEnable, ::common::log::trace::IRegistrationRealTime3* registration = nullptr);

  DlResult setTokenCheck(bool boEnable);

  void loadConfig(const Variant& persistenceParam);
  void saveConfig();

  DlResult setDiagnosis(common::log::diagnosis::IRegistration4* diagnosis);

  enum class ServerSetting
  {
    IDLE_PING_TIMEOUT,
    WAIT_RESPONSE_TIMEOUT,
    MAX_MESSAGE_SIZE,
    MAX_RT_SIZE,
    EMULATED_NVRAM_SIZE,
    TCP_PORT_FRONTEND,
    TCP_PORT_BACKEND,
    FORCE_NVRAM_EMU,
    ZMQ_HWM,
    MAX_BULK,
    MAX_SORT_SIZE,
    MAX_ALIAS_DEPTH,
  };

  uint32_t getSetting(ServerSetting setting);

  bool isBroker() { return m_isBroker; }

  void enableExperimentalFeatures(std::vector<std::string> &features);

  static std::string getTmpPath();

protected:
private:

  void* m_zmqContext = nullptr;
  Factory* m_factory = nullptr;
  Broker* m_broker = nullptr;
  FlatbufferJson* m_converter = nullptr;
  PersistenceHelper* m_persistenceHelper = nullptr;
  ComplianceChecker* m_complianceChecker = nullptr;
  RTDebug* m_rtdebug = nullptr;
  LoadSaveProvider* m_loadSave = nullptr;
  WatchlistProvider* m_watchlist = nullptr;
  ServerSettingsProvider* m_serverSettings = nullptr;
  UtilFlatcProvider* m_utilFlatcProvider = nullptr;
  ZipFileProvider* m_zipFileProvider = nullptr;
  remote::C2CMain* m_remote = nullptr;
  std::string m_ipcPath = "";
  DatalayerCItf m_datalayerCItf;
  FlatbuffersCItf m_flatbuffersCItf;
  RealtimeBroker* m_rtBroker = nullptr;
  std::string m_serverPublicKey;
  std::string m_serverPrivateKey;
  bool m_isBroker = false;
};

}
}
