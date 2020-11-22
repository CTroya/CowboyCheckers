#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#define dimension 7 
#include <time.h>
char tablero[7][7];int opcion=-9;int piezasRestantes=9; char piezaEnemiga; char piezaAliada; char piezaEnemigaBot; char piezaAliadaBot;
int posicJ; int posicI; int bando; //posic guarda la ultima jugada realizada

void initTablero(); int imprimirTablero(); void foo();int menu(void);//Funciones de inicializacion/setup
void insertar(void); void jugarBot(char jugada); void quitarPieza(void); void moverPieza(void); //Funciones de jugadas
int validarEntradaI(char entrada[]); char validarEntradaJ(char entrada[]); bool esNumero();//Funciones de error handling
int binRand(); void debug(void); int welcome(); void etapaInsertar(); int getTurnos(); int cantidadPiezas(char a); int checkMolino();// funciones misc

int main(void)
{	
	foo();
	initTablero();
	imprimirTablero();
	welcome();
	etapaInsertar();
	return 0;
} 

int welcome(void){
	srand(time(NULL));
	bando=rand()%2; char nombre[512];
	printf("Bienvenido a Cowboy Checkers!(Se recomienda usar Pantalla completa)\nDime. Como te llamas?\n");
	scanf("%s",nombre,stdin);
	if(bando==0){
		printf("Hola %s! Te ha tocado el bando 2. Ya puedes jugar ^^!",nombre);
		piezaAliada = '2';
		piezaEnemiga = '1';
		piezaAliadaBot= '1';
		piezaEnemigaBot= '2';
	}else{
		printf("Hola %s! Te ha tocado el bando 1. Ya puedes jugar ^^!",nombre);
		piezaAliada = '1';
		piezaEnemiga = '2';
		piezaAliadaBot= '2';
		piezaEnemigaBot= '1';
	}
	return 0;
 }


