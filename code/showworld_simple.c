/**
 ** This file is part of "2º Projeto de Introdução à Computação 2017/2018"
 ** (2oPIC1718).
 **
 ** 2oPIC1718 is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** 2oPIC1718 is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with 2oPIC1718. If not, see <http://www.gnu.org/licenses/>.
 ** **/

/**
 * @file
 * Implementation of the interface defined in showworld.h which displays an
 * ASCII-based visualization of the current state of the simulation world.
 *
 * @note Students should change or replace this file with a new implementation
 * making use of graphical or game library.
 *
 * @authors Nuno Fachada, André Rosa (a21704022), Ricardo Leal (a21703090), Rodrigo Garcia (a21704304)
 * @date 2018
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

#include "showworld.h"
#include <stdio.h>
#include <stdlib.h>
#include <g2.h>
#include <g2_X11.h>

enum g2_colors {
    WHITE = 0, /** Background **/
    BLACK = 1, /** Nothing **/
    BLUE= 3, /** Playable ZOmbie**/
    GREEN = 7, /** Playable Agent **/
    GRAY = 14, /** Agent None **/
    RED = 19, /** Agent Zombies **/
    YELLOW = 25 /** Agent Humans **/
};

/** The implementation of `SHOWWORLD` type used in this simple text-based world
 ** visualization code. In this simple case, we only need to keep track of the
 ** world dimensions and of the function pointer which knows how to read an
 ** agent from the world data structure.
 **
 ** For a more complex implementation, for example based on the g2 library,
 ** it would also be necessary to keep the g2 device.
 ** **/
struct showworld {
    unsigned int xdim;
    unsigned int ydim;
    get_agent_info_at aginfo_func;
};

/** Cria uma nova interface grafica para a simulacao do mundo.
 **
 * Esta funcao obedece ao prototipo `showworld_new()` que foi definido em
 ** `showworld.h`. **/
SHOWWORLD *showworld_new(
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at aginfo_func) {

	SHOWWORLD *sw = NULL;
    sw = malloc(sizeof(SHOWWORLD));
    sw->xdim = xdim;
    sw->ydim = ydim;
    sw->aginfo_func = aginfo_func;
    
    return sw; 

}

/**Destroi a interface grafica do mundo simulado.
 **
  * Esta funcao obedece ao prototipo `showworld_new()` que foi definido em
 ** `showworld.h`. **/
void showworld_destroy(SHOWWORLD *sw) {
    free(sw);
}

/** Faz update a interface grafica.
 **
 * * Esta funcao obedece ao prototipo `showworld_new()` que foi definido em
 ** `showworld.h`. **/
