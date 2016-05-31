/*
 * UBus.h
 */

#ifndef NETUBUS_UBUS_H_
#define NETUBUS_UBUS_H_

#include <memory>
#include <string>
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

class UBus {
 private:
  struct UBusConnection {
    int timeout;
    struct blob_buf buf;
    struct ubus_context *ctx;
  };

  std::unique_ptr<UBusConnection> connection;

 public:

  std::function<void(std::unique_ptr<UbusObject>)> signatureCallback;
  std::function<void(json)> callCallback;

  UBus();
  virtual ~UBus();

  void Connect();
  void Objects();
  void Signature(std::string path, std::function<void(std::unique_ptr<UbusObject>)> callback);
  void Call(std::string path, std::string function, json data, std::function<void(json)> callback);
  void Listen();

};

#endif /* NETUBUS_UBUS_H_ */
