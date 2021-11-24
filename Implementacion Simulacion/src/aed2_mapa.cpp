#include"aed2_mapa.h"

aed2_Mapa :: aed2_Mapa() : _mapa() {}

aed2_Mapa :: aed2_Mapa(Nat ancho, Nat alto, set<Coordenada> elevaciones, map<Color, Coordenada> receptaculos) {
	_mapa = Mapa(ancho, alto, receptaculos);
	set<Coordenada> :: iterator it = elevaciones.begin();
	for (it; it != elevaciones.end(); it++){
		_mapa.agregarElevacion(*it);
	}
}

void aed2_Mapa :: agregarRampa(Coordenada c){
	_mapa.agregarRampa(c);
}

Nat aed2_Mapa :: ancho() const {
	return _mapa.ancho();
}

Nat aed2_Mapa :: alto() const {
	return _mapa.alto();
}

TipoCasillero aed2_Mapa :: tipoCasillero(Coordenada c) const {
	TipoCasillero res = PISO;
	if (get<0>(_mapa.dameMapa()[c.first][c.second])){
		res = RAMPA;
	} else if (get<1>(_mapa.dameMapa()[c.first][c.second])){
		res = ELEVACION;
	}
	return res;
}

const map<Color, Coordenada>& aed2_Mapa :: receptaculos() const {
	return _mapa.receptaculos();
}

Coordenada aed2_Mapa :: receptaculo(Color c) {
	return _mapa.receptaculo(c);
}

aed2_Mapa :: aed2_Mapa(Mapa m) : _mapa(m) {}

Mapa aed2_Mapa::mapa() const {
	return _mapa;
}
