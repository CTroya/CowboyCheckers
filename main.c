//LISTA DE VERSIONES EN https://github.com/CTroya/CowboyCheckers/blob/main/main.c
//Para los sonidos es importante poner "-lwinmm" dentro de los parametros del proyecto para una correcta compilacion
#include <stdio.h>

#include <ctype.h>

#include <unistd.h>

#include <stdlib.h>

#include <math.h>

#include <ctype.h>

#include <stdbool.h>

#define dimension 7

#include <time.h>

#include <windows.h>
 //variables que indican el estado de la partida
char tablero[7][7];
int piezasRestantes = 9;
char piezaEnemiga;
char piezaAliada;
char piezaEnemigaBot;
char piezaAliadaBot;
int bando, turnos = 1337;
bool ongoing = true;
bool banderaBlanca = false;
//guarda la ultima jugada realizada
int posicJ;
int posicI;
int quitarI;
int quitarJ;
void checkGanador(char pi, char pj);
//Funciones de inicializacion/setup
void initTablero();
int imprimirTablero();
void foo(char sonido, char poster);
int menu();
//Funciones de jugadas
void insertar();
void jugarBot(char jugada);
void quitarPieza(char pieza);
void moverPieza();
void moverPieza();
void moverPiezaBot();
void etapaMover();
int jugadasPosibles(int pi, int pj);
int totalesPosibles(char pieza);
//Funciones de error handling
int validarEntradaI(char entrada[]);
char validarEntradaJ(char entrada[]);
bool esNumero(const char * cadena);
bool verificarJugada(int oldI, int oldJ, int newI, int newJ);
// funciones misc
void debug();
int welcome();
void etapaInsertar();
int getTurnos();
int cantidadPiezas(char a);
int checkMolino();
void getMusica();

