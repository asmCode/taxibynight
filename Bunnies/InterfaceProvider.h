#pragma once

class IGraphicsEngine;
class Content;
class SpriteBatch;
class SpritesMap;
class FontRenderer;

class InterfaceProvider
{
	friend class GameController;

public:
	static IGraphicsEngine* GetGraphicsEngine();
	static Content* GetContent();
	static SpriteBatch* GetSpriteBatch();
	static SpritesMap* GetSpritesMap();
	static FontRenderer* GetFontRenderer();

private:
	static IGraphicsEngine *m_graphicsEngine;
	static Content *m_content;
	static SpriteBatch *m_spriteBatch;
	static SpritesMap* m_spritesMap;
	static FontRenderer *m_fontRenderer;
};

