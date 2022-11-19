#ifndef SHADER_ASSEMBLER_H
#define SHADER_ASSEMBLER_H

#include <memory>
#include <string>
#include <map>
#include <vector>

enum ShaderType {
    VERTEX,
    FRAGMENT
};

enum FieldRole {
    IN,
    OUT,
    UNIFORM,
    FRAGMENT_COLOR,
};

enum DataType {
    VEC_2,
    VEC_3,
    MAT_4,
    SAMPLER_2D
};

struct Field {
    FieldRole field_role;
    DataType data_type;
    std::string name;
    void* data;
};

struct Shader {
    ShaderType shader_type;
    std::string text;
    std::vector<std::shared_ptr<Field>> fields;
};

class ShaderAssembler {
public:
    ShaderAssembler();
    void add_shader(ShaderType shader_type, std::string text);
    void add_field(
        ShaderType shader_type,
        FieldRole field_role,
        DataType data_type,
        std::string name,
        void* data
    );
    void validate();
    void assemble();
    ~ShaderAssembler();
private:
    std::vector<std::shared_ptr<Shader>> shaders;
};

#endif // SHADER_ASSEMBLER_H
