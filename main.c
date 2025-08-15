#include <stdio.h>
// libreria para uso de estructuras de tiempo
#include <time.h>



//################################################
// Estructuras

//estructura de canciones: base( name,min,seg,puntuacion )
typedef struct{
	char name[50];
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
	char name[50];
	int min,seg,veces_repite,preferencia;
	float puntuacion;
}show;



//################################################
//funciones:

// muestra el contenido de una Array de canciones.
void mostrarArraysCanciones(cancion can[],int cant_canciones);

// ordena de menor a mayor puntaje cada cancion.
void ordenar_lista_de_canciones(cancion canciones[],int tamaño);

// ordena de menor a mayor por raiting de cada show.
void ordenar_lista_de_show(show showRadiales[]);

//funcion engargada de 
void lecturaDeShow(show showRadiales[]);

//funcion engargada de 
void lecturaDeCanciones(cancion canciones[]);

//funcion engargada de 
void lecturaDePublicidad(Publicidad publicidades[]);



//################################################
// Cuerpo:

int main(){
	
	cancion canciones[3];

	lecturaDeCanciones(canciones);

	printf("antes:\n");
	mostrarArraysCanciones(canciones,sizeof(canciones)/sizeof(canciones[0]));

	printf("despues:\n");
	ordenar_lista_de_canciones(canciones,2);
	mostrarArraysCanciones(canciones,sizeof(canciones)/sizeof(canciones[0]));


	return 0;
}



//################################################

//implementacion del algoritmo de ordenamiento de burbuja en la estructura de canciones
void ordenar_lista_de_canciones(cancion canciones[],int tamaño){

	for( int i= 0; i < tamaño-1;i++ ){
		for( int j= 0; j < tamaño-i-1;j++ ){
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

	for( int i= 0; i < tamaño-1;i++ ){
		for( int j= 0; j < tamaño-i-1;j++ ){
			if( shows[j].preferencia > shows[j+1].preferencia){
				show temp = shows[j];
				shows[j+1]=shows[j];
				shows[j]=temp;
			}
		}
	}

}

void mostrarArraysCanciones(cancion can[],int cant_canciones){
	for( int i=0; i < 2;i++){
		printf("%s %d %d %d\n",can[i].name,can[i].min,can[i].seg,can[i].puntuacion);
	}
}

void lecturaDeCanciones(cancion canciones[]){
	//Archivo de entrada de canciones.
	FILE *lista_canciones = fopen("canciones.in","r");

	int cant_canciones;

	if( lista_canciones != NULL ){
		//lectura de cantidad de canciones de archivo.
		fscanf(lista_canciones,"%d",&cant_canciones);

		//loop.
		for(int i= 0; i < cant_canciones;i++){
			//lectura de datos de cada cancion.
			fscanf(lista_canciones,"%s%d%d%d",&canciones[i].name,&canciones[i].min,
				&canciones[i].seg,&canciones[i].puntuacion);
		}
	}

	//cerrado de archivos.
	fclose(lista_canciones);
}

void lecturaDeShow(show showRadiales[]){
	//Archivo de entrada de show.
	FILE *lista_show = fopen("shows.in","r");


	int cant_show;

	if( lista_show != NULL ){
		//lectura de cantidad de show de archivo.
		fscanf(lista_show,"%d",&cant_show);

		//loop.
		for(int i= 0; i < cant_show;i++){
			//lectura de datos de cada show.
			fscanf(lista_show,"%s%d%d%d%d",&showRadiales[i].name,&showRadiales[i].min,
				&showRadiales[i].seg,&showRadiales[i].seg,&showRadiales[i].preferencia);
		}
	}

	//cerrado de archivos.
	fclose(lista_show);
}
