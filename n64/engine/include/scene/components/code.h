/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "scene/object.h"
#include "script/scriptTable.h"

namespace P64::Comp
{
  struct Code
  {
    Script::FuncUpdate funcUpdate{};
    Script::FuncUpdate funcDraw{};

    static uint32_t getAllocSize(uint16_t* initData)
    {
      return sizeof(Code);
    }

    static void init(Object& obj, Code* data, uint16_t* initData)
    {
      //debugf("Init: %d %d\n", initData[0], initData[1]);
      auto scriptPtr = Script::getCodeByIndex(initData[0]);
      assert(scriptPtr.update != nullptr);

      data->funcUpdate = scriptPtr.update;
      data->funcDraw = nullptr;
    }

    static void update(Object& obj, Code* data) {
      char* funcData = (char*)data + sizeof(Code);
      if(data->funcUpdate)data->funcUpdate(obj, funcData);
    }

    static void draw(Object& obj, Code* data) {
      char* funcData = (char*)data + sizeof(Code);
      if(data->funcDraw)data->funcDraw(obj, funcData);
    }
  };
}