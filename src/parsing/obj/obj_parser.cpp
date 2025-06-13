#include <iostream>
#include <cstdlib>

#include "../../../include/parsing/obj/obj_parser.hpp"
#include "../../../include/parsing/token.hpp"

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;
    position = 0;
    error_flag = false;
}

Mesh Parser::parse() {
    Mesh mesh;
    std::vector<Position> positions;
    std::vector<Normal> normals;
    std::vector<Texture> textures;
    std::vector<Face> faces;
    
    size_t len = tokens.size();

    while (!error_flag && (position < len)) {
        Token current = tokens[position];
        Position pos;
        Normal norm;
        Texture tex;
        Face face;

        if (current.type == VERTEX) {
            position++;

            Token x = tokens[position];
            if (x.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(x.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string xNum(x.lexeme, x.len);
            pos.x = std::strtof(xNum.c_str(), nullptr);
            position++;

            Token y = tokens[position];
            if (y.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(y.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string yNum(y.lexeme, y.len);
            pos.y = std::strtof(yNum.c_str(), nullptr);
            position++;

            Token z = tokens[position];
            if (z.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(z.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string zNum(z.lexeme, z.len);
            pos.z = std::strtof(zNum.c_str(), nullptr);
            position++;

            Token w = tokens[position];
            if (w.type == NUMBER) {
                position++;
            }

            std::cout << "Position { " << "x: " << pos.x << ", " << "y: " << pos.y << ", " << "z: " << pos.z << " }" << std::endl;

            positions.push_back(pos);
            continue;
        }
        else if (current.type == NORMAL) {
            position++;

            Token x = tokens[position];
            if (x.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(x.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string xNum(x.lexeme, x.len);
            norm.x = std::strtof(xNum.c_str(), nullptr);
            position++;

            Token y = tokens[position];
            if (y.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(y.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string yNum(y.lexeme, y.len);
            norm.y = std::strtof(yNum.c_str(), nullptr);
            position++;

            Token z = tokens[position];
            if (z.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(z.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string zNum(z.lexeme, z.len);
            norm.z = std::strtof(zNum.c_str(), nullptr);
            position++;

            Token w = tokens[position];
            if (w.type == NUMBER) {
                position++;
            }

            std::cout << "Normal { " << "x: " << norm.x << ", " << "y: " << norm.y << ", " << "z: " << norm.z << " }" << std::endl;

            normals.push_back(norm);
            continue;
        }
        else if (current.type == TEXTURE) {
            position++;

            Token u = tokens[position];
            if (u.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(u.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string uNum(u.lexeme, u.len);
            tex.u = std::strtof(uNum.c_str(), nullptr);
            position++;

            Token v = tokens[position];
            if (v.type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(v.type) << std::endl;
                error_flag = true;
                break;
            }
            std::string wNum(v.lexeme, v.len);
            tex.v = std::strtof(wNum.c_str(), nullptr);
            position++;

            std::cout << "Texture { " << "u: " << tex.u << ", " << "v: " << tex.v << " }" << std::endl;

            textures.push_back(tex);
            continue;
        }
        else if (current.type == FACE) {
            position++;
            face.v1 = face.t1 = face.n1 = static_cast<size_t>(-1); // default to invalid

            if (tokens[position].type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(tokens[position].type) << std::endl;
                error_flag = true;
                break;
            }
            face.v1 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
            position++;

            if (position < tokens.size() && tokens[position].type == SLASH) {
                position++;
                if (position < tokens.size() && tokens[position].type == SLASH) {
                    position++;
                    if (tokens[position].type == NUMBER) {
                        face.n1 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                        position++;
                    }
                } else if (tokens[position].type == NUMBER) {
                    face.t1 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                    position++;
                    if (position < tokens.size() && tokens[position].type == SLASH) {
                        position++;
                        if (tokens[position].type == NUMBER) {
                            face.n1 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                            position++;
                        }
                    }
                }
            }

            if (tokens[position].type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(tokens[position].type) << std::endl;
                error_flag = true;
                break;
            }
            face.v2 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
            position++;

            if (position < tokens.size() && tokens[position].type == SLASH) {
                position++;
                if (position < tokens.size() && tokens[position].type == SLASH) {
                    position++;
                    if (tokens[position].type == NUMBER) {
                        face.n2 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                        position++;
                    }
                } else if (tokens[position].type == NUMBER) {
                    face.t2 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                    position++;
                    if (position < tokens.size() && tokens[position].type == SLASH) {
                        position++;
                        if (tokens[position].type == NUMBER) {
                            face.n2 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                            position++;
                        }
                    }
                }
            }

            if (tokens[position].type != NUMBER) {
                std::cerr << "parser: expected a NUMBER! Got " << viewTokentype(tokens[position].type) << std::endl;
                error_flag = true;
                break;
            }
            face.v3 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
            position++;

            if (position < tokens.size() && tokens[position].type == SLASH) {
                position++;
                if (position < tokens.size() && tokens[position].type == SLASH) {
                    // v//vn
                    position++;
                    if (tokens[position].type == NUMBER) {
                        face.n3 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                        position++;
                    }
                } else if (tokens[position].type == NUMBER) {
                    // v/vt or v/vt/vn
                    face.t3 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                    position++;
                    if (position < tokens.size() && tokens[position].type == SLASH) {
                        position++;
                        if (tokens[position].type == NUMBER) {
                            face.n3 = std::stoul(std::string(tokens[position].lexeme, tokens[position].len)) - 1;
                            position++;
                        }
                    }
                }
            }

            std::cout << "Face { " << "v1: " << face.v1 << ", " << "t1: " << face.t1 << ", " << "n1: " << face.n1 << ", " << "v2: " << face.v2 << ", " << "t2: " << face.t2 << ", " << "n2: " << face.n2 <<  ", " << "v3: " << face.v3 << ", " << "t3: " << face.t3 << ", " << "n3: " << face.n3 << " }" << std::endl;

            faces.push_back(face);
            continue;
        }
        else {
            position++;
        }
    }

    return mesh;
}
