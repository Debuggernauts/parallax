#include <string.h>
#include <iostream>

#include "../../../include/parsing/obj/obj_lexer.hpp"

#define IS_ALPHA(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define IS_DIGIT(c) (c >= '0' && c <= '9')
#define IS_ALNUM(c) (IS_ALPHA(c) || IS_DIGIT(c))
#define IS_PUNCT(c) ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
#define IS_SPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')

Lexer::Lexer(const char* source) {
    src = source;
    position = 0;
    error_flag = false;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    size_t len = strlen(src);

    while (!error_flag && (position < len)) {
        Token token;
        char current = src[position];
        if (IS_ALPHA(current)) {
            size_t start = position;
            while (true) {
                char current = src[position];
                if (current == '\0' || !IS_ALNUM(current)) break;
                position++;
            }
            size_t end = position;
            size_t len = end-start;
            if (len == 1) {
                switch (src[start]) {
                    case 'o':
                        token.type = OBJECT;
                        break;
                    case 'g':
                        token.type = GROUP;
                        break;
                    case 'v':
                        token.type = VERTEX;
                        break;
                    case 'f':
                        token.type = FACE;
                        break;
                    case 's':
                        token.type = SMOOTH;
                        break;
                    case 'l':
                        token.type = LINE;
                        break;
                    case 'p':
                        token.type = POINTS;
                        break;
                    default:
                        token.type = IDENTIFIER;
                }
                token.lexeme = &src[start];
                token.len = 1;
                tokens.push_back(token);
                continue;
            }
            if (len == 2) {
                char* str = new char[3];
                memcpy(str, &src[start], len);
                str[len] = '\0';

                if (strncmp(str, "vn", 2) == 0) {
                    token.type = NORMAL;
                }
                else if (strncmp(str, "vt", 2) == 0) {
                    token.type = TEXTURE;
                }
                else if (strncmp(str, "vp", 2) == 0) {
                    token.type = PARAMETER;
                }
                else {
                    token.type = IDENTIFIER;
                }

                free(str);

                token.lexeme = &src[start];
                token.len = 2;
                tokens.push_back(token);
                continue;
            }
            if (len == 6) {
                char* str = new char[7];
                memcpy(str, &src[start], len);
                str[len] = '\0';

                if (strncmp(str, "mtllib", 6) == 0) {
                    token.type = MTLLIB;
                }
                else if (strncmp(str, "usemtl", 6) == 0) {
                    token.type = USEMTL;
                }
                else {
                    token.type = IDENTIFIER;
                }
                free(str);

                token.lexeme = &src[start];
                token.len = 6;
                tokens.push_back(token);
                continue;
            }
            token.type = IDENTIFIER;
            token.lexeme = &src[start];
            token.len = len;
            tokens.push_back(token);
            continue;
        }
        else if (IS_DIGIT(current) || current == '-') {
            size_t start = position;
            size_t decimal_counter = 0;

            if (current == '-') {
                position++;
            }

            while (true) {
                char current = src[position];
                if (current == '\0' || (!IS_DIGIT(current) && current != '.')) break;
                if (current == '.') decimal_counter++;
                position++;
            }

            if (decimal_counter > 1) {
                error_flag = true;
                token.type = ERROR;
            }
            else {
                token.type = NUMBER;
            }

            token.lexeme = &src[start];
            token.len = position-start;
            tokens.push_back(token);
            continue;

        }
        else if (current == '/') {
            token.type = SLASH;
            token.lexeme = &src[position];
            token.len = 1;
            tokens.push_back(token);
            position++;
            continue;
        }
        else if (current == '#') {
            char curr = src[position];
            while (curr != '\n') {
                position++;
                curr = src[position];
            }
            position++;
            continue;
        }
        else {
            position++;
        }
    }

    tokens.push_back({.type=EOC, .lexeme=NULL, .len=0});

    return tokens;
}
