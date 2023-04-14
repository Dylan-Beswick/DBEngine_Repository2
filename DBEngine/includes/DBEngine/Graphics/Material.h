#pragma once
#include "DBEngine/CoreMinimal.h"
#include "DBEngine/Math/Transformations.h"

struct Vec3Texture {
	TexturePtr V3Texture;
	Vector3 V3Multiplier = Vector3(1.0f);
};

class Material {
public:
	Material();
	~Material();

	void Draw(ShaderPtr Shader);

	// store the colour map and multiplier of each value
	Vec3Texture BaseColour;
	Vec3Texture SpecularColour;
	Vec3Texture EmissiveColour;

	float Shininess;
};