#pragma once

#include <string>
#include "cart.h"
#include "catalog.h"

// Save a textual receipt into output/ and return the generated filename on success (empty on failure)
std::string saveReceipt(const Cart &cart, const Catalog &catalog);
