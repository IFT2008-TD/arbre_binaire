//
// Created by Pascal Charpentier on 2022-06-18.
//

#include "gtest/gtest.h"
#include "arbre_binaire.h"

#include <string>

TEST(arbre_binaire, constructeur_3_elements_balance) {
    std::vector<std::string> attendu_eo {"a", "b", "c"} ;
    std::vector<std::string> attendu_po {"b", "a", "c"} ;
    ArbreBinaire<std::string> a({"a", "b", "c"}, {"b", "a", "c"}) ;

    EXPECT_EQ(attendu_eo, a.visiterEnOrdre()) ;
    EXPECT_EQ(attendu_po, a.visiterPreOrdre()) ;
    EXPECT_EQ(attendu_po, a.visiterParNiveau()) ;
}

