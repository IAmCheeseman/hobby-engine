#ifndef _HOBBY_ENGINE_H
#define _HOBBY_ENGINE_H

#include "time.h"

#include "window.h"

typedef struct {
  hb_Time* time;
  hb_Window* window;
} hb_Engine;

hb_Engine hb_createEngine(hb_Window* window);
void hb_destroyEngine(hb_Engine* engine);
void hb_engineStep(hb_Engine* engine);

#endif // _HOBBY_ENGINE_H
