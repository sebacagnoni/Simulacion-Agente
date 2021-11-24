#include "string_map.h"

template <typename T>
string_map<T>::string_map() :  _raiz(new string_map<T>::Nodo()), _size(0) { };

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
  if(this->_size != 0)
  {
    deleteNodes(_raiz);
    _raiz = new Nodo();
  }
  Nodo* pointerCopy = d._raiz;
  copyNodes(_raiz, pointerCopy);
  _size = d._size;

  return *this;
}

template <typename T>
void string_map<T>::copyNodes(typename string_map<T>::Nodo* toCreate, typename string_map<T>::Nodo* toCopy){
  for(int i=0; i < 256; i++)
  {
    if(toCopy->siguientes[i] != nullptr)
    {
      Nodo* nuevoNodo = new string_map<T>::Nodo();
      copyNodes(nuevoNodo, toCopy->siguientes[i]);
      toCreate->siguientes[i] = nuevoNodo;
      toCreate->clavesEnVector++;
    }
  }
  if(toCopy->definicion != nullptr)
  {
    T* copyDef = new T(*toCopy->definicion);
    toCreate->definicion = copyDef;
  }
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& value)
{
  Nodo* next = _raiz;
  string key = value.first;
  T* val = new T(value.second);
  int i=0;
  while(i < key.size())
  {
    if(next->siguientes[(int)key[i]] == nullptr)
    {
      Nodo* newNode = new Nodo();
      next->siguientes[(int)key[i]] = newNode;
      next->clavesEnVector++;
    }
    next = next->siguientes[(int)key[i]];
    i++;
  }
  if(next->definicion != nullptr)
  {
    delete next->definicion;
  }
  next->definicion = val;
  _size++;
}

template <typename T>
string_map<T>::~string_map(){
  Nodo* first = _raiz;
  for(int i=0; i < 256;i++)
  {
    if(first->siguientes[i] != nullptr)
    {
      deleteNodes(first->siguientes[i]);
    }
  }
  delete first;
}

template <typename T>
void string_map<T>::deleteNodes(typename string_map<T>::Nodo* toDelete)
{
  typename string_map<T>::Nodo* first = toDelete;
  for(int i=0; i < 256;i++)
  {
    if(first->siguientes[i] != nullptr)
    {
      deleteNodes(first->siguientes[i]);
    }
  }
  if(toDelete->definicion != nullptr)
  {
    delete toDelete->definicion;
  }
  delete toDelete; 
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
  if(count(clave))
  {
    return at(clave);
  }
  else 
  {
    return createNew(clave);
  }
}

template <class T>
T& string_map<T>::createNew(const string& clave)
{
    Nodo* actual = _raiz;
    for(char c : clave)
    {
        if (actual->siguientes[int(c)] == nullptr) 
        {
            actual->siguientes[int(c)] = new Nodo();
        }
        actual = actual->siguientes[int(c)];
    }

    actual->definicion = new T();
    _size++;

    return *(actual->definicion);
}

template <typename T>
int string_map<T>::count(const string& clave) const{
  int i=0;
  Nodo* next = _raiz;
  int count = clave.size();
  bool found = true;
  if(_size == 0)
  {
    found = false;
  } else
  {
    while(i < count && found)
    {
      if(next->siguientes[(int)clave[i]] != nullptr)
      {
        next = next->siguientes[(int)clave[i]];
      } else
      {
        found = false;
      }
      i++;
    }
    if(next->definicion == nullptr)
    {
      found = false;
    }
  }
  return found;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
  Nodo* next = _raiz;
  int i = 0;
  while(i < clave.size())
  {
    next = next->siguientes[(int)clave[i]];
    i++;
  }
  return *next->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
  Nodo* next = _raiz;
  int i = 0;
  while(i < clave.size())
  {
    next = next->siguientes[(int)clave[i]];
    i++;
  }
  return *next->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
  Nodo* next = _raiz;
  Nodo* parent = _raiz;
  int i = 0;
  int j = 0;
  while(i < clave.size())
  {
    if(next->clavesEnVector > 1 || next->definicion != nullptr)
    {
      parent = next;
      j = i;
    }
    next = next->siguientes[(int)clave[i]];
    i++;
  }

  delete next->definicion;
  next->definicion = nullptr;
  if(next->clavesEnVector == 0)
  {
    Nodo* tmp = parent->siguientes[(int)clave[j]]; 
    parent->siguientes[(int)clave[j]] = nullptr;
    parent = tmp;
    next = parent;
    j++;
    
    while(j < clave.size())
    {
      next = next->siguientes[(int)clave[j]];
      delete parent;
      parent = next;
      j++;
    }
    delete parent;
  }
  _size--;
}

template <typename T>
int string_map<T>::size() const{
  return _size;
}

template <typename T>
bool string_map<T>::empty() const{
  return (_size == 0);
}
