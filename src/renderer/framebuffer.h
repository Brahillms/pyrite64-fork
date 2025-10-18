/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once
#include <SDL3/SDL.h>

#include "../utils/color.h"

namespace Renderer
{
  class Framebuffer
  {
    private:
      SDL_GPUTextureCreateInfo texInfo{};
      SDL_GPUTexture* gpuTex{nullptr};
      SDL_GPUTexture* gpuTexDepth{nullptr};
      SDL_GPUColorTargetInfo targetInfo{};
      SDL_GPUDepthStencilTargetInfo depthTargetInfo{};

    public:
      Framebuffer();
      ~Framebuffer();

      void setClearColor(const Utils::Color &color) {
        targetInfo.clear_color.r = color.r;
        targetInfo.clear_color.g = color.g;
        targetInfo.clear_color.b = color.b;
        targetInfo.clear_color.a = color.a;
      }

      void resize(uint32_t width, uint32_t height);

      [[nodiscard]] const SDL_GPUColorTargetInfo& getTargetInfo() const { return targetInfo; }
      [[nodiscard]] const SDL_GPUDepthStencilTargetInfo& getDepthTargetInfo() const { return depthTargetInfo; }
      [[nodiscard]] SDL_GPUTexture* getTexture() const { return gpuTex; }
  };
}
