#ifndef BB_OPENGL_H
#define BB_OPENGL_H

#include "BaconBox/PlatformFlagger.h"

#if defined (BB_OPENGL) || defined (BB_OPENGLES)

#if defined(BB_MAC_PLATFORM) && defined(BB_SDL)
#include <OpenGL/OpenGL.h>
#endif

#if defined(BB_IPHONE_PLATFORM)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#elif defined(BB_QT)
#include <QtOpenGL>
#elif defined(BB_MAC_PLATFORM)
#include <OpenGL/gl.h>
#elif defined(BB_ANDROID)
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#define GLEW_STATIC
#include "glew.h"
#define BB_GLEW
#endif

#endif

#endif
