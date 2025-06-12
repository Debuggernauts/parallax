#ifndef PARSING_OBJ_LEXER_HPP
#define PARSING_OBJ_LEXER_HPP

#include <vector>
#include "../token.hpp"

class Lexer {
    const char* src;
    size_t position;
    bool error_flag;

public:
    Lexer(const char*);
    std::vector<Token> tokenize();
};

#endif // PARSING_OBJ_LEXER_HPP
