// SL 2012-02-08

varying vec3   v_Nrm;
varying vec2   v_Tex;
varying vec3   v_SrfPos;

uniform vec3   u_Light0Pos;
uniform float  u_SpecExp;
uniform vec3   u_Eye;

uniform sampler2D u_Image;

vec2 light( vec3 nrm, vec3 view, vec3 light ) 
{
  vec3 n         = normalize( nrm );
  vec3 l         = normalize( light );
  float diffuse  = max(0.0,dot(l,n));

  vec3 r         = 2.0 * dot(n,l) * n - l;
  vec3 v         = normalize( view );
  float specular = pow(max(0.0,dot(r,v)),30.0);

  return vec2( diffuse, specular );
}

void main()
{
  vec2 l0        = light( v_Nrm, u_Eye - v_SrfPos , u_Light0Pos - v_SrfPos );

  vec4 srfclr    = texture2D( u_Image, v_Tex );

  vec3 clr       = srfclr.xyz * ( 0.2 + l0.x ) + l0.y * vec3(1,1,1);

  gl_FragColor   = vec4(clr,1);
}
