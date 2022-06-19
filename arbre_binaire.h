//
// Created by Pascal Charpentier on 2022-06-18.
//

#ifndef ARBRE_BINAIRE_ARBRE_BINAIRE_H
#define ARBRE_BINAIRE_ARBRE_BINAIRE_H

#include <vector>
#include <set>
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

    ArbreBinaire(std::initializer_list<V> en_ordre, std::initializer_list<V> pre_ordre) ;

    std::vector<V> visiterEnOrdre () const ;
    std::vector<V> visiterPreOrdre () const ;
    std::vector<V> visiterParNiveau () const ;

private:
    Arbre* construireSousArbre(const std::vector<V>& en_ordre, size_t deo, size_t leo, const std::vector<V>& pre_ordre, size_t dpo) ;


private:
    Arbre * racine ;
    static bool listes_valides(std::vector<V> en_ordre, std::vector<V> pre_ordre) ;

};

template<typename V>
ArbreBinaire<V>::ArbreBinaire(std::initializer_list<V> liste_en_ordre, std::initializer_list<V> liste_pre_ordre) {
    std::vector<V> en_ordre = std::move(liste_en_ordre) ;
    std::vector<V> pre_ordre = std::move(liste_pre_ordre) ;


    if (!listes_valides(en_ordre, pre_ordre)) throw std::invalid_argument("Construction impossible") ;
    racine = construireSousArbre(en_ordre, 0, en_ordre.size(), pre_ordre, 0) ;

}

template<typename V>
std::vector<V> ArbreBinaire<V>::visiterEnOrdre() const {
    return std::vector<V>();
}

template<typename V>
std::vector<V> ArbreBinaire<V>::visiterPreOrdre() const {
    return std::vector<V>();
}

template<typename V>
std::vector<V> ArbreBinaire<V>::visiterParNiveau() const {
    return std::vector<V>();
}

template<typename V>
typename ArbreBinaire<V>::Arbre *
ArbreBinaire<V>::construireSousArbre(const std::vector<V>& en_ordre, size_t deo, size_t leo, const std::vector<V>& pre_ordre,
                                     size_t dpo) {
    if (leo == 0) return nullptr ;

    V element_racine = pre_ordre.at(dpo) ;
    auto lg = static_cast<size_t>(std::find(en_ordre.begin(), en_ordre.end(), element_racine) - en_ordre.begin()) - deo ;
    size_t ld = leo - lg - 1 ;

    auto* root = new Arbre(element_racine) ;
    root->gauche = construireSousArbre(en_ordre, deo, lg, pre_ordre, 1+dpo) ;
    root->droite = construireSousArbre(en_ordre, deo+lg+1, ld, pre_ordre, 1+dpo+lg) ;

    return root ;
}

template<typename V>
bool ArbreBinaire<V>::listes_valides(std::vector<V> en_ordre, std::vector<V> pre_ordre) {
    if (en_ordre.size() != pre_ordre.size()) return false ;

    std::set<V> set_en_ordre(en_ordre.begin(), en_ordre.end()) ;
    std::set<V> set_pre_ordre(pre_ordre.begin(), pre_ordre.end()) ;

    if (set_pre_ordre.size() != pre_ordre.size()) return false ;

    return set_en_ordre == set_pre_ordre ;

}


#endif //ARBRE_BINAIRE_ARBRE_BINAIRE_H
