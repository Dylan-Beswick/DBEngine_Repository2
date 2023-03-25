#pragma once
#include "DBEngine/CoreMinimal.h"
#include "DBEngine/Math/Transformations.h"

class Mesh {
public:
	Mesh();
	~Mesh();

	// Create the mesh out of VAO, a Shader, and Textures
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures);

	// handle the drawing of all the required classes
	void Draw();

	// this holds the location, rotation, and scale of the mesh
	CTransform Transform;

private:
	// store the shader this mesh requires
	ShaderPtr MeshShader;
	// store the texture this mesh requires
	TexturePtrStack MeshTextures;
	// Create a new VAO for the mesh
	VAOPtr MeshVAO;
};