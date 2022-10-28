#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform float x;
uniform float y;
uniform float z;
uniform float r;
uniform float g;
uniform float b;

void main() {
	gl_Position = vec4(aPos.x + x, aPos.y + y, aPos.z + z, 1.0);
	vertexColor = vec4(0.0 + r, 0.0 + g, 0.0 + b, 1.0);
}
