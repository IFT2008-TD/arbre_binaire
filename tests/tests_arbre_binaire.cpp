//
// Created by Pascal Charpentier on 2022-06-18.
//

#include "gtest/gtest.h"
#include "arbre_binaire.h"

#include <string>


class ArbreBinaireTest : public ::testing::Test{
protected:
    ArbreBinaireTest() : abt({4, 2, 1, 6, 3, 7}, {1, 2, 4, 3, 6, 7}),
                         abt_2({1, 3, 2}, {3, 1, 2}) {}

    ArbreBinaire<int> abt, abt_2 ;

    std::vector<int> attendu_eo {4, 2, 1, 6, 3, 7} ;
    std::vector<int> attendu_po {1, 2, 4, 3, 6, 7} ;
    std::vector<int> attendu_niv {1, 2, 3, 4, 6, 7} ;
};

TEST_F(ArbreBinaireTest, construction) {

    EXPECT_EQ(attendu_eo, abt.visiterEnOrdre()) ;
    EXPECT_EQ(attendu_po, abt.visiterPreOrdre()) ;
    EXPECT_EQ(attendu_niv, abt.visiterParNiveau()) ;
}

TEST_F(ArbreBinaireTest, copie) {
    ArbreBinaire<int> copie(abt) ;

    EXPECT_EQ(attendu_eo, copie.visiterEnOrdre()) ;
    EXPECT_EQ(attendu_po, copie.visiterPreOrdre()) ;
    EXPECT_EQ(attendu_niv, copie.visiterParNiveau()) ;
}

TEST_F(ArbreBinaireTest, affectation) {
    abt_2 = abt ;

    EXPECT_EQ(attendu_eo, abt_2.visiterEnOrdre()) ;
    EXPECT_EQ(attendu_po, abt_2.visiterPreOrdre()) ;
    EXPECT_EQ(attendu_niv, abt_2.visiterParNiveau()) ;
}

TEST_F(ArbreBinaireTest, auto_affectation) {
    abt = abt ;

    EXPECT_EQ(attendu_eo, abt.visiterEnOrdre()) ;
    EXPECT_EQ(attendu_po, abt.visiterPreOrdre()) ;
    EXPECT_EQ(attendu_niv, abt.visiterParNiveau()) ;
}

