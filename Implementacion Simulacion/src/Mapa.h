#ifndef MAPA_H
#define MAPA_H
#include "Tipos.h"

using namespace std;

class Mapa {
public:

  	Mapa();

    Mapa(Nat ancho, Nat alto, map<Color, Coordenada> receptaculos);

    vector<vector<datosCelda>> crearMapa(Nat, Nat, map<Color, Coordenada>);

    void agregarRampa(Coordenada c);

    void agregarElevacion(Coordenada c);

    vector<vector<datosCelda>> dameMapa() const;
    
    Nat ancho() const;

    Nat alto() const;

    const map<Color, Coordenada>& receptaculos() const;

    Coordenada receptaculo(Color);

    bool hayUnaPared(Coordenada);

    bool hayUnaRampa(Coordenada);

    bool hayCasillaEspecial(Coordenada);

    bool enRango(Coordenada);

    Nat distancia(Coordenada x, Coordenada y);

    // Pre : La coordenada tiene una casilla especial
    Color colorReceptaculo(Coordenada);
private:
    int _ancho;
    int _alto;
    vector<vector<datosCelda>> _map; 
    map<Color, Coordenada> _casillasEspeciales;

};

#endif
