#ifndef STREET
#define STREET

#include <Math/Matrix.h>

class Model;
class Texture;
class StreetMap;

struct StreetPiece
{
	void Set(Model *model, Texture *texture, const sm::Matrix &world)
	{
		m_model = model;
		m_texture = texture;
		m_world = world;
	}

	Model *m_model;
	Texture *m_texture;
	sm::Matrix m_world;
};

class Street
{
public:
	Street();
	~Street();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

private:
	Model *m_streetModel;
	Model *m_skycrapper;

	Texture *m_skycrapperTexture;
	Texture *m_pavementTexture;

	StreetMap *m_streetMap;

	StreetPiece m_streetPieces[256];
};

#endif // STREET