int main(void) {
    foo('0', 't');
    initTablero();
    imprimirTablero();
    welcome();
    etapaInsertar();
    etapaMover();
    return 0;
}
void etapaMover(void) {
    checkGanador('1', '2');
    printf("Ahora puedes mover tus piezas!\n");
    printf("Elige las coordenadas de tu pieza a seleccionar, luego la coordenada a donde quieras moverla\n");
    sleep(3);
    if (piezaAliada == '1') {
        while (turnos > 0) {
            moverPieza();
            jugarBot('m');
            imprimirTablero();
            if (tablero[posicI][posicJ] == 'O') {
                printf("La computadora ha sacado a %c-%d!\n", posicJ + 65, posicI + 1);
            }
            checkGanador('C', 'D');
            turnos--;
        }
    } else {
        while (turnos > 0) {
        	turnos--;
            jugarBot('m');
            imprimirTablero();
            if (tablero[posicI][posicJ] == 'O') {
                printf("La computadora ha sacado a %c-%d!\n", posicJ + 65, posicI + 1);
            }
            moverPieza();
            checkGanador('C', 'D');
        }
    }
    imprimirTablero();
}
void moverPieza(void) {
    int counter = 0;
    int selectI = -99;
    char inputSelectI[512];
    int moveI = -1;
    char inputMoveI[512];
    int selectJ = -99;
    char inputSelectJ[512];
    int moveJ = -65;
    char inputMoveJ[512];
    while (moveI == -1 || moveJ == -65 || tablero[moveI][moveJ] != 'O' || verificarJugada(selectI, selectJ, moveI, moveJ) == false) {
        selectI = -1;
        selectJ = -65;
        while (selectI == -1 || selectJ == -65 || tablero[selectI][selectJ] != piezaAliada) {
            if (counter > 0) {
                printf("Esa jugada es invalida! No te preocupes, ahora puedes ingresar una jugada de nuevo.\n");
            }
            printf("Inserte la posicion de Columna a seleccionar(Letra): ");
            scanf("%s", inputSelectJ, stdin);
            printf("Inserte la posicion de Fila a seleccionar(Numero): ");
            scanf("%s", inputSelectI, stdin);
            selectI = validarEntradaI(inputSelectI) - 1;
            selectJ = validarEntradaJ(inputSelectJ) - 65;
            checkGanador(validarEntradaJ(inputSelectI), validarEntradaJ(inputSelectJ));
            counter++;
        }
        printf("Seleccionaste %c-%d. A donde la quieres mover? Tienes %d jugadas posibles!\n", selectJ + 65, selectI + 1, jugadasPosibles(selectI, selectJ));
        counter = 0;
        if (counter > 0) {
            printf("Esa jugada es invalida! No te preocupes, ahora puedes ingresar una jugada de nuevo.\n");
        }
        printf("Inserte la posicion de Columna a mover(Letra): ");
        scanf("%s", inputMoveJ, stdin);
        printf("Inserte la posicion de Fila a mover(Numero): ");
        scanf("%s", inputMoveI, stdin);
        moveI = validarEntradaI(inputMoveI) - 1;
        moveJ = validarEntradaJ(inputMoveJ) - 65;
        checkGanador(validarEntradaJ(inputMoveI), validarEntradaJ(inputMoveJ));
        counter++;
    }
    printf("Moviste %c-%d a %c-%d\n", selectJ + 65, selectI + 1, moveJ + 65, moveI + 1);
    tablero[moveI][moveJ] = piezaAliada;
    tablero[selectI][selectJ] = 'O';
    posicI = moveI;
    posicJ = moveJ;
    checkMolino();
}
void checkGanador(char pi, char pj) {
    if (pi == 'F' && pj == 'F') {
        //Bloque que se ejecuta cuando nos rendimos
        printf("\nTe has rendido! (.___.)");
        sleep(2);
        PlaySound(NULL, 0, 0);
        printf("\e[1;1H\e[2J"); //Elimina todos los caracteres de la consola
        foo('d', 'd');
        exit(0);
    }
    if(cantidadPiezas(piezaAliada)-cantidadPiezas(piezaEnemiga) >= 3 && pi=='C' && pj=='D' ){//si se cumple, hay una chance de que la cpu se rinda
    	//Bloque que se ejecuta cuando la cpu se rinde
		int rendirse1=rand()%4;
		int rendirse2=rand()%4;
		if(rendirse1==rendirse2){
			printf("\nLa computadora se rindio! :D\n");
			sleep(2);
			printf("\e[1;1H\e[2J");
        	foo('v', 'v');
        exit(0);
		}
	}
    if (totalesPosibles(piezaAliada) == 0 && piezasRestantes <= 0 && totalesPosibles(piezaEnemiga) > 0 ||//condicion de encierro
        piezasRestantes <= 0 && cantidadPiezas(piezaAliada) <= 2 && cantidadPiezas(piezaEnemiga) > 2 ||//condicion de piezas menor a 3
		turnos<=0 && cantidadPiezas(piezaEnemiga)>cantidadPiezas(piezaAliada)) {//chequeo al fin de turnos
        //Bloque que se ejecuta cuando perdemos
        printf("\e[1;1H\e[2J");
        foo('d', 'd');
        exit(0);
    }
    if (totalesPosibles(piezaEnemiga) == 0 && piezasRestantes <= 0 && totalesPosibles(piezaAliada) > 0 ||//condicion de encierro
        piezasRestantes <= 0 && cantidadPiezas(piezaEnemiga) <= 2 && cantidadPiezas(piezaAliada) > 2||//condicion de piezas menor a 3
		turnos<=0 && cantidadPiezas(piezaEnemiga)<cantidadPiezas(piezaAliada)) {//condicion de piezas menor a 3
        //Bloque que se ejecuta cuando ganamos
        printf("\e[1;1H\e[2J");
        foo('v', 'v');
        exit(0);
    } 
        if (turnos <= 0 && cantidadPiezas(piezaEnemiga) == cantidadPiezas(piezaAliada)) {
            //Bloque que se ejecuta cuando empatamos
            printf("\e[1;1H\e[2J");
            foo('0','e');
            sleep(2);
            exit(0);
        }
        
    }

