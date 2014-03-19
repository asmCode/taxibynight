#include "Texture.h"
#include <vector>
#include <string>
#include "OpenglPort.h"

class PVRTexture : public Texture
{
public:
	~PVRTexture();
	PVRTexture(
		unsigned width,
		unsigned height,
		unsigned bpp,
		GLenum internalFormat,
		std::vector<std::string> data
	);
	
	void SetTextureData(const unsigned char *data);
};
