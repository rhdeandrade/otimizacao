#ifndef hill_climbing_h
#define hill_climbing_h

#include <iostream>
#include "plano_producao.cpp"

using namespace std;

class HillClimbing {
  public:
    PlanoProducao current_state;
    PlanoProducao next_state;

    int maximum_iterations_number;
    int maximum_perturbation_number_iteration;

    HillClimbing(PlanoProducao p, int m, int mp);
    PlanoProducao execute(int operacao_atomica);
    void perturbation(int operacao_atomica, int counter);
};

HillClimbing::HillClimbing(PlanoProducao p, int m, int mp) {
  this->current_state = p;
  this->maximum_iterations_number = m;
  this->maximum_perturbation_number_iteration = mp;
}

PlanoProducao HillClimbing::execute(int operacao_atomica) {
  int counter = 1;
  while (1) {
    this->perturbation(operacao_atomica, counter);
  }
  
  return this->current_state;
}

void HillClimbing::perturbation(int operacao_atomica, int counter) {
  PlanoProducao p(this->current_state);

  this->next_state = p;
  for (int i; i < this->maximum_perturbation_number_iteration; i++) {
    this->next_state.perturbation(operacao_atomica, counter);
  }
}

#endif