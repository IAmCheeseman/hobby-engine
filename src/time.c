#include "time.h"

#include <stdlib.h>

#include "GLFW/glfw3.h"

#define FPS_UPDATE_FREQ 1

struct hb_Time* hb_createTime() {
  struct hb_Time* time = malloc(sizeof(struct hb_Time));
  time->deltaTime = 0;
  time->lastFrameTime = 0;

  time->fps = 0;
  time->lastFpsUpdate = 0;
  time->framesRendered = 0;
  return time;
}

void hb_destroyTime(struct hb_Time *time) {
  free(time);
}

void hb_timeStep(struct hb_Time* time) {
  // Calculate delta time
  f32 currentTime = glfwGetTime();
  time->deltaTime = currentTime - time->lastFrameTime;
  time->lastFrameTime = currentTime;

  // Calculate FPS
  time->framesRendered++;
  f32 timeSinceLastUpdate = currentTime - time->lastFpsUpdate;
  if (timeSinceLastUpdate >= FPS_UPDATE_FREQ) {
    time->fps = time->framesRendered / timeSinceLastUpdate;
    time->lastFpsUpdate = currentTime;
    time->framesRendered = 0;
  }
}
