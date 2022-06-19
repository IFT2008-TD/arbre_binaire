//
// Created by Pascal Charpentier on 2022-06-18.
//

#ifndef ARBRE_BINAIRE_ARBRE_BINAIRE_H
#define ARBRE_BINAIRE_ARBRE_BINAIRE_H

#include <vector>
#include <set>
#include <queue>
#include <algorithm>

template <typename V>
class ArbreBinaire {

private:

    struct Arbre {

        V valeur ;
        Arbre* gauche ;
        Arbre* droite ;

        explicit Arbre(V val) : valeur(val), gauche(nullptr), droite(nullptr) {} ;
    };

public:

    // Constructeur et règle des 3

    ArbreBinaire(std::initializer_list<V> en_ordre, std::initializer_list<V> pre_ordre) ;
    ArbreBinaire(const ArbreBinaire<V>& source) ;
    ~ArbreBinaire() ;
    ArbreBinaire<V>& operator = (ArbreBinaire<V> rhs) ;

    // Itérateurs

    std::vector<V> visiterEnOrdre () const ;
    std::vector<V> visiterPreOrdre () const ;
    std::vector<V> visiterParNiveau () const ;

private:

    // Fonctions auxiliaires pour la règle des 3

    static bool listes_valides(std::vector<V> en_ordre, std::vector<V> pre_ordre) ;
    Arbre* construireSousArbre(const std::vector<V>& en_ordre, size_t deo, size_t leo, const std::vector<V>& pre_ordre, size_t dpo) ;
    Arbre* copierLeSousArbreEnPreOrdre(Arbre* rhs_root) ;
    void detruireLeSousArbreEnPostOrdre(Arbre* root) ;

    // Fonctions auxiliaires des itérateurs

    void visiterEnOrdreLeSousArbre(Arbre* root, std::vector<V>& resultat) const ;
    void visiterPreOrdreLeSousArbre(Arbre* root, std::vector<V>& resultat) const ;


private:
    Arbre * racine ;


};

#include "arbre_binaire.hpp"

#endif //ARBRE_BINAIRE_ARBRE_BINAIRE_H
