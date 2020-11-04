#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int i;
int j;
int dimension=7; char tablero[7][7];int opcion=-9; void initTablero(); int imprimirTablero(); void foo();int menu(void);void insertar(void);int checkMolino();int validarEntradaI(char entrada[]); char validarEntradaJ(char entrada[]);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(void)
{	
	foo();
	initTablero();
	imprimirTablero();
	menu();
	return 0;
} 

void initTablero(void){
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
	int posicI;
	int posicJ;
	int bandera=0;//El valor de la bandera sera de 1 si la posicion de insercion es valida
	char player1[20];
	char player2[20]; //Guarda el nombre de los jugadores
	printf("Inserte el nombre de los jugadores:\n");
	scanf("%s",player1,stdin);
	scanf("%s",player2,stdin);
	int piezasRestantes;
	char posicionI[512];
	char posicionJ[512];
	for(piezasRestantes=0;piezasRestantes<18;piezasRestantes++){ // una vez termine checkmolino tengo que poner dentro de la condicional del for loop
		if(piezasRestantes%2==0){
			printf("	Player1: %s\n",player1);
		}
		if(piezasRestantes%2!=0){
			printf("	PLAYER 2: %s\n", player2);
		}
		printf("Inserte la posicion de Fila(Numero): ");
		scanf("%s", posicionI,stdin);
		printf("Inserte la posicion de Columna(Letra): ");
		scanf("%s", posicionJ,stdin);
		posicI=validarEntradaI(posicionI)-1;
		posicJ=validarEntradaJ(posicionJ)-65;
		printf("%d %d",posicJ, posicI);
		if(tablero[posicI][posicJ]=='0'){
			bandera=1;
		}
		if(piezasRestantes%2!=0&&bandera==1){
			tablero[posicI][posicJ]='2';
		}
		if(piezasRestantes%2==0) {
			tablero[posicI][posicJ]='1';
		}
			imprimirTablero();
		}//Bloque que nos vuelve a preguntar por la posicion si el dato ingresado es incorrecto
		/*while(validarEntradaI(posicionI)==0||validarEntradaJ(posicionJ)==0||bandera==0){
			printf("Bruh\n");
			printf("Inserte la posicion de Fila(Numero): ");
			scanf("%s", posicionI,stdin);
			printf("Inserte la posicion de Columna(Letra): ");
			scanf("%s", posicionJ,stdin);
		
		}*/
			
	}		

/* Retornos de checkMolino
	0=No hay molinos
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
				insertar();
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
int validarEntradaI(char entrada[]){
	int x;
	int bandera;
	int len=0;
	for(x=0;entrada[x]!='\0';x++){
		len++;
	}
	if (len != 1||0==atoi(entrada)){
		bandera=0;
		return bandera;
	}
	return atoi(entrada);
}
char validarEntradaJ(char entrada[]){
	int x;
	int bandera;
	int len=0;
	for(x=0;entrada[x]!='\0';x++){
		len++;
	}
	char caracter1=toupper(entrada[0]);
	if(len!=1||caracter1<65||caracter1>90){
		bandera=0;
		return bandera;
	}
	return entrada[0];
}
