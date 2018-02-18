showworld_update(sw, grid);
   
int tecla;
printf("escolhe a tua jogada '2, 4, 6, 8' \n");
scanf("%d", &tecla);



	switch (tecla) {
	case 2: 
		
		for (int i = 0; i <WORLD_X; i++) {
			for (int j = 0; j < WORLD_Y; j++) {
				if (grid[i][j] != NULL) {
					grid[i][j-1] = grid[i][j];
					grid[i][j] = None;
				}
			}
		}
		
		break;
	case 4:
		
		
		for (int i = 0; i < WORLD_X; i++) {
        for (int j = 0; j < WORLD_Y; j++) {
            if (grid[i][j] != NULL){
            grid[i-1][j] = grid[i][j];
            grid[i][j] = None;
					
				}
			}
		}
		break;	
	case 6:
		
		
		
		for (int i = 19; i >= 0; i--) {
        for (int j = 19; j >= 0; j--) {
            if (grid[i][j] != NULL){
            grid[i+1][j] = grid[i][j];
            grid[i][j] = None;
				}
			}
		}
		break;
	case 8:
		
		for (int i = 19; i >= 0; i--) {
        for (int j = 19; j >= 0; j--) {
            if (grid[i][j] != NULL){
            grid[i][j+1] = grid[i][j];
            grid[i][j] = None;
					
				}
			}
		}
		break;
	
	default:
		
		
		printf("Essa tecla não é aceite,escolha 2,4,6,8\n");
		break;
	
}
showworld_update(sw, grid);
