#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

namespace carnet {

enum class Ordre {
    Croissant,
    Decroissant
};

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    int nbValidees{};
};

[[nodiscard]] Statistiques calculerStatistiques(
    const std::vector<double>& notes)
{
    const auto [mini, maxi] = std::ranges::minmax(notes);

    double somme{0.0};
    int validees{0};

    for (double n : notes) {
        somme += n;

        if (n >= 10.0) {
            ++validees;
        }
    }

    return {
        mini,
        maxi,
        somme / static_cast<double>(notes.size()),
        validees
    };
}
void appliquerBonus(std::vector<double>& notes, double bonus)
{
    std::ranges::for_each(notes, [bonus](double& n) {
        n = std::clamp(n + bonus, 0.0, 20.0);
    });
}

int main()
{
    std::vector<double> notes{12.0, 15.0, 8.0, 17.0, 9.0};

    carnet::appliquerBonus(notes, 2.0);

    const auto stats = carnet::calculerStatistiques(notes);

    std::cout << "Minimum : " << stats.minimum << '\n';
    std::cout << "Maximum : " << stats.maximum << '\n';
    std::cout << "Moyenne : " << stats.moyenne << '\n';
    std::cout << "Notes validees : " << stats.nbValidees << '\n';

    return 0;
}

