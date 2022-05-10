varying vec3 normal, pos;
varying vec4 color;
varying vec2 texCoords;

void main()
{
  color = gl_Color;
  normal = normalize(gl_NormalMatrix * gl_Normal);
  pos = vec3(gl_ModelViewMatrix * gl_Vertex);

  // gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  gl_Position = ftransform();

  texCoords = gl_MultiTexCoord0.xy;
}
