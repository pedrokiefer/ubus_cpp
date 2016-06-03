/*
 * UBus.cpp
 */

#include "UBus.h"

#include <string.h>
#include <iostream>
#include "json.h"

UBus::UBus() :
  running { false },
  signatureCallback { nullptr },
  callCallback { nullptr } {
  // TODO Auto-generated constructor stub

}

UBus::~UBus() {
}

void UBus::runService() {
  while(running) {
    uloop_inner_run();
  }
}

void UBus::Connect() {
  connection = std::unique_ptr<UBusConnection>(new UBusConnection);
  uloop_init();
  connection->ctx = ubus_connect(NULL);
  ubus_add_uloop(connection->ctx);
  connection->timeout = 30;
  memset(&connection->buf, 0, sizeof(connection->buf));
}

void UBus::Disconnect() {
  if (running) {
    running = false;
    service.join();
  }
  ubus_free(connection->ctx);
  uloop_end();
}

void objects_callback(struct ubus_context *ctx, struct ubus_object_data *obj, void *priv) {
  std::cout << "callback called with path: " << obj->path << std::endl;
}

void UBus::Objects() {
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

void local_listen_timeout(struct uloop_timeout *timeout) {
  std::cout << "timeout!" << std::endl;
  uloop_end();
}

void UBus::Listen(std::string path, std::function<void(json)> callback) {
  std::shared_ptr<UBusEvent> ev = std::make_shared<UBusEvent>();
  ev->event.cb = local_ubus_event_handler;
  ev->callback = callback;

  UBusEventStaticManager::addEvent(path, ev);

  int ret = ubus_register_event_handler(connection->ctx, &ev->event, path.c_str());

  if (!running) {
    running = true;
    connection->uloopTimeout.cb = local_listen_timeout;
    uloop_timeout_set(&connection->uloopTimeout, connection->timeout * 1000);
    service = std::thread(&UBus::runService, this);
  }
}
