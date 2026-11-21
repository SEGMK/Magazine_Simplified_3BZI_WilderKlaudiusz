#include "FileDataHandler.h"
#include "Product.h"
#include "ProductSerializer.h"

#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

void FileDataHandler::SaveProducts(vector<Product> products)
{
    ofstream file(FileStoragePath, ios::out | ios::trunc);

    if (!file.is_open())
    {
        throw exception("Failed to open products file.");
    }

    json data = products;

    file << data.dump(4);

    if (!file.good())
    {
        throw exception("Failed to write products to file.");
    }
}

vector<Product> FileDataHandler::LoadProducts()
{
    ifstream file(FileStoragePath);

    if (!file.is_open())
        return {};

    json data;

    file >> data;

    if (!data.is_array())
        throw runtime_error("Invalid products JSON format.");

    vector<Product> products;
    products.reserve(data.size());

    for (const auto& item : data)
    {
        string idString = item.at("id").get<string>();
        wstring wideId(idString.begin(), idString.end());

        GUID id{};

        if (FAILED(CLSIDFromString(wideId.c_str(), &id)))
            throw runtime_error("Invalid product GUID.");

        products.emplace_back(
            id,
            item.at("name").get<string>(),
            item.at("description").get<string>(),
            item.at("type").get<string>(),
            item.at("price").get<double>(),
            item.at("quantity").get<double>(),
            item.at("discountPercentage").get<double>()
        );
    }

    return products;
}