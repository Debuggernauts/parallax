#ifndef PARSING_OBJ_PARSER_HPP
#define PARSING_OBJ_PARSER_HPP

#include <vector>

#include "../../mesh.hpp"
#include "../token.hpp"

class Parser {
    std::vector<Token> tokens;
    size_t position;
    bool error_flag;
public:
    Parser(std::vector<Token>);
    Mesh parse();
};

struct Position {
    float x, y, z;
};

struct Normal {
    float x, y, z;
};

struct Texture {
    float u, v;
};

struct Face {
    size_t v1, t1, n1;
    size_t v2, t2, n2;
    size_t v3, t3, n3;
};

#endif // PARSING_OBJ_PARSER_HPP
