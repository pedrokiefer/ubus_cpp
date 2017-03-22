/*
 * UBus.cpp
 */

#include "UBus.h"

#include <string.h>
#include <iostream>
#include "json.h"

struct local_subscriber {
  struct ubus_subscriber subscriber;
  int id;
};

extern void uloop_disable_signals(void);

template<class P, class M>
size_t coffsetof(const M P::*member)
{
    return (size_t) &( reinterpret_cast<P*>(0)->*member);
}

template<class P, class M>
P* ccontainer_of(M* ptr, const M P::*member)
{
    return (P*)( (char*)ptr - coffsetof(member));
}

UBus::UBus() :
  threadRunning { false },
#ifdef __arm__
  available { true },
#else 
  available { false },
#endif
  signatureCallback { nullptr },
  callCallback { nullptr } {
  uloop_init();
}

UBus::~UBus() {
  StopUloopThread();
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
  StopUloopThread();
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

int local_ubus_event_handler(struct ubus_context *ctx, struct ubus_object *obj,
            struct ubus_request_data *req, const char *method,
            struct blob_attr *msg) {

  struct ubus_subscriber *s;
  struct local_subscriber *sub;

  s = ccontainer_of(obj, &ubus_subscriber::obj);
  sub = ccontainer_of(s, &local_subscriber::subscriber);

  std::cout << "Got method:" << method << " id: " << sub->id << std::endl;
  char *blob = blobmsg_format_json(msg, true);
  auto json = json::parse(blob);
  std::cout << json.dump(4) << std::endl;
  free(blob);

  auto handler = UBusCallbackStaticManager::getCallbackHandler(sub->id);
  if (handler != nullptr) {
    handler->callback(json);
  }
  return 0;
}

void UBus::Subscribe(std::string path, std::function<void(json)> callback) {
  uint32_t id = 0;
  int status;
  if (( status = ubus_lookup_id(connection->ctx, path.c_str(), &id )) ) {
    std::cout << "Unable to find: " << path << std::endl;
    return;
  }

  auto callbackHandler = std::make_shared<UBusCallback>();
  callbackHandler->callback = callback;
  UBusCallbackStaticManager::addCallbackHandler(id, callbackHandler);
  std::cout << path << " -> Id: " << id << std::endl;

  struct local_subscriber *s;

  s = static_cast<struct local_subscriber *>(malloc(sizeof(struct local_subscriber)));
  if (s == nullptr) {
    std::cout << "Unable to allocate memory" << std::endl;
    return;
  }
  memset(s, 0, sizeof(struct local_subscriber));

  s->subscriber.cb = local_ubus_event_handler;
  s->id = id;

  if ((status = ubus_register_subscriber(connection->ctx, &s->subscriber))) {
    std::cout << "Failed to register subscriber" << std::endl;
    return;
  }

  if ((status = ubus_subscribe(connection->ctx, &s->subscriber, id))) { 
    std::cout << "Failed to subscribe" << std::endl;
    return;
  }

  if (!threadRunning) {
    StartUloopThread();
  }

}

void UBus::StartUloopThread() {
  std::cout << "start thread" << std::endl;
  uloopThread = std::thread([&]() {
    threadRunning = true;
    uloop_disable_signals();
    uloop_run();
    uloop_done();
    threadRunning = false;
  });
}

void UBus::StopUloopThread() {
  uloop_end();
  if (uloopThread.joinable()) {
    uloopThread.join();
  }
}