int getDiffI(int coordI, int coordJ) {
    int diffI = 1;
    //hallamos la distancia en las filas a la siguiente casilla libre en la matriz
    if (coordJ == 0 || coordJ == 6) {
        diffI = 3;
    }
    if (coordJ == 1 || coordJ == 5) {
        diffI = 2;
    }
    return diffI;
}
int getDiffJ(int coordI, int coordJ) {
    int diffJ = 1;
    //hallamos la distancia en las columnas a la siguiente casilla libre en la matriz
    if (coordI == 0 || coordI == 6) {
        diffJ = 3;
    }
    if (coordI == 1 || coordI == 5) {
        diffJ = 2;
    }
    return diffJ;
}
bool verificarJugada(int oldI, int oldJ, int newI, int newJ) {
    bool jugadaValida = false;
    int diffI = getDiffI(oldI, oldJ);
    int diffJ = getDiffJ(oldI, oldJ);

    if (abs(oldJ - newJ) == diffJ && oldI == newI) {
        jugadaValida = true;
    }
    if (abs(oldI - newI) == diffI && oldJ == newJ) {
        jugadaValida = true;
    }
    return jugadaValida;
}
int welcome(void) {
    srand(time(NULL));
    bando = rand() % 2;
    char nombre[512];
    printf("Bienvenido a Cowboy Checkers!(Se recomienda usar Pantalla completa)\nDime. Como te llamas?\n");
    scanf("%s", nombre, stdin);
    nombre[0] = toupper(nombre[0]);
    getMusica();
    getTurnos();
    if (bando == 0) {
        printf("Hola %s! Te ha tocado el bando 2. Ya puedes jugar ^^!", nombre);
        piezaAliada = '2';
        piezaEnemiga = '1';
        piezaAliadaBot = '1';
        piezaEnemigaBot = '2';
    } else {
        printf("Hola %s! Te ha tocado el bando 1. Ya puedes jugar ^^!", nombre);
        piezaAliada = '1';
        piezaEnemiga = '2';
        piezaAliadaBot = '2';
        piezaEnemigaBot = '1';
    }
    return 0;
}
void getMusica() {
    int counter = 0;
    char opcionMusica[20];
    printf("Elige la musica: 1.Normal 2.Triste 3.Epica Otro.Sin musica\n");
    bool bandera = false;
    while (bandera == false) {
        if (counter > 0) {
            printf("Oh no! Has insertado un valor invalido!:(\n");
        }
        scanf("%s", opcionMusica, stdin);
        counter++;
        bandera = esNumero(opcionMusica);
    }
    int intMusica = atoi(opcionMusica);
    switch (intMusica) {
    case 1:
        PlaySound(TEXT("music.wav"), NULL, SND_LOOP | SND_ASYNC);
        break;
    case 2:
        PlaySound(TEXT("sadMusic.wav"), NULL, SND_LOOP | SND_ASYNC);
        break;
    case 3:
        PlaySound(TEXT("epicMusic.wav"), NULL, SND_LOOP | SND_ASYNC);
        break;
    }
}
void initTablero(void) {
    int i;
    int j;
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            if (j > 0 && j < 6) {
                tablero[i][j] = 205;
            }
            if (j != 2 && j != 4 && i > 0 && i < 6) {
                tablero[i][j] = 186;
            }
            if (dimension == i + j + 1 || i == j || i != 3 && j == 3 || i == 3 && j != 3) {
                tablero[i][j] = 'O';
            }
            tablero[3][3] = '+';
        }
    }
}

void etapaInsertar() {
    int i;
    printf("\nPeriodo de insercion de piezas. Ambos jugadores pueden insertar 9 Piezas\n"); //tengo que explicar mejor esta parte xd
    if (piezaAliada == '1') {
        while (turnos > 0 && piezasRestantes > 0) {
            turnos--;
            piezasRestantes--;
            insertar();
            jugarBot('i');
            imprimirTablero();
            if (tablero[posicI][posicJ] == 'O') {
                printf("La computadora ha sacado a %c-%d!\n", posicJ + 65, posicI + 1);
            }

        }
    } else {
        while (turnos > 0 && piezasRestantes > 0) {
            jugarBot('i');
            imprimirTablero();
            if (tablero[posicI][posicJ] == 'O') {
                printf("La computadora ha sacado a %c-%d!\n", posicJ + 65, posicI + 1);
            }
            insertar();
            turnos--;
            piezasRestantes--;
        }
    }
    imprimirTablero();
}

