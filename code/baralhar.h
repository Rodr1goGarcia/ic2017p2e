#ifndef SHUFFLE_H
#define SHUFFLE_H

#include "baralhar.h"

/**
 * Funcao Baralhar agentes.
 * @param agents_array Array que guarda apontadores para agentes do tipo humano e zombie
that holds pointers to `AGENT` objects of type
 Human and Zombie.
 * @param nagents numero total de agentes.
 **/
void baralhar(AGENT **baralhar_agentes, unsigned int nagentes);

#endif
