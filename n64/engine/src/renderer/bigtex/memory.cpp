/**
* @copyright 2024 - Max Bebök
* @license MIT
*/
#include "memory.h"

extern "C" {
  // "libdragon/system_internal.h"
  void* sbrk_top(int incr);
}

namespace {
  heap_stats_t heap_stats{};
  surface_t zBuffer{};
}

namespace P64::Renderer::BigTex
{
  surface_t *getZBuffer() {
    assert(zBuffer.buffer);
    return &zBuffer;
  }

  void freeBuffers()
  {
    debugf("@TODO: P64::Renderer::BigTex::freeBuffers()\n");
  }

  FrameBuffers allocBuffers() {
    if(is_memory_expanded()) { // With 8MB, we reserve the upper 4MB (excl. the stack) for the frame-buffers
      // first limit the upper heap to match against the start of our first buffer
      void *buf = sbrk_top(16); // probe current end
      uint32_t missing = (uint32_t)buf - FB_BANK_ADDR[0]; // reserve rest
      buf = sbrk_top(missing);
      assert(FB_BANK_ADDR[0] == (uint32_t)buf);

      zBuffer = surface_make(UncachedAddr(FB_BANK_ADDR[5]), FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH*2);
      return {
        .color = {
          surface_make(UncachedAddr(FB_BANK_ADDR[2]), FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH*2),
          surface_make(UncachedAddr(FB_BANK_ADDR[3]), FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH*2),
          surface_make(UncachedAddr(FB_BANK_ADDR[4]), FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH*2),
          //surface_alloc(FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT),
          //surface_alloc(FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT),
          //surface_alloc(FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT),
        },
        .uv = {
          surface_alloc(FMT_RGBA32, SCREEN_WIDTH, SCREEN_HEIGHT),
          surface_alloc(FMT_RGBA32, SCREEN_WIDTH, SCREEN_HEIGHT),
          surface_alloc(FMT_RGBA32, SCREEN_WIDTH, SCREEN_HEIGHT),
        },
        /*.shade = {
          surface_alloc(FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT),
          surface_alloc(FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT),
          surface_alloc(FMT_RGBA16, SCREEN_WIDTH, SCREEN_HEIGHT),
        },*/
        .depth = &zBuffer
      };
    } else {
      assertf(false, "Expansion-Pack required!");
    }
  }
}