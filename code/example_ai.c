/**
 **This file is part of "Projeto de Introdução à Computação 2ª época 2017/2018"
 **(PIC2e1718).
 **
 **PIC2e1718 is free software: you can redistribute it and/or modify
 **it under the terms of the GNU General Public License as published by
 **the Free Software Foundation, either version 3 of the License, or
 **(at your option) any later version.
 **
 **PIC2e1718 is distributed in the hope that it will be useful,
 **but WITHOUT ANY WARRANTY; without even the implied warranty of
 **MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **GNU General Public License for more details.
 **
 **You should have received a copy of the GNU General Public License
 **along with PIC2e1718. If not, see <http://www.gnu.org/licenses/>.
 **/

/**
 * @file
 * This file is an example of: a) how to use the API defined in the
 * showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided by the
 * showworld_simple.c file).
 * @author Ricardo Leal
 * @author Andre Rosa
 * @author Rodrigo Garcia
 * @author Nuno Fachada
 * @date 2018
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 **/

#include "showworld.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <g2.h>
#include <g2_X11.h>
/** Define o tamanho horizontal do Mundo. **/
#define WORLD_X 20

/** Define o tamanho vertical do mundo. **/
#define WORLD_Y 20

/** Define o numero de humanos. */
#define NHUMANS 6

/** Define o numero de Zombies. */
#define NZOMBIES 6

/** Numero de humanos playable. */
#define NHUMANS_PLAY 2

/** Numero de zombies playable. */
#define NZOMBIES_PLAY 2

/** Numero de turnos **/
#define TURNOS 10

/** Variavel para contar**/
int contar = 0;

/** Array **/
int played[WORLD_X][WORLD_Y];

typedef struct {
    AGENT_TYPE type;        /**Tipo de agente         	**/
    unsigned char playable; /**Jogabilidade do agente	**/
    unsigned short id;      /**< ID do agente.          **/
} AGENT;

/** This function is an implementation of the definition provided by the
 **::get_agent_info_at() function pointer. It only works for AGENT example
 **structure defined in this file. **/
unsigned int example_get_ag_info(void *world, unsigned int x, unsigned int y);

/**
 * This `main` function is only an example of: a) how to use the API defined in
 * the showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided in the
 * showworld_simple.c file).
 *
 * @return Always zero.
 * */
