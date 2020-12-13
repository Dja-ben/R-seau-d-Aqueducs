#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "citiesReader.h"
#include "acm.h"



/*void saveGraph(ListOfCities * cities){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=0; i<cities->number; i++){
    for(int j=0; j<i; j++){
      fprintf(fileOut, "%i %i\n", i, j);
    }
  }
  fclose(fileOut);
} */

void saveGraph(graphe* g){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  int m= graphe_get_n(g);
  for(int i=0; i<m; i++){
    for(int j=0; j<i; j++){
      if(graphe_get_multiplicite_arete(g,i,j))
      {
        
        fprintf(fileOut, "%i %i\n", i, j);
      }
    }
  }
  
  fclose(fileOut);
}


int main(int argc, char ** argv) {

  if( argc != 2 ){
    perror("Veuillez passer une population minimale en paramètre du programme");
    return EXIT_FAILURE;
  }
//-----------------------------------------------------------------
//--- READING cities
//-----------------------------------------------------------------
  int popMin = atoi(argv[1]);
  
  ListOfCities* cities;
  cities = citiesReader(popMin);

  // ... just to check! This line can be removed.
  for(int i=0; i<cities->number; i++){
    printf("%s %i %f %f\n", cities->name[i], cities->pop[i], cities->lon[i], cities->lat[i]);
  }

//-----------------------------------------------------------------
//--- COMPUTING complete graph
//-----------------------------------------------------------------
  graphe g;
	graphe_stable(&g, cities->number);
  graphe_complet(&g, cities->number, cities);


  /*graphe_ecrire_dot(&g, "villes.dot");
  system("dot -Tx11 villes.dot"); */
  graphe acm;
  int statut = graphe_acm_kruskal(&g, &acm);
  printf("la longuer du reseau optimal est : %d\n", statut);
			/*if (statut =! 0) {
				graphe_ecrire_dot_avec_acm(&g, &acm,
					"acm_kruskal.dot");
				system("dot -Tx11 acm_kruskal.dot");
				graphe_detruire(&acm);
			}*/

  /* 
   Écriture du graphe (chaque ligne correspond à une arête)
   !!! Ci-dessous, on écrit le graphe complet pour l'exemple.
   Dans votre rendu, cette fonction prendra un graphe en argument,
   pas une liste de villes.
  */
  saveGraph(&acm);
  freeListOfCities(cities);

  return 0;
}

