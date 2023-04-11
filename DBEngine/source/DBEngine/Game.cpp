#include "DBEngine/Game.h"
#include "DBEngine/Graphics/GraphicsEngine.h"
#include "DBEngine/Graphics/Model.h"
#include "DBEngine/Input.h"
#include "DBEngine/Graphics/Camera.h"
#include "DBEngine/Graphics/Material.h"

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
		TexturePtr TGrid = Graphics->CreateTexture("Game/Textures/ColourGrid.jpg");

		// create the materials
		MaterialPtr MConcrete = make_shared<Material>();
		MaterialPtr MGrid = make_shared<Material>();

		// assign the base colour of the materails using the textures
		MConcrete->BaseColour = TConcrete;
		MGrid->BaseColour = TGrid;

		// create VAOs
		Model = Graphics->CreateSimpleModelShape(GeometricShapes::Cube, TextrueShader);
		Model2 = Graphics->CreateSimpleModelShape(GeometricShapes::Cube, TextrueShader);

		// set materials of the models
		Model->SetMaterialBySlot(0, MGrid);
		Model2->SetMaterialBySlot(0, MConcrete);

		// transforming the models location
		Model->Transform.Location = Vector3(1.0f, 0.0f, -1.0f); 
		Model2->Transform.Location = Vector3(1.0f, 0.0f, 1.0f);

		// import custom meshes
		Wall = Graphics->ImportModel("Game/Models/damaged-wall/source/SM_WallDamaged.obj", TextrueShader);
		Wall2 = Graphics->ImportModel("Game/Models/damaged-wall/source/SM_WallDamaged.obj", TextrueShader);

		// transform the wall
		Wall->Transform.Scale = Vector3(0.05f);
		Wall->Transform.Rotation.y = 90.0f;
		Wall->Transform.Location = Vector3(2.0f, -2.0f, 0.0f);

		Wall2->Transform.Scale = Vector3(0.05f);
		Wall2->Transform.Rotation.y = 90.0f;
		Wall2->Transform.Location = Vector3(5.0f, -2.0f, 0.0f);

		// create the texture
		TexturePtr TWall = Graphics->CreateTexture("Game/Models/damaged-wall/textures/T_Wall_Damaged_BC.png");

		// create a material
		MaterialPtr MWall = make_shared<Material>();
		MWall->BaseColour = TWall;

		// apply the material
		Wall->SetMaterialBySlot(1, MWall);
		Wall2->SetMaterialBySlot(1, MWall);
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
	Model->Transform.Rotation.x += 50.0f * GetFDeltaTime();
	Model->Transform.Rotation.y += 50.0f * GetFDeltaTime();
	Model->Transform.Rotation.z += 50.0f * GetFDeltaTime();

	Model2->Transform.Rotation.x += -50.0f * GetFDeltaTime();
	Model2->Transform.Rotation.y += -50.0f * GetFDeltaTime();
	Model2->Transform.Rotation.z += -50.0f * GetFDeltaTime();

	Vector3 CameraInput = Vector3(0.0f);
	CDirection CamDirections = Graphics->EngineDefaultCam->GetDirections();

	// move cam Forward
	if (GameInput->IsKeyPressed(SDL_SCANCODE_W)) {
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
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime());
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime());
		GameInput->ShowCursor(false);
	}
	else {
		GameInput->ShowCursor(true);
	}

	/*
	// reset FOV
	if (GameInput->IsKeyPressed(SDL_SCANCODE_F)) {
		float FOV = 90.0f;
		Graphics->EngineDefaultCam->GetCameraData().FOV = FOV;
	}*/
}

void Game::Draw()
{
	// TODO: Draw graphics to the screen
	Graphics->Draw();
}

void Game::CloseGame()
{
	// TODO: Clean up code
	delete GameInput;
}
