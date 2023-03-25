#pragma once
#include "DBEngine/Math/Transformations.h"

struct STCameraData {
	// how fast the camrea can move
	float Speed = 25.0f;

	// basically the zoom
	// how much of the view space the camera can see - in degrees
	// think peripheral vision
	float FOV = 70.0f;

	// how close can models get to the camera before disappearing
	float NearClip = 0.01f;
	// opposide of near clip
	float FarClip = 1000.0f;
};

class Camera {
public:
	Camera();

	// move camera in 3D space to a location
	void Translate(Vector3 Location);

	// retun the transform
	CTransform GetTransforms() const { return Transform; }

	// return the current facing directions
	CDirection GetDirections() const { return Directions; }

	// return the extra camera info
	// Speed, FOV, Near Clip, and Far Clip
	STCameraData GetCameraData() const { return CameraData; }

	// return a view matrix that considers position AND rotation
	glm::mat4 GetViewMatrix() const;

	// rotate the camera based on yaw
	void RotatePitch(float Amount);

	// rotate the camera based on pitch
	void RotateYaw(float Amount);

private:
	// find the current direction vectors based on the rotation of the YAW and PITCH of the camera
	void UpdateDirectionVectors();

private:
	// transforms of the camera
	// location, rotation, scale - we don't need scale
	CTransform Transform;

	// forward, right, and up directions
	CDirection Directions;

	// hold all the extra camera info
	STCameraData CameraData;

};