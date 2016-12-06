
void main()
{
  // gl_FragColor = vec4(1,1,1,1);
  gl_FragColor = vec4(gl_TexCoord[1].xyz*0.5+0.5,1);
}
