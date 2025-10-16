#include "../include/catalog.h"
#include <fstream>
#include <sstream>

bool Catalog::loadFromFile(const std::string &path) {
    _products.clear();
    std::ifstream in(path);
    if (!in.is_open()) return false;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        // expected format: id;name;price
        std::stringstream ss(line);
        std::string token;
        Product p;
        if (!std::getline(ss, token, ';')) continue;
        p.id = std::stoi(token);
        if (!std::getline(ss, token, ';')) continue;
        p.name = token;
        if (!std::getline(ss, token, ';')) continue;
        p.price = std::stof(token);
        _products.push_back(p);
    }
    return true;
}

const Product* Catalog::findById(int id) const {
    for (const auto &p : _products) if (p.id == id) return &p;
    return nullptr;
}