int main() {

    /** An instance of a SHOWWORLD world display. **/
    SHOWWORLD *sw = NULL;

    /** A by-dimensional array of agent pointers, representing agents in a
       grid. In the final project the agent grid or world should be abstracted
       to specific world.c/world.h files, with new/destroy functions (see files
       from aula 12).
       All elements in this grid are initialized to NULL, i.e., they don't
       initially point to anything. **/
    AGENT *grid[WORLD_X][WORLD_Y] = { NULL };

    /** Initialize world display. **/
    sw = showworld_new(WORLD_X, WORLD_Y, example_get_ag_info);

    /** Initialize random number generator. **/
    srand(time(NULL));

    /*****************************************/
    /**Create and place human agents in grid**/
    /*****************************************/
    /**Guarda o numero de humanos em contar**/
    contar = NHUMANS;
    /**Enquanto contar nao for 0**/
    while (contar != 0 ){
		/**Ciclo para colocar humanos**/
		for (int i = 0; i < NHUMANS; i++) {

			/** Indica coordenadas x e y aleatorias. **/
			unsigned int x = rand() % WORLD_X;
			unsigned int y = rand() % WORLD_Y;

			/** Verifica se nao ha nada em x,y na grelha.**/
			if (grid[x][y] == NULL) {

				/** Este agente verifica se e jogavel **/
				unsigned char playable = (i < NHUMANS_PLAY);

				/** Criar agente com valores de tipo, jogavel e id**/
				AGENT *ag = malloc(sizeof(AGENT));
				ag->type = Human;
				ag->playable = playable;
				ag->id = (unsigned short) i;
				
				

				/** Coloca o agente na grelha**/
				grid[x][y] = ag;
				
				/**Reduz o contador de Humanos**/
				contar--;

			} else {

				/** Como encima nao deu para fazer por estar ocupado, ele
				 * pede outra vez**/
				i--;
			}

		}
	}

    /*************************************************************************/
    /**Create and place zombie agents in grid. This for loop is very similar**/
    /**to the previous one for humans, so consider putting this common code **/
    /**in a function.                                                       **/
    /*************************************************************************/
    
    /**Guarda o numero de humanos em contar**/
    contar = NZOMBIES;
    
    /**Enquanto contar nao for 0**/
    while (contar != 0){
			/**Ciclo para colocar zombies**/
		for (int i = 0; i < NZOMBIES; i++) {

			/** Indica coordenadas x e y aleatorias. **/
			unsigned int x = rand() % WORLD_X;
			unsigned int y = rand() % WORLD_Y;

			/** Verifica se nao ha nada em x,y na grelha.**/
			if (grid[x][y] == NULL) {

				/** Este agente verifica se e jogavel **/
				unsigned char playable = (i < NZOMBIES_PLAY);

				/** Criar agente com valores de tipo, jogavel e id**/
				AGENT *ag = malloc(sizeof(AGENT));
				ag->type = Zombie;
				ag->playable = playable;
				ag->id = (unsigned short) i + NHUMANS;
			   

				/** Coloca o agente na grelha**/
				grid[x][y] = ag;
				/**Reduz o contador de Zombies**/
				contar--;

			} else {

				/** Como encima nao deu para fazer por estar ocupado, ele
				 * pede outra vez**/
				i--;
			}

		}
	}

    /*************************************************************************/
    /** Update display using the showworld_update() function, as declared in */
    /** the showworld.h file.                                                */
    /*************************************************************************/
  
	showworld_update(sw, grid);

	contar = NHUMANS;
	/** TURNOS **/
	for(int t=1; t<=TURNOS; t++){
		for (int i = 0; i <WORLD_X; i++) {
			for (int j = 0; j < WORLD_Y; j++) {
				if (grid[i][j] != NULL) {
					played[i][j] = 0;
				}
			}
		}
		/**Variavel que vai receber valor para andar**/
		char tecla =' ';
		/**Informa quel e o turno e pede uma accao ao jogador**/
		printf("Turno %d \n", t);
		/**Enquanto nao for tecla 2,4,6,8 mostra o default e repete 
		 * o pedido de tecla**/
		/**Vai procurar, ponto a ponto, pelas casas onde 
		* na grid esta um agente diferente de NULL**/
		for (int i = 0; i <WORLD_X; i++) {
			for (int j = 0; j < WORLD_Y; j++) {
				if(contar != 0){	
					if (grid[i][j] != NULL) {
						if(grid[i][j]->playable){
							if(played[i][j] == 0){
								while (tecla != '2' && tecla != '4' && tecla != '6' 
								&& tecla != '8') {
									printf("escolhe a tua jogada '2, 4, 6, 8' \n");
									printf("E a vez de %02d jogar!: ", grid[i][j]->id);
									/**Receber valor tecla**/
									scanf(" %c", &tecla);
									getchar();
									/**Cases**/
									switch (tecla) {
										/**Andar para baixo**/
										case '2': 
											/**Vai verificar se o agente se vai 
											 * movimentar para fora do mapa 
											 * ultrapassando o limite inferior 
											 * (y maximo)**/
											if (j-1 >= 0){
												if (grid[i][j-1] == NULL) {
													/**Vai efetuar a movimentacao para 
													 * a casa abaixo **/
													grid[i][j-1] = grid[i][j];
													/**Vai apagar a sua posicao anterior**/
													grid[i][j] = None;
													
													/**Guarda o valor do agente para não jogar até a proxima ronda**/
													played[i][j-1]=1;
												}else if (grid[i][j-1]->type == Human) {
													if (grid[i][j]->type == Zombie) {
													/**Vai transformar o agente humano em zombie **/
													grid[i][j-1]->type = Zombie;
													/**Reduz o numero de Humanos**/
													contar--;
														
													/**Guarda o valor do agente para não jogar até a proxima ronda**/
													played[i][j]=1;
													}
												}
											}
											break;
										/**Andar para esquerda**/
										case '4': 
											/**Vai verificar se o agente se vai 
											 * movimentar para fora do mapa 
											 * ultrapassando o limite da esquerda 
											 * (x minimo)**/
											if (i-1 >= 0){
												if (grid[i-1][j] == NULL) {
													/**Vai efetuar a movimentacao para 
													 * a casa a esquerda **/
													grid[i-1][j] = grid[i][j];
													/**Vai apagar a sua posicao anterior**/
													grid[i][j] = None;
													/**Guarda o valor do agente para não jogar até a proxima ronda**/
													played[i-1][j]=1;
												}else if (grid[i-1][j]->type == Human) {
													if (grid[i][j]->type == Zombie) {
														/**Vai transformar o agente humano em zombie **/
														grid[i-1][j]->type = Zombie;
														/**Reduz o numero de Humanos**/
														contar--;
														
														/**Guarda o valor do agente para não jogar até a proxima ronda**/
														played[i][j]=1;
													}
												}
											}
											break;	
										/**Andar para direita**/
										case '6': 
											/**Vai verificar se o agente se vai 
											* movimentar para fora do mapa 
											* ultrapassando o limite da direita 
											* (x maximo)**/
											if (i+1 <= WORLD_X-1){
												if (grid[i+1][j] == NULL) {
													/**Vai efetuar a movimentacao para 
													 * a casa a direita **/
													grid[i+1][j] = grid[i][j];
													/**Vai apagar a sua posicao anterior**/
													grid[i][j] = None;
													/**Guarda o valor do agente para não jogar até a proxima ronda**/
													played[i+1][j]=1;
												}else if (grid[i+1][j]->type == Human) {
													if (grid[i][j]->type == Zombie) {
														/**Vai transformar o agente humano em zombie **/
														grid[i+1][j]->type = Zombie;
														/**Reduz o numero de Humanos**/
														contar--;
														
														/**Guarda o valor do agente para não jogar até a proxima ronda**/
														played[i][j]=1;
													}
												}
											}	
											break;
										/**Andar para cima**/
										case '8': 
											/**Vai verificar se o agente se vai 
											* movimentar para fora do mapa 
											* ultrapassando o limite superior 
											* (y minimo)**/
											if (j+1 <= WORLD_Y-1){
												if (grid[i][j+1] == NULL) {
													/**Vai efetuar a movimentacao para 
													 * a casa acima**/
													grid[i][j+1] = grid[i][j];
													/**Vai apagar a sua posicao anterior**/
													grid[i][j] = None;
													/**Guarda o valor do agente para não jogar até a proxima ronda**/
													played[i][j+1]=1;
												}else if (grid[i][j+1]->type == Human) {
													if (grid[i][j]->type == Zombie) {
														/**Vai transformar o agente humano em zombie **/
														grid[i][j+1]->type = Zombie;
														/**Reduz o numero de Humanos**/
														contar--;
														
														/**Guarda o valor do agente para não jogar até a proxima ronda**/
														played[i][j]=1;
													}
												}
											}
											break;
										/**Caso nenhum dos casos anteriores se confirme, 
										 * executa o seguinte codigo**/
										default:
											printf("Essa tecla não é aceite, escolha 2,4,6,8\n");
											break;
									}
								}
							/**Atualiza posicoes dos agentes**/
							showworld_update(sw, grid);
							if(contar==0){
								t=TURNOS;
								/** Indica que os Zombies ganharam **/
								printf("Os Zombies venceram a raca humana!\n");
							}
							/**Variavel que vai receber valor para andar**/
							tecla =' ';
							}
						}else{
						unsigned int andar = rand() % 5;
							switch(andar){
								/**Andar para baixo**/
								case 1:
									/**Vai verificar se o agente se vai 
									 * movimentar para fora do mapa 
									 * ultrapassando o limite inferior 
									 * (y maximo)**/
									if (j-1 >= 0){
										if (grid[i][j-1] == NULL) {
											/**Vai efetuar a movimentacao para 
											 * a casa abaixo **/
											grid[i][j-1] = grid[i][j];
											/**Vai apagar a sua posicao anterior**/
											grid[i][j] = None;
											
											/**Guarda o valor do agente para não jogar até a proxima ronda**/
											played[i][j-1]=1;
										}else if (grid[i][j-1]->type == Human) {
											if (grid[i][j]->type == Zombie) {
											/**Vai transformar o agente humano em zombie **/
											grid[i][j-1]->type = Zombie;
											/**Reduz o numero de Humanos**/
											contar--;
												
											/**Guarda o valor do agente para não jogar até a proxima ronda**/
											played[i][j]=1;
											}
										}
									}
								break;
								/**Andar para esquerda**/
								case 2:
									/**Vai verificar se o agente se vai 
									 * movimentar para fora do mapa 
									 * ultrapassando o limite da esquerda 
									 * (x minimo)**/
									if (i-1 >= 0){
										if (grid[i-1][j] == NULL) {
											/**Vai efetuar a movimentacao para 
											 * a casa a esquerda **/
											grid[i-1][j] = grid[i][j];
											/**Vai apagar a sua posicao anterior**/
											grid[i][j] = None;
											/**Guarda o valor do agente para não jogar até a proxima ronda**/
											played[i-1][j]=1;
										}else if (grid[i-1][j]->type == Human) {
											if (grid[i][j]->type == Zombie) {
												/**Vai transformar o agente humano em zombie **/
												grid[i-1][j]->type = Zombie;
												/**Reduz o numero de Humanos**/
												contar--;
												
												/**Guarda o valor do agente para não jogar até a proxima ronda**/
												played[i][j]=1;
											}
										}
									}
									break;	
								break;
								/**Andar para direita**/
								case 3:
									/**Vai verificar se o agente se vai 
									* movimentar para fora do mapa 
									* ultrapassando o limite da direita 
									* (x maximo)**/
									if (i+1 <= WORLD_X-1){
										if (grid[i+1][j] == NULL) {
											/**Vai efetuar a movimentacao para 
											 * a casa a direita **/
											grid[i+1][j] = grid[i][j];
											/**Vai apagar a sua posicao anterior**/
											grid[i][j] = None;
											/**Guarda o valor do agente para não jogar até a proxima ronda**/
											played[i+1][j]=1;
										}else if (grid[i+1][j]->type == Human) {
											if (grid[i][j]->type == Zombie) {
												/**Vai transformar o agente humano em zombie **/
												grid[i+1][j]->type = Zombie;
												/**Reduz o numero de Humanos**/
												contar--;
												
												/**Guarda o valor do agente para não jogar até a proxima ronda**/
												played[i][j]=1;
											}
										}
									}	
								/**Andar para cima**/
								case 4:
									/**Vai verificar se o agente se vai 
									* movimentar para fora do mapa 
									* ultrapassando o limite superior 
									* (y minimo)**/
									if (j+1 <= WORLD_Y-1){
										if (grid[i][j+1] == NULL) {
											/**Vai efetuar a movimentacao para 
											 * a casa acima**/
											grid[i][j+1] = grid[i][j];
											/**Vai apagar a sua posicao anterior**/
											grid[i][j] = None;
											/**Guarda o valor do agente para não jogar até a proxima ronda**/
											played[i][j+1]=1;
										}else if (grid[i][j+1]->type == Human) {
											if (grid[i][j]->type == Zombie) {
												/**Vai transformar o agente humano em zombie **/
												grid[i][j+1]->type = Zombie;
												/**Reduz o numero de Humanos**/
												contar--;
												
												/**Guarda o valor do agente para não jogar até a proxima ronda**/
												played[i][j]=1;
											}
										}
									}
									break;
								default:
								break;
							}
							/**Atualiza posicoes dos agentes**/
							showworld_update(sw, grid);
							if(contar==0){
								t=TURNOS;
								/** Indica que os Zombies ganharam **/
								printf("Os Zombies venceram a raca humana!\n");
							}
						}
					}
				}
			}
		}
	}
	if(contar != 0){
		/** Indica que os Humanos ganharam **/
		printf("Os Humanos venceram os zombies!\n");
	}
	/** Fim do Jogo **/
	printf("Acabou o Jogo!\n");
	/** PEDE UM ENTER. **/
	printf("Press ENTER to continue...\n");
	getchar();

	/** Destruir todos os agentes. **/
	for (int i = 0; i < WORLD_X; i++) {
		for (int j = 0; j < WORLD_Y; j++) {
			if (grid[i][j] != NULL) {
				free(grid[i][j]);
			}
		}
	}

	/** Apagar o mundo. **/
	showworld_destroy(sw);

	/** Bye. **/
	return 0;
	}


