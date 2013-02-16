#ifndef usina_hidreletrica_h
#define usina_hidreletrica_h

#include <iostream>
#include "reservatorio.cpp"

using namespace std;

class UsinaHidreletrica : public Usina {
  public:
    static const char TIPO_MAXIMIZACAO_RESERVATORIO = 'r';
    static const char TIPO_MAXIMIZACAO_AFLUENCIA_NATURAL = 'a';
    Reservatorio reservatorio;

};

#endif