void insertar(void) { //tengo que ver wtf se printeo mi codigo en el shell la vez pasada xd
    int bandera = 1; //El valor de la bandera sera de 1 si la posicion de insercion es valida
    int counter = 0;
    char posicionI[512];
    char posicionJ[512];
    while (bandera == 1) { //Bloque que nos vuelve a preguntar por la posicion si el dato ingresado es incorrecto
        if (counter > 0) {
            printf("Has insertado una posicion invalida! No te preocupes, ahora puedes ingresarla de nuevo.\n");
        }
        printf("Inserte la posicion de Columna(Letra): ");
        scanf("%s", posicionJ, stdin);
        printf("Inserte la posicion de Fila(Numero): ");
        scanf("%s", posicionI, stdin);
        posicI = validarEntradaI(posicionI) - 1;
        posicJ = validarEntradaJ(posicionJ) - 65;
        checkGanador(validarEntradaJ(posicionI), validarEntradaJ(posicionJ));
        counter++;
        if (tablero[posicI][posicJ] == 'O') {
            bandera = 0;
        }
    }

    tablero[posicI][posicJ] = piezaAliada;
    checkMolino();
}

void jugarBot(char jugada) { //jugada==i. Insertar pieza/ q.Quitar pieza   / m.Mover Pieza (quiza xd)
    posicI = 3;
    posicJ = 3;
    int selectI = 3;
    int selectJ = 3;
    char query;
    char piezaReemplazar;
    srand(time(NULL));
    if (jugada == 'm') {
        while (tablero[selectI][selectJ] != piezaAliadaBot || 
				tablero[posicI][posicJ] != 'O' || 
				verificarJugada(selectI, selectJ, posicI, posicJ) == false) {
					
            selectI = rand() % 7;
            selectJ = rand() % 7;
            posicI = rand() % 7;
            posicJ = rand() % 7;
            checkGanador(selectI, selectJ);
        }
        tablero[selectI][selectJ] = 'O';
        tablero[posicI][posicJ] = piezaAliadaBot;
        // imprimirTablero();
        printf("La computadora movio [%c-%d] a [%c-%d]\n", selectJ + 65, selectI + 1, posicJ + 65, posicI + 1);
        checkMolino();
    } else {
        if (jugada == 'i') {
            query = 'O';
            piezaReemplazar = piezaAliadaBot;
        }
        if (jugada == 'q') {
            query = piezaAliada;
            piezaReemplazar = 'O';
        }
        while (tablero[posicI][posicJ] != query) { //'O'
            posicI = rand() % 7;
            posicJ = rand() % 7;
        }
        tablero[posicI][posicJ] = piezaReemplazar;
        if (jugada == 'i') {
            printf("La computadora jugo %c-%d\n", posicJ + 65, posicI + 1);
            checkMolino();
        }
    }
}

