/*
 * UBus.cpp
 */

#include "UBus.h"

#include <string.h>
#include <iostream>
#include "json.h"

UBus::UBus() :
#ifdef __arm__
  available { true },
#else 
  available { false },
#endif
  signatureCallback { nullptr },
  callCallback { nullptr } {

}

UBus::~UBus() {
}

void UBus::Connect() {
  if (!available) {
     return;
  }
  connection = std::unique_ptr<UBusConnection>(new UBusConnection);
  connection->ctx = ubus_connect(NULL);
  ubus_add_uloop(connection->ctx);
  connection->timeout = 30;
  memset(&connection->buf, 0, sizeof(connection->buf));
}

void UBus::Disconnect() {
  if (!available) {
    return;
  }
  ubus_free(connection->ctx);
}

void objects_callback(struct ubus_context *ctx, struct ubus_object_data *obj, void *priv) {
  std::cout << "callback called with path: " << obj->path << std::endl;
}

void UBus::Objects() {
  if (!available) {
    return;
  }
  ubus_lookup(connection->ctx, NULL, objects_callback, this);
}

void signatures_callback(struct ubus_context *ctx, struct ubus_object_data *obj, void *priv) {
  std::cout << "callback called with path: " << obj->path  << std::endl;
  auto ubus = static_cast<UBus *>(priv);
  std::unique_ptr<UbusObject> object = std::unique_ptr<UbusObject>(new UbusObject());

  object->id = obj->id;
  object->type_id = obj->type_id;
  object->path = obj->path;
  char *blob = blobmsg_format_json(obj->signature, true);
  object->signature = json::parse(blob);
  free(blob);

  if (ubus->signatureCallback != nullptr) {
    ubus->signatureCallback(std::move(object));
    ubus->signatureCallback = nullptr;
  }
}

void UBus::Signature(std::string path, std::function<void(std::unique_ptr<UbusObject>)> callback) {
  if (!available) {
    return;
  }
  signatureCallback = callback;
  ubus_lookup(connection->ctx, path.c_str(), signatures_callback, this);
}

void function_call_callback(struct ubus_request *req, int type, struct blob_attr *msg)
{
  auto ubus = static_cast<UBus *>(req->priv);

  if (!msg) {
    ubus->callCallback(json::parse("{}"));
    ubus->callCallback = nullptr;
    return;
  }

  char *blob = blobmsg_format_json(msg, true);
  auto json = json::parse(blob);
  free(blob);

  if (ubus->callCallback != nullptr) {
    ubus->callCallback(json);
    ubus->callCallback = nullptr;
  }
}

void UBus::Call(std::string path, std::string function, json data, std::function<void(json)> callback) {
  if (!available) {
    return;
  }
  uint32_t id;
  callCallback = callback;

  if (ubus_lookup_id(connection->ctx, path.c_str(), &id)) {
    return;
  }

  blob_buf_init(&connection->buf, 0);
  std::cout << "data is: " << data.dump() << std::endl;

  blobmsg_add_object(&connection->buf, json_tokener_parse(data.dump().c_str()));

  ubus_invoke(connection->ctx, id, function.c_str(), connection->buf.head, function_call_callback, this, connection->timeout * 1000);
}

void local_ubus_event_handler(struct ubus_context *ctx, struct ubus_event_handler *ev,
      const char *type, struct blob_attr *msg) {

  std::cout << "Got type:" << type << std::endl;
  char *blob = blobmsg_format_json(msg, true);
  auto json = json::parse(blob);
  free(blob);

  auto handler = UBusEventStaticManager::getEventHandler(type);
  if (handler != nullptr) {
    handler->callback(json);
  }
}

void UBus::Listen(std::string path, std::function<void(json)> callback) {
  if (!available) {
    return;
  }
  std::shared_ptr<UBusEvent> ev = std::make_shared<UBusEvent>();
  ev->event.cb = local_ubus_event_handler;
  ev->callback = callback;

  UBusEventStaticManager::addEvent(path, ev);

  ubus_register_event_handler(connection->ctx, &ev->event, path.c_str());
}
