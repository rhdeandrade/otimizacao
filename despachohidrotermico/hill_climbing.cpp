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
    bool stop_main_loop(int iteracao);
};

HillClimbing::HillClimbing(PlanoProducao p, int m, int mp) {
  this->current_state = p;
  this->maximum_iterations_number = m;
  this->maximum_perturbation_number_iteration = mp;
}

PlanoProducao HillClimbing::execute(int operacao_atomica) {
  int counter = 1;
  int para = 1;
  while (para) {
    this->perturbation(operacao_atomica, counter);

    if (this->stop_main_loop(counter)) {
      para = 0;
    }
  }
  
  return this->current_state;
}

bool HillClimbing::stop_main_loop(int iteracao) {
  if (iteracao > this->maximum_iterations_number) {
    return true;
  }
  return false;
}


void HillClimbing::perturbation(int operacao_atomica, int counter) {
  PlanoProducao p(this->current_state);

  this->next_state = p;
  for (int i; i < this->maximum_perturbation_number_iteration; i++) {
    this->next_state.perturbation(operacao_atomica, counter);
  }
}

#endif