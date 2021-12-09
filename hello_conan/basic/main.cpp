#include <fmt/printf.h>
#include <nlohmann/json.hpp>

int main()
{
    nlohmann::json json = {
        {"pi", 3.14},
        {"happy", true},
        {"name", "Kuba"},
        {"nothing", nullptr},
        {"answer", {
            {"everything", 42}
        }},
        {"list", {1, 2, 3}},
        {"object", {
            {"currency", "PLN"},
            {"value", 100.0}
        }}
    };

    fmt::print("JSON: {}\n", json);
    return 0;
}