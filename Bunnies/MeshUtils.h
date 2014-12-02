#pragma once

class Model;
class Texture;
class Material;

class MeshUtils
{
public:
	static void SetMaterial(Model* model, Material* material);
	static void SetDiffusseTexture(Model* model, Texture* texture);
};
