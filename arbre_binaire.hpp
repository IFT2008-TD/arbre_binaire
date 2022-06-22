//
// Created by Pascal Charpentier on 2022-06-19.
//





/**
 * Constructeur reconstituant un arbre binaire à partir des visites en-ordre et pré-ordre, passées en paramètres
 * sous formes de listes d'initialisation.
 * @tparam V
 * @param liste_en_ordre Éléments de l'arbre énumérés en-ordre
 * @param liste_pre_ordre Éléments de l'arbre énumérés pré-ordre
 * @pre Les deux listes ont la même longueur, aucun doublon, et chacune les mêmes éléments
 * @except invalid_argument si les deux listes ne répondent pas aux précondition
 */
template<typename V>
ArbreBinaire<V>::ArbreBinaire(std::initializer_list<V> liste_en_ordre, std::initializer_list<V> liste_pre_ordre) {
    std::vector<V> en_ordre = std::move(liste_en_ordre) ;
    std::vector<V> pre_ordre = std::move(liste_pre_ordre) ;


    if (!listes_valides(en_ordre, pre_ordre)) throw std::invalid_argument("Construction impossible") ;
    // racine = construireSousArbre(en_ordre, 0, en_ordre.size(), pre_ordre, 0) ;
    racine = construireSousArbreIter(en_ordre.begin(), en_ordre.end(), pre_ordre.begin(), pre_ordre.end()) ;

}

/**
 * Constructeur de copie.
 * @tparam V
 * @param source Arbre à copier.
 * @except Utilise new, donc bad_alloc est possible
 */
template<typename V>
ArbreBinaire<V>::ArbreBinaire(const ArbreBinaire<V> &source) : racine(copierLeSousArbreEnPreOrdre(source.racine)) {}

/**
 * Destructeur.
 * @tparam V
 */
template<typename V>
ArbreBinaire<V>::~ArbreBinaire() {
    detruireLeSousArbreEnPostOrdre(racine) ;
}

/**
 * Opérateur d'assignation en sémantique copy-swap.
 * @tparam V
 * @param rhs Membre de droite de l'assignation.
 * @return L'objet courant après l'assignation.
 */
template<typename V>
ArbreBinaire<V> &ArbreBinaire<V>::operator=(ArbreBinaire<V> rhs) {
    std::swap(racine, rhs.racine) ;
    return *this ;
}


/**
 * Énumère les éléments d'un arbre lors d'une visite en-ordre, le sous-arbre gauche ayant priorité sur le sous-
 * arbre droite.
 * @tparam V
 * @return Un vecteur contenant les éléments dans l'ordre de la visite.  Si l'arbre est vide, le vecteur retourné
 * est vide.
 */
template<typename V>
std::vector<V> ArbreBinaire<V>::visiterEnOrdre() const {
    std::vector<V> resultat ;
    visiterEnOrdreLeSousArbre(racine, resultat) ;

    return resultat ;
}

/**
 * Énumère les éléments d'un arbre binaire lors d'une visite pré-ordre.  Le sous-arbre de gauche a priorité sur
 * le sous-arbre de droite.
 * @tparam V
 * @return Un vecteur contenant les éléments dans l'ordre de la visite.  Si l'arbre est vide, le vecteur retourné
 * sera aussi vide.
 */
template<typename V>
std::vector<V> ArbreBinaire<V>::visiterPreOrdre() const {
    std::vector<V> resultat ;
    visiterEnPreOrdreLeSousArbre(racine, resultat) ;

    return resultat ;
}

/**
 * Énumère les éléments d'un arbre par niveau à-partir de la racine, équivalent à une visite en largeur commençant
 * par la racine.
 * @tparam V
 * @return Un vecteur contenant les éléments dans l'ordre de la visite.  Par convention, gauche est visité avant
 * droite.
 */
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

/**
 * Fonction auxiliaire de validation des listes d'initialisation du constructeur.  Les deux visites doivent contenir
 * le même nombre d'éléments, doivent avoir les mêmes éléments et ne peuvent comporter de doublons.
 * @tparam V
 * @param en_ordre Vecteur de la visite en ordre
 * @param pre_ordre Vecteur de la visite pré ordre
 * @return
 */
template<typename V>
bool ArbreBinaire<V>::listes_valides(std::vector<V> en_ordre, std::vector<V> pre_ordre) {
    if (en_ordre.size() != pre_ordre.size()) return false ;

    std::set<V> set_en_ordre(en_ordre.begin(), en_ordre.end()) ;
    std::set<V> set_pre_ordre(pre_ordre.begin(), pre_ordre.end()) ;

    if (set_pre_ordre.size() != pre_ordre.size()) return false ;

    return set_en_ordre == set_pre_ordre ;

}

