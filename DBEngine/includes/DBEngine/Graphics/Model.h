#pragma once
#include "DBEngine/CoreMinimal.h"
#include "DBEngine/Math/Transformations.h"

class Model {
public:
	Model();
	~Model();

	// creates a simple shape based on the engine shapes
	bool CreateSimpleMesh(GeometricShapes Shape, ShaderPtr ModelShader);

	// Draw models to the screen
	void Draw();

	// Change the material relevent to the slot index
	// this will error log if the slot doesn't exist
	void SetMaterialBySlot(unInt SlotIndex, MaterialPtr NewMaterial);

public:
	// position, rotation, and scale of all the meshes in the model
	CTransform Transform;

private:
	// all the meshes related to this model
	MeshPtrStack MeshStack;

	// all the materials relevant to the meshes in this model
	MaterialPtrStack MaterialStack;

	// the model shader
	ShaderPtr ModelShader;
};