//#include <cstdio>
//#include <cstdlib>
#include <iostream>
#include <vector>

//include shape, shader header files
#include "GLerror.h"
#include "SDL_Start.h"
#include "Triangle_T.h"
#include "Circle.h"
#include "CircleTexture.h"
#include "Square.h"
#include "Camera.h"
#include "Cube.h"
#include "Model.h"
#include "ModelLoaderClass.h"
#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H
#ifndef SHADERCLASS_H
#define SHADERCLASS_H

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#ifndef GLEW_H
#define GLEW_H
//#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#ifndef SDL_H
#define SDL_H
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_mixer.h"
//#include "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//***************
//variables
SDL_Event event;
SDL_Window *win;
bool windowOpen = true;
bool isFullScreen = false;
float bubbleSpeed = -0.001f;
float radius;
//screen boundaries for collision tests
float bX_r = 2.0f;
float bX_l = -2.0f;
float bY_t = 1.0f;
float bY_b = -1.0f;
//screen centre
float centreX = 0.0f;
float centreY = 0.0f;
//window aspect/width/height
int w;
int h;
float aspect;
int left;
int newwidth;
int newheight;

//transform matrices
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
glm::mat3 normalMatrix;

glm::mat4 translate;
glm::mat4 circleTranslate;
glm::mat4 circleScale;
glm::mat4 rotate;
glm::mat4 scale;
glm::mat4 backgroundTranslate;
glm::mat4 backgroundScale;
glm::vec3 b_scaleFactor;
glm::mat4 cubeScale;
glm::mat4 cubeRotate;
glm::mat4 cubeTranslate;
glm::mat4 modelRotate;
glm::mat4 modelScale;
glm::mat4 modelTranslate;
float angle = 0;

std::vector<CircleTexture> circles;

//create camera
Camera cam;
//loac camera variables
glm::vec3 camPos;
glm::vec3 camTarget;

bool flag = true;

glm::vec3 lightCol;
glm::vec3 lightPosition;
glm::vec3 viewPosition;
float ambientIntensity;

//**************
//function prototypes
CircleTexture updatePositions(CircleTexture c);
void handleInput();

