#include "impl/Shader/field.h"

Field::Field(FieldRole field_role, DataType data_type, std::string name)
: field_role(field_role), data_type(data_type), name(name) {
}

Field::~Field() {
}
