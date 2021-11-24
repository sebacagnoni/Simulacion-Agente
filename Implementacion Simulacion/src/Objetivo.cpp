#include "Objetivo.h" 

Objetivo :: Objetivo() : _objeto(), _receptaculo() {}

Objetivo :: Objetivo(const Color& objeto, const Color& receptaculo) : _objeto(objeto), _receptaculo(receptaculo) {}

const Color& Objetivo::objeto() const {
	return _objeto;
} 

const Color& Objetivo::receptaculo() const {
	return _receptaculo;
}
