
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

// Función para simular y guardar resultados
inline void simularPartidos(Equipo r[]) {

    if (totalPartidos > 0) {
        cout << "El torneo ya fue simulado." << endl;
        return;
    }

    totalPartidos = 0;

    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 6; j++) {

            int golesj = numeroAleatorio();
            int golesi = numeroAleatorio();

            // Guardar el resultado
            resultados[totalPartidos].equipo1 = r[i].nombre;
            resultados[totalPartidos].equipo2 = r[j].nombre;
            resultados[totalPartidos].goles1 = golesi;
            resultados[totalPartidos].goles2 = golesj;

            totalPartidos++;

            // Mostrar el partido
            cout << r[i].nombre << "      "
                 << golesi << "---" << golesj
                 << "      " << r[j].nombre << endl;
        }
    }
}

