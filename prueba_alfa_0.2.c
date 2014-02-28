#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

void escribirtablafrecuencias (int tablafrec[],int k);

int main( int argc, char *argv[] ) 
{
	//Recoger valores
    char *filepath = "./Mosca_7k.txt";
    int k = 4;
    int fADN;
    int i;
    int p;
    struct stat stat_ent;
    off_t tam;
    char *dir_ent;
    int *tablafrec;
    int and = pow( 4, k );
    int ventana = 0; 

    fADN = open( filepath, O_RDONLY );
    fstat( fADN, &stat_ent );
    tam = stat_ent.st_size;
    dir_ent = ( char* ) mmap( NULL, tam, PROT_READ, MAP_SHARED, fADN, 0 );
    close( fADN );

    if( ( tablafrec = ( int* ) calloc( and, sizeof( int ) ) ) == NULL ) 
    {
    	//colocar cosas
    }

    for( p = 0 ; p < and ; p ++ )
    {
    	tablafrec[ p ] = 0;

    }

    and -= 4; 
   
    int j = 0;

    for( i = 0 ; i < tam ; i++ )
    {
    	printf(  "%c", dir_ent[ i ] );

    	if( dir_ent[ i ] == 'A' )
    	{
    	    ventana = ventana << 2;
    	    ventana = ventana & and;
	    	printf( "%d", ventana );
	    	j++;
	  	}
	  	else if( dir_ent[ i ] == 'C' )
	  	{
	  		ventana = ventana << 2;
	  		ventana = ventana & and;
	        ventana = ventana | 1;
	    	printf( "%d", ventana );
	    	j++;
	  	}
	    else if( dir_ent[ i ] == 'G' )
	    {
	        ventana = ventana << 2;
	        ventana = ventana & and;
	    	ventana = ventana | 2;
	    	printf( "%d", ventana );
	    	j++;
	    }
	    else if( dir_ent[ i ] == 'T' )
	   	{
	   	    ventana = ventana << 2;
	   	    ventana = ventana & and;
	   	    ventana = ventana | 3;
	   	    printf( "%d", ventana );
	   	    j++;
	   	}
	   	else if( dir_ent[ i ] == 'N' ) // Pongo la comparación por si el fichero tiene retorno de carro que pase de él
	   	{
	   		j = 0;
	   	}
	   	if( j == k )
	   	{
	   	    printf( "escribir en la tabla" );
	   	    tablafrec[ ventana ]++;
	   	    printf( "%d", ventana );
	   	    j = k - 1;
	   	}
	   	//!!!!!!!!!!!!!!!Leer el vector y añadirlo en esa posición en la tabla
	   }

    fADN = munmap( dir_ent, tam );
    
    //!!!!!!!!!!!!!!!Declarar aqui la tabla de frecuencias como la queremos hacer
    for(p =0; p< and+4;p++){
      printf ("%d\n",tablafrec[p]);
    }
    
    
    escribirtablafrecuencias(tablafrec, k);
    
    return 0;
}
void escribirtablafrecuencias (int tablafrec[],int k){
  
  //Para la fecha
  char fecha[128];
  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);
  strftime(fecha,128,"%d-%m-%y %H:%M:%S",tlocal);
  
  //Archivo Resumen tabla de frecuencias
  char path [40]= "TF"; 
  strcpy(path,fecha);
  strcat(path,".txt");
  
  //Creo el archivo y lo preparo para escritura
  FILE *fADNresult = fopen(path, "a");
  if (fADNresult == NULL) 
  {
      perror("FOPEN ERROR ");
      fclose(fADNresult);
   }
   
   fprintf(fADNresult,"******************************************************************\n" );
   fprintf(fADNresult,"***********  Fichero Resultado Tabla de frecuencias****************** \n");
   fprintf(fADNresult,"******* ****** Fecha: %s  **********\n",fecha );
   fprintf(fADNresult,"*************************************************\n\n\n" );
   fprintf(fADNresult,"*Combinación - Frecuencia*\n");
   int i =0;
   
   //Volcar tabla de frecuencias
   for (i =0; i < (pow(4,k));i++){
     fprintf(fADNresult,"%d  %d\n",i,tablafrec[i] );
   }
   fclose (fADNresult);
}

