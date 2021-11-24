#include "Simulacion.h"

Simulacion::Simulacion(const Mapa& mapa, Coordenada posicion, const map<Color, Coordenada>& objetos) : _mapa(mapa), _objDisponibles(), _conjObjetivosDisponibles(), _cantMovimientos(0), 
        _cantObjetivosRealizados(0), _pos(posicion) {
  vector<Celda> vectorChico;
	Celda celdaVacia(false, " ");
	for (int i = 0; i < _mapa.ancho(); i ++)
		vectorChico.push_back(celdaVacia);

	for (int j = 0; j < _mapa.alto(); j ++)
    _mapaObjetos.push_back(vectorChico);
  
	map<Color, Coordenada>::const_iterator it = objetos.begin();

  for (it; it != objetos.end(); ++it) {
  	Color clave = it -> first; 
  	Coordenada sig = it -> second;
  	get<0>(_mapaObjetos[sig.first][sig.second]) = true;
  	get<1>(_mapaObjetos[sig.first][sig.second]) = clave;

    _posObjetos.insert(make_pair(clave, sig));

    _colores.insert(clave);
  }
}
void Simulacion::moverAgente(Direccion d)
{
  Coordenada siguiente = siguienteCoordenada(posAgente(), d);
  Coordenada siguienteSig = siguienteCoordenada(siguiente, d);
  bool hayMovimiento = false;
  if(_mapa.enRango(siguiente))
  {
    bool objetoPosicionSiguiente = _mapaObjetos[siguiente.first][siguiente.second].first;
    _cantMovimientos++;
    if(!objetoPosicionSiguiente || (esPosibleMover(siguiente, d) && !hayObjetoEnPosicion(siguienteSig)))
    {
      if(esPosibleMover(_pos, d))
      {
        hayMovimiento = true;
      }
    }
  }

  if(hayMovimiento)
  {
    if(hayObjetoEnPosicion(siguiente))
    {
      _mapaObjetos[siguiente.first][siguiente.second].first = false;
      _mapaObjetos[siguienteSig.first][siguienteSig.second].first = true;
      Color colorObjeto = _mapaObjetos[siguiente.first][siguiente.second].second;
      _mapaObjetos[siguienteSig.first][siguienteSig.second].second = colorObjeto;
      _posObjetos[colorObjeto] = siguienteSig;
      bool cumplirObjetivo = false;

      if(_mapa.hayCasillaEspecial(siguienteSig))
      {
        Color receptaculo = _mapa.colorReceptaculo(siguienteSig);
        if(_objDisponibles.count(colorObjeto))
        {
          string_map<list<Objetivo>::iterator>& receptaculos = _objDisponibles[colorObjeto];
          if(receptaculos.count(receptaculo))
          {
            cumplirObjetivo = true;
          }
        }
      }

      if(cumplirObjetivo)
      {
        Color receptaculo = _mapa.colorReceptaculo(siguienteSig);
        string_map<list<Objetivo>::iterator>& receptaculos = _objDisponibles[colorObjeto];
        list<Objetivo>::iterator itLista = receptaculos[receptaculo];

        _conjObjetivosDisponibles.erase(itLista);
        
        receptaculos.erase(receptaculo);
        if(receptaculos.size() == 0)
        {
          _objDisponibles.erase(colorObjeto);
        } 
        _cantObjetivosRealizados++;
      }
    }
  _pos = siguiente;
  }
}

void Simulacion::agregarObjetivo(Objetivo obj)
{
  Color objeto = obj.objeto();
  Color receptaculo = obj.receptaculo();

  map<Color, Coordenada> posReceptaculo = mapa().receptaculos();
  Coordenada coordReceptaculo  = posReceptaculo[receptaculo];
  Coordenada coordObjeto = posicionDeObjeto(objeto);


  if(coordObjeto == coordReceptaculo)
  {
    _cantObjetivosRealizados++; 
  } else
  {
    _conjObjetivosDisponibles.push_back(obj);
    list<Objetivo>::iterator itList = _conjObjetivosDisponibles.end();
    itList--;

    if(_objDisponibles.count(objeto))
    {
      string_map<list<Objetivo>::iterator>& colorReceptaculos = _objDisponibles.at(objeto);
      colorReceptaculos.insert(make_pair(receptaculo, itList));
    } else
    {
      string_map<list<Objetivo>::iterator> colorReceptaculos;
      colorReceptaculos.insert(make_pair(receptaculo, itList));
      _objDisponibles.insert(make_pair(objeto, colorReceptaculos));
    }
  }

}

const Mapa Simulacion::mapa() const
{
  return _mapa;
}

Coordenada Simulacion::posAgente() const
{
  return _pos;
}

const list<Objetivo>& Simulacion::objetivosDisponibles() const
{
  return _conjObjetivosDisponibles;
}

Nat Simulacion::movimientos() const
{
  return _cantMovimientos;
}

Nat Simulacion::objetivosResueltos() const
{
  return _cantObjetivosRealizados;
}

set<Color> Simulacion::coloresDeObjetos() const {
  return _colores;
}

const Coordenada Simulacion::posicionDeObjeto(Color c) {
  return _posObjetos[c];  
}

bool Simulacion::esPosibleMover(Coordenada c, Direccion d){
  bool meMuevo = true;
  if(!_mapa.enRango(siguienteCoordenada(c, d)))
  {
    meMuevo = false;
  } else
  {
    meMuevo &= (!_mapa.hayUnaPared(siguienteCoordenada(c, d)) || _mapa.hayUnaRampa(c));
  }
  return meMuevo;
}

bool Simulacion::hayObjetoEnPosicion(Coordenada c){
  return get<0>(_mapaObjetos[c.first][c.second]);
}

// Pre : Direccion valida
Coordenada Simulacion::siguienteCoordenada(Coordenada c, Direccion d){
  switch(d){
    case ARRIBA:
      return make_pair(c.first , c.second + 1);
    case ABAJO:
      return make_pair(c.first , c.second - 1);
    case IZQUIERDA:
      return make_pair(c.first - 1, c.second);
    case DERECHA:
      return make_pair(c.first + 1, c.second);
  }
  return c;
}
