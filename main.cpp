#include <iostream>
#include <string_view>
#include <array>
#include <span>

struct recipe {
    constexpr static std::array<std::string_view, 3> ingredients{
            {
                    {"milk"},
                    {"coco beans"},
                    {"sugar"},
            }
    };
};

class chocolate {
    std::span<std::string_view> ingredients_;

    struct factory {
        template<class Recipe>
        constexpr static chocolate create() noexcept
        {
            return chocolate{{Recipe::ingredients}}; // won't work with std::span
        }
    };

    constexpr explicit chocolate(const std::span<std::string_view>& ingredients) noexcept
            :ingredients_{ingredients} { }

public:
    chocolate() = delete;

    template<class Recipe>
    constexpr static auto from_recipe() noexcept
    {
        return factory::create<Recipe>();
    }

    const auto& ingredients()
    {
        return ingredients_;
    }
};

int main()
{
    auto chocolate = chocolate::from_recipe<recipe>();

    for (const auto& ingredient: chocolate.ingredients()) {
        std::cout << ingredient << ',';
    }
    std::cout << '\n';
    return 0;
}
