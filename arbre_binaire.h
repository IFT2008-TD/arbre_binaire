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

template<typename V>
ArbreBinaire<V>::ArbreBinaire(std::initializer_list<V> liste_en_ordre, std::initializer_list<V> liste_pre_ordre) {
    std::vector<V> en_ordre = std::move(liste_en_ordre) ;
    std::vector<V> pre_ordre = std::move(liste_pre_ordre) ;


    if (!listes_valides(en_ordre, pre_ordre)) throw std::invalid_argument("Construction impossible") ;
    racine = construireSousArbre(en_ordre, 0, en_ordre.size(), pre_ordre, 0) ;

}

template<typename V>
std::vector<V> ArbreBinaire<V>::visiterEnOrdre() const {
    std::vector<V> resultat ;
    visiterEnOrdreLeSousArbre(racine, resultat) ;

    return resultat ;
}

template<typename V>
std::vector<V> ArbreBinaire<V>::visiterPreOrdre() const {
    std::vector<V> resultat ;
    visiterPreOrdreLeSousArbre(racine, resultat) ;

    return resultat ;
}

template<typename V>
std::vector<V> ArbreBinaire<V>::visiterParNiveau() const {
    std::vector<V> resultat ;
    std::queue<Arbre *> attente ;

    if (!racine) return resultat ;

    attente.push(racine) ;
    while (!attente.empty()) {
        auto prochain = attente.front() ;
        resultat.push_back(prochain->valeur) ;
        attente.pop() ;
        if (prochain->gauche) attente.push(prochain->gauche) ;
        if (prochain->droite) attente.push(prochain->droite) ;
    }
    return resultat ;
}

template<typename V>
typename ArbreBinaire<V>::Arbre *
ArbreBinaire<V>::construireSousArbre(const std::vector<V>& en_ordre, size_t deo, size_t leo, const std::vector<V>& pre_ordre,
                                     size_t dpo) {
    if (leo == 0) return nullptr ;

    V element_racine = pre_ordre.at(dpo) ;
    auto lg = static_cast<size_t>(std::find(en_ordre.begin(), en_ordre.end(), element_racine) - en_ordre.begin()) - deo ;
    if (lg >= leo) throw std::runtime_error("construireSousArbre: racine non trouvée.") ;
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

template<typename V>
void ArbreBinaire<V>::visiterEnOrdreLeSousArbre(ArbreBinaire::Arbre *root, std::vector<V> &resultat) const {
    if (root == nullptr) return ;

    visiterEnOrdreLeSousArbre(root->gauche, resultat) ;
    resultat.push_back(root->valeur) ;
    visiterEnOrdreLeSousArbre(root->droite, resultat) ;
}

template<typename V>
void ArbreBinaire<V>::visiterPreOrdreLeSousArbre(ArbreBinaire::Arbre *root, std::vector<V> &resultat) const {
    if (root == nullptr) return ;

    resultat.push_back(root->valeur) ;
    visiterPreOrdreLeSousArbre(root->gauche, resultat) ;
    visiterPreOrdreLeSousArbre(root->droite, resultat) ;
}

template<typename V>
ArbreBinaire<V>::ArbreBinaire(const ArbreBinaire<V> &source) : racine(copierLeSousArbreEnPreOrdre(source.racine)) {}

template<typename V>
ArbreBinaire<V>::~ArbreBinaire() {
    detruireLeSousArbreEnPostOrdre(racine) ;
}

template<typename V>
ArbreBinaire<V> &ArbreBinaire<V>::operator=(ArbreBinaire<V> rhs) {
    std::swap(racine, rhs.racine) ;
    return *this ;
}

template<typename V>
typename ArbreBinaire<V>::Arbre *ArbreBinaire<V>::copierLeSousArbreEnPreOrdre(ArbreBinaire::Arbre *rhs_root) {
    if (!rhs_root) return nullptr ;

    auto retval = new Arbre(rhs_root->valeur) ;
    retval->gauche = copierLeSousArbreEnPreOrdre(rhs_root->gauche) ;
    retval->droite = copierLeSousArbreEnPreOrdre(rhs_root->droite) ;
    return retval ;
}

template<typename V>
void ArbreBinaire<V>::detruireLeSousArbreEnPostOrdre(Arbre* root) {
    if (!root) return ;
    detruireLeSousArbreEnPostOrdre(root->gauche) ;
    detruireLeSousArbreEnPostOrdre(root->droite) ;
    delete root ;
}


#endif //ARBRE_BINAIRE_ARBRE_BINAIRE_H
