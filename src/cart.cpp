#include "../include/cart.h"
#include "../include/catalog.h"

void Cart::add(int productId) {
    _items[productId]++;
}

bool Cart::removeOne(int productId) {
    auto it = _items.find(productId);
    if (it == _items.end()) return false;
    if (--(it->second) <= 0) _items.erase(it);
    return true;
}

bool Cart::removeAll(int productId) {
    return _items.erase(productId) > 0;
}

void Cart::clear() {
    _items.clear();
}

float Cart::total(const Catalog &catalog) const {
    float sum = 0.0f;
    for (auto &kv : _items) {
        const Product* p = catalog.findById(kv.first);
        if (p) sum += p->price * kv.second;
    }
    return sum;
}