void showworld_update(SHOWWORLD *sw, void *w) {
	
	int *device;
    device = malloc(sizeof(int));
	
    /**Abrir janela **/
    *device = g2_open_X11(sw->xdim * 21.5, sw->ydim * 23.5);
    
    /** Desenhar o fundo **/
    g2_set_background(*device, WHITE);
    
    /** Especificar tamanho e forma dos agentes **/
    g2_set_QP(*device, 20, QPcirc);
    
    printf("\n");
    
    /**Usa caneta da cor cizenta**/
    g2_pen(*device, GRAY);
    /**Desenha um circulo nas posicoes x (0.5) e y (0.5)**/
	g2_plot_QP(*device, 0.5, 0.5);
	/**Usa caneta da cor verde**/
    g2_pen(*device, GREEN);
    /**Desenha um circulo nas posicoes x (2.5) e y (0.5)**/
	g2_plot_QP(*device, 2.5, 0.5);
	/**Usa caneta da cor preto**/
	g2_pen(*device, BLACK);
	/**Escreve HP (Humanos player) nas posicoes x (xdim*2.75) e y (ydim*0.75)**/
	g2_string(*device, sw->xdim * 2.75, sw->ydim*0.75, "P");
	/**Usa caneta da cor amarelo**/
	g2_pen(*device, YELLOW);
	/**Desenha um circulo nas posicoes x (4.5) e y (0.5)**/
	g2_plot_QP(*device, 4.5, 0.5);
	/**Usa caneta da cor preto**/
	g2_pen(*device, BLACK);
	/**Escreve H (Humanos) nas posicoes x (xdim*4.75) e y (ydim*0.75)**/
	g2_string(*device, sw->xdim * 4.75, sw->ydim*0.75, "H");
	/**Usa caneta da cor azul**/
	g2_pen(*device, BLUE);
	/**Desenha um circulo nas posicoes x (6.5) e y (0.5)**/
	g2_plot_QP(*device, 6.5, 0.5);
	/**Usa caneta da cor preto**/
	g2_pen(*device, BLACK);
	/**Escreve ZP (Zombies player) nas posicoes x (xdim*6.75) e y (ydim*0.75)**/
	g2_string(*device, sw->xdim * 6.75, sw->ydim*0.75, "ZP");
	/**Usa caneta da cor vermelha**/
	g2_pen(*device, RED);
	/**Desenha um circulo nas posicoes x (8.5) e y (0.5)**/
	g2_plot_QP(*device, 8.5, 0.5);
	/**Usa caneta da cor preto**/
	g2_pen(*device, BLACK);
	/**Escreve Z (Zombies) nas posicoes x (xdim*8.75) e y (ydim*0.75)**/
	g2_string(*device, sw->xdim * 8.75, sw->ydim*0.75, "Z");
	/**Desenha um circulo nas posicoes x (10.5) e y (0.5)**/
	g2_plot_QP(*device, 10.5, 0.5);
	/**Usa caneta da cor branca**/
	g2_pen(*device, WHITE);
	/**Escreve U (Unknown) nas posicoes x (xdim*10.75) e y (ydim*0.75)**/
	g2_string(*device, sw->xdim * 10.75, sw->ydim*0.75, "U");
    
    /** Mostra uma nova linha depois do mundo ser mostrado/atualizado. **/
    printf("\n");

    /** Percorre todas as linhas **/
    for (unsigned int y = (sw->ydim); y > 0; --y) {

        /** Percorre todas as colunas da linha atual **/
        for (unsigned int x = 0; x < sw->xdim; ++x) {

            /** Recebe o estado da funcao (bit a bit) 
             * usando a funcao fornecida pelo utilizador. **/
            unsigned int item = sw->aginfo_func(w, x, y-1);

            /**Recolhe o tipo de agente(2 bits). **/
            AGENT_TYPE ag_type = item & 0x3;
            /** Recolhe se o agente e jogavel ou nao (1 bit). **/
            unsigned char playable = (item >> 2) & 0x1;
            /** Recolhe o ID dos agentes (16 bits). **/
            unsigned short ag_id = (item >> 3) & 0xFFFF;
            

            /** Este switch determina o tipo de agente e desenha-o na
             * grelha e na janela de g2. **/
            switch (ag_type) {

                /** Se nao ha nenhum agente numa certa coordenada (x,y)
                 * mostra, no terminal um ponto e um circulo 
                 * cinzento na janela de g2. **/
                case None:
                    printf(" .  ");
                    g2_pen(*device, GRAY);
                    g2_plot_QP(*device, x+0.5, y+1.5);
                    break;

                /** Se ha um humano na coordenada (x,y) 
                 * mostra um 'h' ou um 'H' no terminal e um circulo verde
                 * ou amarelo na janela g2. **/
                case Human:
                    if (playable) {
                        /** Se o 'H' for maiusculo, o humano e 
                         * controlado pelo jogador (playable) e imprime
                         * na janela g2 um circulo verde. **/
                        printf("H");
                        g2_pen(*device, GREEN);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    } else {
                        /** Se o 'h' for minusculo o humano
                         * e controlado por AI (not playble) e imprime
                         * na janela g2 um circulo amarelo. **/
                        printf("h");
                        g2_pen(*device, YELLOW);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    }
                    /** Mostra o ID do humano depois de 
                     * 'H' ou 'h' (ex:H01,h02). **/
                    printf("%02X ", ag_id);
                    break;

                /** Se esta um zombie presente na coordenada (x,y)
                 * imprime no terminal um 'z' ou um 'Z' no terminal e um 
                 * circulo azul ou vermelho na janela g2. **/
                case Zombie:
                    if (playable) {
                        /** Se o Z for maiusculo o zombie e controlado 
                         * pelo jogador (playable) e imprime na janela g2
                         * um circulo azul. **/
                        printf("Z");
                        g2_pen(*device, BLUE);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    } else {
                        /** Se o 'h' for minusculo os zombie sao
                         *  controlados por AI (not playable)
                         * e imprime na janela g2 um circulo vermelho. **/
                        printf("z");
                        g2_pen(*device, RED);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    }
                    /** Mostra o id do zombie depois de 'Z' ou'z'
                     * (ex:Z01,z02) **/
                    printf("%02X ", ag_id);
                    break;

                /** no caso de haver um agent unknown, 
                 * imprime no terminal um '?' e na janela g2 imprime
                 * um circulo preto. **/
                default:
                    printf("?   ");
                    g2_pen(*device, BLACK);
                    g2_plot_QP(*device, x+0.5, y+1.5);

            }
        }

        /** Imprime no terminal duas linhas em branco depois de cada linha 
         * do mapa . **/
        printf("\n\n");

    }
    
    /** Imprime uma linha em branco no terminal depois de 
     * mostrar o mundo na totalidade **/
    printf("\n");
}
