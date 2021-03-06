#version 300 es
precision mediump float;
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 textColour;
void main()
{
	vec4 sampled = vec4(1.0,1.0,1.0,texture(texture1,TexCoord).r);
	FragColor = vec4(textColour,1.0) * sampled;
}
