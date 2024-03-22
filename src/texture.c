#include "texture.h"

#include "glad/glad.h"
#include "log.h"
#include "stb/stb_image.h"

static hb_TextureFilter defaultMin = hb_TEXTURE_FILTER_LINEAR;
static hb_TextureFilter defaultMag = hb_TEXTURE_FILTER_LINEAR;
static hb_TextureWrap defaultWrap = hb_TEXTURE_WRAP_NONE;

static u32 getGlFilter(hb_TextureFilter filter) {
  switch (filter) {
    case hb_TEXTURE_FILTER_LINEAR:
      return GL_LINEAR;
    case hb_TEXTURE_FILTER_NEAREST:
      return GL_NEAREST;
    default:
      hb_fatal("Invalid filter type.\n");
  }
}

static u32 getGlWrap(hb_TextureWrap wrap) {
  switch (wrap) {
    case hb_TEXTURE_WRAP_NONE:
      return GL_CLAMP_TO_BORDER;
    case hb_TEXTURE_WRAP_REPEAT:
      return GL_REPEAT;
    case hb_TEXTURE_WRAP_MIRRORED_REPEAT:
      return GL_MIRRORED_REPEAT;
    case hb_TEXTURE_WRAP_CLAMP:
      return GL_CLAMP_TO_EDGE;
  }
}

hb_Texture hb_createTexture(const char* path) {
  s32 width, height, channelCount;
  u8* data = stbi_load(path, &width, &height, &channelCount, 0);

  hb_fatalAssert(data != NULL, "Failed to load image '%s'", path);

  u32 channels;
  
  switch (channelCount) {
    case 3: channels = GL_RGB; break;
    case 4: channels = GL_RGBA; break;
  }

  u32 glId;
  glGenTextures(1, &glId);
  glBindTexture(GL_TEXTURE_2D, glId);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getGlWrap(defaultWrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getGlWrap(defaultWrap));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getGlFilter(defaultMin));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getGlFilter(defaultMag));

  glTexImage2D(
    GL_TEXTURE_2D, 0,
    channels, width, height, 0,
    channels, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  hb_Texture texture;
  texture.width = width;
  texture.height = height;
  texture.min = defaultMin;
  texture.mag = defaultMag;
  texture.wrap = defaultWrap;
  texture.glId = glId;

  return texture;
}

void hb_setDefaultFilter(hb_TextureFilter min, hb_TextureFilter mag) {
  defaultMin = min;
  defaultMag = mag;
}

void hb_setDefaultWrap(hb_TextureWrap wrap) {
  defaultWrap = wrap;
}
