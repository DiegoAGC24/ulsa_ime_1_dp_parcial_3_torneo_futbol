#pragma once
#include "simulacion.h"
#include "escenario_prueba.h"
#include "torneo.h"
#include "utilerias.h"
#include <iostream>
#include <string>
#include <cctype>



// OJO: en main.cpp incluye este archivo DESPUES de torneo.h y utilerias.h

// Pasa un texto a minusculas usando un apuntador a char
inline std::string aMinusculas(std::string texto)
{
    char* p = &texto[0];
    for (int i = 0; i < static_cast<int>(texto.size()); i++)
    {
        *p = std::tolower(static_cast<unsigned char>(*p));
        p++;
    }
    return texto;
}

// Agrega espacios al final para que las columnas queden alineadas
inline std::string rellenar(std::string texto, int ancho)
{
    while (static_cast<int>(texto.size()) < ancho)
    {
        texto += " ";
    }
    return texto;
}

// Busca el equipo con un apuntador. Regresa su posicion o -1 si no existe
inline int buscarEquipo(Registro_equipos* equipos, std::string nombre)
{
    std::string buscado = aMinusculas(nombre);
    Registro_equipos* p = equipos;

    for (int i = 0; i < MAX_EQUIPOS; i++)
    {
        if (aMinusculas(p->nombre) == buscado)
        {
            return i;
        }
        p++;
    }
    return -1;
}

// Dice en que fila de la matriz goles quedo el partido entre a y b (a < b)
// Los partidos van en el orden: 0-1, 0-2, 0-3, 0-4, 0-5, 1-2, 1-3, ...
inline int indicePartido(int a, int b)
{
    int k = 0;
    for (int i = 0; i < MAX_EQUIPOS; i++)
    {
        for (int j = i + 1; j < MAX_EQUIPOS; j++)
        {
            if (i == a && j == b)
            {
                return k;
            }
            k++;
        }
    }
    return -1;
}

// Guarda en *gf los goles del equipo y en *gc los goles del rival
inline void obtenerMarcador(const int goles[][2], int equipo, int rival, int* gf, int* gc)
{
    if (equipo < rival)
    {
        int k = indicePartido(equipo, rival);
        *gf = goles[k][0];
        *gc = goles[k][1];
    }
    else
    {
        int k = indicePartido(rival, equipo);
        *gf = goles[k][1];
        *gc = goles[k][0];
    }
}

// Muestra la ficha del equipo que esta en la posicion pos
inline void mostrarFicha(Registro_equipos* equipos, const int goles[][2], int pos)
{
    int ganados = 0, empatados = 0, perdidos = 0;
    int golesFavor = 0, golesContra = 0;
    std::string tabla = "";

    for (int j = 0; j < MAX_EQUIPOS; j++)
    {
        if (j == pos)
        {
            continue;
        }

        int gf, gc;
        obtenerMarcador(goles, pos, j, &gf, &gc);

        golesFavor += gf;
        golesContra += gc;

        std::string resultado;
        if (gf > gc)
        {
            ganados++;
            resultado = "Ganado";
        }
        else if (gf == gc)
        {
            empatados++;
            resultado = "Empatado";
        }
        else
        {
            perdidos++;
            resultado = "Perdido";
        }

        std::string marcador = std::to_string(gf) + " - " + std::to_string(gc);
        tabla += rellenar((equipos + j)->nombre, 16) + rellenar(marcador, 10) + resultado + "\n";
    }

    int puntos = ganados * PUNTOS_VICTORIA + empatados * PUNTOS_EMPATE;

    std::cout << "\n--- FICHA DE EQUIPO ---" << std::endl;
    std::cout << "Equipo: " << (equipos + pos)->nombre << std::endl;
    std::cout << "Jugados: " << ganados + empatados + perdidos << std::endl;
    std::cout << "Ganados: " << ganados << std::endl;
    std::cout << "Empatados: " << empatados << std::endl;
    std::cout << "Perdidos: " << perdidos << std::endl;
    std::cout << "Goles a favor: " << golesFavor << std::endl;
    std::cout << "Goles en contra: " << golesContra << std::endl;
    std::cout << "Puntos: " << puntos << std::endl << std::endl;
    std::cout << rellenar("RIVAL", 16) << rellenar("MARCADOR", 10) << "RESULTADO" << std::endl;
    std::cout << tabla;
}

// Pide el nombre, lo valida, busca el equipo y muestra su ficha
inline void consultarEquipo(Registro_equipos* equipos, const int goles[][2])
{
    std::string nombre;
    bool valido = false;
    while (!valido)
    {
        nombre = leerCadena("Ingresa el nombre del equipo que buscas: ");
        if (static_cast<int>(nombre.size()) < MIN_CARACTERES_NOMBRE ||
            static_cast<int>(nombre.size()) > MAX_CARACTERES_NOMBRE)
        {
            std::cout << "El nombre debe tener entre " << MIN_CARACTERES_NOMBRE
                      << " y " << MAX_CARACTERES_NOMBRE << " caracteres." << std::endl;
        }
        else
        {
            valido = true;
        }
    }

    int pos = buscarEquipo(equipos, nombre);

    if (pos == -1)
    {
        std::cout << "\n--- FICHA DE EQUIPO ---" << std::endl;
        std::cout << "Equipo no encontrado: " << nombre << std::endl;
    }
    else
    {
        mostrarFicha(equipos, goles, pos);
    }
}






