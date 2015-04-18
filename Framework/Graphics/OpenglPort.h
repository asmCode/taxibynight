#if _WIN32
#	include <gl/glew.h>
#elif _TIZEN
#	include <FGraphicsOpengl2.h>
	using namespace Tizen::Graphics::Opengl;
#elif __APPLE__
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#elif __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
