
/*------------------------------LIBRERIAS UTILIZADAS--------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
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

//estructura de cantidades.
typedef struct{
	int cancion,show,publicidad;
}cantidad;

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

// aleatoriedad en publicidad.
void elepcion_publicidades(grilla* grilla_dia,int cantPubli,Publicidad publicidades[],tiempo* t);
// aleatoriedad en canciones.
void elepcion_canciones(grilla* grilla_dia,int cantCanc,cancion canciones[],tiempo* t);
// aleatoriedad en shows.
void elepcion_shows(grilla* grilla_dia,int cantShows,show shows[],tiempo* t);
// reinicia tiempo a tiempo inicial 00:05:00
tiempo tiempo_inicial(tiempo tiempoInicial);

void creacion_grilla(int c_h,int c_c,int c_p,show h[],cancion c[],Publicidad p[],grilla grilla_dia[],int *cant_elem);


void llenar_grilla(show shows[],Publicidad publicidades[],cancion canciones[]
	,tiempo* timeInicial,grilla result[]);

/*-------------------FUNCIONES COMPLEMENTARIAS-------------------------*/

int showsEspeciales(int num);

//funcion para casos aletorios.
int aleatorio_en_rango(int min, int max);

// acomda horas,minutos y segundos.
void convertir_a_hhmmss(int minutos, int segundos,tiempo* tiempoI);

void aleatoriedad_de_grilla(
			int numAleatorio,int posicionG,int posicionO,
			show shows[],Publicidad publicidades[],cancion canciones[]
			,tiempo* timeInicial,grilla result[]
		);

/*-------------------CREACION DE LAS GRILLAS-------------------------*/

// Posible funcion para las grillas de cada dia.
void grilla_dia(grilla horario[],int dia);
// Posible funcion para las grillas de terminal.
void grilla_principal(show shows[],Publicidad publicidades[],cancion canciones[]
	,tiempo* timeInicial,grilla result[]);


/*-------------------FUNCIONES DE ANALISIS DE ERROR-------------------------*/

// muestra el contenido de una Array de canciones en terminal.
void mostrarArraysCanciones(cancion can[],int cant_canciones);
// muestra el contenido de una Array de shows en terminal.
void mostrarArraysShows(show sh[],int cant_canciones);
// muestra el contenido de una Array de publicidades en terminal.
void mostrarArraysPublicidades(Publicidad pub[],int cant_pub);
// muestra el contenido de una Array de grilla en terminal.(Una fraccion)
void mostrarArraysGrilla(grilla g[],int cant_grilla);


/*------------------FUNCIONES DE ORDENAMIENTO DE DATOS-------------------------*/

// ordena de menor a mayor puntaje cada cancion.
void ordenar_lista_de_canciones(cancion canciones[],int tamaño);
// ordena de menor a mayor por raiting de cada show.
void ordenar_lista_de_show(show showRadiales[]);


/*-------------------FUNCIONES DE REGISTRO DE DATOS-------------------------*/

//funcion engargada de llenar arreglos de shows
void lecturaDeShow(show showRadiales[],int* cant_shows);
//funcion engargada de llenar arreglos de canciones.
void lecturaDeCanciones(cancion canciones[],int* cant_canciones );
//funcion engargada de llenar arreglos de publicidades. 
void lecturaDePublicidad(Publicidad publicidades[],int* cant_publicida);





/*----------------------------------MAIN-------------------------------------*/

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
	grilla matriz[50][7];

	grilla grilla_aux[100][3];

	/*---------------------AREA DE PRUEBA--------------------------*/

	int cant_shows,cant_canciones,cant_publicidades;
	
	lecturaDeCanciones(canciones,&cant_canciones);
	lecturaDeShow(shows,&cant_shows);
	lecturaDePublicidad(publicidades,&cant_publicidades);

	//llenar_grilla(shows,publicidades,canciones,&tiempoInicial,result);
	int cant_dia;
	creacion_grilla(cant_shows,cant_canciones,cant_publicidades,shows,canciones,publicidades,result,&cant_dia);
	mostrarArraysGrilla(result,cant_dia);

	//mostrarArraysCanciones(canciones,cant_canciones);
	//mostrarArraysShows(shows,cant_shows);
	

	
	return 0;
}





