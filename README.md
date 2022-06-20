# IFT-2008 Travaux dirigés
## TD du mercredi 22 juin: parcours des arbres binaires

### Instructions

Le dépôt git du projet se trouve sur Github à l'adresse:

https://github.com/IFT2008-TD/arbre_binaire.git

Vous n'avez qu'à cliquer New Projet dans le menu de CLion, puis
Get from VCS, choisir Git et saisir l'adresse ci-dessus.  Il vous faudra 
ensuite choisir la branche "squelette" du projet afin de pouvoir le travailler.

### Travail à faire

Vous devez compléter les méthodes de l'interface de la classe ArbreBinaire.
L'interface est dans le fichier arbre_binaire.h et votre implantation
sera dans arbre_binaire.hpp.

Vous remarquerez que des méthodes privées sont suggérées dans
le fichier d'implantation.  Libre à vous de suivre ou non ce canevas.

Vous devrez donc:

- Implanter un constructeur qui bâtit un objet ArbreBinaire à-partir de 2 listes d'initialisation:
  - Un liste d'éléments représentant la visite en ordre de l'arbre
  - Une seconde liste d'éléments représentant la visite pré-ordre de l'arbre
- Implanter les opérateurs de la règle des 3, puisque la classe ArbreBinaire sera une classe de Coplien.
- Implanter les itérateurs "en ordre", "pré-ordre" et "par niveau".  Ceux-ci retourneront un vecteur contenant la liste des sommets visités selon le type de visite demandée.

### Notes sur le constructeur

Lisez bien l'énoncé du laboratoire.  Dans un premier temps il est plus 
simple de réaliser un constructeur prenant en paramètre deux structures de
données faciles à manipuler comme des vecteurs ou des listes d'initialisation.
Celui proposé ici prend deux listes d'initialisation, les convertit en vecteurs
et la construction de l'arbre se fera à-partir de ces deux vecteurs.

Une fois cette étape faite, vous pourrez ensuite utiliser le prototype
compliqué proposé dans l'énoncé du laboratoire, il suffira d'ajouter cette
surcharge à votre classe.

### Notes sur les itérateurs

La récursivité est inhérente au type ArbreBinaire.  La totalité des
méthodes publiques de l'implantation, sauf une exception, utilisera
des méthodes auxiliaires récursives.  

Si vous être observateurs, vous noterez que:

- la visite par niveau correspond à la visite en largeur (je vous rappelle qu'un arbre est d'abord et avant tout un Graphe)
- la visite en pré-ordre correspond à la visite en profondeur.  Elle pourrait donc être implantée aussi de manière purement itérative (comment?  Comparez avec la visite par niveau...)


