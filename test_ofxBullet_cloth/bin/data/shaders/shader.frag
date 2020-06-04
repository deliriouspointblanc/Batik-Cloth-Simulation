#version 150

out vec4 fragColor;

uniform float time;
uniform vec2 u_resolution;
uniform vec2 mousePos;

uniform sampler2D imageText;
//uniform sampler2D fboTexture;

in vec2 texCoordVarying;

void main(){
  vec2 pixelPos = texCoordVarying/u_resolution;
  pixelPos.y = 1.0 - pixelPos.y;
  
  vec4 image = texture(imageText, texCoordVarying);
  
//  vec3 src = texture(imageText, texCoordVarying).rgb;
  
  fragColor = image;
}
/*
void main(){
  float mYpos = mousePos.y;
  
  float change = abs(sin(10. + time));
//  float change = map(mousePos.y, 0., 1., -2., 2.); //not what vals to map
  
  vec2 pixelPos = gl_FragCoord.xy/u_resolution;
  pixelPos.y = 1.0 - pixelPos.y;
  vec4 image = texture(fboTexture, pixelPos.xy);
  
  vec4 displace = texture(rockImageTexture, pixelPos.xy);
  vec2 displacedUV = vec2(pixelPos.x, pixelPos.y);
  
  //Displacement using mix function
  displacedUV.y = mix(pixelPos.y, displace.r, change / 2.);
//  displacedUV.x = 0.1 * mousePos.x  / u_resolution.x; //use mouseXpos to displace image in x-axis to create additional effect
  vec4 col = texture(fboTexture, displacedUV);
  
  //Making colour glitch
  col.r = texture(fboTexture, displacedUV + vec2(0.,0.005)*change).r;
  col.g = texture(fboTexture, displacedUV + vec2(0.,0.01)*change).g;
  col.b = texture(fboTexture, displacedUV + vec2(0.,0.05)*change).b;
  
  fragColor = col;
}
 //from https://gist.github.com/companje/29408948f1e8be54dd5733a74ca49bb9
 float map(float value, float min1, float max1, float min2, float max2) {
   return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
 }
*/
