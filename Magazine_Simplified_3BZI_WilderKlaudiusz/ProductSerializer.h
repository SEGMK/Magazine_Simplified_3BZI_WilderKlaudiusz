#pragma once

#include "Product.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

inline void to_json(json& j, const Product& product)
{
    j = json{
        {"name", product.GetName()},
        {"description", product.GetDescription()},
        {"type", product.GetType()},
        {"price", product.GetPrice()},
        {"quantity", product.GetQuantity()},
        {"amount", product.GetAmount()}
    };
}