/*
Standard calculation for vertex positions: multiplying modelViewProjectionMatrix * vertex position to calculate position of vertices
*/

#version 150

// these are passed in from OF programmable renderer
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;

void main() {
  
//  vec4 posModelSpace = position;
  
  
  gl_Position = modelViewProjectionMatrix * position;
  
  texCoordVarying = texcoord;
}