int checkMolino() { //global posicI posicJ son las ultimas jugadas realizadas
    int i;
    int finI;
    int j;
    int finJ;
    int piezasAlineadasi = 0;
    int piezasAlineadasj = 0;

    if (posicI == 3) { //se verifica la excepcion de la FILA central
        if (posicJ > 3) { //wakala
            j = 4;
            finJ = dimension;
        } else {
            j = 0;
            finJ = 3;
        }
        while (j < finJ) {
            if (tablero[posicI][j] == tablero[posicI][posicJ]) {
                piezasAlineadasj++;
            }
            j++;
        }
    } else { //si no es una pieza central se recorre la linea y columna de la ultima jugada 
        for (j = 0; j < dimension; j++) {
            if (tablero[posicI][j] == tablero[posicI][posicJ]) {
                piezasAlineadasj++;
            }
        }
    }
    if (posicJ == 3) { //se verifica la excepcion de la COLUMNA central
        if (posicI > 3) {
            i = 4;
            finI = dimension;
        } else {
            i = 0;
            finI = 3;
        }
        while (i < finI) {
            if (tablero[i][posicJ] == tablero[posicI][posicJ]) {
                piezasAlineadasi++;
            }
            i++;
        }
    } else {
        for (i = 0; i < dimension; i++) {
            if (tablero[i][posicJ] == tablero[posicI][posicJ]) {
                piezasAlineadasi++;
            }
        }
    }
    if (piezasAlineadasi == 3 || piezasAlineadasj == 3) {
        if (tablero[posicI][posicJ] == piezaAliadaBot) {
            printf("Oh no! La computadora ha creado un molino y sacara una de tus piezas!\n");
            sleep(3);
            jugarBot('q');
            return 1;
        } else {
            imprimirTablero();
            printf("Creaste un molino, puedes sacar una pieza enemiga!\n");
            quitarPieza(piezaEnemiga);
        }
    }
    return 0;
}
int imprimirTablero() {
    int i;
    int j;

    printf("\n						Si quieres rendirte, inserta F-F en las coordenadas de jugada!");
    printf("\n                                            			[Turnos Restantes]: %d\n", turnos);
    if (piezasRestantes != 0) {
        printf("								[Piezas Restantes]: %d\n", piezasRestantes);
    }

    printf("\n                                                             A    B    C    D    E    F    G");
    for (i = 0; i < dimension; i++) {
        printf("\n");
        printf("\n");
        for (j = 0; j < dimension; j++) {
            if (j == 0) {
                printf("                                      			%d-", i + 1);
            }
            if (tablero[i][j] == 'O' || tablero[i][j] == '1' || tablero[i][j] == '2') {
                printf("  [%c]", tablero[i][j]);
            } else printf("   %c ", tablero[i][j]);
        }
    }
    printf("\n");
    printf("							Bando 1: Cant de piezas en juego: %d\n", cantidadPiezas('1'));
    //printf("							Bando 1: Cant de jugadas posibles: %d\n", totalesPosibles('1'));
    printf("							Bando 2: Cant de piezas en juego: %d\n", cantidadPiezas('2'));
    // printf("							Bando 2: Cant de jugadas posibles: %d\n", totalesPosibles('2'));
    return 0;
}

void foo(char sonido, char poster) {
    int fondo = 0;
    if (sonido == 'd') {
        PlaySound(NULL, 0, 0);
        PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);
    }
    if (sonido == 'v') {
        PlaySound(NULL, 0, 0);
        PlaySound(TEXT("victory.wav"), NULL, SND_ASYNC);
    }
    FILE * title;
    int counter = 0;
    int c;
    int end = 3000;
    if (poster == 't') {
        system("COLOR 06");
        title = fopen("foo.txt", "r");
    }
    if (poster == 'd') {
        system("COLOR 40");
        title = fopen("gameover.txt", "r");
        end = 5000;
    }
    if (poster == 'v') {
        title = fopen("victory.txt", "r");
    }
    if(poster == 'e'){
    	title = fopen("tie.txt", "r");
	}
    
    if (poster != '0') {
        while (counter <= end) {
            c = fgetc(title);
            counter++;
            printf("%c", c);
        }
    }
    if (poster == 'd') {
        while (fondo < 4) {
            system("COLOR 40");
            sleep(1);
            system("COLOR 04");
            sleep(1);
            fondo++;
        }
    }
    if (poster == 'v') {
        while (fondo < 2) {
            system("COLOR 20");
            sleep(1);
            system("COLOR 02");
            sleep(1);
            fondo++;
        }
    }
    fclose(title);
}

