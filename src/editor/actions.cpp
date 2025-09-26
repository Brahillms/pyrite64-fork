/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "actions.h"

#include <utility>

namespace
{
  Editor::Actions::ActionFn actionCallbacks[0xFF];
}

void Editor::Actions::init() {
  for (auto &cb : actionCallbacks) {
    cb = nullptr;
  }
}

void Editor::Actions::registerAction(Type type, ActionFn fn) {
  actionCallbacks[static_cast<uint8_t>(type)] = std::move(fn);
}

bool Editor::Actions::call(Type type, const std::string &arg) {
  if (actionCallbacks[static_cast<uint8_t>(type)]) {
    return actionCallbacks[static_cast<uint8_t>(type)](arg);
  }
  return false;
}
