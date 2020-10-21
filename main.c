#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
char player1[10] , player2[10]; //Guarda el nombre de los jugadores
int i;
int j;
int dimension=7; char tablero[7][7];int opcion=-9; void initTablero(); int imprimirTablero(); void foo();int menu(void);void insertar(void);int checkMolino();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(void)
{
	initTablero();
	insertar();
	return 0;
 } 
 


void initTablero(){
	for(i = 0;i< dimension;i++) {
		for( j = 0; j < dimension; j++){
			if(j > 0&& j < 6){
				tablero[i][j] = 205;
			}
			if(j!=2&&j!=4&&i>0&&i<6){
				tablero[i][j] = 186;
			}
			if(dimension==i+j+1||i==j||i!=3&&j==3||i==3&&j!=3){
				tablero[i][j]='O';
			}
			tablero[3][3]='+';
		}
	}
}

void insertar(void){
	int piezasRestantes;
	char posicionI[512];
	char posicionJ[512];
	for(piezasRestantes=0;piezasRestantes<1;piezasRestantes++){
		if(piezasRestantes%2==0){
			printf("	PLAYER 1\n");
		}
		else if(piezasRestantes%2!=0){
			printf("	PLAYER 2\n");
		}
		printf("Inserte la posicion de Fila(Numero): ");
		int check1=scanf("%s", posicionI,stdin);
		while(check1!=1||strtof(posicionI,NULL)<1||strtof(posicionI,NULL)>7||strtof(posicionI,NULL)==0){
			printf("Inserte la posicion de Fila(Numero): ");
			check1=scanf("%s",512, posicionI,stdin);
		}
		printf("Inserte la posicion de Columna(Letra): ");
		int check2=scanf("%s", posicionJ,stdin);
		while(check2!=1||strtof(posicionJ,NULL)<1||strtof(posicionJ,NULL)>7){
			printf("Inserte la posicion de Fila(Numero): ");
			check1=scanf("%s",512, posicionJ,stdin);
		}
		if(tablero[atoi(posicionI)-1][atoi(posicionJ)-1]=='O'){
			if(piezasRestantes%2==0){
				tablero[atoi(posicionI)-1][atoi(posicionJ)-1]='1';
			}else{
				tablero[atoi(posicionI)-1][atoi(posicionJ)-1]='2';
			}		
		}	
		imprimirTablero();	
	}		
}
/*0=No hay molinos
  1=Molino Blanco
  2=Molino Negro	*/
int checkMolino(){
	int i;
	int j;
	int piezasAlineadas;
	for(i = 0;i < dimension;i++){//este loop recorre y verifica los molinos en filas
		for(j = 0;j < dimension; j++){
			if(tablero[i][j]=='1'||tablero[i][j]=='2'){
				piezasAlineadas++;
			}
		}
	if(piezasAlineadas>=3){
		printf("sosfacha\n");
	}piezasAlineadas=0;
	}
}





int imprimirTablero(){
	
	printf("\n\n                                                             A    B    C    D    E    F    G");
	for(i = 0; i < dimension; i++ ){
		printf("\n");
		printf("\n");
		for( j= 0; j < dimension; j++){
			if (j==0){ 
			printf("                                      			%d-",i+1);
			}
			if(tablero[i][j]=='O'||tablero[i][j]=='1'||tablero[i][j]=='2'){
				printf("  [%c]", tablero[i][j]);
			}else printf("   %c ", tablero[i][j]);
		}	
	}
	printf("\n");
	return 0;
}

void foo() {
	   FILE *title;
   int c;
   int counter=0;
   title = fopen("foo.txt","r");
   while(1) {
      c = fgetc(title);
      counter++;
      if( counter==1512 ) { 
         break ;
      }
      printf("%c", c);
   }
   fclose(title);
}
int menu(void){
 	char input = 0;
	printf("Bienvenido a Cowboy Checkers!(Usar Pantalla completa)\n");
	printf("Opciones:\n 1.Player1 vs Player2\n 2.Player vs CPU\n 3.Exit\n ");
	while(1) {
		if(scanf("%c",&input) == 1) {
			if(input == '1') {
				foo();
				return 1;
			} else if(input == '2') {
				break;
			}else if(input=='3'){
				exit(1);
			} 
			else if(input != '\n') {
				printf("Unknown command '%c'! Ignoring...\n",input);
			}
			
		} else {
			printf("Invalid input! Ignoring...\n");
		}
	}
	return 0;
 }
 
 
