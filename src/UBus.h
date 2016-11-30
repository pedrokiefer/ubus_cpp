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

struct UBusEvent {
  struct ubus_event_handler event;
  std::function<void(json)> callback;
};

class UBusEventStaticManager {
 private:
  static std::map<std::string, std::shared_ptr<UBusEvent>> & GetEventsMap() {
    static std::map<std::string, std::shared_ptr<UBusEvent>> events;
    return events;
  }
 public:
  UBusEventStaticManager();
  virtual ~UBusEventStaticManager() {};

  static void addEvent(std::string name, std::shared_ptr<UBusEvent> handler) {
    if (GetEventsMap().count(name) != 0) {
      return;
    }

    GetEventsMap()[name] = handler;
  }

  static std::shared_ptr<UBusEvent> getEventHandler(std::string name) {
    if (GetEventsMap().count(name) == 1) {
      return GetEventsMap()[name];
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

  std::unique_ptr<UBusConnection> connection;
  std::atomic_bool running;
  std::thread service;
  bool available;

  void runService();

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
  void Listen(std::string path, std::function<void(json)> callback);

};

#endif /* NETUBUS_UBUS_H_ */
