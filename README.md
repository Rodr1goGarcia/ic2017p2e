# The Walking Circle

* André Rosa - a21704022
* Ricardo Leal - a21703090
* Rodrigo Garcia - a21704304


## Our solution

### Architecture

Para evitar ter um código principal muito cheio, dividi-mos o código em alguns ficheiros .c sendo que cada um tem o seu
.h que contêm vários parâmetros e funções. 

O ficheiro principal é o "example.c". 
Para fazer o shuffle da ordem de jogar de cada Humano e Zombie, de forma a evitar que exista vantagem de jogar em primeiro,
criá-mos o ficheiro "baralha.c".

![Fluxogram] (https://cdn.discordapp.com/attachments/414878391938842626/414895228688924672/IC_E2.svg)

### Data structures

As bibliotecas de funções que utilizámos para este trabalho foram: ``G2.H, G2_X11.H, STDIO.H, STDLIB.H e TIME.H ``

Utilizá-mos **arrays** e **structs** em grande parte da estrutura do nosso trabalho, constituem portanto uma parte muito 
importante neste projeto.

Criá-mos ainda uma struct ``AGENT`` que contém a informação se o agente é jogável, a sua ID e o seu tipo.

### Algorithms

**Movimento** 
``switch (tecla)`` Este algoritmo altera uma das coordenadas de um agente controlável. 
Ao clicar **2** é somado 1 ao **y** do agente controlável. 
Ao clicar **4** é subtraído 1 ao **x** do agente controlável. 
Ao clicar **6** é somado 1 ao **x** do agente controlável. 
Ao clicar **8** é subtraído 1 ao **y** do agente controlável. 
O agente vai mover-se então, respectivamente, para **Baixo**, **Esquerda**, **Direita** e **Cima**.

**NOTA: Este modelo de controlo de movimentos pode parecer pouco intuitivo, no entanto se reparar-mos no teclado numérico (Num Pad) 
este modelo de movimentação torna-se bastante simples.**

**Limite da grelha**
O nosso jogo dando uso a uma grelha não toroidal utiliza um conjunto de algoritmos que impedem que os agentes ultrapassem os limites do mundo jogável,
sendo estes:

``if (j-1 >= 0)`` Este algoritmo serve para impedir que os agentes ultrapassem o **limite superior** do mundo jogável.
Ou seja, a posição dos agentes nunca pode ser **negativa** em relação a j.                  

``if (i-1 >= 0)`` Este algoritmo serve para impedir que os agentes ultrapassem o **limite esquerdo** do mundo jogável.
Ou seja, a posição dos agentes nunca pode ser **negativa** em relação a i. 

``if (i+1 <= WORLD_X-1)`` Este algoritmo serve para impedir que os agentes ultrapassem o **limite direito** do mundo jogável.
Ou seja, a posição dos agentes nunca pode ser **superior** ao valor de WORLD_X.

``if (j+1 <= WORLD_Y-1)`` Este algoritmo serve para impedir que os agentes ultrapassem o **limite inferior** do mundo jogável.
Ou seja, a posição dos agentes nunca pode ser **superior** ao valor de WORLD_Y.

## User guide

Para dar inicio ao jogo o Jogador necessita de:

**1º** - Abrir o terminal do Ubuntu

**2º** - Fazer cd para a pasta do nosso projeto e executar o nosso ficheiro ``Makefile`` com a linha de comando ``make``

**3º** - Executar a linha de comando "./example -x a -y b -h c -z d -H e -Z f -t g"
Substituir:  "a" por um valor inteiro positivo para definir o tamanho horizontal da grelha;
             "b" por um valor inteiro positivo para definir o número de zombies controlados pela I.A;
			 "e" por um valor inteiro positivo, ou zero, para definir o número de Humanos controláveis; 
             "f" por um valor inteiro positivo, ou zero, para definir o número de Zombies controláveis;
			 "g" por um valor inteiro positivo para definir o número de turnos que o jogo terá;

**4º** Premir ENTER para começar e avançar rondas;

No caso de se estar a jogar com o modo interativo, cada número do teclado numérico corresponde a uma direção que se pode mover. 
No caso: **8-Cima; 2-Baixo; 4-Esquerda; 6-Direita**; 
Estas são as únicas direções que cada um dos agentes se consegue mover, pois o jogo funciona com uma **vizinhança de Von Neumann**;

O jogo conta com uma interface gráfica desenvolvida em G2 bastante simplista mas de facil percepção. Todos os agentes são "bolas"
cada uma com a sua cor de forma a diferenciar cada um deles.

**Bola Verde (HP)**- Humanos jogáveis;
**Bola Azul (ZP)**- Zombies jogáveis;
**Bola Vermelha (Z)**- Zombies controlados pela I.A;
**Bola Cinzenta ( )**- Espaço livre;
**Bola Preta (U)**- Unknown;

**5º** O jogo acaba quando forem jogados todos os turnos, sendo que pede ao jogador que prima a tecla ENTER para encerrar o mesmo.

Os zombies podem infetar os humanos ao moverem-se para as mesma coordenadas que um humano, nesse caso o humano transforma-se num zombie.
Apenas os agentes jogáveis se podem mexer.
O jogo acaba quando : os humanos forem todos infetados;
                      quando acaberem os turnos ainda ouver humanos por infeta; 

## Conclusions

Ao desenvolver este trabalho conseguimos aprofundar, aplicar e perceber melhor os conhecimentos adquiridos em aula. 
O conceito "HumanosVSZombies" é em si muito interessante e agradou-nos bastante. Já o código propriamente dito foi
bastante desafiante e a maior parte do tempo foi passado a tentar perceber a lógica necessária para fazer tudo funcionar. 

## References

* <a name="ref1">\[1\]</a> Pereira, A. (2017). C e Algoritmos, 2ª edição. Sílabo.
* <a name="ref2">\[2\]</a> Reagan, P. (2014). [Game Programming in C with the
Ncurses Library](https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library),
Viget Labs.
* <a name="ref3">\[3\]</a> [2D game development basics (2010)](https://stackoverflow.com/questions/3144399/2d-game-development-basics),
stackoverflow.com
