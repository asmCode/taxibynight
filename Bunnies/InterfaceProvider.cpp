#include "InterfaceProvider.h"
#include <stddef.h>
#include <assert.h>

IGraphicsEngine *InterfaceProvider::m_graphicsEngine;
Content *InterfaceProvider::m_content;
SpriteBatch *InterfaceProvider::m_spriteBatch;
SpritesMap* InterfaceProvider::m_spritesMap;
FontRenderer *InterfaceProvider::m_fontRenderer;

IGraphicsEngine* InterfaceProvider::GetGraphicsEngine()
{
	assert(m_graphicsEngine != NULL);
	return m_graphicsEngine;
}

Content* InterfaceProvider::GetContent()
{
	return m_content;
}

SpriteBatch* InterfaceProvider::GetSpriteBatch()
{
	return m_spriteBatch;
}

SpritesMap* InterfaceProvider::GetSpritesMap()
{
	return m_spritesMap;
}

FontRenderer* InterfaceProvider::GetFontRenderer()
{
	return m_fontRenderer;
}

