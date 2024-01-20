#include<stdio.h>

int N,M;

void createAdjMatrix(int adj[][N+1],int arr[][2]){
	int i,j,x,y;
	//Initialize all values to zero.
	for(i=0;i<N+1;i++){
		for(j=0;j<N+1;j++){
			adj[i][j] =0;
		}
	}
	//Traverse the array of Edges
	for(i=0;i<M;i++){
		//find edges
                x = arr[i][0];
		y = arr[i][1];

		//Update value to 1.
		adj[x][y] = 1;
		adj[y][x] = 1;
	}
}

//Function to print created Adjacency Matrix.
void printmatrix(int adj[][N+1]){
	int i,j;
	for(i=1;i<N+1;i++){
		for(j=1;j<N+1;j++){
			printf("v%d%d->%d " ,i,j, adj[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	//Number of Vertices.
	N =5;
	//Given Edges.
	int arr[][2] = {{1,2},{2,3},{4,5},{1,5}};
	//Number of Edges.
	M = sizeof(arr)/ sizeof(arr[0]);
	//for adjacency matrix.
	int adj[N+1][N+1];
	//Function call to create Adjacency matrix.
	createAdjMatrix(adj,arr);
        //Print Adjacency Matrix.
	printmatrix(adj);
        return 0;
}


