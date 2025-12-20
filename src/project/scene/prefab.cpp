/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "prefab.h"

#include "simdjson.h"
#include "../../utils/json.h"
#include "../../utils/jsonBuilder.h"

using Builder = Utils::JSON::Builder;

std::string Project::Prefab::serialize(const Object &obj) const
{
  Builder builder{};
  builder.set(uuid);
  builder.setRaw("obj", obj.serialize());
  return builder.toString();
}

void Project::Prefab::deserialize(const std::string &str)
{
  auto doc = Utils::JSON::load(str);
  if(!doc.is_object())return;
  Utils::JSON::readProp(doc, uuid);
  obj.deserialize(nullptr, doc["obj"]);
}
