/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
//#include "glm/gtx/quaternion.hpp"

Renderer::Camera::Camera() {
  rot = glm::identity<glm::quat>();
}

void Renderer::Camera::update() {
}

void Renderer::Camera::apply(UniformGlobal &uniGlobal)
{
  float x = SDL_GetTicks() / 1000.0f;
  float aspect = screenSize.x / screenSize.y;
  uniGlobal.projMat = glm::perspective(70.0f, aspect, 0.1f, 100.0f);

  //uniGlobal.cameraMat = glm::lookAt(glm::vec3{0,0,-10}, {sinf(x) * 4,0,0}, {0,1,0});

  uniGlobal.cameraMat = glm::mat4_cast(rot);
  uniGlobal.cameraMat = glm::translate(uniGlobal.cameraMat, -pos * rot);
}

void Renderer::Camera::rotateDelta(glm::vec2 screenDelta)
{
  if (!isRotating) {
    rotBase = rot;
    isRotating = true;
  }

  // rotate based on screen delta
  float angleX = screenDelta.x * -0.0025f;
  float angleY = screenDelta.y * 0.0025f;
  glm::quat qx = glm::angleAxis(angleX, glm::vec3(0, 1, 0));
  glm::quat qy = glm::angleAxis(angleY, glm::vec3(1, 0, 0));
  rot = qx * rotBase * qy;
  rot = glm::normalize(rot);

}

void Renderer::Camera::moveDelta(glm::vec2 screenDelta) {
  if (!isMoving) {
    posBase = pos;
    isMoving = true;
  }
  float moveX = screenDelta.x * 0.001f;
  float moveY = screenDelta.y * -0.001f;

  glm::vec3 right = rot * glm::vec3(1, 0, 0);
  glm::vec3 up = rot * glm::vec3(0, 1, 0);

  pos = posBase + (right * moveX) + (up * moveY);
}
