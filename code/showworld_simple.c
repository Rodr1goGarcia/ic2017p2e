/*
 * This file is part of "2º Projeto de Introdução à Computação 2017/2018"
 * (2oPIC1718).
 *
 * 2oPIC1718 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 2oPIC1718 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 2oPIC1718. If not, see <http://www.gnu.org/licenses/>.
 * */

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
    WHITE = 0, /* Background */
    BLACK = 1, /* Nothing */
    BLUE= 3, /*Playable ZOmbie*/
    GREEN = 7, /* Playable Agent */
    GRAY = 14, /* Agent None */
    RED = 19, /* Agent Zombies */
    YELLOW = 25 /* Agent Humans */
};

/* The implementation of `SHOWWORLD` type used in this simple text-based world
 * visualization code. In this simple case, we only need to keep track of the
 * world dimensions and of the function pointer which knows how to read an
 * agent from the world data structure.
 *
 * For a more complex implementation, for example based on the g2 library,
 * it would also be necessary to keep the g2 device.
 * */
struct showworld {
    unsigned int xdim;
    unsigned int ydim;
    get_agent_info_at aginfo_func;
};

/* Create a new display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_new()` prototype defined in
 * `showworld.h`. */
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

/* Destroy a display/visualization object for the simulation world.
 *
 * This function obeys the `showworld_destroy()` prototype defined in
 * `showworld.h`. */
void showworld_destroy(SHOWWORLD *sw) {
    free(sw);
}

/* Update the simulation world display/visualization.
 *
 * This function obeys the `showworld_update()` prototype defined in
 * `showworld.h`. */
void showworld_update(SHOWWORLD *sw, void *w) {
	
	int *device;
    device = malloc(sizeof(int));
	
    /* Abrir janela */
    *device = g2_open_X11(sw->xdim * 21.5, sw->ydim * 23.5);
    
    /* Desenhar o fundo */
    g2_set_background(*device, WHITE);
    
    /* Especificar tamanho e forma dos agentes */
    g2_set_QP(*device, 20, QPcirc);
    
    printf("\n");
    
    g2_pen(*device, GRAY);
	g2_plot_QP(*device, 0.5, 0.5);
    g2_pen(*device, GREEN);
	g2_plot_QP(*device, 2.5, 0.5);
	g2_pen(*device, BLACK);
	g2_string(*device, sw->xdim * 2.75, sw->ydim*0.75, "HP");
	g2_pen(*device, YELLOW);
	g2_plot_QP(*device, 4.5, 0.5);
	g2_pen(*device, BLACK);
	g2_string(*device, sw->xdim * 4.75, sw->ydim*0.75, "H");
	g2_pen(*device, BLUE);
	g2_plot_QP(*device, 6.5, 0.5);
	g2_pen(*device, BLACK);
	g2_string(*device, sw->xdim * 6.75, sw->ydim*0.75, "ZP");
	g2_pen(*device, RED);
	g2_plot_QP(*device, 8.5, 0.5);
	g2_pen(*device, BLACK);
	g2_string(*device, sw->xdim * 8.75, sw->ydim*0.75, "Z");
	g2_pen(*device, BLACK);
	g2_plot_QP(*device, 10.5, 0.5);
	g2_pen(*device, WHITE);
	g2_string(*device, sw->xdim * 10.75, sw->ydim*0.75, "U");
    
        /* Print a newline after world is shown/updated. */
    printf("\n");

    /* Cycle through all the rows */
    for (unsigned int y = (sw->ydim); y > 0; --y) {

        /* Cycle through all the columns for the current row */
        for (unsigned int x = 0; x < sw->xdim; ++x) {

            /* Get state of the world (in bit packed fashion) using the user
               supplied function. */
            unsigned int item = sw->aginfo_func(w, x, y-1);

            /* Extract the agent type (2 bits). */
            AGENT_TYPE ag_type = item & 0x3;
            /* Extract whether the agent is playable (1 bit). */
            unsigned char playable = (item >> 2) & 0x1;
            /* Extract the agent ID (16 bits). */
            unsigned short ag_id = (item >> 3) & 0xFFFF;
            

            /* Determine the agent type. */
            switch (ag_type) {

                /* If no agent is present at (x,y) just print a dot. */
                case None:
                    printf(" .  ");
                    g2_pen(*device, GRAY);
                    g2_plot_QP(*device, x+0.5, y+1.5);
                    break;

                /* If human agent present at (x,y) print 'h' or 'H'. */
                case Human:
                    if (playable) {
                        /* Uppercase 'H' for player-controlled human agent. */
                        printf("H");
                        g2_pen(*device, GREEN);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    } else {
                        /* Lowercase 'h' for AI-controlled human agent. */
                        printf("h");
                        g2_pen(*device, YELLOW);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    }
                    /* Print the agent ID in front of the 'h'/'H'. */
                    printf("%02X ", ag_id);
                    break;

                /* If zombie agent present at (x,y) print 'z' or 'Z'. */
                case Zombie:
                    if (playable) {
                        /* Uppercase 'Z' for player-controlled zombie agent. */
                        printf("Z");
                        g2_pen(*device, BLUE);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    } else {
                        /* Lowercase 'z' for AI-controlled zombie agent. */
                        printf("z");
                        g2_pen(*device, RED);
                        g2_plot_QP(*device, x+0.5, y+1.5);
                    }
                    /* Print the agent ID in front of the 'h'/'H'. */
                    printf("%02X ", ag_id);
                    break;

                /* Print '?' if unknown type detected. This should *never*
                   happen. */
                default:
                    printf("?   ");
                    g2_pen(*device, BLACK);
                    g2_plot_QP(*device, x+0.5, y+1.5);

            }
        }

        /* Print two newlines after each row. */
        printf("\n\n");

    }
    
    /* Print a newline after world is shown/updated. */
    printf("\n");
}
