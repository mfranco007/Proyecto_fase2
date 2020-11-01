#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

//PROTOTIPO DE LAS FUNCIONES
void ingresarTexto();
void gotoxy(int x,int y);
void dibujarCuadro(int x1,int y1,int x2,int y2);
void limpia();
void menu();

//ESTRUCTURA PRINCIPAL QUE CONTIENE LAS PALABRAS Y  LA FUNCIONALIDAD
typedef struct{
	char palabra_esp[40];
	char palabra_ing[40];
	char funcionalidad[80];
}palabra;


//FUNCION PRINCIPAL MAIN, ES LA PRIMER FUNCION QUE EL PROGRAMA LEE
int main(){
	system("COLOR 70");
	dibujarCuadro(0,1,119,3); //DIBUJA CUADRO DEL TITULO
	gotoxy(55,2); cout << "TRADUCTOR";
	menu();
	system("pause");
	return 0;
}

//ESTA FUNCION IMPRIME EL MENU EN PANTALLA
void menu(){
	int op;
	do{
		gotoxy(1,6); cout <<"MENU PRINCIPAL";
		gotoxy(1,8); cout <<"1. Ingresar texto";
		gotoxy(1,10); cout <<"2. Cerrar Programa";
		gotoxy(1,12); cout <<"Ingrse opcion: ";
		cin >> op;
	}while(op < 0 || op > 2);
	
	if (op == 1) ingresarTexto();
	if (op == 2) exit(0);
}

//ESTA FUNCION MUESTAR TODAS LAS PALABRAS CON SU RESPECTIVA FUNCIONALIDAD EN PANTALLA
void ingresarTexto(){
	FILE *pa, *pa2;
	palabra p1, listaP[100];
	int i, ultimo,f=10,j,k,limite_inf,in=0,encontro,b,longi,longitud,aux=0,aux2=0,indice,longitud_t,inc;
	char texto[300], palabra_[100][20], traducido[300];
	limpia();
	
	if (((pa = fopen("Archivo Binario","a+b"))==NULL)){ 
		printf("No se puede abrir el archivo.\n");
		return ;
	}
	
	rewind(pa);  //COLOCA EL CURSOR AL INICIO DEL ARCHIVO
	i=0;
	
	while(!feof(pa)){     //RECORRE TODO EL ARCHIVO
		if(fread(&p1, sizeof(palabra), 1, pa)){               
			listaP[i]=p1;                                        
			i++;
		}                                               
	}
	fclose(pa);
	
	fflush(stdin);
	gotoxy(1,6); cout <<"INGRESAR TEXTO";
	gotoxy(1,8); cout << "Ingrese texto: ";
	gets(texto);
	
	
	limite_inf = 0;
	longitud = strlen(texto);
	indice = 0;
	
	for(j = 0; j < longitud+1; j++){
		if(texto[j] == ' ' || texto[j] == '(' || texto[j] == '{' || texto[j] == '\0'){
			aux++;
			
			if(aux != 1){
				limite_inf = inc+1;
			}
				
			else{
				limite_inf = 0;
				inc = j;
			}
				
				
			//ASIGNAMOS A LA CADENA PALABRA LAS FRASES
			for (k = 0; k < j; k++){
				palabra_[aux][k] = texto[limite_inf]; 
				limite_inf++;
			}
			
			gotoxy(1,10); cout << palabra_[aux];
	
			
			//PROCESO DE BUSQUEDA DE INFORMACION
			encontro=1;
			ultimo=i;
			b=0;
			while (b < ultimo && encontro){
				if (strcmpi(listaP[b].palabra_ing,palabra_[aux])==0)
					encontro=0;           
				else 
					b++;
			}
			
			int recorrido = 0;
			
			if (encontro == 0){
				aux2++;	
				longi = strlen(listaP[b].palabra_esp);
				longitud_t = strlen(traducido);
						
				if(aux2 != 1)
					indice = longitud_t;
				else
					indice = 0;
							
				//LA VARIABLE K SERA EL INDICE DE TODA LA FRASE TRADUCIDA
				while(indice < longi){
					traducido[indice] = listaP[b].palabra_esp[recorrido];
					recorrido++;
					indice++;
				}
				
				if(texto[j] == ' ')
					traducido[indice] = ' ';
			}
			
			gotoxy(1,12); cout << "Texto traducido: " << traducido;
			
			for (k = 0; k < j; k++){
				palabra_[aux][k] = ' '; 
			}
			getch();
		}
	}
	
	gotoxy(1,28); cout << "PRESIONE UNA TECLA PARA VOLVER..";	
	
	getch();
	limpia();
	menu();	
}


//FUNCION GOTOXY, SIRVE PARA POSICIONAR LOS MENSAJES EN UNA DETERMINADA ZONA DE LA PANTALLA, SE INGRESA COLUMNA Y FILA DE LA PANTALLA, EJEMPLO: gotoxy(4,10); printf("HOla"); ESTE MENSAJE SE IMPRIMIRÁ EN LA POSICIÓN COLUMNA 4, FILA 10
void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }


//FUNCION QUE DIBUJA UN CUADRO, SE PASAN LOS VALORES DONDE QUEREMOS QUE SE FORME EL CUADRO, EJEMPLO dibujarCuadro(1,1,78,24);
void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;
    
    for (i=x1;i<x2;i++){
	gotoxy(i,y1);printf("\304") ;//linea horizontal superior
	gotoxy(i,y2);printf("\304") ;//linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
	gotoxy(x1,i);printf("\263") ;//linea vertical izquierda
	gotoxy(x2,i);printf("\263") ;//linea vertical derecha
    }
    
    
    //Dibujar las esquinas del cuadro
    gotoxy(x1,y1); cout<< "\332"; 
    gotoxy(x1,y2); cout<< "\300";
    gotoxy(x2,y1); cout<< "\277";
    gotoxy(x2,y2); cout<< "\331";
}


//FUNCION LIMPIAR AREA
void limpia(){
	int i,j;
	for(i=6;i<=28;i++){
		for(j=0;j<=117;j++){
			gotoxy(j,i); printf(" ");}}
}

