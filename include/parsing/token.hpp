#ifndef PARSING_TOKEN_HPP
#define PARSING_TOKEN_HPP

#include <cstddef>

enum TokenType {
    ERROR,
    EOC,
    MTLLIB,
    USEMTL,
    OBJECT,
    GROUP,
    VERTEX,
    NORMAL,
    TEXTURE,
    PARAMETER,
    FACE,
    LINE,
    POINTS,
    SMOOTH,
    NUMBER,
    IDENTIFIER,
    SLASH
};

struct Token {
    TokenType type;
    const char* lexeme;
    size_t len;
};

const char* viewTokentype(TokenType);

#endif
