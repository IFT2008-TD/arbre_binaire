//
// Created by Pascal Charpentier on 2022-06-18.
//

#ifndef ARBRE_BINAIRE_ARBRE_BINAIRE_H
#define ARBRE_BINAIRE_ARBRE_BINAIRE_H

#include <vector>
#include <set>
#include <queue>
#include <algorithm>

/**
 * @class Classe représentant un arbre binaire: la racine est le seul sommet d'ordre 2, les feuilles sont d'ordre 1 et
 * tous les noeuds internes sont d'ordre 3. Voir README pour une description complète.
 * @tparam V
 */
template <typename V>
class ArbreBinaire {

private:

    typedef  typename std::vector<V>::iterator Iterateur ;

    // Type privé Arbre: tout arbre binaire est un sommet comportant deux sous-arbres.

    struct Arbre {

        V      valeur ;
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
    Arbre*      construireSousArbre(const std::vector<V>& en_ordre, size_t deo, size_t leo, const std::vector<V>& pre_ordre, size_t dpo) ;
    Arbre       *construireSousArbreIter(Iterateur eo_deb, Iterateur eo_fin, Iterateur po_deb, Iterateur po_fin) ;
    Arbre*      copierLeSousArbreEnPreOrdre(Arbre* rhs_root) ;
    void        detruireLeSousArbreEnPostOrdre(Arbre* root) ;

    // Fonctions auxiliaires des itérateurs

    void visiterEnOrdreLeSousArbre(Arbre* root, std::vector<V>& resultat) const ;
    void visiterEnPreOrdreLeSousArbre(Arbre* root, std::vector<V>& resultat) const ;


private:

    // Le seul attribut: la racine du sommet.

    Arbre * racine ;



};

// Implantation dans ce fichier

#include "arbre_binaire.hpp"

#endif //ARBRE_BINAIRE_ARBRE_BINAIRE_H
