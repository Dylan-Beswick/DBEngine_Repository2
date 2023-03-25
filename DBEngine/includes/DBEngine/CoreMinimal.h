#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int unInt;

// class/type definitions
class GraphicsEngine;
typedef shared_ptr<GraphicsEngine> GraphicsEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;

class Texture;
typedef shared_ptr<Texture> TexturePtr;
typedef vector<TexturePtr> TexturePtrStack;

class ShaderProgram;
typedef shared_ptr<ShaderProgram> ShaderPtr;

class Mesh;
typedef shared_ptr<Mesh> MeshPtr;
typedef vector<MeshPtr> MeshPtrStack;

class Camera;
typedef shared_ptr<Camera> CameraPtr;

// useful for shape data and VAO Matrices
typedef vector<float> PositionMatrix;
typedef vector<unInt> IndicesMatrix;

// this structure will handle matrices for VAOs
struct ShapeData {
	vector<float> PositionMatrix;
	vector<unInt> IndicesMatrix;
};

// a list of the Geometric shapes available in the VAO
enum class GeometricShapes {
	Triangle = 0,
	Square,
	Circle,
	Cube
};

// store the parameters required to create a shader program
struct VFShaderParams
{
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

// the types of shaders that can be accepted in our shader program
enum class ShaderTypes {
	Vertex = 0,
	Fragment
};