/**
 * This function is an implementation of the ::get_agent_info_at() function
 * definition. It only works for the ::AGENT structure defined in this example,
 * and considers the agent world as a 2D grid of agent pointers (as defined in
 * main).
 *
 * It basically receives a pointer to a 2D grid of agent pointers, obtains the
 * AGENT pointer in the given coordinates, and returns the agent information in
 * a bit-packed `unsigned int`.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of
 * ::get_agent_info_at() and agent/world data structures.
 *
 * @param w Generic pointer to object representing the simulation world.
 * @param x Horizontal coordinate of the simulation world from where to fetch
 * the agent information.
 * @param y Vertical coordinate of the simulation world from where to fetch
 * the agent information.
 * @return An integer containing bit-packed information about an agent, as
 * follows: bits 0-1 (agent type), bit 2 (is agent playable), bits 3-18 (agent
 * ID). Bits 19-31 are available for student-defined agent extensions.
 * */
unsigned int example_get_ag_info(void *w, unsigned int x, unsigned int y) {

    /** A informacao do agente a devolver. **/
    unsigned int ag_info = 0;

    /** Convert generic pointer to world to a 2D grid of agent pointers (in
       practice we are reinterpreting the grid as 1D). **/
    AGENT **grid = (AGENT **) w;

    /** verificar se as coordenadas (x,y) estao dento do World. **/
    if ((x >= WORLD_X) || (y >= WORLD_Y)) {

        /** Chegando aqui, as coordenadas estao fora do mundo, logo vamos
         *  reportar a tentativa de colocacao e de tipo desconhecidos,
         * nao sendo necessario espicificar o ID pois e desconhecido. **/
        ag_info = Unknown;

    } else {

        /** Sendo que as coordenadas estao dentro do mundo, 
         * vamos comecar a recolher as informacoes dos agentes  **/

        /** Obter as coordenadas do agente. **/
        AGENT *ag = grid[x * WORLD_Y + y];

        /** ver se ha um agente em x, y **/
        if (ag == NULL) {

            /**Se nao ha agente nas coordenadas (x, y),
             *  o seu ID é defenido como none **/
            ag_info = None;

        } else {

            /**Se chegamos aqui e porque ha um agente em (x,y).
             * Vai ser junta toda a informacao, bit a bit dos agentes
             * como e especificada pela funcao get_agent_info_at. **/
            ag_info = (ag->id << 3) | (ag->playable << 2) | ag->type;

        }

    }

    /** Devolver a informacao pedida. **/
    return ag_info;
}
