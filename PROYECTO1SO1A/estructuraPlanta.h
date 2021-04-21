/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estructuraPlanta.h
 * Author: Esmeralda
 *
 * Created on 24 de marzo de 2021, 13:54
 */

#ifndef ESTRUCTURAPLANTA_H
#define ESTRUCTURAPLANTA_H

#include <unistd.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <wait.h>




void mostrarPlantas(char *numeroPlanta);
void imprimirArbol(int numeroProceso);



//constantes
#define RESET_COLOR    "\x1b[0m"
#define NEGRO_T        "\x1b[30m"
#define NEGRO_F        "\x1b[40m"
#define ROJO_T     "\x1b[31m"
#define ROJO_F     "\x1b[41m"
#define VERDE_T        "\x1b[32m"
#define VERDE_F        "\x1b[42m"
#define AMARILLO_T "\x1b[33m"
#define    AMARILLO_F  "\x1b[43m"
#define AZUL_T     "\x1b[34m"
#define    AZUL_F      "\x1b[44m"
#define MAGENTA_T  "\x1b[35m"
#define MAGENTA_F  "\x1b[45m"
#define CYAN_T     "\x1b[36m"
#define CYAN_F     "\x1b[46m"
#define BLANCO_T   "\x1b[37m"
#define BLANCO_F   "\x1b[47m"

#define sizePlantas 10

struct hoja {
    int pidHoja;
};

struct rama {
    struct hoja arregloHojas[10];
    int pidRama;
};



struct planta {
    struct rama arregloRamas[5];
    int pidPlanta;
    int idPlanta;
    int cantidadRamas;
    int cantidadHojas;
};



//Creacion de planta
struct planta arregloPlantas[10];

void crearPlanta(char *numeroPlanta) {
    int numero = atoi(numeroPlanta);
    //    printf("\n el id de la planta es %d ", numero);

    struct planta plantaNueva;
    plantaNueva.idPlanta = numero;

    //antes de agregar la planta al arregloPlantas asegurarse que no exista una planta con el mismo ID
    for (int i = 0; i < sizePlantas; i++) {
        if (arregloPlantas[i].idPlanta == 0) {
            //si el espacio es vacio (-1) agregamos la planta
            //          printf("\n Se agrego una nueva planta");
            arregloPlantas[i] = plantaNueva;
            printf(" %d", arregloPlantas[i].idPlanta);

            break;
        } else {
            //es un espacio ocupado
            if (arregloPlantas[i].idPlanta == numero) {//si la planta existe entonces ya no se agrega
                // printf("Ya existe la planta con el id %d", numero);
                break;
            } else {
                //continua verificando los siguientes espacios
            }
        }
    }
}

void mostrarPlantas(char *numeroPlanta) {
        int numero = atoi(numeroPlanta);

    for (int i = 0; i < sizePlantas; i++) {
        if (arregloPlantas[i].idPlanta != 0) { //-1 es una planta no creada
            printf(RESET_COLOR);
            if(arregloPlantas[i].idPlanta == numero){
                printf("\n\n PLANTA: %d RAMAS: %d HOJAS: %d", arregloPlantas[i].idPlanta, arregloPlantas[i].cantidadRamas, arregloPlantas[i].cantidadHojas);

                for (int j = 0; j < arregloPlantas[i].cantidadRamas; j++) {
                    printf(AMARILLO_T "\n\t || ");
                    printf(AZUL_T "\n\t   ===");
                    for (int k = 0; k < arregloPlantas[i].cantidadHojas; k++) {
                        printf(VERDE_T "$");
                    }
                    printf(AMARILLO_T "\n\t ||");
                }
            }
        } else {
            //espacio vacion, no mostramos nada
        }
    }
}

