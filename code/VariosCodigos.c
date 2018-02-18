/*Codigo implementado no projecto*/
/* Movimentacao do player*/
char tecla = "";
printf("escolhe a tua jogada '2, 4, 6, 8' ");
getchar (tecla);
while (tecla != 2 || tecla != 4 || tecla != 6 || tecla != 8) {

Switch(tecla){
	case 2: 
		
		for (int i = 0; i <WORLD_X; i++) {
			for (int j = 0; j < WORLD_Y; j++) {
				if grid[i][j] != NULL) {
					grid[i][j-1] = grid[i][j];
					grid[i][j] = None;
				}
			}
		}
		Break;
	case 4:
		
		for (int i = 0; i <WORLD_X; i++) {
			for (int j = 0; j < WORLD_Y; j++) {
				if grid[i][j] != NULL) {
					grid[i-1][j] = grid[i][j];
					grid[i][j] = None;
				}
			}
		}
		break;	
	case 6:
		
		for (int i = 19; i >= 0; i--) {
			for (int j = 19; j >= 0; j--) {
				if grid[i][j] != NULL) {
					grid[i+1][j] = grid[i][j];
					grid[i][j] = None;
				}
			}
		}
		break;
	case 8:
		
		for (int i = 19; i >= 0; i--) {
			for (int j = 19; j >= 0; j--) {
				if grid[i][j] != NULL) {
					grid[i][j+1] = grid[i][j];
					grid[i][j] = None;
				}
			}
		}
		break;
	default:
		printf("Essa tecla não é aceite,escolha 2,4,6,8");
	}
}
showworld_update(sw, grid);


/*Codigo não implementado no projecto */


/* Parametros e variaveis*/
if(argc != 15){
	fprintf(stderr,
            "Exemplo de uso:\n\t%s "
            "-x 20 "
            "-y 20 "
            "-z 10 "
            "-h 30 "
            "-Z 1 "
            "-H 2 "
            "-t 1000\n",
            argv[0]);
        exit(-1);
}

for(int i=1;i<argc;i=i+2){
	if(argv[i]=="-x"){
		WORLD_X=argv[i+1];
		break;
	}
	if(argv[i]=="-y"){
		WORLD_Y=argv[i+1];
		break;
	}
	if(argv[i]=="-z"){
		NZOMBIES=argv[i+1];
		break;
	}
	if(argv[i]=="-h"){
		NHUMANOS=argv[i+1];
		break;
	}
	if(argv[i]=="-Z"){
		NZOMBIES_PLAY=argv[i+1];
		break;
	}
	if(argv[i]=="-H"){
		NHUMANOS_PLAY=argv[i+1];
		break;
	}
	if(argv[i]=="-t"){
		TURNS=argv[i+1];
		break;
	}
}

