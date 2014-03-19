#ifdef _WIN32
#	include <gl/glew.h>
#elif _TIZEN
#	include <FGraphicsOpengl2.h>
	using namespace Tizen::Graphics::Opengl;
#elif TARGET_OS_IPHONE
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