int main(int argc, char *argv[]) {
	//start and initialise SDL
	SDL_Start sdl;
	SDL_GLContext context = sdl.Init();
	win = sdl.win;

	SDL_GetWindowSize(win, &w, &h);
	glViewport(0, 0, w, h);
	aspect = (float)w / (float)h;

	//error class
	GLerror glerr;
	int errorLabel;

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	//register debug callback
	if (glDebugMessageCallback)
	{
		std::cout << "Registering OpenGL Debug callback function" << std::endl;
		glDebugMessageCallback(glerr.openglCallbackFunction, &errorLabel);
		glDebugMessageControl(GL_DONT_CARE,
			GL_DONT_CARE,
			GL_DONT_CARE,
			0,
			NULL,
			true);
	}

	//*****************************************************
	//OpenGL specific data

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//objects
	//create cube
	Cube cube;
	//create background square
	Square background;
	//create model
	//could make this better by specifying the texture in this model header
	Model model;
	//create model loader
	ModelImport modelLoader; 
	modelLoader.LoadOBJ2("..//..//Assets//Models//blenderCube.obj", model.vertices, model.texCoords, model.normals, model.indices);

	errorLabel = 0;

	//*********************
	//create texture collection
	//create textures - space for 4, but only using 2
	Texture texArray[4];
	//background texture
	texArray[0].load("..//..//Assets//Textures//sky.png");
	texArray[0].setBuffers();
	texArray[1].load("..//..//Assets//Textures//carbon-fibre-seamless-texture.jpg");
	texArray[1].setBuffers();

	errorLabel = 2;

	//OpenGL buffers

	cube.setBuffers();
	background.setBuffers();
	model.setBuffers();

	errorLabel = 3;
	//*****************************************
	//set uniform variables
	int transformLocation;
	int modelLocation;
	int viewLocation;
	int projectionLocation;
	int importModelLocation;
	int importViewLocation;
	int importProjectionLocation;
	int backgroundColourLocation;
	int ambientIntensityLocation;
	int cubeModelLocation;
	int cubeViewLocation;
	int cubeProjectionLocation;
	int modelColourLocation;
	int modelAmbientLocation;
	int lightColLocation;
	int normalMatrixLocation;
	int lightPositionLocation;
	int viewPositionLocation;

	GLuint currentTime = 0;
	GLuint lastTime = 0;
	GLuint elapsedTime = 0;

	//lighting for the cube
	//Light position setting
	lightPosition = glm::vec3(0.6f, 0.0f, 0.5f);
	//light colour setting
	// Candle:  r:1.0 g:0.57 b:0.16
	// 100W bulb: r:1.0 g:0.84 b:0.66
	// direct sunlight: r:1.0 g:1.0 b:0.98
	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 0.98f);

	glm::vec3 viewPosition = glm::vec3(0.0f, 0.0f, 4.0f);

	//light for the background
	//light distance setting
	ambientIntensity = 1.0f;
	lightCol = glm::vec3(1.0f, 1.0f, 1.0f);

	//initialise transform matrices 
	//orthographic (2D) projection
	//projectionMatrix = glm::ortho(0.0f, 4.0f, 0.0f, 3.0f, -1.0f, 100.0f);
	//perspective (3D) projection
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
	//initialise view matrix to '1'
	viewMatrix = glm::mat4(1.0f);

	backgroundScale = glm::mat4(1.0f);
	backgroundTranslate = glm::mat4(1.0f);
	cubeScale = glm::mat4(1.0f);
	cubeRotate = glm::mat4(1.0f);
	cubeTranslate = glm::mat4(1.0f);
	modelScale = glm::mat4(1.0f);
	modelRotate = glm::mat4(1.0f);
	modelTranslate = glm::mat4(1.0f);

	//once only scale to background, and translate to centre
	b_scaleFactor = { 60.0f, 50.0f, 1.0f };
	backgroundScale = glm::scale(backgroundScale, glm::vec3(b_scaleFactor));
	backgroundTranslate = glm::translate(backgroundTranslate, glm::vec3(0.0f, 0.0f, -2.0f));

	//translate imported modelto side
	//modelTranslate = glm::translate(modelTranslate, glm::vec3(1.0f, 0.0f, -1.0f));

	//once only scale and translate to cube
	cubeScale = glm::scale(cubeScale, glm::vec3(1.0f, 1.0f, 1.0f));
	cubeTranslate = glm::translate(cubeTranslate, glm::vec3(0.0f, 0.0f, 0.0f));
	errorLabel = 4;

	//*****************************
	//'game' loop
	while (windowOpen)
	{
		//*************************
		//****************************
		// OpenGL calls.

		glClearColor(1.0f, 1.0f, 1.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//process inputs
		handleInput();
		cam.updateCamera();

		//time
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastTime;
		lastTime = currentTime;

		//update camera matrix
		//camera only moves side to side, formards and backwards (no rotation)
		// set position, target, up direction
		viewMatrix = glm::lookAt(glm::vec3(cam.camXPos, cam.camYPos, cam.camZPos), cam.cameraTarget, cam.cameraUp);

		errorLabel = 5;
		

		//background
		glUseProgram(background.shaderProgram);
		//set background lighting
		backgroundColourLocation = glGetUniformLocation(background.shaderProgram, "uLightColour");
		glProgramUniform3fv(background.shaderProgram, backgroundColourLocation, 1, glm::value_ptr(lightCol));
		//light distance
		ambientIntensityLocation = glGetUniformLocation(background.shaderProgram, "uAmbientIntensity");
		glProgramUniform1f(background.shaderProgram, ambientIntensityLocation, ambientIntensity);

		//set background image
		modelLocation = glGetUniformLocation(background.shaderProgram, "uModel");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(backgroundTranslate*backgroundScale));
		viewLocation = glGetUniformLocation(background.shaderProgram, "uView");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		projectionLocation = glGetUniformLocation(background.shaderProgram, "uProjection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glBindTexture(GL_TEXTURE_2D, texArray[0].texture);
		background.render();

		//set cube
		glUseProgram(cube.shaderProgram);
		//lighting uniforms
		//get and set light colour and position and view position uniform
		lightColLocation = glGetUniformLocation(cube.shaderProgram, "lightCol");
		glUniform3fv(lightColLocation, 1, glm::value_ptr(lightColour));
		lightPositionLocation = glGetUniformLocation(cube.shaderProgram, "lightPosition");
		glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));
		viewPositionLocation = glGetUniformLocation(cube.shaderProgram, "viewPosition");
		glUniform3fv(viewPositionLocation, 1, glm::value_ptr(viewPosition));
		//rotation
		cubeRotate = glm::rotate(cubeRotate, (float)elapsedTime / 1000, glm::vec3(1.0f, 1.0f, 0.0f));
		cubeModelLocation = glGetUniformLocation(cube.shaderProgram, "uModel");
		glUniformMatrix4fv(cubeModelLocation, 1, GL_FALSE, glm::value_ptr(cubeTranslate*cubeRotate*cubeScale));
		cubeViewLocation = glGetUniformLocation(cube.shaderProgram, "uView");
		glUniformMatrix4fv(cubeViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		cubeProjectionLocation = glGetUniformLocation(cube.shaderProgram, "uProjection");
		glUniformMatrix4fv(cubeProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		//set the normal matrix to send to the vertex shader
		normalMatrix = (glm::mat3)glm::transpose(glm::inverse(cubeTranslate*cubeRotate*cubeScale));
		//set the normalMatrix in the shaders
		normalMatrixLocation = glGetUniformLocation(cube.shaderProgram, "uNormalMatrix");
		glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		cube.render();

		//////set .obj model
		//glUseProgram(model.shaderProgram);
		////set sphere lighting
		////modelColourLocation = glGetUniformLocation(model.shaderProgram, "uLightColour");
		////glProgramUniform3fv(model.shaderProgram, modelColourLocation, 1, glm::value_ptr(lightCol));
		//////light distance
		////modelAmbientLocation = glGetUniformLocation(model.shaderProgram, "uAmbientIntensity");
		////glProgramUniform1f(model.shaderProgram, modelAmbientLocation, ambientIntensity);
		////lighting uniforms
		////get and set light colour and position uniform
		//lightColLocation = glGetUniformLocation(cube.shaderProgram, "lightCol");
		//glUniform3fv(lightColLocation, 1, glm::value_ptr(lightColour));
		//lightPositionLocation = glGetUniformLocation(cube.shaderProgram, "lightPosition");
		//glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPosition));
		////rotation
		//modelRotate = glm::rotate(modelRotate, (float)elapsedTime / 1000, glm::vec3(0.0f, 1.0f, 0.0f));
		//importModelLocation = glGetUniformLocation(model.shaderProgram, "uModel");
		//glUniformMatrix4fv(importModelLocation, 1, GL_FALSE, glm::value_ptr(modelTranslate));
		//importViewLocation = glGetUniformLocation(model.shaderProgram, "uView");
		//glUniformMatrix4fv(importViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		//importProjectionLocation = glGetUniformLocation(model.shaderProgram, "uProjection");
		//glUniformMatrix4fv(importProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		////set the normal matrix to send to the vertex shader
		//normalMatrix = (glm::mat3)glm::transpose(glm::inverse(modelTranslate));
		////set the normalMatrix in the shaders
		//normalMatrixLocation = glGetUniformLocation(cube.shaderProgram, "uNormalMatrix");
		//glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		//glBindTexture(GL_TEXTURE_2D, texArray[1].texture);
		//model.render();

		//set to wireframe so we can see the circles
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		SDL_GL_SwapWindow(sdl.win);

	}//end loop

	//****************************
	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	SDL_GL_DeleteContext(context);

	SDL_Quit();
	return 0;
}

