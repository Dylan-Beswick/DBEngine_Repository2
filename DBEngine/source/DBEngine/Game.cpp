#include "DBEngine/Game.h"
#include "DBEngine/Graphics/GraphicsEngine.h"
#include "DBEngine/Graphics/Mesh.h"
#include "DBEngine/Input.h"
#include "DBEngine/Graphics/Camera.h"

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

		// create VAOs
		Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextrueShader, { TConcrete });
		Poly2 = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextrueShader, { TGrid });

		Poly->Transform.Location = Vector3(1.0f, 0.0f, -1.0f); 
		Poly2->Transform.Location = Vector3(1.0f, 0.0f, 1.0f);
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
	Poly->Transform.Rotation.x += 50.0f * GetFDeltaTime();
	Poly->Transform.Rotation.y += 50.0f * GetFDeltaTime();
	Poly->Transform.Rotation.z += 50.0f * GetFDeltaTime();

	Poly2->Transform.Rotation.x += -50.0f * GetFDeltaTime();
	Poly2->Transform.Rotation.y += -50.0f * GetFDeltaTime();
	Poly2->Transform.Rotation.z += -50.0f * GetFDeltaTime();

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

	CameraInput *= 3.0f * GetFDeltaTime();

	Vector3 NewLocation = Graphics->EngineDefaultCam->GetTransforms().Location += CameraInput;
	Graphics->EngineDefaultCam->Translate(NewLocation);

	if (GameInput->IsMouseButtonPressed(MouseButtons::RIGHT)) {
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime() * 25.0f);
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime() * 25.0f);
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
