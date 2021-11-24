#include "aed2_simulacion.h"

//aed2_Simulacion :: aed2_Simulacion(const aed2_Mapa& mapa, const map<Color, Coordenada>& objetos, Coordenada inicio){
//	Mapa m = mapa.mapa(); // Utilizamos el conversor de aed2_Mapa a Mapa.
//  Simulacion s(m, inicio, objetos);
//	_sim = s;
//}

aed2_Simulacion :: aed2_Simulacion(const aed2_Mapa& mapa, const map<Color, Coordenada>& objetos, Coordenada inicio) : _sim(Simulacion(mapa.mapa(), inicio, objetos)) {}

void aed2_Simulacion :: mover(Direccion d){
	_sim.moverAgente(d);
}

void aed2_Simulacion :: agregarObjetivo(Objetivo o){
	_sim.agregarObjetivo(o);
}

const aed2_Mapa aed2_Simulacion :: mapa() const{
	return aed2_Mapa(_sim.mapa());
}

const map<Color, Coordenada> aed2_Simulacion :: posObjetos() {
	set<Color> coloresObjetos = _sim.coloresDeObjetos();
	map<Color, Coordenada> posiciones;
	for (Color c : coloresObjetos){
		posiciones[c] = _sim.posicionDeObjeto(c);
	}
	return posiciones;
}

Coordenada aed2_Simulacion :: posAgente() const {
	return _sim.posAgente();
}

const list<Objetivo>& aed2_Simulacion :: objetivosDisponibles() const {
	return _sim.objetivosDisponibles();
}

Nat aed2_Simulacion :: movimientos() const {
	return _sim.movimientos();
}

Nat aed2_Simulacion :: objetivosResueltos() const {
	return _sim.objetivosResueltos();
}
