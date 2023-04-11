#pragma once
#include "DBEngine/CoreMinimal.h"
#include "DBEngine/Math/Transformations.h"

struct aiNode;
struct aiScene;
struct aiMesh;

class Model {
public:
	Model();
	~Model();

	// creates a simple shape based on the engine shapes
	bool CreateSimpleMesh(GeometricShapes Shape, ShaderPtr ModelShader);

	// import a 3d model from a common file type using ASSIMP
	bool ImportMeshFromFile(const char* ImportFilePath, ShaderPtr ModelShader);

	// Draw models to the screen
	void Draw();

	// Change the material relevent to the slot index
	// this will error log if the slot doesn't exist
	void SetMaterialBySlot(unInt SlotIndex, MaterialPtr NewMaterial);

	// this will get a material in the material stack if it exists
	MaterialPtr GetMaterialBySlot(unInt SlotIndex) const;

	// get the directory the model was imported from
	const char* GetFilePath() const { return ModelFilePath; }

private:
	// find all of the meshes in a import file/scene
	void FindAndImportSceneMeshes(aiNode* Node, const aiScene* Scene);

	// convert a mesh from the importer to our engine mesh class
	MeshPtr ConvertImportMeshToEngineMesh(aiMesh* ImportMesh, const aiScene* Scene);

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

	// imported file path
	const char* ModelFilePath;
};