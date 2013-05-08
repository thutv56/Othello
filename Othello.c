#include <stdio.h>
#include <stdlib.h>


#define BLACK  1
#define NONE   0
#define WHITE -1


int** board;         
                  
int size;            

int current = BLACK; 

int count;          


void initialize ( const int n ) {
	
	int i, j;

		board = (int**)malloc( sizeof(int*) * n );
	for ( i=0; i < n; i++ ) {
		board[i] = (int*)malloc( sizeof(int) * n );
		for ( j=0; j < n; j++ ) {
			board[i][j] = NONE;
		}
	}
	board[n/2-1][n/2-1] = WHITE;
	board[n/2-1][n/2]   = BLACK;
	board[n/2][n/2-1]   = BLACK;
	board[n/2][n/2]     = WHITE;

		size = n;
}


void finalize ( ) {
	
	int i;
	for ( i=0; i < size; i++ ) {
		free(board[i]);
	}
	free(board);
}


void display ( ) {
	
	
	int i, j;
	
	printf("  ");
	for ( i=0; i < size; i++ ) printf("%4d", i);
	printf("\n");
	
	printf("  +");
	for ( i=0; i < size-1; i++ ) { printf("--"); }
	printf("-+\n");
	
	for ( i=0; i < size; i++ ) {
		printf("%2d|", i);
		for ( j=0; j < size; j++ ) {
			switch ( board[j][i] ) {
				case BLACK: printf("?");
				            break;
				case WHITE: printf("?");
				            break;
				case NONE : printf(" ");
				            break;
			}
			printf("|");
		}
		printf("\n");
		if ( i < size-1 ) {
			printf("  +");
			for ( j=0; j < size-1; j++ ) {
				printf("-+");
			}
			printf("-¦\n");
		}
	}

	printf("  +");
	for ( i=0; i < size-1; i++ ) { printf("--"); }
	printf("-+\n");
}


int isReversible ( const int m, const int n ) {
		int i, j;
	int result = 0; 
	int count = 0;  
	
	if ( m < 0 || size <= m || n < 0 || size <= n ) return 0;
	if ( board[m][n] != NONE ) return 0;
	
	
	if ( n > 1 && board[m][n-1] == -current ) {  		for ( j=n-2; j >= 0; j-- ) {
			if ( board[m][j] == current ) { result += 1; count += n-j-1; break; }
			if ( board[m][j] == NONE    ) { break; }
		}
	}
	

	if ( n < size-2 && board[m][n+1] == -current ) {  
		for ( j=n+2; j < size; j++ ) {
			if ( board[m][j] == current ) { result += 2; count += j-n-1; break; }
			if ( board[m][j] == NONE    ) { break; }
		}
	}
	
		if ( m > 1 && board[m-1][n] == -current ) {  		for ( i=m-2; i >= 0; i-- ) {
			if ( board[i][n] == current ) { result += 4; count += m-i-1; break; }
			if ( board[i][n] == NONE    ) { break; }
		}
	}

	
	if ( m < size-2 && board[m+1][n] == -current ) {  
		for ( i=m+2; i < size; i++ ) {
			if ( board[i][n] == current ) { result += 8; count += i-m-1; break; }
			if ( board[i][n] == NONE    ) { break; }
		}
	}


	if ( m > 1 && n > 1 && board[m-1][n-1] == -current ) {  
		for ( i=m-2, j=n-2;  i>=0 && j>=0;  i--, j-- ) {
			if ( board[i][j] == current ) { result += 16; count += n-j-1; break; }
			if ( board[i][j] == NONE    ) { break; }
		}
	}
	

	if ( m < size-2 && n > 1 && board[m+1][n-1] == -current ) {  		for ( i=m+2, j=n-2;  i<size && j>=0;  i++, j-- ) {
			if ( board[i][j] == current ) { result += 32; count += n-j-1; break; }
			if ( board[i][j] == NONE    ) { break; }
		}
	}


	if ( m > 1 && n < size-2 && board[m-1][n+1] == -current ) {  		for ( i=m-2, j=n+2;  i>=0 && j<size;  i--, j++ ) {
			if ( board[i][j] == current ) { result += 64; count += j-n-1; break; }
			if ( board[i][j] == NONE    ) { break; }
		}
	}
	
		if ( m < size-2 && n < size-2 && board[m+1][n+1] == -current ) {  		for ( i=m+2, j=n+2;  i < size && j < size;  i++, j++ ) {
			if ( board[i][j] == current ) { result += 128; count += j-n-1; break; }
			if ( board[i][j] == NONE    ) { break; }
		}
	}


	return result;
}



