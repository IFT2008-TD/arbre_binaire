//
// Created by Pascal Charpentier on 2022-06-18.
//

#include "gtest/gtest.h"
#include "arbre_binaire.h"

#include <string>

TEST(arbre_binaire, constructeur_3_elements_balance) {
    ArbreBinaire<std::string> a({"a", "b", "c"}, {"b", "a", "c"}) ;

}

