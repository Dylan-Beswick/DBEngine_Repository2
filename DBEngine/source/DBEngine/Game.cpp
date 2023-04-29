#include "DBEngine/Game.h"
#include "DBEngine/Graphics/GraphicsEngine.h"
#include "DBEngine/Graphics/Model.h"
#include "DBEngine/Input.h"
#include "DBEngine/Graphics/Camera.h"
#include "DBEngine/Graphics/Material.h"
#include "DBEngine/Collisions/Collision.h"

Game& Game::GetGameInstance()
{
	static Game* GameInstance = new Game();
	return *GameInstance;
}

void Game::DestroyGameInstance()
{
	static Game* GameInstance = &GetGameInstance();

	delete GameInstance;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	Graphics = make_shared<GraphicsEngine>();

	if (!Graphics->InitGE(WTitle, bFullscreen, WWidth, WHeight)) {
		bIsGameOver = true;
	}

	Run();
}

TexturePtr Game::GetDefaultEngineTexture()
{
	return Graphics->DefaultEngineTexture;
}

MaterialPtr Game::GetDefaultEngineMaterial()
{
	return Graphics->DefaultEngineMaterial;
}

void Game::RemoveModelFromGame(ModelPtr& ModelToRemove)
{
	// remove from the graphics engine
	Graphics->RemoveModel(ModelToRemove);
	
	// change the reference to nullptr and remove from the game
	ModelToRemove = nullptr;
}

Game::Game()
{
	cout << "Game Initialised!" << endl;

	Graphics = nullptr;
	bIsGameOver = false;
}

Game::~Game()
{
	// since nothing else is storing graphics memory
	// this will destroy the graphics from memory
	Graphics = nullptr;

	cout << "Game Over..." << endl;
}

