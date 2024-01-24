#include "head.h"

Status Hadlock(){

	Vertex s = {SX, SY, -1, -1}; 
	Stack nstack, pstack, visit;
	InitStack(nstack);
	InitStack(pstack);
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

	Push(pstack, s);
	int detour = 0;
	bool path_exist = false;

	Vertex u,v;

	while(true){
		Pop(pstack, u);
		if(is_blocked(u.x, u.y, obstacle)){
			if(StackEmpty(pstack)){
				if(StackEmpty(nstack)){
					path_exist = false;
					break;
				} else {
					CopyStack(pstack, nstack);
					ClearStack(nstack);
					detour++;
				}
			}
			continue;
		}

		obstacle[u.x][u.y] = 1;
		Push(visit, u);
		if(u.x == TX && u.y == TY){
			path_exist = true;
			break;
		}
		if(u.y + 1 < GRID) {
			if(!is_blocked(u.x, u.y + 1, obstacle)){
				v.x = u.x;
				v.y = u.y + 1;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(p_or_n(u, v)){
					Push(pstack, v);
				} else {
					Push(nstack, v);
				}
			}
		}
		if(u.x - 1 >= 0) {
			if(!is_blocked(u.x - 1, u.y, obstacle)){
				v.x = u.x - 1;
				v.y = u.y;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(p_or_n(u, v)){
					Push(pstack, v);
				} else {
					Push(nstack, v);
				}
			}
		}
		if(u.y - 1 >= 0) {
			if(!is_blocked(u.x, u.y - 1, obstacle)){
				v.x = u.x;
				v.y = u.y - 1;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(p_or_n(u, v)){
					Push(pstack, v);
				} else {
					Push(nstack, v);
				}
			}
		}
		if(u.x + 1 < GRID) {
			if(!is_blocked(u.x + 1, u.y, obstacle)){
				v.x = u.x + 1;
				v.y = u.y;
				v.pre_x = u.x;
				v.pre_y = u.y;
				if(p_or_n(u, v)){
					Push(pstack, v);
				} else {
					Push(nstack, v);
				}
			}
		}
		if(StackEmpty(pstack)){
			if(StackEmpty(nstack)){
				path_exist = false;
				break;
			} else {
				CopyStack(pstack, nstack);
				ClearStack(nstack);
				detour++;
			}
		}
	}
	free(obstacle);
	if(path_exist == true){
		int len = abs(SX - TX) + abs(SY - TY) + 2 * detour;
		printf("Path exists, length is %d\n", len);
		int **path = retrace(u, len, visit);
		visualization(path, len, visit, visual);
		return TRUE;
	} else {
		printf("No path exists\n");
		int **take_position;
		visualization(take_position, -1, visit, visual);
		return FALSE;
	}

}

bool is_blocked(int x, int y, int **obstacle){
	if(obstacle[x][y] == 1) return true;
	return false;
}

bool p_or_n(Vertex u, Vertex v){
	int du, dv;
	du = abs(u.x - TX) + abs(u.y - TY);
	dv = abs(v.x - TX) + abs(v.y - TY);
	if(du > dv) return true;
	return false;
}

int **retrace(Vertex u, int len, Stack visit){
	Vertex v, *resume;	
	resume = visit.top;
	int **path;
	path = (int **)malloc(MPL * sizeof(int *));
	for(int i = 0; i < MPL; i++){
		path[i] = (int *)malloc(2 * sizeof(int));
	}

	path[len][0] = TX;
	path[len][1] = TY;
	for(i = len - 1; i >= 0; i--){
		visit.top--;
		while(visit.top != visit.base) {
			v = *visit.top;
			if(v.x == u.pre_x && v.y == u.pre_y){
				path[i][0] = v.x;
				path[i][1] = v.y;
				u = v;
				break;
			}
			visit.top--;
		}
		v = *visit.top;
		if(v.x == u.pre_x && v.y == u.pre_y){
			path[i][0] = v.x;
			path[i][1] = v.y;
			u = v;
		}
		visit.top = resume;
	}

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
