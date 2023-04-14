#include "DBEngine/Graphics/Material.h"
#include "DBEngine/Graphics/Texture.h"
#include "DBEngine/Graphics/ShaderProgram.h"
#include "DBEngine/Game.h"

Material::Material()
{
	// make sure the base colour can be set to engine default
	if (Game::GetGameInstance().GetDefaultEngineTexture() != nullptr) {
		BaseColour.V3Texture = Game::GetGameInstance().GetDefaultEngineTexture();
		SpecularColour.V3Texture = Game::GetGameInstance().GetDefaultEngineTexture();
		EmissiveColour.V3Texture = Game::GetGameInstance().GetDefaultEngineTexture();
	}
	else {
		BaseColour.V3Texture = SpecularColour.V3Texture = EmissiveColour.V3Texture = nullptr;
	}

	EmissiveColour.V3Multiplier = Vector3(0.0f);
	Shininess = 0.1f;
}

Material::~Material()
{
	BaseColour.V3Texture = SpecularColour.V3Texture = EmissiveColour.V3Texture = nullptr;
}

void Material::Draw(ShaderPtr Shader)
{
	// base colour to shader
	if (BaseColour.V3Texture != nullptr) {
		// activate the tecture for slot 0
		BaseColour.V3Texture->ActivateTexture(0);
		// telling the shader to get the texture colour from slot 0
		Shader->SetInt("ImportMat.TColour", 0);
		// bind the texture to OpenGL
		BaseColour.V3Texture->BindTexture();
	}

	Shader->SetVector3("ImportMat.MColour", BaseColour.V3Multiplier);

	// Specular colour to shader
	if (SpecularColour.V3Texture != nullptr) {
		// activate the tecture for slot 1
		SpecularColour.V3Texture->ActivateTexture(1);
		// telling the shader to get the texture colour from slot 1
		Shader->SetInt("ImportMat.TSpecular", 1);
		// bind the texture to OpenGL
		SpecularColour.V3Texture->BindTexture();
	}

	Shader->SetVector3("ImportMat.MSpecular", SpecularColour.V3Multiplier);

	// Specular colour to shader
	if (EmissiveColour.V3Texture != nullptr) {
		// activate the tecture for slot 2
		EmissiveColour.V3Texture->ActivateTexture(2);
		// telling the shader to get the texture colour from slot 2
		Shader->SetInt("ImportMat.TEmissive", 2);
		// bind the texture to OpenGL
		EmissiveColour.V3Texture->BindTexture();
	}

	Shader->SetVector3("ImportMat.MEmissive", EmissiveColour.V3Multiplier);

	// set the shininess value in the shader
	Shader->SetFloat("ImportMat.Shininess", Shininess);
}
