
/*------------------------------LIBRERIAS UTILIZADAS--------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <ctype.h>

/*-------------------------------LIMITES Y CONSTANTES-------------------------------*/

// Limites de Cantidades.

#define MAX_SHOW 15
#define MAX_CANCIONES  1000
#define MAX_PUBLICIDADES 100
#define MAX_TAMAÑO_NOMBRE 500


/*---------------------------------ESTRUCTURAS--------------------------------------*/

//estructura de tiempo: solo incorpora segundos,minutos y horas.
typedef struct tm tiempo;

//posible estructura Auxiliar para el terminal y busqueda y grilla
typedef struct{
	char nombre[MAX_TAMAÑO_NOMBRE];
	char tipo; // S,C,P
	tiempo tiempoS; // H:M:S
}grilla;

//estructura de canciones: base( name,min,seg,puntuacion )
typedef struct{
	char name[100];
	int min,seg,veces_repite,puntuacion;
}cancion;

//estructura de Publicidad: base( name,min,seg,puntuacion )
typedef struct{
	char name[50];
	int min,seg,veces_repite;
	float puntuacion;
}Publicidad;

//estructura de show: base( name,min,seg,puntuacion )
typedef struct{
	char name[200];
	int min,seg,veces_repite,preferencia;
	float puntuacion;
}show;



/*--------------------------------DECLARACION DE FUNCIONES---------------------------------*/

void mostrarArraysGrilla(grilla g[],int cant_grilla);
void llenar_grilla(show shows[],Publicidad publicidades[],cancion canciones[]
	,tiempo* timeInicial,grilla result[]);

/*-------------------FUNCIONES COMPLEMENTARIAS-------------------------*/

int showsEspeciales(int num);

//funcion para casos aletorios.
int aleatorio_en_rango(int min, int max);

// acomda horas,minutos y segundos.
void convertir_a_hhmmss(int minutos, int segundos,tiempo* tiempoI);

/*-------------------CREACION DE LAS GRILLAS-------------------------*/

// Posible funcion para las grillas de cada dia.
void grilla_dia(grilla horario[],int dia);

// Posible funcion para las grillas de terminal.
void grilla_principal(show shows[],Publicidad publicidades[],cancion canciones[]
	,tiempo* timeInicial,grilla result[]);


/*-------------------FUNCIONES DE ANALISIS DE ERROR-------------------------*/

// muestra el contenido de una Array de canciones.
void mostrarArraysCanciones(cancion can[],int cant_canciones);

void mostrarArraysShows(show sh[],int cant_canciones);

void mostrarArraysPublicidades(Publicidad pub[],int cant_pub);


/*------------------FUNCIONES DE ORDENAMIENTO DE DATOS-------------------------*/

// ordena de menor a mayor puntaje cada cancion.
void ordenar_lista_de_canciones(cancion canciones[],int tamaño);

// ordena de menor a mayor por raiting de cada show.
void ordenar_lista_de_show(show showRadiales[]);


/*-------------------FUNCIONES DE REGISTRO DE DATOS-------------------------*/

//funcion engargada de llenar arreglos de shows
void lecturaDeShow(show showRadiales[]);

//funcion engargada de llenar arreglos de canciones.
void lecturaDeCanciones(cancion canciones[]);

//funcion engargada de llenar arreglos de publicidades. 
void lecturaDePublicidad(Publicidad publicidades[]);





/*----------------------------------CUERPO PRINCIPAL-------------------------------------*/

int main(){
	
	// contador de tiempo para grilla.
	tiempo tiempoInicial;

	// tiempo inicial: 00:05:00
	tiempoInicial.tm_hour = 0;
	tiempoInicial.tm_min = 5;
	tiempoInicial.tm_sec = 0;


	/*------------------------ARRAYS--------------------------*/
	cancion canciones[MAX_CANCIONES];
	show shows[MAX_SHOW];
	Publicidad publicidades[MAX_PUBLICIDADES];
	grilla result[1000];


	/*---------------------AREA DE PRUEBA--------------------------*/

	lecturaDeCanciones(canciones);
	lecturaDeShow(shows);
	lecturaDePublicidad(publicidades);

	llenar_grilla(shows,publicidades,canciones,&tiempoInicial,result);

	printf("%-3c %-3c %-3c %-2c %s\n",'H','M','S','T',"nombre:");
	// mostrarArraysCanciones(canciones,9);
	//mostrarArraysPublicidades(publicidades,2);
	mostrarArraysGrilla(result,4);

	/*	printf("despues:\n");
	ordenar_lista_de_canciones(canciones,2);
	mostrarArraysCanciones(canciones,sizeof(canciones)/sizeof(canciones[0]));*/

	

	return 0;
}





/*---------------------------------CODIGO DE FUNCIONES---------------------------------*/