void initTablero(void){
	int i; int j;
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

void insertar(void){//tengo que ver wtf se printeo mi codigo en el shell la vez pasada xd
	int bandera=1;//El valor de la bandera sera de 1 si la posicion de insercion es valida
	char posicionI[512]; char posicionJ[512]; int counter=0;
	while(bandera == 1){	//Bloque que nos vuelve a preguntar por la posicion si el dato ingresado es incorrecto
		if(counter>0){
			printf("Has insertado una posicion invalida! Tranquilo, ahora puedes ingresarla de nuevo.\n");
		}
		printf("Inserte la posicion de Columna(Letra): "); scanf("%s", posicionJ,stdin);
		printf("Inserte la posicion de Fila(Numero): "); scanf("%s", posicionI,stdin);
		posicI = validarEntradaI(posicionI) - 1;
		posicJ = validarEntradaJ(posicionJ) - 65;
		counter++;
		if(tablero[posicI][posicJ]=='O'){
			bandera = 0;
		}
	}
	if(piezasRestantes%2!=bando){
		tablero[posicI][posicJ]='2';
	}else{
		tablero[posicI][posicJ]='1';
	}
	checkMolino();
}


void jugarBot(char jugada){//jugada==i. Insertar pieza/ q.Quitar pieza   / m.Mover Pieza (quiza xd)
	posicI=1; posicJ=0;
	char query; char piezaReemplazar;
	srand(time(NULL));
	if(jugada=='i'){
		query='O';
		piezaReemplazar=piezaAliadaBot;
	}
	if(jugada=='q'){
		query=piezaAliadaBot;
		piezaReemplazar='O';
	}
	while(tablero[posicI][posicJ]!='O' && tablero[posicI][posicJ]!=query){//'O'
		posicI=rand()%7;
		posicJ=rand()%7;
	}
	tablero[posicI][posicJ]=piezaReemplazar;
	if(jugada=='i'){
		checkMolino();
	}
}


void etapaInsertar(){
	int i;
	printf("\nPeriodo de insercion de piezas\nAmbos jugadores pueden insertar 9 Piezas\n"); //tengo que explicar mejor esta parte xd
	if(piezaAliada=='1'){
		for(i=0;i<piezasRestantes;i++){
			insertar();
			jugarBot('i');
			imprimirTablero();
			if(tablero[posicI][posicJ]=='O'){
				printf("La computadora ha sacado a %c-%d!\n",posicJ+65,posicI+1);
			}else{
				printf("La computadora jugo %c-%d\n",posicJ+65,posicI+1);
			}
		}
	}else{
		for(i=0;i<piezasRestantes;i++){
			jugarBot('i');
			imprimirTablero();
			printf("La computadora jugo %c-%d\n",posicJ+65,posicI+1);
			insertar();
			imprimirTablero();
	}
	}
}
int checkMolino(){//global posicI posicJ son las ultimas jugadas realizadas
	int i; int finI;
	int j; int finJ;
	int piezasAlineadasi = 0;
	int piezasAlineadasj = 0;
	
	
	if(posicI==3){//se verifica la excepcion de la FILA central
			if(posicJ>3){//wakala
				j=4;
				finJ=dimension;
			}
			else{
				j=0;
				finJ=3;
			}
			while(j<finJ){
				if(tablero[posicI][j]==tablero[posicI][posicJ]){
					piezasAlineadasj++;
				}
				j++;
			}
		}		
	else{//si no es una pieza central se recorre la linea y columna de la ultima jugada 
		for(j = 0;j < dimension; j++){
			if(tablero[posicI][j] == tablero[posicI][posicJ]){
				piezasAlineadasj++;	
			}
		}
	}
	if(posicJ==3){//se verifica la excepcion de la COLUMNA central
		if(posicI>3){
			i=4;
			finI=dimension;
		}
		else{
			i=0;
			finI=3;
		}
		while(i<finI){
				if(tablero[i][posicJ]==tablero[posicI][posicJ]){
					piezasAlineadasi++;
				}
				i++;
			}	
	}else{
	for(i = 0 ; i < dimension; i++){
		if(tablero[i][posicJ] == tablero[posicI][posicJ]){
			piezasAlineadasi++;
		}
	}
}
	if(piezasAlineadasi==3 || piezasAlineadasj==3 && tablero[posicI][posicJ]==piezaAliadaBot){
		imprimirTablero();
		printf("La computadora jugo %c-%d\n",posicJ+65,posicI+1);
		printf("Oh no! La computadora ha creado un molino y sacara una de tus piezas!\n");
		jugarBot('q');
		//printf("La computadora ha sacado a %c-%d!\n",posicJ+65,posicI+1);
	}		
	if(piezasAlineadasi==3 || piezasAlineadasj==3 && tablero[posicI][posicJ]==piezaAliada){//Si la pieza buscada es del jugador
		imprimirTablero();
		printf("Creaste un molino, ¡puedes sacar una pieza enemiga!\n");
		quitarPieza();
	}		
}
int imprimirTablero(){
	int i; int j;
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
	printf("							Bando 1: Cant de piezas en juego: %d\n", cantidadPiezas('1'));
	printf("							Bando 2: Cant de piezas en juego: %d\n",cantidadPiezas('2'));
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

int validarEntradaI(char entrada[]){//Verifica las entradas de numeros de un digito
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
}//estas funciones se pueden hacer con isdigit(), si tan solo alguien me podia decir que eso existia antes que haga ._.
char validarEntradaJ(char entrada[]){//Verifica las entradas de numeros de una Letra
	int x;
	int len=0;
	for(x=0;entrada[x]!='\0';x++){
		len++;
	}
	char caracter1=toupper(entrada[0]);
	if(len!=1||caracter1<65||caracter1>71){
		return 0;
	}
	return toupper(entrada[0]);
}

int cantidadPiezas(char a){
	int x; int y;
	int cantPiezas = 0;
	for(x=0;x<dimension;x++){//este nested loop busca todos los caracteres iguales al parametro que recibe y retorna la cantidad de caracteres iguales
		for(y=0;y<dimension;y++){
			if (tablero[x][y]==a){
				cantPiezas++;
			}
		}
	}
	return cantPiezas;
}
void quitarPieza(){
	int counter=0;//simplemente cuenta las veces que se pidio la posicion para luego dar una notificacion de error de insercion
	int quitarI;
	int quitarJ;
	char stringI[512];
	char stringJ[512]; 
	quitarI=-1;
	quitarJ=-65;
	while(quitarI==-1||quitarJ==-65||tablero[quitarI][quitarJ]!=piezaEnemiga){
		if(counter>0){
			printf("Has ingresado una posicion incorrecta\n");
		}
		printf("Inserte la posicion de Columna(Letra): ");scanf("%s", stringJ,stdin);
		printf("Inserte la posicion de Fila(Numero): ");scanf("%s", stringI,stdin);
		quitarI=validarEntradaI(stringI)-1;
		quitarJ=validarEntradaJ(stringJ)-65;
		counter++;
	}
	tablero[quitarI][quitarJ]='O';
	imprimirTablero();
	
}
void moverPieza(void){//que paja me da hacer esto por lo del player 1 y 2 asaaaash :/ necesito un compañero asdsad 
	printf("Seleccione la pieza a mover: ");
	quitarPieza();
	
}
int jugadasPosibles(int pi , int pj){
	int casillasLibresI=0;
	int casillasLibresJ=0;
	int i; int j;
}
int totalesPosibles(char pieza){
	int totalesLibres=0;
	int casillasLibresJ=0;
	int i; int j;
	for(i=0;i<dimension;i++){
		for(j=0;j<dimension;j++){
		if(tablero[i][j]=pieza){
			jugadasPosibles(i,j);
		}
	}
}
}
int getTurnos(){
	char cantTurnos[512]; int i; int retorno=1; int counter=0; bool bandera=false;
while(bandera==false){
		if(counter>0){
			printf("Valor Invalido\n");
		}
		printf("Inserta la cantidad de turnos que el juego tendra: "); scanf("%s",cantTurnos,stdin);
		counter++;
		bandera=esNumero(cantTurnos);
	}
	return atoi(cantTurnos);
}
bool esNumero(const char *cadena) 
{
    while(*cadena != '\0')
    {
        if(*cadena < '0' || *cadena > '9')
            return false;
        cadena++;
    }
    return true;
}


