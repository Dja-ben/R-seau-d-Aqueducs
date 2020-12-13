
#ifndef ACM_H
#define ACM_H

#include "graphe.h"
#include "citiesReader.h"


/**
 * \brief Calcule l'arbre couvrant minimal de g par l'algorithme de Kruskal
 * \param g adresse de la variable graphe à lire
 * \param acm adresse de l'arbre couvrant minimal à écrire
 * \return la sommes des couts des arretes resultant, si tout s'est bien passé, -1 en cas de problème d'allocation
 * mémoire
 *
 * On suppose que \a g est connexe.
 * De la mémoire est allouée pour \a acm. Il faut la libérer avec la
 * fonction \a graphe_detruire.
 */
int graphe_acm_kruskal(graphe *g, graphe *acm);

/* Cette fonction est juste pour tester avant de passer à appliquer sur les villes*/ 
/**
 * \brief Écrit dans le fichier nommé \a nom_fichier une description au format
 * dot du graphe \a g avec son arbre couvrant minimal \a acm
 * \param g adresse de la variable graphe à lire
 * \param acm adresse de l'arbre couvrant minimal à lire
 * \return 0 si tout s'est bien passé, -1 en cas de problème d'entrée sortie
 *
 * Les arêtes de l'arbre couvrant minimal sont tracées en rouge. Celles qui
 * n'appartiennent pas à cet arbre couvrant sont tracées en noir.
 */
int graphe_ecrire_dot_avec_acm(graphe *g, graphe *acm, char *nom_fichier);

/**
 * \brief ALLOUE de la mémoire pour la matrice d'adjacence d'un graphe d'ordre
 * \a n, et l'initialise en un graphe simple complet
 * \param g adresse d'une variable de type graphe *existante*
 * \param n ordre du graphe
 * \return -1 si l'allocation de mémoire pour la matrice d'adjacence a échoué,
 * 	-2 si \a n est négatif, 0 sinon.
*/
int graphe_complet(graphe* g, int n, ListOfCities* cities);


/**
* \brief permet de trouver la racine d'un sommet dans une composante connexe 
*\param racine tableau de sommet avec leurs racines 
* \param i  indice du sommet auquel on veut trouver la racine
*/
int find(int* racine, int i) ;


/**
* \brief permet de faire l'union de deux sommet de telle facon a ce qu'ils soient dans la meme composante connexe 
*\param racine tableau de sommet avec leurs racines 
* \param x  indice du sommet  1
*\param y  indice du sommet  2 
*/
void Union(int* racine, int x, int y) ;


#endif /* ACM_H */
