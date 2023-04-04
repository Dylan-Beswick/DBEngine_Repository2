#include "DBEngine/Graphics/Material.h"
#include "DBEngine/Graphics/Texture.h"
#include "DBEngine/Graphics/ShaderProgram.h"
#include "DBEngine/Game.h"

Material::Material()
{
	// make sure the base colour can be set to engine default
	if (Game::GetGameInstance().GetDefaultEngineTexture() != nullptr) {
		BaseColour = Game::GetGameInstance().GetDefaultEngineTexture();
	}
	else {
		BaseColour = nullptr;
	}
}

Material::~Material()
{
	BaseColour = nullptr;
}

void Material::Draw(ShaderPtr Shader)
{
	if (BaseColour != nullptr) {
		// activate the tecture for slot 0
		BaseColour->ActivateTexture(0);
		// telling the shader to get the texture colour from slot 0
		Shader->SetInt("TextureColour", 0);
		// bind the texture to OpenGL
		BaseColour->BindTexture();
	}
}
