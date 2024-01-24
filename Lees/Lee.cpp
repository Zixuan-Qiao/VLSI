#include "head.h"

Status Lee(){

	Stack wf, nwf, visit;
	InitStack(wf);
	InitStack(nwf);
	InitStack(visit);

	int **obstacle;
	obstacle = auto_gen();
	obstacle[SX][SY] = 0;
	obstacle[TX][TY] = 0;
	int visual[GRID][GRID];
	for(int i = 0; i < GRID; i++){
		for(int j = 0; j < GRID; j++){
			visual[i][j] = obstacle[i][j];
		}
	}

	Vertex s = {SX, SY, -1, -1};
	Push(wf, s);

	int len = 0;
	bool path_exist = false;
	Vertex u, v;

	while(true){
		len++;
		while(!StackEmpty(wf)){
			Pop(wf, u);
			if(u.y + 1 < GRID){
				v.x = u.x;
				v.y = u.y + 1;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(is_blocked(v.x, v.y, obstacle) == false){
					obstacle[v.x][v.y] = 1;
					Push(visit, v);
					Push(nwf, v);
				}
				if(v.x == TX && v.y == TY){
					path_exist = true;
					break;
				}
			}
			if(u.x - 1 >= 0){
				v.x = u.x - 1;
				v.y = u.y;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(is_blocked(v.x, v.y, obstacle) == false){
					obstacle[v.x][v.y] = 1;
					Push(visit, v);
					Push(nwf, v);
				}
				if(v.x == TX && v.y == TY){
					path_exist = true;
					break;
				}
			}
			if(u.y - 1 >= 0){
				v.x = u.x;
				v.y = u.y - 1;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(is_blocked(v.x, v.y, obstacle) == false){
					obstacle[v.x][v.y] = 1;
					Push(visit, v);
					Push(nwf, v);
				}
				if(v.x == TX && v.y == TY){
					path_exist = true;
					break;
				}
			}
			if(u.x + 1 < GRID){
				v.x = u.x + 1;
				v.y = u.y;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(is_blocked(v.x, v.y, obstacle) == false){
					obstacle[v.x][v.y] = 1;
					Push(visit, v);
					Push(nwf, v);
				}
				if(v.x == TX && v.y == TY){
					path_exist = true;
					break;
				}
			}
		}
		if(path_exist == true) break;
		if(StackEmpty(nwf)){
			path_exist = false;
			break;
		}
		CopyStack(wf, nwf);
		ClearStack(nwf);
	}
	if(path_exist == false){
		printf("No path exists\n");
		int **take_position;
		visualization(take_position, -1, visit, visual);
		return FALSE;
	} else {
		printf("Path exists, length: %d\n", len);
		int **path;
		path = retrace(len, visit);
		visualization(path, len, visit, visual);
		return TRUE;
	}

}

bool is_blocked(int x, int y, int **obstacle){
	if(obstacle[x][y] == 1) return true;
	return false;
}

int **retrace(int len, Stack v){

	int **path;
	path = (int **)malloc(MPL * sizeof(int *));
	for(int i = 0; i < MPL; i++){
		path[i] = (int *)malloc(2 * sizeof(int));
	}
	Vertex p, q;
	Vertex *resume;
	resume = v.top;
	v.top--;
	p = *v.top;
	for(i = len - 1; i > 0; i--){
		while(v.top != v.base){
			v.top--;
			q = *v.top;
			if(p.pre_x == q.x && p.pre_y == q.y){
				path[i][0] = q.x;
				path[i][1] = q.y;
				break;
			}	
		}
		p = q;
	}
	path[0][0] = SX;
	path[0][1] = SY;
	path[len][0] = TX;
	path[len][1] = TY;

	v.top = resume;
	return path;
}

void visualization(int **p, int len, Stack v, int visual[][GRID]){

	Vertex u;
	while(!StackEmpty(v)){
		Pop(v, u);
		visual[u.x][u.y] = 3;
	}

	for(int i = 0; i <= len; i++){
		visual[p[i][0]][p[i][1]] = 2;
	}
	for(i = 0; i < GRID; i++){
		for(int j = 0; j < GRID; j++){
			if(i == SX && j == SY) printf("S ");
			else if(i == TX && j == TY) printf("T ");
			else if(visual[i][j] == 3) printf("o ");
			else if(visual[i][j] == 2) printf("+ ");
			else if(visual[i][j] == 1) printf("B ");
			else printf(". ", visual[i][j]);
		}
		printf("\n");
	}
}