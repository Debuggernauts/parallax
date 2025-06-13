#include "../../include/parsing/token.hpp"

const char* viewTokentype(TokenType type) {
    switch (type) {
        case ERROR: return "ERROR";
        case EOC: return "EOC";
        case MTLLIB: return "MTLLIB";
        case USEMTL: return "USEMTL";
        case OBJECT: return "OBJECT";
        case GROUP: return "GROUP";
        case VERTEX: return "VERTEX";
        case NORMAL: return "NORMAL";
        case TEXTURE: return "TEXTURE";
        case PARAMETER: return "PARAMETER";
        case FACE: return "FACE";
        case LINE: return "LINE";
        case POINTS: return "POINTS";
        case SMOOTH: return "SMOOTH";
        case NUMBER: return "NUMBER";
        case IDENTIFIER: return "IDENTIFIER";
        case SLASH: return "SLASH";
    }
}
