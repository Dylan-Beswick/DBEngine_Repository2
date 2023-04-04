#include "DBEngine/Graphics/GraphicsEngine.h"
#include "GL/glew.h"
#include "DBEngine/Graphics/Model.h"
#include "DBEngine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "DBEngine/Graphics/Texture.h"
#include "DBEngine/Graphics/Camera.h"
#include "DBEngine/Graphics/Material.h"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
	// initialise out camera back a little bit
	EngineDefaultCam = make_shared<Camera>();
}

GraphicsEngine::~GraphicsEngine()
{
	// clear the model stack
	ModelStack.clear();

	// clear the shader
	Shader = nullptr;

	// remove textures from memory
	TextureStack.clear();

	// this will handle deleting the SDL window from memory
	SDL_DestroyWindow(SdlWindow);
	// destroy the GL context for SDL
	SDL_GL_DeleteContext(SdlGLContext);
	// close the SDL framework
	SDL_Quit();

	cout << "Destroy Graphics Engine..." << endl;
}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	// make sure SDL initialises
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL failed: " << SDL_GetError() << endl;
		return false;
	}

	// Use OpenGL 3.1 and set default attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // OpenGL "4".6
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6); // OpenGL 4".6"
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // Using default profile
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Transparency level
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // How many bits of allocation awarded to "RED" colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // How many bits of allocation awarded to "GREEN" colour
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // How many bits of allocation awarded to "BLUE" colour

	// Set the fullscreen flag
	int FullScreenFlag = 0;

	if (bFullscreen) {
		FullScreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	else {
		FullScreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	// create the SDL2 window
	SdlWindow = SDL_CreateWindow(
		WTitle, // title of the window
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // location of the window
		WWidth, WHeight, // width and height of the window
		FullScreenFlag
	);

	// if the window fails then error log
	if (SdlWindow == nullptr) {
		cout << "SDL window failed: " << SDL_GetError() << endl;
		return false;
	}

	// add all the gl attributes to the window
	SdlGLContext = SDL_GL_CreateContext(SdlWindow);

	if (SdlGLContext == NULL) {
		cout << "SDL GL Context failed: " << SDL_GetError() << endl;
		return false;
	}

	// To make glew work we need to mark experimental true
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK) {
		cout << "GLEW failed: " << glewGetErrorString(InitGLEW) << endl;
		return false;
	}

	// enable 3D depth
	glEnable(GL_DEPTH_TEST);

	// create the default engine texture
	DefaultEngineTexture = CreateTexture("Game/Textures/DefaultTexture.png");
	// create the default engine material
	// materials when created auto assigned the default texture
	DefaultEngineMaterial = make_shared<Material>();

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	// present the new graphics using opengl
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	// set the background colour
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireframeMode(false);

	// run through each model and call its draw method
	for (ModelPtr LModel : ModelStack) {
		LModel->Draw();
	}

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

ModelPtr GraphicsEngine::CreateSimpleModelShape(GeometricShapes Shape, ShaderPtr MeshShader)
{
	// initialise a new model class
	ModelPtr NewModel = make_shared<Model>();

	// make sure it worked
	if (!NewModel->CreateSimpleMesh(Shape, MeshShader)) {
		return nullptr;
	}

	// add mesh into the stack of modelss to be renderer
	ModelStack.push_back(NewModel);

	// return the new model
	return NewModel;
}

ShaderPtr GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	// create a new shader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();

	// initialise the shader into openGL
	NewShader->InitVFShader(ShaderFilePaths);

	// add the shader to our graphics engine
	Shader = NewShader;

	return NewShader;
}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{
	TexturePtr NewTexture = nullptr;

	// Run through all the textures and check if one with same path exists
	for (TexturePtr TestTexture : TextureStack) {
		// if we find a texture with the same file path
		if (TestTexture->GetFilePath() == FilePath) {
			// pass in the already created texture
			NewTexture = TestTexture;
			cout << "Texture found! Assigning current texture." << endl;
			break;
		}
	}

	// if there is no texture alredy in existance
	if (NewTexture == nullptr) {
		cout << "Creating a new texture..." << endl;

		// create a new texture as a shared_ptr
		NewTexture = make_shared<Texture>();

		// if the file was found, assign it to the texture stack
		if (NewTexture->CreateTextureFromFilePath(FilePath)) {
			cout << "Texture " << NewTexture->GetID() << " creation success! Adding to Texture Stack." << endl;

			// ass the texture to the texture stack
			TextureStack.push_back(NewTexture);
		}
	}

	return NewTexture;
}

void GraphicsEngine::ApplyScreenTransformation(ShaderPtr Shader)
{
	// the angle of the camera planes - basically your zoom
	float FOV = EngineDefaultCam->GetCameraData().FOV;
	// find the size of the screen
	int WWidth, WHeight = 0;
	// use sdl to get the size of the window
	SDL_GetWindowSize(SdlWindow, &WWidth, &WHeight);
	// calculate the aspect ratio from the window size
	float AR = static_cast<float>(WWidth) / static_cast<float>(max(WHeight, 1));

	// create the default coordinates for the projection and view
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// update the coordinates for 3D
	view = EngineDefaultCam->GetViewMatrix();
	// create the perspective view to allow us to see in 3D
	// also adjusting the near and far clip
	projection = glm::perspective(glm::radians(FOV), AR,
		EngineDefaultCam->GetCameraData().NearClip, EngineDefaultCam->GetCameraData().FarClip);

	Shader->SetMat4("view", view);
	Shader->SetMat4("projection", projection);
}

void GraphicsEngine::HandleWireframeMode(bool bShowWireframeMode)
{
	// if wireframe mode is set, change it, and visa versa
	if (bShowWireframeMode != bWireframeMode) {
		bWireframeMode = bShowWireframeMode;

		// change how OpenGL renders between the vertices
		if (bWireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		cout << "Wireframe Mode Updated..." << endl;
	}
}