void Game::Run()
{
	if (!bIsGameOver) {
		// create an input class to detect input
		GameInput = new Input();

		// create a shader
		ShaderPtr TextrueShader = Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});

		TexturePtr TConcrete = Graphics->CreateTexture("Game/Textures/ConcreteFloor.jpg");

		TexturePtr TMagicStone = Graphics->CreateTexture("Game/Models/magic-portal/textures/MagicStone_base.png");
		TexturePtr TPortalSurface = Graphics->CreateTexture("Game/Models/magic-portal/textures/PortalSurface_base.png");

		TexturePtr TFinishLine = Graphics->CreateTexture("Game/Models/finish-line/textures/finish.png");

		// create the materials
		MaterialPtr MConcrete = make_shared<Material>();

		MaterialPtr MMagicStone = make_shared<Material>();
		MaterialPtr MPortalSurface = make_shared<Material>();

		MaterialPtr MFinishLine = make_shared<Material>();

		// assign the base colour of the materails using the textures
		MConcrete->BaseColour.V3Texture = TConcrete;

		MMagicStone->BaseColour.V3Texture = TMagicStone;
		MPortalSurface->BaseColour.V3Texture = TPortalSurface;

		MFinishLine->BaseColour.V3Texture = TFinishLine;

		// create VAOs
		Boundary1 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary2 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary3 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary4 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary5 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary6 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary7 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary8 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary9 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary10 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary11 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary12 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary13 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary14 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary15 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary16 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary17 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary18 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary19 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary20 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary21 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary22 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary23 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary24 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary25 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary26 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary27 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary28 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary29 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary30 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary31 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary32 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary33 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary34 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary35 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary36 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary37 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary38 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary39 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary40 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary41 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary42 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary43 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary44 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);
		Boundary45 = Graphics->ImportModel("Game/Models/Primitives/Plane.fbx", TextrueShader);

		Gateway1 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway2 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway3 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway4 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway5 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway6 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway7 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway8 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway9 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway10 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway11 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway12 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway13 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway14 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway15 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway16 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);
		Gateway17 = Graphics->ImportModel("Game/Models/magic-portal/source/Portal.fbx", TextrueShader);

		FinishLine = Graphics->ImportModel("Game/Models/finish-line/source/finish_line.fbx", TextrueShader);

		// add collisions to models
		Boundary1->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary2->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary3->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary4->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary5->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary6->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary7->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary8->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary9->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary10->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary11->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary12->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary13->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary14->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary15->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary16->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary17->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary18->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary19->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary20->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary21->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary22->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary23->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary24->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary25->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary26->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary27->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary28->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary29->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary30->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary31->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary32->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary33->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary34->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary35->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary36->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary37->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary38->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary39->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary40->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary41->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary42->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary43->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary44->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));
		Boundary45->AddCollisionToModel(Vector3(0.01, 5.0f, 5.0f));

		Gateway1->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway2->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway3->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway4->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway5->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway6->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway7->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway8->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway9->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway10->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway11->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway12->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway13->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway14->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway15->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway16->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));
		Gateway17->AddCollisionToModel(Vector3(0.5f, 2.6f, 2.6f), Vector3(0.0f, 0.35f, 0.0f));

		FinishLine->AddCollisionToModel(Vector3(0.45f, 3.65f, 5.55f));

		// set materials of the models
		Boundary1->SetMaterialBySlot(0, MConcrete);
		Boundary2->SetMaterialBySlot(0, MConcrete);
		Boundary3->SetMaterialBySlot(0, MConcrete);
		Boundary4->SetMaterialBySlot(0, MConcrete);
		Boundary5->SetMaterialBySlot(0, MConcrete);
		Boundary6->SetMaterialBySlot(0, MConcrete);
		Boundary7->SetMaterialBySlot(0, MConcrete);
		Boundary8->SetMaterialBySlot(0, MConcrete);
		Boundary9->SetMaterialBySlot(0, MConcrete);
		Boundary10->SetMaterialBySlot(0, MConcrete);
		Boundary11->SetMaterialBySlot(0, MConcrete);
		Boundary12->SetMaterialBySlot(0, MConcrete);
		Boundary13->SetMaterialBySlot(0, MConcrete);
		Boundary14->SetMaterialBySlot(0, MConcrete);
		Boundary15->SetMaterialBySlot(0, MConcrete);
		Boundary16->SetMaterialBySlot(0, MConcrete);
		Boundary17->SetMaterialBySlot(0, MConcrete);
		Boundary18->SetMaterialBySlot(0, MConcrete);
		Boundary19->SetMaterialBySlot(0, MConcrete);
		Boundary20->SetMaterialBySlot(0, MConcrete);
		Boundary21->SetMaterialBySlot(0, MConcrete);
		Boundary22->SetMaterialBySlot(0, MConcrete);
		Boundary23->SetMaterialBySlot(0, MConcrete);
		Boundary24->SetMaterialBySlot(0, MConcrete);
		Boundary25->SetMaterialBySlot(0, MConcrete);
		Boundary26->SetMaterialBySlot(0, MConcrete);
		Boundary27->SetMaterialBySlot(0, MConcrete);
		Boundary28->SetMaterialBySlot(0, MConcrete);
		Boundary29->SetMaterialBySlot(0, MConcrete);
		Boundary30->SetMaterialBySlot(0, MConcrete);
		Boundary31->SetMaterialBySlot(0, MConcrete);
		Boundary32->SetMaterialBySlot(0, MConcrete);
		Boundary33->SetMaterialBySlot(0, MConcrete);
		Boundary34->SetMaterialBySlot(0, MConcrete);
		Boundary35->SetMaterialBySlot(0, MConcrete);
		Boundary36->SetMaterialBySlot(0, MConcrete);
		Boundary37->SetMaterialBySlot(0, MConcrete);
		Boundary38->SetMaterialBySlot(0, MConcrete);
		Boundary39->SetMaterialBySlot(0, MConcrete);
		Boundary40->SetMaterialBySlot(0, MConcrete);
		Boundary41->SetMaterialBySlot(0, MConcrete);
		Boundary42->SetMaterialBySlot(0, MConcrete);
		Boundary43->SetMaterialBySlot(0, MConcrete);
		Boundary44->SetMaterialBySlot(0, MConcrete);
		Boundary45->SetMaterialBySlot(0, MConcrete);

		Gateway1->SetMaterialBySlot(0, MMagicStone);
		Gateway1->SetMaterialBySlot(1, MMagicStone);
		Gateway1->SetMaterialBySlot(2, MPortalSurface);
		Gateway2->SetMaterialBySlot(0, MMagicStone);
		Gateway2->SetMaterialBySlot(1, MMagicStone);
		Gateway2->SetMaterialBySlot(2, MPortalSurface);
		Gateway3->SetMaterialBySlot(0, MMagicStone);
		Gateway3->SetMaterialBySlot(1, MMagicStone);
		Gateway3->SetMaterialBySlot(2, MPortalSurface);
		Gateway4->SetMaterialBySlot(0, MMagicStone);
		Gateway4->SetMaterialBySlot(1, MMagicStone);
		Gateway4->SetMaterialBySlot(2, MPortalSurface);
		Gateway5->SetMaterialBySlot(0, MMagicStone);
		Gateway5->SetMaterialBySlot(1, MMagicStone);
		Gateway5->SetMaterialBySlot(2, MPortalSurface);
		Gateway6->SetMaterialBySlot(0, MMagicStone);
		Gateway6->SetMaterialBySlot(1, MMagicStone);
		Gateway6->SetMaterialBySlot(2, MPortalSurface);
		Gateway7->SetMaterialBySlot(0, MMagicStone);
		Gateway7->SetMaterialBySlot(1, MMagicStone);
		Gateway7->SetMaterialBySlot(2, MPortalSurface);
		Gateway8->SetMaterialBySlot(0, MMagicStone);
		Gateway8->SetMaterialBySlot(1, MMagicStone);
		Gateway8->SetMaterialBySlot(2, MPortalSurface);
		Gateway9->SetMaterialBySlot(0, MMagicStone);
		Gateway9->SetMaterialBySlot(1, MMagicStone);
		Gateway9->SetMaterialBySlot(2, MPortalSurface);
		Gateway10->SetMaterialBySlot(0, MMagicStone);
		Gateway10->SetMaterialBySlot(1, MMagicStone);
		Gateway10->SetMaterialBySlot(2, MPortalSurface);
		Gateway11->SetMaterialBySlot(0, MMagicStone);
		Gateway11->SetMaterialBySlot(1, MMagicStone);
		Gateway11->SetMaterialBySlot(2, MPortalSurface);
		Gateway12->SetMaterialBySlot(0, MMagicStone);
		Gateway12->SetMaterialBySlot(1, MMagicStone);
		Gateway12->SetMaterialBySlot(2, MPortalSurface);
		Gateway13->SetMaterialBySlot(0, MMagicStone);
		Gateway13->SetMaterialBySlot(1, MMagicStone);
		Gateway13->SetMaterialBySlot(2, MPortalSurface);
		Gateway14->SetMaterialBySlot(0, MMagicStone);
		Gateway14->SetMaterialBySlot(1, MMagicStone);
		Gateway14->SetMaterialBySlot(2, MPortalSurface);
		Gateway15->SetMaterialBySlot(0, MMagicStone);
		Gateway15->SetMaterialBySlot(1, MMagicStone);
		Gateway15->SetMaterialBySlot(2, MPortalSurface);
		Gateway16->SetMaterialBySlot(0, MMagicStone);
		Gateway16->SetMaterialBySlot(1, MMagicStone);
		Gateway16->SetMaterialBySlot(2, MPortalSurface);
		Gateway17->SetMaterialBySlot(0, MMagicStone);
		Gateway17->SetMaterialBySlot(1, MMagicStone);
		Gateway17->SetMaterialBySlot(2, MPortalSurface);

		FinishLine->SetMaterialBySlot(0, MFinishLine);

		// transforming the models location
		Boundary1->Transform.Location = Vector3(-5.0f, 0.0f, 5.0f);
		Boundary2->Transform.Location = Vector3(-5.0f, 0.0f, 0.0f);
		Boundary3->Transform.Location = Vector3(-5.0f, 0.0f, -5.0f);
		Boundary4->Transform.Location = Vector3(20.0f, 0.0f, 5.0f);
		Boundary5->Transform.Location = Vector3(20.0f, 0.0f, 0.0f);
		Boundary6->Transform.Location = Vector3(20.0f, 0.0f, -5.0f);
		Boundary7->Transform.Location = Vector3(-7.5f, 0.0f, 7.5f);
		Boundary8->Transform.Location = Vector3(-2.5f, 0.0f, 7.5f);
		Boundary9->Transform.Location = Vector3(2.5f, 0.0f, 7.5f);
		Boundary10->Transform.Location = Vector3(7.5f, 0.0f, 7.5f);
		Boundary11->Transform.Location = Vector3(12.5f, 0.0f, 7.5f);
		Boundary12->Transform.Location = Vector3(17.5f, 0.0f, 7.5f);
		Boundary13->Transform.Location = Vector3(-7.5f, 0.0f, -7.5f);
		Boundary14->Transform.Location = Vector3(-2.5f, 0.0f, -7.5f);
		Boundary15->Transform.Location = Vector3(2.5f, 0.0f, -7.5f);
		Boundary16->Transform.Location = Vector3(20.0f, 0.0f, -10.0f);
		Boundary17->Transform.Location = Vector3(20.0f, 0.0f, -15.0f);
		Boundary18->Transform.Location = Vector3(20.0f, 0.0f, -20.0f);
		Boundary19->Transform.Location = Vector3(17.5f, 0.0f, -22.5f);
		Boundary20->Transform.Location = Vector3(12.5f, 0.0f, -22.5f);
		Boundary21->Transform.Location = Vector3(7.5f, 0.0f, -22.5f);
		Boundary22->Transform.Location = Vector3(-10.0f, 0.0f, -10.0f);
		Boundary23->Transform.Location = Vector3(-10.0f, 0.0f, -15.0f);
		Boundary24->Transform.Location = Vector3(-10.0f, 0.0f, -20.0f);
		Boundary25->Transform.Location = Vector3(5.0f, 0.0f, -25.0f);
		Boundary26->Transform.Location = Vector3(5.0f, 0.0f, -30.0f);
		Boundary27->Transform.Location = Vector3(5.0f, 0.0f, -35.0f);
		Boundary28->Transform.Location = Vector3(2.5f, 0.0f, -37.5f);
		Boundary29->Transform.Location = Vector3(-2.5f, 0.0f, -37.5f);
		Boundary30->Transform.Location = Vector3(-7.5f, 0.0f, -37.5f);
		Boundary31->Transform.Location = Vector3(-12.5f, 0.0f, -37.5f);
		Boundary32->Transform.Location = Vector3(-17.5f, 0.0f, -37.5f);
		Boundary33->Transform.Location = Vector3(-22.5f, 0.0f, -37.5f);
		Boundary34->Transform.Location = Vector3(-12.5f, 0.0f, 7.5f);
		Boundary35->Transform.Location = Vector3(-17.5f, 0.0f, 7.5f);
		Boundary36->Transform.Location = Vector3(-22.5f, 0.0f, 7.5f);
		Boundary37->Transform.Location = Vector3(-25.0f, 0.0f, 5.0f);
		Boundary38->Transform.Location = Vector3(-25.0f, 0.0f, 0.0f);
		Boundary39->Transform.Location = Vector3(-25.0f, 0.0f, -5.0f);
		Boundary40->Transform.Location = Vector3(-25.0f, 0.0f, -10.0f);
		Boundary41->Transform.Location = Vector3(-25.0f, 0.0f, -15.0f);
		Boundary42->Transform.Location = Vector3(-25.0f, 0.0f, -20.0f);
		Boundary43->Transform.Location = Vector3(-25.0f, 0.0f, -25.0f);
		Boundary44->Transform.Location = Vector3(-25.0f, 0.0f, -30.0f);
		Boundary45->Transform.Location = Vector3(-25.0f, 0.0f, -35.0f);

		Gateway1->Transform.Location = Vector3(1.0f, -0.5f, 0.0f);
		Gateway2->Transform.Location = Vector3(5.0f, -0.5f, 3.0f);
		Gateway3->Transform.Location = Vector3(11.0f, -0.5f, -3.0f);
		Gateway4->Transform.Location = Vector3(16.0f, -0.5f, -8.0f);
		Gateway5->Transform.Location = Vector3(11.0f, -0.5f, -13.0f);
		Gateway6->Transform.Location = Vector3(5.0f, -0.5f, -13.0f);
		Gateway7->Transform.Location = Vector3(1.0f, -0.5f, -10.0f);
		Gateway8->Transform.Location = Vector3(-4.0f, -0.5f, -15.0f);
		Gateway9->Transform.Location = Vector3(-0.0f, -0.5f, -23.0f);
		Gateway10->Transform.Location = Vector3(-4.0f, -0.5f, -28.0f);
		Gateway11->Transform.Location = Vector3(-9.0f, -0.5f, -35.0f);
		Gateway12->Transform.Location = Vector3(-19.0f, -0.5f, -28.0f);
		Gateway13->Transform.Location = Vector3(-23.0f, -0.5f, -20.0f);
		Gateway14->Transform.Location = Vector3(-13.0f, -0.5f, -15.0f);
		Gateway15->Transform.Location = Vector3(-23.0f, -0.5f, -10.0f);
		Gateway16->Transform.Location = Vector3(-18.0f, -0.5f, -5.0f);
		Gateway17->Transform.Location = Vector3(-13.0f, -0.5f, 0.0f);

		FinishLine->Transform.Location = Vector3(-7.5f, 0.0f, 0.0f);
		
		// rotate to visible FOV
		Boundary1->Transform.Rotation.z += 90.0f;
		Boundary2->Transform.Rotation.z += 90.0f;
		Boundary3->Transform.Rotation.z += 90.0f;
		Boundary4->Transform.Rotation.z += 90.0f;
		Boundary5->Transform.Rotation.z += 90.0f;
		Boundary6->Transform.Rotation.z += 90.0f;
		Boundary7->Transform.Rotation.x += 90.0f;
		Boundary8->Transform.Rotation.x += 90.0f;
		Boundary9->Transform.Rotation.x += 90.0f;
		Boundary10->Transform.Rotation.x += 90.0f;
		Boundary11->Transform.Rotation.x += 90.0f;
		Boundary12->Transform.Rotation.x += 90.0f;
		Boundary13->Transform.Rotation.x += 90.0f;
		Boundary14->Transform.Rotation.x += 90.0f;
		Boundary15->Transform.Rotation.x += 90.0f;
		Boundary16->Transform.Rotation.z += 90.0f;
		Boundary17->Transform.Rotation.z += 90.0f;
		Boundary18->Transform.Rotation.z += 90.0f;
		Boundary19->Transform.Rotation.x += 90.0f;
		Boundary20->Transform.Rotation.x += 90.0f;
		Boundary21->Transform.Rotation.x += 90.0f;
		Boundary22->Transform.Rotation.z += 90.0f;
		Boundary23->Transform.Rotation.z += 90.0f;
		Boundary24->Transform.Rotation.z += 90.0f;
		Boundary25->Transform.Rotation.z += 90.0f;
		Boundary26->Transform.Rotation.z += 90.0f;
		Boundary27->Transform.Rotation.z += 90.0f;
		Boundary28->Transform.Rotation.x += 90.0f;
		Boundary29->Transform.Rotation.x += 90.0f;
		Boundary30->Transform.Rotation.x += 90.0f;
		Boundary31->Transform.Rotation.x += 90.0f;
		Boundary32->Transform.Rotation.x += 90.0f;
		Boundary33->Transform.Rotation.x += 90.0f;
		Boundary34->Transform.Rotation.x += 90.0f;
		Boundary35->Transform.Rotation.x += 90.0f;
		Boundary36->Transform.Rotation.x += 90.0f;
		Boundary37->Transform.Rotation.z += 90.0f;
		Boundary38->Transform.Rotation.z += 90.0f;
		Boundary39->Transform.Rotation.z += 90.0f;
		Boundary40->Transform.Rotation.z += 90.0f;
		Boundary41->Transform.Rotation.z+= 90.0f;
		Boundary42->Transform.Rotation.z += 90.0f;
		Boundary43->Transform.Rotation.z += 90.0f;
		Boundary44->Transform.Rotation.z += 90.0f;
		Boundary45->Transform.Rotation.z += 90.0f;

		Gateway1->Transform.Rotation.y = 90.0f;
		Gateway2->Transform.Rotation.y = 90.0f;
		Gateway3->Transform.Rotation.y = 0.0f;
		Gateway4->Transform.Rotation.y = 0.0f;
		Gateway5->Transform.Rotation.y = 45.0f;
		Gateway6->Transform.Rotation.y = 90.0f;
		Gateway7->Transform.Rotation.y = 90.0f;
		Gateway8->Transform.Rotation.y = 45.0f;
		Gateway9->Transform.Rotation.y = 0.0f;
		Gateway10->Transform.Rotation.y = 45.0f;
		Gateway11->Transform.Rotation.y = 90.0f;
		Gateway12->Transform.Rotation.y = -45.0f;
		Gateway13->Transform.Rotation.y = 0.0f;
		Gateway14->Transform.Rotation.y = 0.0f;
		Gateway15->Transform.Rotation.y = 0.0f;
		Gateway16->Transform.Rotation.y = 45.0f;
		Gateway17->Transform.Rotation.y = 90.0f;

		FinishLine->Transform.Rotation.y = 90.0f;

		// resize to required/desired scale
		Boundary1->Transform.Scale = Vector3(5.0f);
		Boundary2->Transform.Scale = Vector3(5.0f);
		Boundary3->Transform.Scale = Vector3(5.0f);
		Boundary4->Transform.Scale = Vector3(5.0f);
		Boundary5->Transform.Scale = Vector3(5.0f);
		Boundary6->Transform.Scale = Vector3(5.0f);
		Boundary7->Transform.Scale = Vector3(5.0f);
		Boundary8->Transform.Scale = Vector3(5.0f);
		Boundary9->Transform.Scale = Vector3(5.0f);
		Boundary10->Transform.Scale = Vector3(5.0f);
		Boundary11->Transform.Scale = Vector3(5.0f);
		Boundary12->Transform.Scale = Vector3(5.0f);
		Boundary13->Transform.Scale = Vector3(5.0f);
		Boundary14->Transform.Scale = Vector3(5.0f);
		Boundary15->Transform.Scale = Vector3(5.0f);
		Boundary16->Transform.Scale = Vector3(5.0f);
		Boundary17->Transform.Scale = Vector3(5.0f);
		Boundary18->Transform.Scale = Vector3(5.0f);
		Boundary19->Transform.Scale = Vector3(5.0f);
		Boundary20->Transform.Scale = Vector3(5.0f);
		Boundary21->Transform.Scale = Vector3(5.0f);
		Boundary22->Transform.Scale = Vector3(5.0f);
		Boundary23->Transform.Scale = Vector3(5.0f);
		Boundary24->Transform.Scale = Vector3(5.0f);
		Boundary25->Transform.Scale = Vector3(5.0f);
		Boundary26->Transform.Scale = Vector3(5.0f);
		Boundary27->Transform.Scale = Vector3(5.0f);
		Boundary28->Transform.Scale = Vector3(5.0f);
		Boundary29->Transform.Scale = Vector3(5.0f);
		Boundary30->Transform.Scale = Vector3(5.0f);
		Boundary31->Transform.Scale = Vector3(5.0f);
		Boundary32->Transform.Scale = Vector3(5.0f);
		Boundary33->Transform.Scale = Vector3(5.0f);
		Boundary34->Transform.Scale = Vector3(5.0f);
		Boundary35->Transform.Scale = Vector3(5.0f);
		Boundary36->Transform.Scale = Vector3(5.0f);
		Boundary37->Transform.Scale = Vector3(5.0f);
		Boundary38->Transform.Scale = Vector3(5.0f);
		Boundary39->Transform.Scale = Vector3(5.0f);
		Boundary40->Transform.Scale = Vector3(5.0f);
		Boundary41->Transform.Scale = Vector3(5.0f);
		Boundary42->Transform.Scale = Vector3(5.0f);
		Boundary43->Transform.Scale = Vector3(5.0f);
		Boundary44->Transform.Scale = Vector3(5.0f);
		Boundary45->Transform.Scale = Vector3(5.0f);

		Gateway1->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway2->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway3->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway4->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway5->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway6->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway7->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway8->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway9->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway10->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway11->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway12->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway13->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway14->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway15->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway16->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);
		Gateway17->Transform.Scale = Vector3(1.0f, 1.0f, 0.5f);

		FinishLine->Transform.Scale = Vector3(0.5f, 0.5f, 0.75f);
	}

	// as long as the game is not over run the loop
	while (!bIsGameOver) {
		// make sure we process what the user has done
		ProcessInput();
		// apply the logic base on the inputs and the game logic
		Update();
		// render the screen based on the 2 functions above
		Draw();
	}

	CloseGame();
}

