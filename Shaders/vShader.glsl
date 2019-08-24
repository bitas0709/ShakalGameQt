attribute highp vec4 vertexAttr;
uniform mediump mat4 matrix;
attribute highp vec2 textureAttr;
varying highp vec2 textureCoord;

void main()
{
    gl_Position = matrix * vertexAttr;
    textureCoord = textureAttr;
}