void llenar_grilla(show shows[],Publicidad publicidades[],cancion canciones[]
	,tiempo* timeInicial,grilla result[])
{

	int num,elem,i=0;

	while( i < 4 ){

		switch( aleatorio_en_rango(0,2) ){
			case 0:
				result[i].tipo = 'S';
				strcpy(result[i].nombre, shows[i].name);
				convertir_a_hhmmss(shows[i].min,shows[i].seg,&*timeInicial); 
				result[i].tiempoS = *timeInicial;
				break;
			case 1:
				result[i].tipo = 'C';
				strcpy(result[i].nombre, canciones[i].name);
				convertir_a_hhmmss(shows[i].min,canciones[i].seg,&*timeInicial); 
				result[i].tiempoS = *timeInicial;
				break;
			default:
				result[i].tipo = 'P';
				strcpy(result[i].nombre, publicidades[i].name);
				convertir_a_hhmmss(publicidades[i].min,0,&*timeInicial); 
				result[i].tiempoS = *timeInicial;
				break;
		}

		i++;
	}
}

void grilla_principal(show shows[],Publicidad publicidades[],cancion canciones[]
	,tiempo* timeInicial,grilla result[])
{

	int num,elem,i=0;

	while( timeInicial->tm_hour < 24 ){

		//condicion para los shows especiales.( 7:00 a 9:00,12:00 a 14:00,18:00 a 19:00).
		if( showsEspeciales(timeInicial->tm_hour) ){
			num = sizeof(shows[MAX_SHOW])/sizeof(shows[0]); // tamaño de Arrays de shows.
			elem = aleatorio_en_rango(num-3,num-1); // entre (n-2,n) de Array.

			strcpy(result[i].nombre, shows[elem].name);
			convertir_a_hhmmss(shows[elem].min,shows[elem].seg,&*timeInicial); 
			result[i].tiempoS = *timeInicial;
			result[i].tipo = 'S';
		}

		i++;
	}
}


/*-------------------FUNCIONES COMPLEMENTARIAS-------------------------*/

//funcion para identificar las horas de shows especiales.
int showsEspeciales(int num){
	int res = 0;
	if( (num <= 9 && num >= 7) || (num <= 14 && num >= 12) || (num <= 19 && num >= 18)){
		res = 1;
	}
	return res;
}


// Función que genera un número aleatorio entre min y max (inclusive)
int aleatorio_en_rango(int min, int max){
    // Asegurarse de que min <= max
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }
    
    // Generar el número aleatorio en el rango [min, max]
    return min + rand() % (max - min + 1);
}


void convertir_a_hhmmss(int minutos, int segundos,tiempo* tiempoI){
    
    // Asigna los segundos y minutos
    tiempoI->tm_sec += segundos;
    tiempoI->tm_min += minutos;
    
    // Normaliza la estructura (ajusta horas, minutos, segundos)
    mktime(&*tiempoI); // Esta función ajusta los valores
}

/*------------------FUNCIONES DE ORDENAMIENTO DE DATOS-------------------------*/

//implementacion del algoritmo de ordenamiento de burbuja en la estructura de canciones
void ordenar_lista_de_canciones(cancion canciones[],int tamaño){

	//loop 1
	for( int i= 0; i < tamaño-1;i++ ){
		//loop 2
		for( int j= 0; j < tamaño-i-1;j++ ){
			//condicional para el intercambio.
			if( canciones[j].puntuacion > canciones[j+1].puntuacion ){
				cancion temp = canciones[j];
				canciones[j]= canciones[j+1];
				canciones[j+1]= temp;
			}
		}
	}

}

//implementacion del algoritmo de ordenamiento de burbuja en la estructura de shows
void ordenar_lista_de_shows(show shows[],int tamaño){

	//loop 1
	for( int i= 0; i < tamaño-1;i++ ){
		//loop 2
		for( int j= 0; j < tamaño-i-1;j++ ){
			//condicional para el intercambio.
			if( shows[j].preferencia > shows[j+1].preferencia){
				show temp = shows[j];
				shows[j+1]=shows[j];
				shows[j]=temp;
			}
		}
	}

}

//muestra el array de canciones.
void mostrarArraysCanciones(cancion can[],int cant_canciones){
	for( int i=0; i < cant_canciones;i++){
		printf("%s %d %d %d\n",can[i].name,can[i].min,can[i].seg,can[i].puntuacion);
	}
}

//muestra el array de shows.
void mostrarArraysShows(show sh[],int cant_canciones){
	for( int i=0; i < cant_canciones;i++){
		printf("%s %d %d %d %d\n",
					sh[i].name,
					sh[i].min,
					sh[i].seg,
					sh[i].veces_repite,
					sh[i].preferencia
				);
	}
}

