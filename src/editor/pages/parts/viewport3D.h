/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include "../../../renderer/camera.h"
#include "../../../renderer/vertBuffer.h"
#include "../../../renderer/framebuffer.h"

namespace Editor
{
  class Viewport3D
  {
    private:
      Renderer::UniformGlobal uniGlobal{};
      Renderer::Framebuffer fb{};
      Renderer::Camera camera{};
      uint32_t passId{};

      bool isMouseHover{false};
      bool isMouseDown{false};

      glm::vec2 mousePos{};
      glm::vec2 mousePosStart{};

      void onRenderPass(SDL_GPUCommandBuffer* cmdBuff, SDL_GPUGraphicsPipeline* pipeline);
      void onCopyPass(SDL_GPUCommandBuffer* cmdBuff, SDL_GPUCopyPass *copyPass);

    public:
      Viewport3D();
      ~Viewport3D();

      void draw();
  };
}
