#pragma once

#include "product.h"
#include <vector>
#include <unordered_map>

class Cart {
public:
    // add one unit of productId
    void add(int productId);
    // remove one unit of productId; returns false if not present
    bool removeOne(int productId);
    // remove all units of productId
    bool removeAll(int productId);
    void clear();
    float total(const class Catalog &catalog) const;
    // items as productId -> quantity map
    const std::unordered_map<int,int>& items() const { return _items; }
private:
    std::unordered_map<int,int> _items;
};