void imprimirPlantas(char *numeroPlanta){
   int numero = atoi(numeroPlanta);

    for (int i = 0; i < sizePlantas; i++) {
        if (arregloPlantas[i].idPlanta != 0) { //-1 es una planta no creada
            if(arregloPlantas[i].idPlanta == numero){
                printf("\n\n PLANTA: %d RAMAS: %d HOJAS: %d", arregloPlantas[i].idPlanta, arregloPlantas[i].cantidadRamas, arregloPlantas[i].cantidadHojas);
                int ramas = arregloPlantas[i].cantidadRamas;
                int hojas=  arregloPlantas[i].cantidadHojas;
    pid_t pid;
                //en caso de solo ser la planta se imprime el arbol 
            if(ramas == 0){
                pid = fork();
                if (pid) {//planta
                    printf("\n  #Planta %d", getpid());
                    int numeroP = getpid();
                    imprimirArbol(numeroP);
                }else{}
            }else{
            }
    int x, y;

    for (x = 1; x <= ramas; x++) {
        pid = fork();
        if (pid) {//planta
            printf("\n  #Planta %d", getpid());
            sleep(3);

        } else {
            printf("\n      #Rama %d de la planta %d", getpid(),getppid());
            for (y = 1; y <= hojas; y++) {
                pid = fork();
                if (pid) {//rama
                } else {//hoja
                        printf("\n          #Hoja %d de la rama %d", getpid(), getppid());
                    exit(0);
                }
            }
            int numeroPR = getppid();
            imprimirArbol( numeroPR);
            exit(0);
        }
    }
                }
        } else {
            //espacio vacion, no mostramos nada
        }
    }

}
void imprimirArbol(int numeroProceso){
            char texto1[] = "pstree -snp ";
            char texto2[10];
            sprintf(texto2, "%d", numeroProceso);
            strcat(texto1, texto2); 
            system(texto1);
        //printf("la cadena es %s ",cadena);
/*
FILE *fichero;
//  int numeros[TAM] = {20, 20, 20, 20, 20, 20};
int TAM=20;
  char nombre_fichero[] = "arboles.txt";
  //Esta variable irá recogiendo los resultados de lectura/escritura
  size_t resultado;

  // Abrimos para escritura en bloque
  fichero = fopen(nombre_fichero, "at");
  if (fichero == NULL)
  {
	  printf("El fichero no se ha podido abrir para escritura.\n");
	  return -1;
  }
  // Se escribe en bloque los elementos del vector.
  resultado = fwrite(system(texto1), sizeof(int), TAM, fichero);
  if (resultado!=TAM)
  {
	  printf("No se han escrito todos los %d números del array.\n", TAM);
  }

  if (fclose(fichero)!=0)
  {
    printf("No se ha podido cerrar el fichero.\n");
	return -1;
  }*/

}


void recrearPlantaYRama(int numeroPlanta, int numeroRama) {
    for (int i = 0; i < sizePlantas; i++) {
        if (arregloPlantas[i].idPlanta == numeroPlanta) {
            //encontramos la planta
            //ahora se procede a recrear la cantidad de ramas
            arregloPlantas[i].cantidadRamas = numeroRama;
            //el numero de hojas no nos interesa
        } else {
            //espacio vacion, no mostramos nada
        }
    }
}

void recrearPlantaRamasYHojas(int numeroPlanta, int numeroRama, int numeroHojas) {
    for (int i = 0; i < sizePlantas; i++) {
        if (arregloPlantas[i].idPlanta == numeroPlanta) {
            //encontramos la planta
            //ahora se procede a recrear la cantidad de ramas
            arregloPlantas[i].cantidadRamas = numeroRama;
            arregloPlantas[i].cantidadHojas = numeroHojas;
            //el numero de hojas no nos interesa
        } else {
            //espacio vacion, no mostramos nada
        }
    }
}

pid_t crearProcesoSuelo() {
    //generamos un proceso para la planta y guardamos el pid
    pid_t pid;
    pid_t idRetornar = 0;

    if ((pid = fork()) == 0) { /* hijo */
        printf("\nSoy el hijo (%d, hijo de %d)\n", getpid(),
                getppid());
        idRetornar = getpid();
    } else { /* padre */
        printf("\nSoy el padre (%d, hijo de %d)\n", getpid(),
                getppid());
        // exit(0);
    }
    return idRetornar;
}

void crearProcesoHijo(pid_t pidPadre) {
    if ((pidPadre = fork()) == 0) { /* hijo */
        printf("\nSoy el hijo (%d, hijo de %d)\n", getpid(),
                getppid());
        //  exit(0);
    } else { /* padre */
        printf("\nSoy el padre (%d, hijo de %d)\n", getpid(),
        getppid());
        wait(0);

    }
}

#endif /* ESTRUCTURAPLANTA_H */


