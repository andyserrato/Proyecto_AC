/*
 * PROYECTO AC
 * 
 *    V 0.1
 *     Código casi completa falta meter a tabla de frecuencias
 * 
 * 
 * 
 */


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void escribirtablafrecuencias(int[], int);
    

  
int main(int argc, char *argv[]) 
{
     
    //Comprobación de los parámetros
   /* if (argc != 3)
    {
        printf("%s <Path complet del fichero a leer><Número de nucleotidos a realizar la prueba>\n", argv[0]);
        exit (0);
    }
    //Cargo el número de nucleotidos pasados por parámetro
    int k= atoi(argv[3]);*/
    
    //Recoger valores
    char filepath[40];
    int k;
    printf("Por favor introduzca el Path completo del fichero a leer: ");
    scanf("%s",&filepath);
    printf("%s\n", filepath);
    printf("Ahora introduzca el número de nucleotidos de cada secuencia:");
    scanf("%d",&k);
    printf("%d\n", k);
    //Abro el fichero para leer
    

    FILE *fADN;
	
    if ((fADN= fopen(filepath, "r"))==NULL) 
    {
        perror("FOPEN ERROR ");
        fclose(fADN);
        return -1;
    }
   
    
    //Declaro vector usado como registro, declaro tabla de frecuencias
    
    int *tablafrec;
    
    int and= pow(4,k);
    //!!!!!!!!!!!!!!!Declarar aqui la tabla de frecuencias como la queremos hacer
    if( (tablafrec = (int*)calloc (and, sizeof(int)))==NULL) {
    }
    int p;
    for (p =0; p< and; p++){
      tablafrec[p] = 0;
    }
    and -=4; 
    int i = 0;
    char nucle;
    int ventana =0; 
    while(!feof(fADN)){
      
  
	nucle= getc(fADN);
	  printf("%c\n",nucle);
	  if (nucle == 'A'){
	    ventana =ventana <<2;
	    ventana =ventana &and;
	    printf ("%d",ventana);
	    i++;
	  }
	  else if (nucle == 'C'){
	    
	    ventana =ventana <<2;
	    ventana=ventana &and;
	    
	    ventana =ventana | 1;
	    printf ("%d",ventana);
	    i++;
	  }
	  else if (nucle == 'G'){
	    ventana =ventana <<2;
	    ventana =ventana &and;
	    ventana =ventana | 2;
	    printf ("%d",ventana);
	    i++;
	  }
	  else if (nucle == 'T'){
	    ventana =ventana <<2;
	    ventana =ventana &and;
	    ventana =ventana | 3;
	    printf ("%d",ventana);
	    i++;
	  }
	  else if (nucle == 'N'){ // Pongo la comparación por si el fichero tiene retorno de carro que pase de él
	    i = 0; 
	  }
	  if( i == k){
	    printf ("escribir en la tabla");
	    tablafrec[ventana]++;
	    printf ("%d",ventana);
	    i =k-1;
	  }
	  
      
    //!!!!!!!!!!!!!!!Leer el vector y añadirlo en esa posición en la tabla
    }
    
    for (p =0; p< and+4;p++){
      printf ("%d\n",tablafrec[p]);
    }
    fclose(fADN);
    
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
