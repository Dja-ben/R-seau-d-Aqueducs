#include "analyzer.h"
#include "acm.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <time.h>

/*************** Kruskal */


/**
 * \brief Type \a arete avec cout
 *
 * Une arête est représentée par ses deux extrémités :
 * \a v et \a w et son coût \a cout
 * Pour l'unicité de la représentation, on supposera que
 * \f$ v \leq w \f$.
 * On accèdera directement aux champs de cette structure.
 */
typedef struct arete_t {
	int v; /**<plus petite extrémité de l'arête */
	int w; /**<plus grande extrémité de l'arête */
	double cout; /**<coût de l'arête */
} arete;

/**
 * \brief Trie les arêtes du graphe par coût croissant
 * \param g adresse du graphe à lire
 * \return un pointeur vers un tableau des arêtes de g triées par coût
 * croissant. Les boucles sont supprimées et en cas d'arêtes multiples, seule
 * l'arête de plus petit coût est présente dans le tableau. Si l'allocation du
 * tableau a échoué, la valeur de retour est \a NULL.
 * La taille du tableau est graphe_get_m(g) ; les arêtes supprimées donnent
 * lieu à des entrées {v:0,w:0,cout:0.0} à la fin du tableau.
 *
 * La fonction appelante devra libérer la mémoire allouée au tableau avec la
 * fonction \a free.
 */
static struct arete_t *graphe_tri_aretes(graphe * g);




int find(int* racine, int i) 
{
	if(racine[i] == -1) 
		return i;
	return racine[i]= find(racine,racine[i]); 
} 


void Union(int* racine, int x, int y) 
{ 
	int racineX = find(racine, x); 
	int racineY = find(racine, y); 
	racine[racineY] = racineX; 
} 


int graphe_acm_kruskal(graphe *g, graphe *acm)
{
	analyzer_t * time_analysis = analyzer_create();
  	struct timespec before, after;
  	clockid_t clk_id = CLOCK_REALTIME;
	int nb_ar=0;
	int cpt=0;
	arete* tab_arr=graphe_tri_aretes(g);
	int* racine = malloc((graphe_get_n(g))*sizeof(int));

	if((racine <0) || (graphe_stable(acm,graphe_get_n(g))<0) || (tab_arr==NULL))
		return -1 ;

	for (int i = 0; i < graphe_get_n(g); i++) 
		racine[i] = -1;

	while( (graphe_get_m(acm)<graphe_get_n(g)-1) && ( nb_ar < graphe_get_m(g) )){
		arete e =tab_arr[nb_ar];

		int x = find(racine, e.v); 
		int y = find(racine, e.w); 
		if (x != y) 
		{ 
			clock_gettime(clk_id, &before);
			graphe_ajouter_arete(acm,e.v,e.w,e.cout);
			cpt= cpt + e.cout;
			Union(racine, x, y);
			clock_gettime(clk_id, &after);
  			analyzer_append(time_analysis, after.tv_nsec - before.tv_nsec); 
		}
		nb_ar++; //on compte meme les arêtes vides ;) 
	}
	fprintf(stderr, "Total cost: %Lf\n", get_total_cost(time_analysis));
  	fprintf(stderr, "Average cost: %Lf\n", get_average_cost(time_analysis));
  	fprintf(stderr, "Variance: %Lf\n", get_variance(time_analysis));
  	fprintf(stderr, "Standard deviation: %Lf\n", get_standard_deviation(time_analysis));
  
  	save_values(time_analysis, "../plots/acm_amortized_time_c.plot");
	analyzer_destroy(time_analysis);	
	return cpt;
}

/**
 * \brief Compare les arêtes par coût
 * \param e1 adresse de la première arête
 * \param e2 adresse de la deuxième arête
 * \return -1, 0 ou 1 selon que le coût de e1 est respectivement inférieur,
 * égal ou supérieur au coût de e2.
 *
 * Cette fonction n'est utilisée que par \a graphe_tri_arete et ne doit pas être
 * modifiée.
 */
static int cmp_arete(const void *e1, const void *e2)
{
	const arete *f1 = e1;
	const arete *f2 = e2;
	if (f1->cout == f2->cout)
		return 0;
	if (f1->cout < f2->cout)
		return -1;
	return 1;
}

#pragma GCC diagnostic ignored "-Wunused-function"
static arete *graphe_tri_aretes(graphe *g)
{
	int v, w, i = 0;
	arete *tab = calloc(graphe_get_m(g), sizeof(arete));
	if (!tab)
		return NULL;
	for (v = 0; v < graphe_get_n(g); ++v)
		for (w = v + 1; w < graphe_get_n(g); ++w)
			if (graphe_get_multiplicite_arete(g, v, w)) {
				tab[i].v = v;
				tab[i].w = w;
				tab[i].cout = graphe_get_cout(g, v, w);
				++i;
			}
	qsort(tab, i, sizeof(arete), cmp_arete);
	return tab;
}
#pragma GCC diagnostic pop


int graphe_ecrire_dot_avec_acm(graphe *g, graphe *acm, char *nom_fichier)
{
	int u, v;
	FILE *f = fopen(nom_fichier, "w");
	if (!f) { perror("fopen"); return -1; }
	fputs("graph {\n", f);
	for (u = 0; u < graphe_get_n(g); ++u)
		fprintf(f, "\t%d;\n", u);
	fputs("\n", f);
	fputs("\tsubgraph g {\n", f);
	for (u = 0; u < graphe_get_n(g); ++u)
		for (v = u; v < graphe_get_n(g); ++v)
			if (graphe_get_multiplicite_arete(g, u, v) &&
				( u == v || !graphe_get_multiplicite_arete(acm, u, v)))
					fprintf(f, "\t\t%d -- %d [label = %.2d];\n",
						u, v, graphe_get_cout(g, u, v));
	fputs("\t}\n", f);
	fputs("\tsubgraph acm {\n\t\tedge [color = red]\n", f);
	for (u = 0; u < graphe_get_n(acm); ++u)
		for (v = u; v < graphe_get_n(acm); ++v)
			if (graphe_get_multiplicite_arete(acm, u, v))
				fprintf(f, "\t\t %d -- %d [fontcolor = red, label = %.2d];\n",
					u, v, graphe_get_cout(acm, u, v));
	fputs("\t}\n}\n", f);
	fclose(f);
	return 0;
}

/***************************************************************************************************/
/***************************************************************************************************/
/**
 * \brief Cree une arrete entre deux villes tel que son cout est la distance entre ces deux villes
 * \param villeD la première ville
 * \param villeA la deuxième ville
 * \param cities adresse d'une liste de villes 
 * \return une arete ces deux extrémitées villesD et villeA et son cout la distance entre eux
 */
static struct arete_t * creer_arete(int villeD, int villeA, ListOfCities * cities);

static  arete * creer_arete(int villeD, int villeA, ListOfCities * cities)
{
  static struct arete_t * nv_arete;
  nv_arete   = malloc(sizeof(struct arete_t));
  nv_arete->v = villeD;
  nv_arete->w = villeA;
  nv_arete->cout = calculer_distance(villeD, villeA, cities); 
  return nv_arete;
}

int graphe_complet(graphe* g, int n, ListOfCities* cities)
{
	int v, w;
	static  arete * arrete;
	if (graphe_stable(g, n) < 0)
		return -1;
	for (v = 0; v < graphe_get_n(g); ++v)
	{
		for (w = v + 1; w < graphe_get_n(g); ++w)
		{
			arrete= creer_arete(v, w, cities);
			graphe_ajouter_arete(g, arrete->v, arrete->w, arrete->cout);
		}
	}
	return 0;
}



