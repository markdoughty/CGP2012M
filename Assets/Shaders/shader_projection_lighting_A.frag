#version 440 core
//out vec4 vertColour;	//output colour of vertex
in vec2 textureCoordinate; //tex coords from vertex shader
in vec3 lightColour;

uniform sampler2D aTex;		//uniform holding texture info from main programme

//uniform vec3 lightPosition; //uniform holding the light position


void main()
{
	float lightAmbientStrength = 0.5f;
	vec3 objectAmbientReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambient = (lightAmbientStrength * objectAmbientReflectionCoeff) * lightColour;
	
	vec4 textureColour = texture(aTex, textureCoordinate);
	gl_FragColor = vec4(ambient, 1.0f) * textureColour;

}