#pragma once

#include "product.h"
#include <vector>
#include <string>

class Catalog {
public:
    Catalog() = default;
    bool loadFromFile(const std::string &path);
    const std::vector<Product>& products() const { return _products; }
    const Product* findById(int id) const;
private:
    std::vector<Product> _products;
};
