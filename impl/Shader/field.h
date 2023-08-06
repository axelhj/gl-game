#ifndef FIELD_H
#define FIELD_H

#include <string>

enum FieldRole {
    IN,
    OUT,
    UNIFORM,
    FRAGMENT_COLOR
};

enum DataType {
    VEC_2,
    VEC_3,
    MAT_4,
    SAMPLER_2D
};

class ShaderProgram;

class Field {
    friend class ShaderProgram;
public:
    Field(FieldRole field_role, DataType data_type, std::string name);
    ~Field();
private:
    FieldRole field_role;
    DataType data_type;
    std::string name;
};

#endif // FIELD_H
