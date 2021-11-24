#include"Mapa.h"
#include<math.h>

Mapa::Mapa() : _ancho(), _alto(), _casillasEspeciales(), _map() {} 

Mapa::Mapa(Nat ancho, Nat alto, map<Color, Coordenada> receptaculos) : _ancho(ancho), _alto(alto), _casillasEspeciales(receptaculos) {
  vector<datosCelda> vectorChico;
	datosCelda celdaVacia(false, false, false, " ");
	for (int i = 0; i < ancho; i ++)
		vectorChico.push_back(celdaVacia);

	for (int j = 0; j < alto; j ++)
    _map.push_back(vectorChico);
  
	map<Color, Coordenada> :: iterator it = receptaculos.begin();

  for (it; it != receptaculos.end(); ++it) {
  	Color clave = it -> first; 
  	Coordenada sig = it -> second;
  	get<2>(_map[sig.first][sig.second]) = true;
  	get<3>(_map[sig.first][sig.second]) = clave;
  }
}

void Mapa :: agregarRampa(Coordenada c){
	get<0>(_map[c.first][c.second]) = true;
}

void Mapa :: agregarElevacion(Coordenada c){
	get<1>(_map[c.first][c.second]) = true;
}

vector<vector<datosCelda>> Mapa :: dameMapa() const {
	return _map;
}

Nat Mapa :: ancho() const {
	return _ancho;
}

Nat Mapa :: alto() const {
	return _alto;
}

const map<Color, Coordenada>& Mapa :: receptaculos() const {
	return _casillasEspeciales;
}

Coordenada Mapa :: receptaculo(Color c) {
	return _casillasEspeciales[c];
}

bool Mapa::hayUnaPared(Coordenada c)
{
  return get<1>(_map[c.first][c.second]);
}

bool Mapa::hayUnaRampa(Coordenada c)
{
  return get<0>(_map[c.first][c.second]);
}

bool Mapa::hayCasillaEspecial(Coordenada c)
{
  return get<2>(_map[c.first][c.second]);
}

bool Mapa::enRango(Coordenada c)
{
  bool en_rango = true;
  en_rango &= (0 <= c.first && c.first < alto());
  en_rango &= (0 <= c.second && c.second < ancho());
  return en_rango;
}

Color Mapa::colorReceptaculo(Coordenada c)
{
  return get<3>(_map[c.first][c.second]);
}

Nat Mapa::distancia(Coordenada x, Coordenada y)
{
  Nat distancia = pow(x.first - y.first, 2) + pow(x.second - y.second, 2);
  return distancia;
}
