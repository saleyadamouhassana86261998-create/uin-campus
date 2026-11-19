#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/version.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main() {
    constexpr std::size_t nbMentions = 5;

    const std::string ue = uin::lireTexte("Nom de l'UE : ");
    const int nb = uin::lireEntier("Nombre d'etudiants (1 a 200) : ", 1, 200);

    std::vector<double> notes;

    for (int i = 1; i <= nb; ++i) {
        notes.push_back(uin::lireNote("Note de l'etudiant " + std::to_string(i) + " : "));
    }

    double minimum = uin::noteMax;
    double maximum = uin::noteMin;
    double somme = 0.0;
    int admis = 0;

    std::array<int, nbMentions> repartition{};

    for (double note : notes) {
        minimum = std::min(minimum, note);
        maximum = std::max(maximum, note);
        somme += note;

        if (note >= uin::seuilValidation) {
            ++admis;
        }

        const auto mention = uin::mentionPour(note);
        ++repartition[static_cast<std::size_t>(mention)];
    }

    const double taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    double sommeEcarts = 0.0;

    for (double note : notes) {
        const double ecart = note - moyenne;
        sommeEcarts += ecart * ecart;
    }

    const double ecartType = std::sqrt(sommeEcarts / taille);

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\nStatistiques — " << ue << " (" << nb << " etudiants)\n";

    std::cout << "------------------------------------------\n";
    std::cout << "Note minimale : " << minimum << '\n';
    std::cout << "Note maximale : " << maximum << '\n';
    std::cout << "Moyenne       : " << moyenne << '\n';
    std::cout << "Ecart-type    : " << ecartType << '\n';

    std::cout << std::setprecision(1);
    std::cout << "Admis         : " << admis << " (" << 100.0 * admis / taille << " %)\n";

    std::cout << "\nRepartition par mention\n";

    for (std::size_t i = 0; i < nbMentions; ++i) {
        const auto mention = static_cast<uin::Mention>(i);

        std::cout << uin::libelle(mention) << " : "
                  << std::string(static_cast<std::size_t>(repartition[i]), '*') << " ("
                  << repartition[i] << ")\n";
    }

    return 0;
}