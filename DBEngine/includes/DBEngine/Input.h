#pragma once
#include "SDL2/SDL.h"

enum MouseButtons {
	LEFT = SDL_BUTTON_LEFT,
	MIDDLE = SDL_BUTTON_MIDDLE,
	RIGHT = SDL_BUTTON_RIGHT
};

class Input {
public:
	Input();

	// detect the input of the user
	void ProcessInput();

	// detect if a specific key is down based on an sdl scancode
	// Hint* SDL_SCANCODE_"Key"
	bool IsKeyPressed(SDL_Scancode Key);

	// detect if the mouse button inputed is being pressed down
	bool IsMouseButtonPressed(MouseButtons Button);

private:
	// update the mouse button states with the current state of the mouse
	void SetMouseButtonStates(Uint8 ButtonIndex, bool CurrentState);

	// handle the varaibles that rely on mouse motion
	void OnMouseMove(SDL_MouseMotionEvent& MEvent);

	void OnMouseScroll(SDL_MouseWheelEvent& MEvent);

public:
	// Mouse position
	int MouseX, MouseY;

	// How far the mouse has moved since the last check/tick
	int MouseXDelta, MouseYDelta;

	// How far the player has scrolled since the last frame
	float ScrollDetla;

private:
	// keyboard current states
	const Uint8* KeyboardState;

	// mouse button current states
	bool MouseButtonStates[10] = { false };

};