showworld_update(sw, grid);
      
   for (int i = 19; i >= 0; i--) {
        for (int j = 19; j >= 0; j--) {
            if (grid[i][j] != NULL){
            grid[i+1][j] = grid[i][j];
            grid[i][j] = None;

			}
		}
	} 
	mexe para direita
	
	for (int i = 19; i >= 0; i--) {
        for (int j = 19; j >= 0; j--) {
            if (grid[i][j] != NULL){
            grid[i][j+1] = grid[i][j];
            grid[i][j] = None;

			}
		}
	}
	mexe para cima
	
	for (int i = 0; i < WORLD_X; i++) {
        for (int j = 0; j < WORLD_Y; j++) {
            if (grid[i][j] != NULL){
            grid[i-1][j] = grid[i][j];
            grid[i][j] = None;
			}
		}
	}
	mexe para esquerda
	
	for (int i = 0; i < WORLD_X; i++) {
        for (int j = 0; j < WORLD_Y; j++) {
            if (grid[i][j] != NULL){
            grid[i][j-1] = grid[i][j];
            grid[i][j] = None;
			}
		}
	}
	mexe para baixo
