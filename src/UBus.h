/*
 * UBus.h
 */

#ifndef NETUBUS_UBUS_H_
#define NETUBUS_UBUS_H_

#include <memory>
#include <string>
#include <list>
#include <thread>
#include <atomic>
#include "json.hpp"

extern "C" {
#include "libubus.h"
#include "libubox/blobmsg.h"
#include "libubox/blobmsg_json.h"
}

using json = nlohmann::json;

struct UbusObject {
  uint32_t id;
  uint32_t type_id;
  std::string path;
  json signature;
};

struct UBusCallback {
  std::function<void(json)> callback;
};

class UBusCallbackStaticManager {
 private:
  static std::map<int, std::shared_ptr<UBusCallback>> & GetEventsMap() {
    static std::map<int, std::shared_ptr<UBusCallback>> events;
    return events;
  }
 public:
  UBusCallbackStaticManager();
  virtual ~UBusCallbackStaticManager() = default;

  static void addCallbackHandler(int id, std::shared_ptr<UBusCallback> handler) {
    if (GetEventsMap().count(id) != 0) {
      return;
    }

    GetEventsMap()[id] = handler;
  }

  static std::shared_ptr<UBusCallback> getCallbackHandler(int id) {
    if (GetEventsMap().count(id) == 1) {
      return GetEventsMap()[id];
    }
    return nullptr;
  }
};

class UBus {
 private:
  struct UBusConnection {
    int timeout;
    struct blob_buf buf;
    struct ubus_context *ctx;
    struct uloop_timeout uloopTimeout;
  };

  std::thread uloopThread;
  bool threadRunning;
  std::unique_ptr<UBusConnection> connection;
  bool available;

 protected:
  void StartUloopThread();
  void StopUloopThread();
 public:

  std::function<void(std::unique_ptr<UbusObject>)> signatureCallback;
  std::function<void(json)> callCallback;

  UBus();
  virtual ~UBus();

  void Connect();
  void Disconnect();
  void Objects();
  void Signature(std::string path, std::function<void(std::unique_ptr<UbusObject>)> callback);
  void Call(std::string path, std::string function, json data, std::function<void(json)> callback);
  void Subscribe(std::string path, std::function<void(json)> callback);

};

#endif /* NETUBUS_UBUS_H_ */
