#include "impl/Shader/shader.h"

Shader::Shader(ShaderType shader_type, std::string text,
    std::vector<std::shared_ptr<Field>> fields)
    : shader_type(shader_type), text(text), fields(fields) {
}

Shader::~Shader() {
}