int reverse ( int m, int n ) {
	
	int i, j;
	int reversed = 0;
	int reversible = isReversible(m, n);

	if ( !reversible ) return 0;

	board[m][n] = current;


	
	if ( reversible & 1 ) {
		for ( j=n-1;  board[m][j] == -current;  j-- ) {
			board[m][j] = current;
			reversed++;
		}
	}
	reversible >>= 1;
	
		if ( reversible & 1 ) {
		for ( j=n+1;  board[m][j] == -current;  j++ ) {
			board[m][j] = current;
			reversed++;
		}
	}
	reversible >>= 1;
	

	if ( reversible & 1 ) {
		for ( i=m-1;  board[i][n] == -current;  i-- ) {
			board[i][n] = current;
			reversed++;
		}
	}
	reversible >>= 1;


	if ( reversible & 1 ) {
		for ( i=m+1;  board[i][n] == -current;  i++ ) {
			board[i][n] = current;
			reversed++;
		}
	}
	reversible >>= 1;

	
	if ( reversible & 1 ) {
		for ( i=m-1, j=n-1;  board[i][j] == -current;  i--, j-- ) {
			board[i][j] = current;
			reversed++;
		}
	}
	reversible >>= 1;
	
	
	if ( reversible & 1 ) {
		for ( i=m+1, j=n-1;  board[i][j] == -current;  i++, j-- ) {
			board[i][j] = current;
			reversed++;
		}
	}
	reversible >>= 1;


	if ( reversible & 1 ) {
		for ( i=m-1, j=n+1;  board[i][j] == -current;  i--, j++ ) {
			board[i][j] = current;
			reversed++;
		}
	}
	reversible >>= 1;
	

	if ( reversible & 1 ) {
		for ( i=m+1, j=n+1;  board[i][j] == -current;  i++, j++ ) {
			board[i][j] = current;
			reversed++;
		}
	}
	reversible >>= 1;

	current = -current;
	

	for ( i=0; i < size; i++ ) {
		for ( j=0; j < size; j++ ) {
			if ( isReversible(i, j) ) { 
				return reversed;          			}
		}
	}


	current = -current;
	for ( i=0; i < size; i++ ) {
		for ( j=0; j < size; j++ ) {
			if ( isReversible(i, j) ) {
				return reversed;
			}
		}
	}
	
	
	return -1;
}



int winner ( ) {
	
	
	int i, j;
	int t = 0, count=0, blank=0;
	
	for ( i=0; i < size; i++ ) {
		for ( j=0; j < size; j++ ) {
			t += board[i][j];
			if(board[i][j]==BLACK) count++;
			else if(board[i][j]==NONE) blank++;
		}
	}
	printf("Black %d  vs White %d \n", count, size*size-count-blank);
	
	if      ( t < 0 ) return WHITE;
	else if ( t > 0 ) return BLACK;
	else              return NONE;
}

int AI_move () {


	
    
	int i, j, check=0, target, arrayi[100],arrayj[100];
	int result = 1;  

	if ( current == BLACK ) {
	  printf("AI black's turn?\n");
	}else {
	  printf("AI white's turn?\n");
	}

	if (isReversible(0,0)!=0){
		 result=reverse(0,0);
	return result;}
	if (isReversible(size,size)!=0){
		result=reverse(size,size);
	return result;}
	if (isReversible(size,0)!=0){
		 result=reverse(size,0);
	return result;}
	if (isReversible(0,size)!=0){
		 result=reverse(0,size);
	return result;}
	
	for ( i=0; i < size; i++ ) {
		for ( j=0; j < size; j++ ) {
			if (isReversible(i,j)!=0){
		 		//result=reverse(i,j);
		 		arrayi[check]=i;arrayj[check]=j;
		 	check++;}
		 }
	}
	target=rand()%check;
	result=reverse(arrayi[target],arrayj[target]);
	return result;}

	  
	  

int main ( int argc, char** argv ) {
	int arg;   	int m, n;  
	int AI;	   

	
	
	int result = 1;


		if ( argc >= 2 ) {
		if ( sscanf(argv[1], "%d", &arg) <= 0 ) {
			printf("'%s' is not appropriate for board size?\n", argv[1]);
			exit(1);
		}
		initialize(arg);
	}
	else {	
		initialize(8); 	
	}
	if ( argc >= 3 ) {
		sscanf(argv[2], "%d", &AI);
		if(AI!=BLACK && AI!=WHITE && AI!=NONE){
			printf("'%s' is not an appropriate type for a computer opponent?\n", argv[2]);
			exit(1);
		}
	}
	else {
		AI=NONE;        


	while ( result > 0 ) {
		display();
		if (current == AI) result = AI_move();
		else {
			if ( current == BLACK ) {
				printf("black's turn?\n");
			}
			else {
				printf("white's turn?\n");
			}
			while ( 1 ) {
				printf("enter horizontal, then vertical=> ");
				fflush(stdin);
				if ( scanf("%d", &m)<0 || scanf("%d", &n)<0 ) {
					printf("Input is wrong?\n");
					printf("enter again?");
					continue;
				}
				result = reverse(m, n);
				if ( result == 0 ) {
					printf("(%d, %d) you can't place a stone here?\n", m, n);
					printf("place again?");
				}
				else {
					break;
				}
			}
		}
	}

	display();
	printf("\nresult: ");
	switch ( winner() ) {
		case BLACK: printf("winner, black!\n\n");
			        break;
		case WHITE: printf("winner, white!\n\n");
			        break;
		case NONE : printf("no winner!\n\n");
			        break;
	}

	finalize();
	return 0;
}
