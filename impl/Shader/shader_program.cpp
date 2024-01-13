#include "impl/Shader/shader_program.h"

ShaderProgram::ShaderProgram() {
}

void ShaderProgram::add_field(
    ShaderType shader_type,
    FieldRole field_role,
    DataType data_type,
    std::string name,
    void* data
) {
    std::shared_ptr<Shader> target_shader = NULL;
    for (auto shader : shaders) {
        if (shader->shader_type == shader_type) {
            target_shader = shader;
        }
    }
    if (target_shader == NULL) {
        target_shader = std::make_shared<Shader>(
            shader_type, std::string(""),
            std::vector<std::shared_ptr<Field>>()
        );
        shaders.push_back(target_shader);
    }
    auto field = std::make_shared<Field>(
        field_role, data_type, name);
    target_shader->fields.push_back(field);
}

void ShaderProgram::setup_rendering() {

}

void ShaderProgram::validate() {
    // Outputs in v-shader needs to be input in f-shader.
    // Inputs in v-shader take data from v-shader.
}

void ShaderProgram::assemble() {

}

ShaderProgram::~ShaderProgram() {

}
