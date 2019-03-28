#pragma once
#include <GL/glew.h>
#include "ShaderClass.h"
#include "TextureClass.h"
#include <array>

class Cube
{
public:
	//set up vertex buffer object
	GLuint VBO;
	//set up vertex array object
	GLuint VAO;
	//set up index buffer object
	//GLuint EBO;
	//shader for the pyramid
	Shader vSh, fSh;
	GLuint shaderProgram;
	//single texture 
	Texture tex;
	
	//constructor
	Cube() 
	{
		//shaders
		//vSh.shaderFileName("..//..//Assets//Shaders//shader_projection_lighting_A.vert");
		//fSh.shaderFileName("..//..//Assets//Shaders//shader_projection_lighting_A.frag");
		vSh.shaderFileName("..//..//Assets//Shaders//shader_projection_lighting_AD.vert");
		fSh.shaderFileName("..//..//Assets//Shaders//shader_projection_lighting_AD.frag");
		//vSh.shaderFileName("..//..//Assets//Shaders//shader_projection_lighting_ADS.vert");
		//fSh.shaderFileName("..//..//Assets//Shaders//shader_projection_lighting_ADS.frag");

		vSh.getShader(1);
		fSh.getShader(2);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vSh.shaderID);
		glAttachShader(shaderProgram, fSh.shaderID);
		glLinkProgram(shaderProgram);

		glDeleteShader(vSh.shaderID);
		glDeleteShader(fSh.shaderID);

		//load the texture file
		tex.load("..//..//Assets//Textures//United_Kingdom.png");
	};
	
	//define vertices for the Cube
	GLfloat vertices[396] = {
		//vertices			 colour values    texture coords      normals
	 -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	1.0f, 0.0f,    0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,   1.0f,0.0f,  0.0f,	0.0f, 1.0f,    0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,	0.0f, 0.0f,    0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,0.0f, 0.0f,		1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,    0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 0.0f,    -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,    -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,    -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,    -1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,    -1.0f, 0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,0.0f, 0.0f,		0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     0.0f, -1.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,		0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,     0.0f, 1.0f, 0.0f
	};

	void setBuffers()
	{
		//
		//OpenGL buffers
		//set up 1 for the cube
		glGenBuffers(1, &VBO);
		// Initialization code using Vertex Array Object (VAO) (done once (unless the object frequently changes))
		glGenVertexArrays(1, &VAO);
		//initialise the index buffer
		//glGenBuffers(1, &this->EBO);
		// Bind Vertex Array Object
		glBindVertexArray(VAO);
		// Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		// Then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		
		//set the colour attribute pointer
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		
		//set texture attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		//set normal attrib pointer
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		//Unbind the VAO
		glBindVertexArray(0);

		//texture buffers
		tex.setBuffers();
	}

	void render()
	{
	
		//specify the shader program and texture
		glUseProgram(shaderProgram);
		glBindTexture(GL_TEXTURE_2D, tex.texture);
		//draw the cube
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

};
