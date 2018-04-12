#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	Camera(Shader *shader, float w, float h); //pass the aspect ratio
	void setShader(Shader *shader);

	void setTranslation(float x, float y, float z); // Going to set the postion of the camera
	void setRotaion(float rotation, float x, float y, float z); //sets what the rotation is currently
	void Translate(float x, float y, float z); // for the translation of the character
	void Rotate(float rotation, float x, float y, float z); //rotates over the current rotation
	void Update();
private:
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	glm::mat4 translation;
	glm::mat4 rotation;

	Shader *shader;
	int vpUniform; //view_projection_uniform value
	void updateViewMatrix();
};