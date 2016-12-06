// SL 2012-02-08

varying vec3      v_Nrm;

void main()
{
  vec3  nrm = normalize( v_Nrm );
  float d   = v_Nrm.z;
  gl_FragColor = vec4(d,d,d,1);
}