//muestra el array de publicidades.
void mostrarArraysPublicidades(Publicidad pub[],int cant_pub){
	for( int i=0; i < cant_pub;i++){
		printf("%s %d %d \n",
				pub[i].name,
				pub[i].seg,
				pub[i].veces_repite
			);
	}
}

//muestra el array de grilla.
void mostrarArraysGrilla(grilla g[],int cant_grilla){
	for( int i=0; i < cant_grilla;i++){

		printf("%-3d %-3d %-3d %-2c %s\n",
				g[i].tiempoS.tm_hour,
				g[i].tiempoS.tm_min,
				g[i].tiempoS.tm_sec,
				g[i].tipo,
				g[i].nombre
			);
	}
}

/*-------------------FUNCIONES DE REGISTRO DE DATOS-------------------------*/

void lecturaDeCanciones(cancion canciones[]) {
    FILE *lista_canciones = fopen("canciones.in", "r");
    
    if (lista_canciones == NULL) {
        printf("No se pudo abrir el archivo canciones.in\n");
        return;
    }

    int cantidad;
    fscanf(lista_canciones,"%d", &cantidad);
    
    // Leer el salto de línea después del número
    char temp;
    fscanf(lista_canciones, "%c", &temp); 

    for (int i = 0; i < cantidad; i++) {
        // Leer el nombre hasta encontrar un número
        int pos = 0;
        char nombre[100];
        char letra;
        
        fscanf(lista_canciones, "%c", &letra);
        while (!isdigit(letra) && pos < 99) {
            nombre[pos] = letra;
            pos++;
            fscanf(lista_canciones, "%c", &letra);
        }
        nombre[pos] = '\0'; // Fin del string
        strcpy(canciones[i].name, nombre);
        
        // Devolver el numero que leimos de mas
        ungetc(letra, lista_canciones);
        
        // Leer los numeros (min, seg, puntuacion)
        fscanf(lista_canciones, "%d %d %d", 
              &canciones[i].min, 
              &canciones[i].seg, 
              &canciones[i].puntuacion);
        
        // Leer el salto de linea al final
        fscanf(lista_canciones, "%c", &temp); 
    }
    
    fclose(lista_canciones);
}

void lecturaDeShow(show showRadiales[]){
    FILE *lista_shows = fopen("shows.in", "r");
    
    if (lista_shows == NULL) {
        printf("No se pudo abrir el archivo canciones.in\n");
        return;
    }

    int cantidad;
    fscanf(lista_shows,"%d", &cantidad);
    
    // Leer el salto de línea después del número
    char temp;
    fscanf(lista_shows, "%c", &temp); 

    for (int i = 0; i < cantidad; i++) {
        // Leer el nombre hasta encontrar un número
        int pos = 0;
        char nombre[100];
        char letra;
        
        fscanf(lista_shows, "%c", &letra);
        while (!isdigit(letra) && pos < 99) {
            nombre[pos] = letra;
            pos++;
            fscanf(lista_shows, "%c", &letra);
        }
        nombre[pos] = '\0'; // Fin del string
        strcpy(showRadiales[i].name, nombre);
        
        // Devolver el numero que leimos de mas
        ungetc(letra,lista_shows);
        
        // Leer los numeros (min, seg, puntuacion)
        fscanf(lista_shows, "%d %d %d %d",
					&showRadiales[i].min,
					&showRadiales[i].seg,
					&showRadiales[i].veces_repite,
					&showRadiales[i].preferencia
				);
        
        // Leer el salto de linea al final
        fscanf(lista_shows, "%c", &temp); 
    }
    
    fclose(lista_shows);
}

void lecturaDePublicidad(Publicidad publicidades[]){
	//Archivo de entrada de show.
	FILE *lista_publicidades = fopen("publicidad.in","r");

	int i = 0;
	char temp;

	if(lista_publicidades != NULL){
		//loop.
		while(!feof(lista_publicidades)){
			// Leer el nombre hasta encontrar un número
			int pos = 0;
			char nombre[100];
			char letra;
			
			fscanf(lista_publicidades, "%c", &letra);
			while(!isdigit(letra) && pos < 99 && !feof(lista_publicidades)) {
				nombre[pos] = letra;
				pos++;
				fscanf(lista_publicidades, "%c", &letra);
			}
			nombre[pos] = '\0'; // Fin del string
			strcpy(publicidades[i].name, nombre);
			
			// Devolver el numero que leimos de mas
			ungetc(letra, lista_publicidades);
			fscanf(lista_publicidades, "%d %d", &publicidades[i].seg, &publicidades[i].veces_repite);

			// Leer el salto de linea al final
			if(fscanf(lista_publicidades, "%c", &temp) == 1 && temp == '\n'){
				i++;
			}
		}
	}

	//cerrado de archivos.
	fclose(lista_publicidades);
}