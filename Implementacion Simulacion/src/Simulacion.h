#include "Tipos.h"
#include "Mapa.h"
#include "Objetivo.h"
#include "string_map.h"

class Simulacion {
public:

    Simulacion(const Mapa& mapa, Coordenada inicio, const map<Color, Coordenada>& objetos);

    void moverAgente(Direccion);

    void agregarObjetivo(Objetivo);

    const Mapa mapa() const;

    Coordenada posAgente() const;

    Nat movimientos() const;

    const list<Objetivo>& objetivosDisponibles() const;

    Nat objetivosResueltos() const;

    set<Color> coloresDeObjetos() const;

    const Coordenada posicionDeObjeto(Color c);

private:
    Mapa _mapa;
    vector<vector<Celda>> _mapaObjetos;
    string_map<Coordenada> _posObjetos;
    string_map<string_map<list<Objetivo>::iterator>>_objDisponibles;
    list<Objetivo> _conjObjetivosDisponibles;
    Nat _cantMovimientos;
    Nat _cantObjetivosRealizados;
    Coordenada _pos;
    set<Color> _colores;

    Coordenada siguienteCoordenada(Coordenada, Direccion);
    bool esPosibleMover(Coordenada, Direccion);
    bool hayObjetoEnPosicion(Coordenada);
    vector<vector<Celda>> crearMapaObjetos(Nat, Nat, map<Color, Coordenada>&);
};
