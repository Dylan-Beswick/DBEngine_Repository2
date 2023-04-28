#pragma once
#include "DBEngine/CoreMinimal.h"

class Input;

class Game {
public:
	// Get the game instance or create one if it doesn't exist
	static Game& GetGameInstance();

	// Destroy the game running the destructor
	static void DestroyGameInstance();

	// Start the game/app
	// Load the window
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	// get precise delta time
	double GetDeltaTime() { return DeltaTime; }

	// get less precise delta time
	float GetFDeltaTime() { return static_cast<float>(DeltaTime); }

	// return the graphics engine
	GraphicsEnginePtr GetGraphicsEngine() { return Graphics; }

	// set the bIsGameOver to true
	void CloseApp() { bIsGameOver = true; }

	// return the graphics engine default texture
	TexturePtr GetDefaultEngineTexture();

	// return the graphics engine default material
	MaterialPtr GetDefaultEngineMaterial();

	// remove a model from everywhere it needs to be removed
	void RemoveModelFromGame(ModelPtr& ModelToRemove);

private:
	Game();
	~Game();

	// Run the game loop
	void Run();

	// Handle the Input
	void ProcessInput();

	// Handle Game Logic
	void Update();

	// Handle the 3D graphics drawing to the screen
	// Will clear and present each frame
	void Draw();

	// Handle anything that needs to be deleted when the game ends
	void CloseGame();

private:
	// boolean that ends the game
	bool bIsGameOver;

	// shared pointer to the Graphics class
	GraphicsEnginePtr Graphics;

	// this is the time between each frame
	double DeltaTime;

	// read the input of the player
	Input* GameInput;

	// Temporary mesh variables
	ModelPtr Model2;
	ModelPtr Model;

	ModelPtr Wall;
	ModelPtr Wall2;
};