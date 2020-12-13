
#include "graphe.h"
#include "citiesReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int graphe_stable(graphe* g, int n)
{
	int i;
	if (n < 0) return -2;
	g->adj = calloc(n * n, sizeof(int));
	if (g->adj == NULL)
		return -1;
	g->cout = malloc(n * n * sizeof(int));
	if (g->cout == NULL) {
		free(g->adj);
		return -1;
	}
	g->n = n;
	g->m = 0;
	for (i = 0; i < n * n; ++i)
		g->cout[i] = INT_MAX;
	return 0;
}

void graphe_detruire(graphe *g)
{
	free(g->adj);
	free(g->cout);
}
/* __________________________________ Ajout / Suppression d'arêtes */

void graphe_ajouter_arete(graphe* g, int v, int w, int cout)
{
	++(g->adj[v*(g->n) + w]);
	++(g->m);
	if (cout < g->cout[v*(g->n) + w])
		g->cout[v*(g->n) + w] = cout;
	if (v != w)
	{
		++(g->adj[w*(g->n) + v]);
		if (cout < g->cout[w*(g->n) + v])
			g->cout[w*(g->n) + v] = cout;
	}
}

/* ______________________________________ Accesseurs en lecture */

int graphe_get_n(graphe* g)
{
	return g->n;
}

int graphe_get_m(graphe* g)
{
	return g->m;
}

int graphe_get_multiplicite_arete(graphe* g, int v, int w)
{
	return g->adj[v*(g->n) + w];
}

int graphe_get_cout(graphe *g, int v, int w)
{
	return g->cout[v*(g->n) + w];
}


/* NE PAS ACCÉDER DIRECTEMENT AUX CHAMPS EN-DESSOUS DE CETTE LIGNE */

int graphe_get_degre(graphe* g, int v)
{
	int deg =0;
	int w;
	for (w = 0 ; w < graphe_get_n(g) ; ++w)
		deg += graphe_get_multiplicite_arete(g, v, w) ;
	/* les boucles comptent 2 dans le degré */
	deg += graphe_get_multiplicite_arete(g, v, v);
	return deg;
}

/* ______________________________________ Entrées / Sorties */

void graphe_afficher(graphe* g)
{
	int v, w;
	printf("graphe d'ordre %d sur %d aretes: \n",
			graphe_get_n(g), graphe_get_m(g));
	/* matrice d'adjacence */
	/* ligne indices colonnes */
	printf("\t\t");
	for (w = 0 ; w < graphe_get_n(g) ; w ++)
		printf("%d\t", w);
	printf("|d\n");

	/* ligne séparatrice entête colonne / corps matrice */
	printf("\t\t");
	for (w = 0 ; w < graphe_get_n(g) ; w ++)
		printf("_\t");

	printf("__\n");

	/* lignes de la matrice */
	for (v = 0 ; v < graphe_get_n(g) ; v ++) {
		printf("%d\t|\t", v);
		for (w = 0 ; w < graphe_get_n(g) ; w ++)
			printf("%d\t", graphe_get_multiplicite_arete(g, v, w));
		printf("|%d\n", graphe_get_degre(g, v));
	}
	/* ligne séparatrice corps matrice / degrés entrants */
	printf("\t\t");
	for (w = 0 ; w < graphe_get_n(g) ; w ++)
		printf("_\t");
	printf("__\n");
	/* lignes des degrés */
	printf("d\t|\t");
	for (w = 0 ; w < graphe_get_n(g) ; w ++)
		printf("%d\t", graphe_get_degre(g, w));
	printf("\n");
}

int graphe_ecrire_dot(graphe *g, char *nom_fichier)
{
	int u, v, k;
	FILE *f = fopen(nom_fichier, "w");
	if (!f) { perror("fopen"); return -1; }
	fputs("graph {\n", f);
	for (u = 0; u < graphe_get_n(g); ++u)
		fprintf(f, "\t%d;\n", u);
	fputs("\n", f);
	for (u = 0; u < graphe_get_n(g); ++u)
		for (v = u; v < graphe_get_n(g); ++v)
			for (k = graphe_get_multiplicite_arete(g, u, v);
				k > 0; --k)
				fprintf(f, "\t%d -- %d [label = %.2d];\n",
					u, v, graphe_get_cout(g, u, v));
	fputs("}\n", f);

	fclose(f);
	return 0;
}

/* ______________________________________ Autres fonctions d'initialisation */


int graphe_aleatoire(graphe* g, int n, double p)
{
	int v, w;
	if (graphe_stable(g, n) < 0)
		return -1;
	if (p < 0 || p > 1)
		return -2;
	for (v = 0; v < graphe_get_n(g); ++v)
		for (w = v + 1; w < graphe_get_n(g); ++w)
			if ((double) rand()/RAND_MAX <p)
				graphe_ajouter_arete(g, v, w,
					(double) rand() / RAND_MAX);
	return 0;
}
