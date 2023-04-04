#include "DBEngine/Graphics/Model.h"
#include "DBEngine/Graphics/Mesh.h"
#include "DBEngine/Game.h"

Model::Model()
{

}

Model::~Model()
{
	// clean up the model
	MeshStack.clear();
	MaterialStack.clear();
	ModelShader = nullptr;
}

bool Model::CreateSimpleMesh(GeometricShapes Shape, ShaderPtr ModelShader)
{
	// initialise the mesh
	MeshPtr NewMesh = make_shared<Mesh>();
	
	// try to create the simple shape
	if (!NewMesh->CreateSimpleShape(Shape, ModelShader, 0)) {
		return false;
	}

	// clear the old data if there is any and assign the new
	MeshStack.clear();
	MaterialStack.clear();
	this->ModelShader = ModelShader;

	// assign the default engine material to the first material slot
	MaterialStack.push_back(Game::GetGameInstance().GetDefaultEngineMaterial());

	// assign the mesh to the model mesh stack
	MeshStack.push_back(NewMesh);

	return true;
}

void Model::Draw()
{
	// cycle through the meshes and draw each one
	for (MeshPtr LMesh : MeshStack) {
		// assign the model transformations to the mesh
		LMesh->Transform = this->Transform;

		// draw the mesh using the material slot it has been assigned
		LMesh->Draw(MaterialStack[LMesh->GetMaterialSlot()]);
	}
}

void Model::SetMaterialBySlot(unInt SlotIndex, MaterialPtr NewMaterial)
{
	// check if the index is valid to the array
	if (MaterialStack.size() <= SlotIndex) {
		cout << "Model | No material slot of index (" << SlotIndex << ") exists" << endl;
		return;
	}

	// reassign the array item
	MaterialStack[SlotIndex] = NewMaterial;
}
