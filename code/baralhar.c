#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralhar.h"

/** Esta funcao vai baralhar os agentes antes de começar cada ronda  **/
void baralhar(AGENT **baralhar_agentes, unsigned int nagentes) {
    /** Neste momento o programa vai avisar o utilizador que o embaralhamento vai comecar **/
    printf("%s\n\n", "A ordem esta definida! Vamos começar \n");

    unsigned int i = 0; /** variavel para passar valor para j  **/
    unsigned int j = 0; /** variavel que recebe o valor de temp **/
    AGENT *temp; /** Apontador para o agente que recebe o valor temporario **/

        
    for (i = nagentes - 1; i > 0; i--) {
		/**Vai guardar um numero aleatorio em J**/
        j = rand() % (i + 1);
        /**vai guardar o agente na variavel temp**/
        temp = baralhar_agentes[i];
        /**vai guardar o agente j em i**/
        baralhar_agentes[i] = baralhar_agentes[j];
        /** vai guardar o agente i em j  **/
        baralhar_agentes[j] = temp;
        
    }
}
