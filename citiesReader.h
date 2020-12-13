#include <math.h>
#ifndef CITIES_READER
#define CITIES_READER

typedef struct ListOfCities ListOfCities;

struct ListOfCities
{
  int    number;
  char** name;
  int*   pop;
  float* lon;
  float* lat;
};

ListOfCities* citiesReader(int popMin);
void saveListOfCities(ListOfCities* cities);
int calculer_distance( int villeD, int villeA, ListOfCities * cities);
void freeListOfCities(ListOfCities * cities);

#endif
