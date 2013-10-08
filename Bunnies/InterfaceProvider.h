#pragma once

class IShapesRenderer;
class IGraphicsEngine;
class Content;
class SpriteBatch;
class SpritesMap;

class InterfaceProvider
{
	friend class GameController;

public:
	static IShapesRenderer* GetShapesRenderer();
	static IGraphicsEngine* GetGraphicsEngine();
	static Content* GetContent();
	static SpriteBatch* GetSpriteBatch();
	static SpritesMap* GetSpritesMap();

private:
	static IShapesRenderer *m_shapesRenderer;
	static IGraphicsEngine *m_graphicsEngine;
	static Content *m_content;
	static SpriteBatch *m_spriteBatch;
	static SpritesMap* m_spritesMap;
};

