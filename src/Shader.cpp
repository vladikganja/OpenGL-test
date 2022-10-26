#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : ID(0) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    if (!vShaderFile.is_open() || !fShaderFile.is_open()) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
        vShaderFile.close();
        fShaderFile.close();
        return;
    }

    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, log_type::vertex_t);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, log_type::fragment_t);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, log_type::program_t);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    /*not used*/
}

void Shader::use() {
    glUseProgram(ID);
}

GLuint Shader::getID() const {
    return ID;
}

void Shader::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    GLint vertexColorLocation = glGetUniformLocation(ID, "myColor");
    use();
    glUniform4f(vertexColorLocation, r, g, b, a);
}

void Shader::setBool(const std::string& name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkCompileErrors(GLuint shader, log_type type) {
    int success;
    char infoLog[512];
    switch (type) {
    case log_type::vertex_t:
    case log_type::fragment_t:
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "\n" << infoLog << 
                "\n -- --------------------------------------------------- -- " << std::endl;
        }
        break;
    case log_type::program_t:
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << "\n" << infoLog << 
                "\n -- --------------------------------------------------- -- " << std::endl;
        }
        break;
    default:
        break;
    }
}
