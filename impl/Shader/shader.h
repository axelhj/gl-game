#ifndef SHADER_H
#define SHADER_H

#include <memory>
#include <string>
#include <vector>
#include "impl/Shader/field.h"

enum ShaderType {
    VERTEX,
    FRAGMENT
};

class ShaderProgram;

class Shader {
    friend class ShaderProgram;
public:
    Shader(ShaderType shader_type, std::string text,
        std::vector<std::shared_ptr<Field>> fields);
    ~Shader();
private:
    ShaderType shader_type;
    std::string text;
    std::vector<std::shared_ptr<Field>> fields;
};

#endif // SHADER_H
