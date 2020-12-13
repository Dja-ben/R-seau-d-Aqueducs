

#ifndef GRAPHE_H
#define GRAPHE_H

/* ______________________________________ Structure de données */

/**
 * \brief Graphe non orienté représenté par sa matrice d'adjacence.
 *
 * Un graphe est ici représenté par son nombre de sommets \a n
 * et sa matrice d'adjacence (tableau dynamique de n*n entiers) \a adj.
 *
 * L'ensemble des sommets du graphe est alors \f$\{0, 1, 2, \ldots, n-1\}\f$.
 *
 * Le champ \a m est le nombre d'arêtes et est mis à jour par les fonctions de
 * manipulation.
 */
struct s_graphe {
	int n;/**< nombre de sommets du graphes (doit être >=0) */
	int m;/**< nombre d'arêtes du graphes */
	int *adj;
	/**< matrice d'adjacence du graphe
	 *
	 * Doit être cohérente avec m.
	 *
	* Nombre d'arete de v vers w : adj[w + v * n]
	 */
	int *cout;
	/**< matrice des couts des aretes du graphe
	 *
	 * Doit être cohérente avec m et adj.
	 * S'il y a au moins une arete entre v et w, alors cout[w + v * n]
	 * est le plus petit cout parmi les aretes entre v et w.
	 */
};
typedef struct s_graphe graphe;

/* ______________________________________ Constructeur et destructeur */

/**
 * \brief ALLOUE de la mémoire pour la matrice d'adjacence et la matrice des
 * couts d'un graphe d'ordre \a n, et l'initialise en un graphe sans arête. Tous
 * les couts de la matrice des couts sont initialisés à DBL_MAX
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \return -1 si l'allocation de mémoire pour la matrice d'adjacence a échoué,
 * 	-2 si \a n est négatif, 0 sinon.
*/
int graphe_stable(graphe* g, int n);

/**
 * \brief Libère la zone mémoire occupée par la matrice d'adjacence et la
 * matrice des couts d'un graphe g.
 * \param g pointeur vers un graphe dont la matrice d'adjacence est allouée
 *
 * Si g->adj est le pointeur NULL, ne fait rien.
 */
void graphe_detruire(graphe *g);

/* ______________________________________ Ajout / Suppression d'arêtes */

/**
 * \brief Ajoute une arête entre deux sommets dans le graphe, de cout égal à
 * \a cout.
 * \param g adresse de la variable graphe à modifier
 * \param v une extrémité de l'arête (entre 0 et n - 1)
 * \param w une extrémité de l'arête (entre 0 et n - 1)
 * \param cout cout de l'arête à ajouter.
 */
void graphe_ajouter_arete(graphe* g, int v, int w, int cout);

/* ______________________________________ Accesseurs en lecture */

/**
 * \brief Retourne l'ordre du graphe.
 * \param g adresse de la variable graphe à lire
 * \return le nombre de sommets du graphe
 */
int graphe_get_n(graphe* g);

/**
 * \brief Retourne le nombre d'arêtes du graphe.
 * \param g adresse de la variable graphe à lire
 * \return le nombre d'arêtes du graphe
 */
int graphe_get_m(graphe* g);

/**
 * \brief Retourne le nombre de fois qu'une arete est présente entre deux
 * sommets donnés.
 * \param g adresse de la variable graphe à lire
 * \param v une extrémité de l'arête (entre 0 et n - 1)
 * \param w une extrémité de l'arête (entre 0 et n - 1)
 * \return le nombre d'arêtes entre les sommets \a v et \a w
 */
int graphe_get_multiplicite_arete(graphe* g, int v, int w);

/**
 * \brief Retourne le coût d'une arête.
 * \param g adresse de la variable graphe à lire
 * \param v première extrémité de l'arête (entre 0 et n - 1)
 * \param w deuxième extrémité de l'arête (entre 0 et n - 1)
 * \return le degré du sommet v dans le graphe
 *
 * L'arête est supposée exister dans le graphe.
 */
int graphe_get_cout(graphe *g, int v, int w);

/* NE PAS ACCÉDER DIRECTEMENT AUX CHAMPS EN-DESSOUS DE CETTE LIGNE */

/**
 * \brief Retourne le degré d'un sommet.
 * \param g adresse de la variable graphe à lire
 * \param v sommet du graphe (entre 0 et n - 1)
 * \return le degré du sommet v dans le graphe
 */
int graphe_get_degre(graphe* g, int v);

/* ______________________________________ Entrées / Sorties */

/**
 * \brief Affiche sur la sortie standard les données d'un graphe
 * \param g adresse de la variable graphe à lire
 *
 * Affiche le nombre de sommets, d'arêtes, la matrice d'adjacence et les degrés
 * des sommets du graphe
 */
void graphe_afficher(graphe* g);



/**
 * \brief ALLOUE de la mémoire pour la matrice d'adjacence d'un graphe d'ordre
 * \a n, et l'initialise en un graphe simple aléatoire d'ordre \a n, où chaque arête
 * est, de façon indépendante, présente avec probabilité \a p.
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \param p probabilité de présence de chaque arête
 * \return -1 si l'allocation de mémoire pour la matrice d'adjacence a échoué,
 * 	-2 si \a n est négatif, -3 si \a p n'est pas compris entre 0 et 1 et
 * 	0 sinon.
*/
int graphe_aleatoire(graphe* g, int n, double p);

/**
 * \brief Écrit le graphe au format dot dans un fichier.
 * \param g adresse de la variable graphe à lire
 * \param nom_fichier nom du fichier à écrire
 * \return 0 si l'écriture du fichier a réussi, -1 sinon
 */
int graphe_ecrire_dot(graphe *g, char *nom_fichier);

#endif