/**
 * Fonction récursive auxiliaire au constructeur.  Construit un sous-arbre, à-partir de deux segments de visites
 * en ordre et en pré-ordre.
 * @tparam V
 * @param en_ordre Vecteur contenant la visite en-ordre
 * @param deo Index de départ dans le vecteur en ordre
 * @param leo Nombre d'éléments à lire dans les deux vecteurs.
 * @param pre_ordre Vecteur contenant la visite pré-ordre
 * @param dpo Index de départ dans le vecteur pré-ordre
 * @return Pointeur vers la racine du sous-arbre reconstruit
 * @except Vu que l'opérateur new est employé, susceptible de lancer bad_alloc
 */
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

/**
 * Fonction récursive auxiliaire au constructeur. Construit un sous-arbre à partir de deux vecteurs repérés par des
 * itérateurs.
 * @tparam V
 * @param eo_deb Itérateur sur le début de la visite en-ordre
 * @param eo_fin Itérateur sur la fin de la visite en-ordre
 * @param po_deb Itérateur sur le début de la visite post-ordre
 * @param po_fin Itérateur sur la fin de la visite post-ordre
 * @return Adresse de la racine de l'arbre construit.
 */
template <typename V>
typename ArbreBinaire<V>::Arbre *
ArbreBinaire<V>::construireSousArbreIter(Iterateur eo_deb, Iterateur eo_fin, Iterateur po_deb, Iterateur po_fin) {
    if ((eo_fin - eo_deb) != (po_fin - po_deb)) throw std::invalid_argument("Listes non-valides") ;

    if (eo_fin == eo_deb) return nullptr ;
    if (eo_fin - eo_deb == 1) return new Arbre(*eo_deb) ;

    auto* root = new Arbre(*po_deb) ;
    ++po_deb ;

    auto po = po_deb ;
    auto eo = eo_deb ;

   do {
        ++eo ;
        ++po ;
    } while (*eo != root->valeur) ;

   root->gauche = construireSousArbreIter(eo_deb, eo, po_deb, po) ;
   root->droite = construireSousArbreIter(eo + 1, eo_fin, po, po_fin) ;
   return root ;
}

/**
 * Méthode auxiliaire récursive pour le constructeur copie: Copie profonde d'un sous-arbre
 * @tparam V
 * @param rhs_root Adresse de la racine du sous-arbre à copier
 * @return Adresse de la racine de la copie profonde
 * @except Utilise new, donc bad_alloc
 */
template<typename V>
typename ArbreBinaire<V>::Arbre *ArbreBinaire<V>::copierLeSousArbreEnPreOrdre(ArbreBinaire::Arbre *rhs_root) {
    if (!rhs_root) return nullptr ;

    auto retval = new Arbre(rhs_root->valeur) ;
    retval->gauche = copierLeSousArbreEnPreOrdre(rhs_root->gauche) ;
    retval->droite = copierLeSousArbreEnPreOrdre(rhs_root->droite) ;
    return retval ;
}

/**
 * Méthode auxiliaire récursive pour de destructeur: désallocation des noeuds d'un sous-arbre
 * @tparam V
 * @param root Racine du sous-arbre à détruire.
 */
template<typename V>
void ArbreBinaire<V>::detruireLeSousArbreEnPostOrdre(Arbre* root) {
    if (!root) return ;

    detruireLeSousArbreEnPostOrdre(root->gauche) ;
    detruireLeSousArbreEnPostOrdre(root->droite) ;
    delete root ;
}


/**
 * Fonction récursive auxiliaire pour la visite en ordre.
 * @tparam V
 * @param root Adresse de la racine du sous-arbre à visiter
 * @param resultat Vecteur contenant les sommets du sous-arbre visité.  Celui-ci est inchangé si le sous-arbre
 * est vide.
 */
template<typename V>
void ArbreBinaire<V>::visiterEnOrdreLeSousArbre(ArbreBinaire::Arbre *root, std::vector<V> &resultat) const {
    if (root == nullptr) return ;

    visiterEnOrdreLeSousArbre(root->gauche, resultat) ;
    resultat.push_back(root->valeur) ;
    visiterEnOrdreLeSousArbre(root->droite, resultat) ;
}

/**
 * Fonction auxiliaire récursive pour la visite pré-ordre.
 * @tparam V
 * @param root Adresse de la racine du sous-arbre à visiter.
 * @param resultat Vecteur contenant les sommets du sous-arbre visité.  Celui-ci sera inchangé si le sous-arbre
 * est vide.
 */
template<typename V>
void ArbreBinaire<V>::visiterEnPreOrdreLeSousArbre(ArbreBinaire::Arbre *root, std::vector<V> &resultat) const {
    if (root == nullptr) return ;

    resultat.push_back(root->valeur) ;
    visiterEnPreOrdreLeSousArbre(root->gauche, resultat) ;
    visiterEnPreOrdreLeSousArbre(root->droite, resultat) ;
}




