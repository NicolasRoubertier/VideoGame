
varying vec2      v_UV;
varying vec3      v_Light;

uniform sampler2D u_Color;
uniform sampler2D u_Normal;
uniform sampler2D u_Specular;

void main()
{
  float spec   = texture2D( u_Specular, v_UV ).x;
  vec4 clr     = texture2D( u_Color, v_UV );
  vec3 nrm     = (texture2D( u_Normal, v_UV ).xyz - 0.5) * 2.0;

  vec3 li      = normalize( v_Light );
  float d      = max( 0.0 , dot( nrm,li ) );

  gl_FragColor = vec4(d,d,d,1);
}
