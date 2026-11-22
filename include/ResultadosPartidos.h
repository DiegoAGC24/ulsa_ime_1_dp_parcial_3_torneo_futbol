
#pragma once

#include "simulacion.h"
#include "escenario_prueba.h"
#include "torneo.h"
#include "utilerias.h"

#include <iostream>
#include <string>
#include <cctype>

using namespace std;


// Estructura para guardar cada partido
struct Partido {
    string equipo1;
    string equipo2;
    int goles1;
    int goles2;
};

// Arreglo para almacenar los 15 partidos
inline Partido resultados[15];
inline int totalPartidos = 0;

