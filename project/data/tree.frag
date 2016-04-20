
// TODO: create varying variable to receive color values from the vertex shader, don't forget to specify precision

varying lowp vec4 colorVarying;

void main()
{
    // TODO: change output color
    gl_FragColor = colorVarying;
}
