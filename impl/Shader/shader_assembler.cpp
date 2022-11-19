#include "impl/Shader/shader_assembler.h"

ShaderAssembler::ShaderAssembler() {
}

void ShaderAssembler::add_shader(
    ShaderType shader_type,
    std::string text
) {
    std::shared_ptr<Shader> target_shader = std::make_shared<Shader>();
    target_shader->text = text;
    target_shader->shader_type = shader_type;
    shaders.push_back(target_shader);
}

void ShaderAssembler::add_field(
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
    target_shader->shader_type = shader_type;
    std::shared_ptr<Field> field = std::make_shared<Field>();
    field->field_role = field_role;
    field->data_type = data_type;
    field->name = name;
    field->data = data;
    target_shader->fields.push_back(field);
}

void ShaderAssembler::assemble() {

}

void ShaderAssembler::validate() {
    // Outputs in v-shader needs to be input in f-shader.
    // Inputs in v-shader take data from v-shader.
}

ShaderAssembler::~ShaderAssembler() {

}