void Game::ProcessInput()
{
	// run the input detection for our game input
	GameInput->ProcessInput();

	Vector3 CameraInput = Vector3(0.0f);
	CDirection CamDirections = Graphics->EngineDefaultCam->GetDirections();
	//CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	// move cam Forward
	if (GameInput->IsKeyPressed(SDL_SCANCODE_W)) {
		/* Unable to figure out way to make it so turning the camera re-initiates the forward ability, while also locking appropriate lateral 
		movement
		Also, very tedious to add for every Boundary instance

		// stops forward momentum when collided with Boundary1
		if (Boundary1 != nullptr && !CamCol->IsOverlapping(*Boundary1->GetCollision())) {
			CameraInput += CamDirections.Forward;
		}
		
		*/
		CameraInput += CamDirections.Forward;
	}
	// move cam Backward
	if (GameInput->IsKeyPressed(SDL_SCANCODE_S)) {
		CameraInput += -CamDirections.Forward;
	}
	// move cam Left
	if (GameInput->IsKeyPressed(SDL_SCANCODE_A)) {
		CameraInput += -CamDirections.Right;
	}
	// move cam Right
	if (GameInput->IsKeyPressed(SDL_SCANCODE_D)) {
		CameraInput += CamDirections.Right;
	}
	// move cam Up
	if (GameInput->IsKeyPressed(SDL_SCANCODE_Q)) {
		CameraInput += CamDirections.Up;
	}
	// move cam Down
	if (GameInput->IsKeyPressed(SDL_SCANCODE_E)) {
		CameraInput += -CamDirections.Up;
	}
	
	// move the camera based on input
	Graphics->EngineDefaultCam->AddMovementInput(CameraInput);

	if (GameInput->IsMouseButtonPressed(MouseButtons::RIGHT)) {
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta);
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta);
		GameInput->ShowCursor(false);
	}
	else {
		GameInput->ShowCursor(true);
	}
}