void handleInput()
{
	//*****************************
		//SDL handled input
		//Any input to the program is done here

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			windowOpen = false;
		}
		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				std::cout << "Window resized w:" << w << " h:" << h << std::endl;
				SDL_GetWindowSize(win, &w, &h);
				newwidth = h * aspect;
				left = (w - newwidth) / 2;
				glViewport(left, 0, newwidth, h);
				break;
				

			default:
				break;
			}
		}
		
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			
			case SDLK_UP:
				translate = glm::translate(translate, glm::vec3((float)cos(angle)*0.02f, (float)sin(angle)*0.02f, 0.0f));
				break;
			case SDLK_a:
				angle += glm::radians(10.0f);
				rotate = glm::rotate(rotate,glm::radians(10.0f), glm::vec3(0, 0, 1));
				break;
			case SDLK_d:
				angle -= glm::radians(10.0f);
				rotate = glm::rotate(rotate, glm::radians(-10.0f) , glm::vec3(0, 0, 1));
				break;
			case SDLK_p:
				//move camera 'forward' in the -ve z direction
				cam.camZPos -= cam.camSpeed;
				break;
			case SDLK_l:
				//move camera 'backwards' in +ve z direction
				cam.camZPos += cam.camSpeed;
				break;
			case SDLK_z:
				//move camera left
				//move camera target with position
				cam.camXPos -= cam.camSpeed;
				cam.camXTarget -= cam.camSpeed;
				break;
			case SDLK_x:
				//move camera right
				//move camera target with position
				cam.camXPos += cam.camSpeed;
				cam.camXTarget += cam.camSpeed;
				break;

			case SDLK_m:
				//move camera up
				cam.camYPos += cam.camSpeed;
				cam.camYTarget += cam.camSpeed;
				break;
			case SDLK_k:
				//move camera down
				cam.camYPos -= cam.camSpeed;
				cam.camYTarget -= cam.camSpeed;
				break;
			case SDLK_v:
				lightPosition.x -= 0.1f;
				break;
			case SDLK_b:
				lightPosition.x += 0.1f;
				break;
			
			}
		}
	}
}
#endif
#endif
#endif
#endif