int validarEntradaI(char entrada[]) { //Verifica las entradas de numeros de un digito
    int x;
    int bandera;
    int len = 0;
    for (x = 0; entrada[x] != '\0'; x++) {
        len++;
    }
    if (len != 1 || 0 == atoi(entrada)) {
        bandera = 0;
        return bandera;
    }
    return atoi(entrada);
} //estas funciones se pueden hacer con isdigit(), si tan solo alguien me podia decir que eso existia antes que haga ._.
char validarEntradaJ(char entrada[]) { //Verifica las entradas de numeros de una Letra
    int x;
    int len = 0;
    for (x = 0; entrada[x] != '\0'; x++) {
        len++;
    }
    char caracter1 = toupper(entrada[0]);
    if (len != 1 || caracter1 < 65 || caracter1 > 71) {
        return 0;
    }
    return toupper(entrada[0]);
}

int cantidadPiezas(char a) {
    int x;
    int y;
    int cantPiezas = 0;
    for (x = 0; x < dimension; x++) { //este nested loop busca todos los caracteres iguales al parametro que recibe y retorna la cantidad de caracteres iguales
        for (y = 0; y < dimension; y++) {
            if (tablero[x][y] == a) {
                cantPiezas++;
            }
        }
    }
    return cantPiezas;
}
void quitarPieza(char pieza) {
    int counter = 0; //simplemente cuenta las veces que se pidio la posicion para luego dar una notificacion de error de insercion 
    char stringI[512];
    char stringJ[512];
    quitarI = -1;
    quitarJ = -65;
    while (quitarI == -1 || quitarJ == -65 || tablero[quitarI][quitarJ] != pieza) {
        if (counter > 0) {
            printf("Has insertado una posicion invalida! Tranquilo, ahora puedes ingresarla de nuevo.\n");
        }
        printf("Inserte la posicion de Columna(Letra): ");
        scanf("%s", stringJ, stdin);
        printf("Inserte la posicion de Fila(Numero): ");
        scanf("%s", stringI, stdin);
        quitarI = validarEntradaI(stringI) - 1;
        quitarJ = validarEntradaJ(stringJ) - 65;
        checkGanador(validarEntradaJ(stringI), validarEntradaJ(stringJ));
        counter++;
    }
    tablero[quitarI][quitarJ] = 'O';
}
int jugadasPosibles(int pi, int pj) {
    int cantPosibles = 0;
    int casillasLibresI = 0;
    int casillasLibresJ = 0;
    int i, j;
    char NULO = 'x';
    int diffI = getDiffI(pi, pj);
    int diffJ = getDiffJ(pi, pj);
    char up = tablero[pi - diffI][pj];
    char down = tablero[pi + diffI][pj];
    char left = tablero[pi][pj - diffJ];
    char right = tablero[pi][pj + diffJ];
    if (pi == 0) {
        up = NULO;
    }
    if (pi == 6) {
        down = NULO;
    }
    if (pj == 0) {
        left = NULO;
    }
    if (pj == 6) {
        right = NULO;
    }
    //printf("\nup:%c\ndown:%c\nleft:%c\nright:%c\ndiffI:%d\ndiffJ:%d\n",up,down,left,right,diffI,diffJ);
    char jugadas[4] = {
        up,
        down,
        left,
        right
    };
    for (i = 0; i < 4; i++) {
        if (jugadas[i] == 'O') {
            cantPosibles++;
        }
    }
    return cantPosibles;
}
int totalesPosibles(char pieza) {
    int totalesLibres = 0;
    int i, j;
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            if (tablero[i][j] == pieza) {
                totalesLibres += jugadasPosibles(i, j);
            }
        }
    }
    return totalesLibres;
}
int getTurnos() {
    char cantTurnos[512];
    int i;
    int retorno = 1;
    int counter = 0;
    bool bandera = false;
    while (bandera == false) {
        if (counter > 0) {
            printf("Oh no! Has insertado un valor invalido!:(\n");
        }
        printf("Elige la cantidad de turnos que el juego tendra: ");
        scanf("%s", cantTurnos, stdin);
        counter++;
        bandera = esNumero(cantTurnos);
    }

    turnos = atoi(cantTurnos);
    return 0;
}
bool esNumero(const char * cadena) {
    while ( * cadena != '\0') {
        if ( * cadena < '0' || * cadena > '9')
            return false;
        cadena++;
    }
    return true;
}
