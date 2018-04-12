#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtx\transform.hpp>

#include <Windows.h>
#include <GL\glew.h>
#include "graphics\Shader.h"

#include "graphics\Camera.h"

Camera::Camera(Shader *shader, float w, float h)
{
	this->shader = shader;
	this-> vpUniform = this->shader->getUniformLocation("mvpMatrix");
	this->projectionMatrix = glm::perspective(glm::radians(45.0f), w / h , 0.05f, 1000.0f);  
	
}

void Camera::setShader(Shader *shader)
{
	this->shader = shader;
	this->vpUniform = this->shader->getUniformLocation("mvpMatrix");
}


void Camera::setTranslation(float x, float y, float z)
{
	
	this->translation = glm::translate(glm::mat4(1.0f), glm::vec3(-x, -y, -z));
	this->updateViewMatrix();
}
void Camera::Translate(float x, float y, float z)
{
	this->translation = glm::translate(this->translation, glm::vec3(-x, -y, -z)); // tranlating from previous tranlation point 
	this->updateViewMatrix();
}


void Camera::setRotaion(float rotation, float x, float y, float z)
{
	this->rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(x, y, z)); // tranlating from previous tranlation point 
	this->updateViewMatrix();
}
void Camera::Rotate(float rotation, float x, float y, float z)
{
	this->rotation = glm::rotate(this->rotation, glm::radians(rotation), glm::vec3(x, y, z)); // tranlating from previous tranlation point 
	this->updateViewMatrix();
}
void Camera::Update(){
	
	this->shader->setUniformMatrix(this->vpUniform, this->projectionMatrix * this->viewMatrix); // the order of projection and view matrices is also important
}


void Camera :: updateViewMatrix()
{
	this->viewMatrix = this->rotation * this->translation;	// order of operations can chage it completely
	// we first rotate so that translation occurs on adjusted axes 
}
/*
detail::tmat4x4<T> glm::perspective	(	T const & 	fovy,
										T const & 	aspect,
										T const & 	near,
										T const & 	far
									)
Creates a matrix for a symetric perspective-view frustum.

Parameters
fovy	Expressed in radians if GLM_FORCE_RADIANS is define or degrees otherwise.
aspect
near
far
)	*/


/*
detail::tmat4x4<T> glm::translate	(	detail::tmat4x4< T > const & 	m,
detail::tvec3< T > const & 	v
)
Builds a translation 4 * 4 matrix created from a vector of 3 components.

Parameters
m	Input matrix multiplied by this translation matrix.
v	Coordinates of a translation vector.
Template Parameters
T	Value type used to build the matrix. Currently supported: half (not recommanded), float or double.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
...
glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f));
// m[0][0] == 1.0f, m[0][1] == 0.0f, m[0][2] == 0.0f, m[0][3] == 0.0f
// m[1][0] == 0.0f, m[1][1] == 1.0f, m[1][2] == 0.0f, m[1][3] == 0.0f
// m[2][0] == 0.0f, m[2][1] == 0.0f, m[2][2] == 1.0f, m[2][3] == 0.0f
// m[3][0] == 1.0f, m[3][1] == 1.0f, m[3][2] == 1.0f, m[3][3] == 1.0f
*/