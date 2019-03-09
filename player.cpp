#include "player.h"

player::player()
{
    hp = 100; //уровень здоровья игрока
    score = 0; //стартовые очки
    time = 500; //скорость перемещения игрока (в миллисекундах)

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "attribute highp vec4 vertexAttr;\n"
        "uniform mediump mat4 matrix;\n"
        "attribute lowp vec4 colorAttr;\n"
        "varying lowp vec4 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = matrix * vertexAttr;\n"
        "    color = colorAttr;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "varying lowp vec4 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    m_program = new QOpenGLShaderProgram;
    m_program->addShader(vshader);
    m_program->addShader(fshader);
    m_program->link();

    m_vertexAttr = m_program->attributeLocation( "vertexAttr" );
    m_colorAttr = m_program->attributeLocation( "colorAttr" );
    m_matrixUniform = m_program->attributeLocation( "matrix" );
}

player::initVertices() {
    m_vertices.resize(9);


}