void Game::Update()
{
	// Set delta time first always
	static double LastFrameTime = 0.0;
	// set current time since the game has passed
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	// find the time difference between Last and Current frame
	double NewDeltaTime = CurrentFrameTime - LastFrameTime;
	// set delta time as seconds
	DeltaTime = NewDeltaTime / 1000.0;
	// update the last frame time for the next iteration
	LastFrameTime = CurrentFrameTime;

	// TODO: Handle Update
	// Model2->Transform.Location.z += -0.1f * GetFDeltaTime();

	Graphics->EngineDefaultCam->Update();

	// do collision stuff
	CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	// if we run into the wall remove it from the game
	if (Gateway1 != nullptr && CamCol->IsOverlapping(*Gateway1->GetCollision())) {
		RemoveModelFromGame(Gateway1);
	}
	if ((Gateway1 == nullptr && Gateway2 != nullptr) && CamCol->IsOverlapping(*Gateway2->GetCollision())) {
		RemoveModelFromGame(Gateway2);
	}
	if ((Gateway2 == nullptr && Gateway3 != nullptr) && CamCol->IsOverlapping(*Gateway3->GetCollision())) {
		RemoveModelFromGame(Gateway3);
	}
	if ((Gateway3 == nullptr && Gateway4 != nullptr) && CamCol->IsOverlapping(*Gateway4->GetCollision())) {
		RemoveModelFromGame(Gateway4);
	}
	if ((Gateway4 == nullptr && Gateway5 != nullptr) && CamCol->IsOverlapping(*Gateway5->GetCollision())) {
		RemoveModelFromGame(Gateway5);
	}
	if ((Gateway5 == nullptr && Gateway6 != nullptr) && CamCol->IsOverlapping(*Gateway6->GetCollision())) {
		RemoveModelFromGame(Gateway6);
	}
	if ((Gateway6 == nullptr && Gateway7 != nullptr) && CamCol->IsOverlapping(*Gateway7->GetCollision())) {
		RemoveModelFromGame(Gateway7);
	}
	if ((Gateway7 == nullptr && Gateway8 != nullptr) && CamCol->IsOverlapping(*Gateway8->GetCollision())) {
		RemoveModelFromGame(Gateway8);
	}
	if ((Gateway8 == nullptr && Gateway9 != nullptr) && CamCol->IsOverlapping(*Gateway9->GetCollision())) {
		RemoveModelFromGame(Gateway9);
	}
	if ((Gateway9 == nullptr && Gateway10 != nullptr) && CamCol->IsOverlapping(*Gateway10->GetCollision())) {
		RemoveModelFromGame(Gateway10);
	}
	if ((Gateway10 == nullptr && Gateway11 != nullptr) && CamCol->IsOverlapping(*Gateway11->GetCollision())) {
		RemoveModelFromGame(Gateway11);
	}
	if ((Gateway11 == nullptr && Gateway12 != nullptr) && CamCol->IsOverlapping(*Gateway12->GetCollision())) {
		RemoveModelFromGame(Gateway12);
	}
	if ((Gateway12 == nullptr && Gateway13 != nullptr) && CamCol->IsOverlapping(*Gateway13->GetCollision())) {
		RemoveModelFromGame(Gateway13);
	}
	if ((Gateway13 == nullptr && Gateway14 != nullptr) && CamCol->IsOverlapping(*Gateway14->GetCollision())) {
		RemoveModelFromGame(Gateway14);
	}
	if ((Gateway14 == nullptr && Gateway15 != nullptr) && CamCol->IsOverlapping(*Gateway15->GetCollision())) {
		RemoveModelFromGame(Gateway15);
	}
	if ((Gateway15 == nullptr && Gateway16 != nullptr) && CamCol->IsOverlapping(*Gateway16->GetCollision())) {
		RemoveModelFromGame(Gateway16);
	}
	if ((Gateway16 == nullptr && Gateway17 != nullptr) && CamCol->IsOverlapping(*Gateway17->GetCollision())) {
		RemoveModelFromGame(Gateway17);
	}
	if ((Gateway17 == nullptr && FinishLine != nullptr) && CamCol->IsOverlapping(*FinishLine->GetCollision())) {
		CloseApp();
	}
}

void Game::Draw()
{
	Graphics->ClearGraphics();

	// TODO: Draw graphics to the screen
	Graphics->Draw();

	//Gateway1->GetCollision()->DebugDraw(Vector3(255));
	//FinishLine->GetCollision()->DebugDraw(Vector3(255));

	Graphics->PresentGraphics();
}

void Game::CloseGame()
{
	// TODO: Clean up code
	delete GameInput;
}