/*---------------------------------IMPLEMENTACION---------------------------------*/

void elepcion_shows(grilla* grilla_dia,int cantShows,show shows[],tiempo* t){
	int num = aleatorio_en_rango(1,cantShows);

	grilla_dia->tipo = 'S';
	strcpy(grilla_dia->nombre,shows[num].name);
	convertir_a_hhmmss(shows[num].min,shows[num].seg,&*t);
	grilla_dia->tiempoS = *t ;
}

void elepcion_canciones(grilla* grilla_dia,int cantCanc,cancion canciones[],tiempo* t){
	int num = aleatorio_en_rango(1,cantCanc);

	grilla_dia->tipo = 'C';
	strcpy(grilla_dia->nombre,canciones[num].name);
	convertir_a_hhmmss(canciones[num].min,canciones[num].seg,&*t); 
	grilla_dia->tiempoS = *t;
}

void elepcion_publicidades(grilla* grilla_dia,int cantPubli,Publicidad publicidades[],tiempo* t){
	int num = aleatorio_en_rango(1,cantPubli);

	grilla_dia->tipo = 'P';
	strcpy(grilla_dia->nombre,publicidades[num].name);
	convertir_a_hhmmss(0,publicidades[num].seg,&*t); 
	grilla_dia->tiempoS = *t;
}

// contador de tiempo para grilla.
tiempo tiempo_inicial(tiempo tiempoInicial){

	// tiempo inicial: 00:05:00
	tiempoInicial.tm_hour = 0;
	tiempoInicial.tm_min = 5;
	tiempoInicial.tm_sec = 0;

	return tiempoInicial;
}

// Creacion de la grilla y cant de elementos de grilla.
void creacion_grilla(int c_h,int c_c,int c_p,show h[],cancion c[],Publicidad p[],grilla grilla_dia[],int *cant_elem){

	// contador de tiempo para grilla.
	tiempo tiempoInicial = tiempo_inicial(tiempoInicial);
	int numAleatorio,pos_grilla=0;

	// probar con tres 24:00:00
	while( tiempoInicial.tm_hour < 12 ){
		numAleatorio = aleatorio_en_rango(1,3);//posible elepcion entre shows,canciones y publiciades.
		switch(numAleatorio){
			case 1:
				elepcion_shows(&grilla_dia[pos_grilla],c_h,h,&tiempoInicial);
				break;
			case 2:
				elepcion_canciones(&grilla_dia[pos_grilla],c_c,c,&tiempoInicial);
				break;
			default:
				elepcion_publicidades(&grilla_dia[pos_grilla],c_p,p,&tiempoInicial);
				break;
		}
		pos_grilla++;
	}
	*cant_elem = pos_grilla;
}

void aleatoriedad_de_grilla(
			int numAleatorio,int posicionG,int posicionO,
			show shows[],Publicidad publicidades[],cancion canciones[]
			,tiempo* timeInicial,grilla result[]
		)
{
		switch(numAleatorio){
			case 0:
				result[posicionG].tipo = 'S';
				strcpy(result[posicionG].nombre, shows[posicionO].name);
				convertir_a_hhmmss(shows[posicionO].min,shows[posicionO].seg,&*timeInicial); 
				result[posicionG].tiempoS = *timeInicial;
				break;
			case 1:
				result[posicionG].tipo = 'C';
				strcpy(result[posicionG].nombre, canciones[posicionO].name);
				convertir_a_hhmmss(canciones[posicionO].min,canciones[posicionO].seg,&*timeInicial); 
				result[posicionG].tiempoS = *timeInicial;
				break;
			default:
				result[posicionG].tipo = 'P';
				strcpy(result[posicionG].nombre, publicidades[posicionO].name);
				convertir_a_hhmmss(0,publicidades[posicionO].seg,&*timeInicial); 
				result[posicionG].tiempoS = *timeInicial;
				break;
		}
}

// llena una grilla(protipo).
void llenar_grilla(show shows[],Publicidad publicidades[],cancion canciones[]
	,tiempo* timeInicial,grilla result[])
{

	int num,elem,i=0;

	while( i < 4 ){

		aleatoriedad_de_grilla(aleatorio_en_rango(0,2),
			i,i,shows,publicidades,
			canciones,&*timeInicial,result);

		i++;
	}
}


