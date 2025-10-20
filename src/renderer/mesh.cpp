/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "mesh.h"
#include "../context.h"
#include "scene.h"

void Renderer::Mesh::recreate(Renderer::Scene &scene) {
  if (indices.empty())return;
  //delete vertBuff;
  if (!vertBuff) {
    vertBuff = new VertBuffer(ctx.gpu);
  }

  if (!vertLines.empty()) {
    vertBuff->setData(vertLines, indices);
  } else {
    aabb.reset();
    for (const auto& v : vertices) {
      aabb.addPoint(glm::vec3(v.pos) * (1.0f / 65536.0f));
    }

    vertBuff->setData(vertices, indices);
  }

  scene.addOneTimeCopyPass([this](SDL_GPUCommandBuffer* cmdBuff, SDL_GPUCopyPass *copyPass){
    vertBuff->upload(*copyPass);
    dataReady = true;
  });
}

void Renderer::Mesh::draw(SDL_GPURenderPass* pass) {
  if (!dataReady || !vertBuff)return;

  SDL_GPUBufferBinding bufferBindings[2];
  vertBuff->addBindings(bufferBindings);

  SDL_BindGPUVertexBuffers(pass, 0, bufferBindings, 1);
  SDL_BindGPUIndexBuffer(pass, &bufferBindings[1], SDL_GPU_INDEXELEMENTSIZE_16BIT);

  //SDL_DrawGPUPrimitives(pass, vertices.size(), 1, 0, 0); // unindexed
  SDL_DrawGPUIndexedPrimitives(pass, indices.size(), 1, 0, 0, 0);
}

Renderer::Mesh::Mesh() {
}

Renderer::Mesh::~Mesh() {
  delete vertBuff;
}
