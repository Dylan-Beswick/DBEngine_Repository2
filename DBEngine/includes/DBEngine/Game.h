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
	ModelPtr Boundary1;
	ModelPtr Boundary2;
	ModelPtr Boundary3;
	ModelPtr Boundary4;
	ModelPtr Boundary5;
	ModelPtr Boundary6;
	ModelPtr Boundary7;
	ModelPtr Boundary8;
	ModelPtr Boundary9;
	ModelPtr Boundary10;
	ModelPtr Boundary11;
	ModelPtr Boundary12;
	ModelPtr Boundary13;
	ModelPtr Boundary14;
	ModelPtr Boundary15;
	ModelPtr Boundary16;
	ModelPtr Boundary17;
	ModelPtr Boundary18;
	ModelPtr Boundary19;
	ModelPtr Boundary20;
	ModelPtr Boundary21;
	ModelPtr Boundary22;
	ModelPtr Boundary23;
	ModelPtr Boundary24;
	ModelPtr Boundary25;
	ModelPtr Boundary26;
	ModelPtr Boundary27;
	ModelPtr Boundary28;
	ModelPtr Boundary29;
	ModelPtr Boundary30;
	ModelPtr Boundary31;
	ModelPtr Boundary32;
	ModelPtr Boundary33;
	ModelPtr Boundary34;
	ModelPtr Boundary35;
	ModelPtr Boundary36;
	ModelPtr Boundary37;
	ModelPtr Boundary38;
	ModelPtr Boundary39;
	ModelPtr Boundary40;
	ModelPtr Boundary41;
	ModelPtr Boundary42;
	ModelPtr Boundary43;
	ModelPtr Boundary44;
	ModelPtr Boundary45;

	ModelPtr Gateway1;
	ModelPtr Gateway2;
	ModelPtr Gateway3;
	ModelPtr Gateway4;
	ModelPtr Gateway5;
	ModelPtr Gateway6;
	ModelPtr Gateway7;
	ModelPtr Gateway8;
	ModelPtr Gateway9;
	ModelPtr Gateway10;
	ModelPtr Gateway11;
	ModelPtr Gateway12;
	ModelPtr Gateway13;
	ModelPtr Gateway14;
	ModelPtr Gateway15;
	ModelPtr Gateway16;
	ModelPtr Gateway17;
	ModelPtr Gateway18;
	ModelPtr Gateway19;
	ModelPtr Gateway20;

	ModelPtr FinishLine;
};