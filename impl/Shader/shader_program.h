#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <memory>
#include <string>
#include <map>
#include <vector>
#include "impl/Shader/field.h"
#include "impl/Shader/shader.h"

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();
    void add_field(
        ShaderType shader_type,
        FieldRole field_role,
        DataType data_type,
        std::string name,
        void* data
    );
    void setup_rendering();
    void validate();
    void assemble();
private:
    std::vector<std::shared_ptr<Shader>> shaders;
};

#endif // SHADER_PROGRAM_H
