// GLSL

uniform vec3 lightSource;
uniform float shininess;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform sampler2D texture;

varying vec2 texCoords;
varying vec3 normal, pos;
varying vec4 color;

void main()
{
  vec3 nlight = normalize((gl_ModelViewMatrix * vec4(lightSource, 1)).xyz - pos);
  
  vec3 neye = normalize(-pos);

  vec3 nnormal = normalize(normal);

  vec3 nhalf = normalize(neye + nlight);
  float diff = ambientIntensity + diffuseIntensity * max(0.0, dot(nlight, nnormal));

  float spec = pow(max(0.0, dot(nhalf, nnormal)), shininess) * (1 - diffuseIntensity);

  // gl_FragColor = vec4(color * diff + spec);

  gl_FragColor = texture2D(texture, texCoords) * diff + spec; 
}
