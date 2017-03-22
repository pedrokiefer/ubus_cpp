/*
 * main.cpp
 */

#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include "UBus.h"

int main(int argc, char *argv[]) {

  std::shared_ptr<UBus> bus = std::make_shared<UBus>();

  bus->Connect();
  bus->Objects();

  bus->Signature("network", [](std::unique_ptr<UbusObject> object) {
    std::cout << "Signature for: " << object->path << std::endl;
    std::cout << object->signature.dump(4) << std::endl;
  });

  json device = {{ "name", "wlan0" }};

  bus->Call("network.device", "status", device, [](json data) {
    std::cout << data.dump(4) << std::endl;
  });

  /*
  std::this_thread::sleep_for(std::chrono::seconds(1));
  */
  device["name"] = "eth0";
  bus->Call("network.device", "status", device, [](json data) {
      std::cout << data.dump(4) << std::endl;
  });


  //std::this_thread::sleep_for(std::chrono::milliseconds(15));

  bus->Call("network.interface.lan", "status", json::parse("{}"), [](json data) {
    std::cout << data.dump(4) << std::endl;
  });


  bus->Subscribe("network.interface", [&](json data) {
    std::cout << "Listen: " << data.dump(4) << std::endl;
    bus->Call("network.interface.lan", "status", json::parse("{}"), [](json data) {
      std::cout << data.dump(4) << std::endl;
    });
  });

  //uloop_run();
  //while(true) {
    std::this_thread::sleep_for(std::chrono::seconds(15));
  //}

  bus->Disconnect();
  std::cout << "Leaving..." << std::endl;

  return 0;
}



