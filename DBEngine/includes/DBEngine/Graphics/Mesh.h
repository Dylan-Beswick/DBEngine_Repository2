#pragma once
#include "DBEngine/CoreMinimal.h"
#include "DBEngine/Math/Transformations.h"

class Mesh {
public:
	Mesh();
	~Mesh();

	// Create the mesh out of VAO, a Shader, and Textures
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, unInt MaterialSlot);

	// handle the drawing of all the required classes
	void Draw(MaterialPtr MeshMaterial);

	// return material slot assigned by the model to the mesh
	unInt GetMaterialSlot() const { return MaterialSlot; }

public:
	// this holds the location, rotation, and scale of the mesh
	CTransform Transform;

private:
	// store the shader this mesh requires
	ShaderPtr MeshShader;

	// assigned material slot relevant to the model class
	unInt MaterialSlot;

	// Create a new VAO for the mesh
	VAOPtr MeshVAO;
};