// Crear la grilla de cada dia(prototipo).
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


/*-------------------------FUNCIONES COMPLEMENTARIAS---------------------------*/

//funcion para identificar las horas de shows especiales.
int showsEspeciales(int num){
	int res = 0;
	if( (num <= 9 && num >= 7) || (num <= 14 && num >= 12) || (num <= 19 && num >= 18)){
		res = 1;
	}
	return res;
}

// Función que genera un numero aleatorio entre min y max (inclusive)
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

// Ajusta el tiempo de forma estandar de h:mn:seg
void convertir_a_hhmmss(int minutos, int segundos,tiempo* tiempoI){
    
    // Asigna los segundos y minutos
    tiempoI->tm_sec += segundos;
    tiempoI->tm_min += minutos;

	// Asegurar que la estructura está completa
    if (tiempoI->tm_year == 0) {
        tiempoI->tm_year = 2024 - 1900;
        tiempoI->tm_mon = 0;
        tiempoI->tm_mday = 1;
    }
    
    
    // Normaliza la estructura (ajusta horas, minutos, segundos)
    mktime(&*tiempoI); // Esta funcion ajusta los valores
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

/*------------------FUNCIONES DE OPSERVACION EN TERMINAL-------------------------*/

//muestra en el terminal el array de canciones.
void mostrarArraysCanciones(cancion can[],int cant_canciones){
	for( int i=0; i < cant_canciones;i++){
		printf("%s %d %d %d\n",
					can[i].name,
					can[i].min,
					can[i].seg,
					can[i].puntuacion
				);
	}
}

//muestra en el terminal el array de shows.
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

//muestra en el terminal el array de publicidades.
void mostrarArraysPublicidades(Publicidad pub[],int cant_pub){
	for( int i=0; i < cant_pub;i++){
		printf("%s %d %d \n",
				pub[i].name,
				pub[i].seg,
				pub[i].veces_repite
			);
	}
}

//muestra en el terminal el array de grilla.
void mostrarArraysGrilla(grilla g[],int cant_grilla){
	printf("%-3c %-3c %-3c %-2c %s\n",'H','M','S','T',"nombre:");
	for( int i=0; i < cant_grilla;i++){
		//muestra en pantalla los resultados.
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

void lecturaDeCanciones(cancion canciones[],int* cant_canciones ){
    FILE *lista_canciones = fopen("canciones.in", "r");
    
    if (lista_canciones == NULL) {
        printf("No se pudo abrir el archivo canciones.in\n");
        return;
    }


    fscanf(lista_canciones,"%d", &*cant_canciones);
    
    // Leer el salto de línea después del numero
    char temp;
    fscanf(lista_canciones, "%c", &temp); 

    for (int i = 0; i < *cant_canciones; i++) {
        // Leer el nombre hasta encontrar un numero
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

void lecturaDeShow(show showRadiales[],int* cant_shows){
    FILE *lista_shows = fopen("shows.in", "r");
    
    if (lista_shows == NULL) {
        printf("No se pudo abrir el archivo canciones.in\n");
        return;
    }


    fscanf(lista_shows,"%d", &*cant_shows);
    
    // Leer el salto de línea después del numero
    char temp;
    fscanf(lista_shows, "%c", &temp); 

    for (int i = 0; i < *cant_shows; i++) {
        // Leer el nombre hasta encontrar un numero
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

void lecturaDePublicidad(Publicidad publicidades[],int* cant_publicida){
	//Archivo de entrada de show.
	FILE *lista_publicidades = fopen("publicidad.in","r");

	int i = 0;
	char temp;

	if(lista_publicidades != NULL){
		//loop.
		while(!feof(lista_publicidades)){
			// Leer el nombre hasta encontrar un numero
			int pos = 0;
			char nombre[100];
			char letra;
			
			fscanf(lista_publicidades, "%c", &letra);
			// loop interno:
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
		*cant_publicida = i;
	}

	//cerrado de archivos.
	fclose(lista_publicidades);
}