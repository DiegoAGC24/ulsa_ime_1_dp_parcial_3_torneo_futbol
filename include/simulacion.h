#pragma once

#include <iostream>
#include <string>
using namespace std;
#include "torneo.h"

void simulacion(){

cout << "--- RESULTADOS DE LOS PARTIDOS ---" << endl;


for(int i = 0; i < 6; i++)
{
     for(int j = i + 1; j < 6; j++)
     {
cout << r[i].nombre << " vs " << r[j].nombre << endl;
     }
  }
}

































