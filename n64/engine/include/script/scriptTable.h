/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <libdragon.h>

namespace P64 { class Object; }

namespace P64::Script
{
  typedef void(*FuncUpdate)(Object&, void*);

  struct ScriptEntry
  {
    FuncUpdate update;
    FuncUpdate draw;
    uint32_t dataSize;
  };

  // Note: generated and implement in the project:
  ScriptEntry &getCodeByIndex(uint32_t idx);
}