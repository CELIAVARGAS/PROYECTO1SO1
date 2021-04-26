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
int imprimirPlantas(char *numeroPlanta);



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

void mostrarArbolTotal() {
    FILE *fp;
    fp = fopen("impresion.txt", "at");
    if (fp == NULL) {
        fputs("File error", stderr);
        exit(1);
    } else {
        for (int i = 0; i < 10; i++) {
            if (arregloPlantas[i].idPlanta != 0) { //-1 es una planta no creada
                if (arregloPlantas[i].pidPlanta != 0) {
                    //printf("\n\n PLANTA %d ", arregloPlantas[i].idPlanta);
                    //printf("\n Planta: %d Ramas: %d Hojas: %d", arregloPlantas[i].idPlanta, arregloPlantas[i].cantidadRamas, arregloPlantas[i].cantidadHojas);
                    int planta = arregloPlantas[i].pidPlanta;
                    //printf("\n es la planta %d ", planta);

                    char cadena[] = "\n\n#########################################\n";
                    fputs(cadena, fp);
                    char textoP[] = "\nID DE LA PLANTA A MOSTRAR:  ";
                    char textoP1[50];
                    sprintf(textoP1, "%d", arregloPlantas[i].idPlanta);
                    strcat(textoP, textoP1);
                    fputs(textoP, fp);

                    char textoRamas[] = " RAMAS:  ";
                    char textoRamas1[50];
                    sprintf(textoRamas1, "%d", arregloPlantas[i].cantidadRamas);
                    strcat(textoRamas, textoRamas1);
                    fputs(textoRamas, fp);

                    char textoHojas[] = " HOJAS:  ";
                    char textoHojas1[50];
                    sprintf(textoHojas1, "%d", arregloPlantas[i].cantidadHojas);
                    strcat(textoHojas, textoHojas1);
                    fputs(textoHojas, fp);

                    char textoIP[] = "\n   PID PLANTA:  ";
                    char textoIP2[50];
                    sprintf(textoIP2, "%d", planta);
                    strcat(textoIP, textoIP2);
                    fputs(textoIP, fp);


                    //verificar cantidad de ramas
                    if (arregloPlantas[i].cantidadRamas == 0) {
                    } else {
                        for (int j = 0; j < 5; j++) {
                            if (arregloPlantas[i].arregloRamas[j].pidRama == 0) {
                            } else {
                                int rama = arregloPlantas[i].arregloRamas[j].pidRama;
                                //printf("\n      es la rama %d ", rama);

                                char textoIR[] = "\n      PID RAMA:  ";
                                char textoIR2[50];
                                sprintf(textoIR2, "%d", rama);
                                strcat(textoIR, textoIR2);
                                fputs(textoIR, fp);

                                //verificar cantidad de hojas
                                if (arregloPlantas[i].cantidadHojas == 0) {
                                } else {
                                    for (int k = 0; k < 10; k++) {
                                        if (arregloPlantas[i].arregloRamas[j].arregloHojas[k].pidHoja == 0) {
                                        } else {
                                            int hoja = arregloPlantas[i].arregloRamas[j].arregloHojas[k].pidHoja;
                                            //("\n          es la hoja %d ", hoja);
                                            char textoIH[] = "\n          PID HOJA:  ";
                                            char textoIH2[50];
                                            sprintf(textoIH2, "%d", hoja);
                                            strcat(textoIH, textoIH2);
                                            fputs(textoIH, fp);

                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                }

            } else {
                //espacio vacion, no mostramos nada
            }
        }
    }
    fclose(fp);
}

void mostrarPlantas(char *numeroPlanta) {
    int numero = atoi(numeroPlanta);

    for (int i = 0; i < sizePlantas; i++) {
        if (arregloPlantas[i].idPlanta != 0) { //-1 es una planta no creada
            printf(RESET_COLOR);
            if (arregloPlantas[i].idPlanta == numero) {
                printf("\n\n PLANTA: %d RAMAS: %d HOJAS: %d", arregloPlantas[i].idPlanta, arregloPlantas[i].cantidadRamas, arregloPlantas[i].cantidadHojas);

                if (arregloPlantas[i].cantidadRamas == 0) {
                    printf(AMARILLO_T "\n\t || ");
                } else {
                    for (int j = 0; j < arregloPlantas[i].cantidadRamas; j++) {
                        printf(AMARILLO_T "\n\t || ");
                        printf(AZUL_T "\n\t   ===");
                        for (int k = 0; k < arregloPlantas[i].cantidadHojas; k++) {
                            printf(VERDE_T "$");
                        }
                        printf(AMARILLO_T "\n\t ||");
                    }
                }
            }
        } else {
            //espacio vacion, no mostramos nada
        }
    }


}

int imprimirPlantas(char *numeroPlanta) {
    int numero = atoi(numeroPlanta);

    for (int i = 0; i < sizePlantas; i++) {
        if (arregloPlantas[i].idPlanta > 0) { //-1 es una planta no creada
            if (arregloPlantas[i].idPlanta == numero) {
                int cantidadR = arregloPlantas[i].cantidadRamas;
                int cantidadH = arregloPlantas[i].cantidadHojas;
                int cantidadRamasOriginal = arregloPlantas[i].cantidadRamas;
                int cantidadHojasOriginal = arregloPlantas[i].cantidadHojas;
                pid_t pid1, pid2, pidG, pid3;
                int status1, status2, statusG, status3;

                printf("\n\n PLANTA: %d RAMAS: %d HOJAS: %d", arregloPlantas[i].idPlanta, cantidadR, cantidadH);


                if ((pidG = fork()) == 0) { /* PLANTA  */
                    if (cantidadRamasOriginal == 0) {
                        printf("\n Soy la planta  (%d, hija de %d)\n", getpid(), getppid());
                        int numeroPR = getpid();
                        arregloPlantas[i].pidPlanta = numeroPR;
                        imprimirArbol(numeroPR);
                    } else {
                    }
                    return 0;
                } else { /* padre */
                    if ((pid1 = fork()) == 0) { /* planta */
                        printf("\n Soy  la planta (%d, hija de %d)\n", getpid(), getppid());
                        int numeroPR = getpid();
                        arregloPlantas[i].pidPlanta = numeroPR;

                        for (int b = 0; b < cantidadR; b++) { //ramas
                            struct rama ramaPlanta;

                            if ((pid2 = fork()) == 0) { /* rama */
                                int numeroR1 = getpid();
                                ramaPlanta.pidRama = numeroR1;
                                arregloPlantas[i].arregloRamas[cantidadR] = ramaPlanta;

                                if (cantidadHojasOriginal == 0) {
                                    printf("\nSoy la rama    (%d, hijo de %d)\n", getpid(), getppid());
                                    imprimirArbol(numeroR1);
                                } else {
                                    printf("\nSoy la rama (%d, hijo de %d)\n", getpid(), getppid());

                                    for (int c = 0; c < cantidadH; c++) { //rama
                                        struct hoja hojaRama;
                                        if ((pid3 = fork()) == 0) { /* hoja */
                                            //                    sleep(1);
                                            printf("\n Soy la hoja (%d, hijo de %d)\n", getpid(), getppid());
                                            int numeroH = getpid();
                                            hojaRama.pidHoja = numeroH;
                                            arregloPlantas[i].arregloRamas[cantidadR].arregloHojas[cantidadH] = hojaRama;
                                            imprimirArbol(numeroH);
                                            return 0;
                                        } else { /*  rama */
                                            waitpid(pid3, &status3, 0);
                                            //    printf("\n Soy la rama   (%d, hija de %d)\n", getpid(), getppid());
                                        }
                                    }
                                }
                                return 0;
                            } else { /*  planta */
                                waitpid(pid2, &status2, 0);
                                //printf("Soy la planta   (%d, hija de %d)\n", getpid(), getppid());
                            }
                        }
                        return 0;
                    } else { /*  suelo */
                        // printf("Soy el suelo  (%d, hija de %d)\n", getpid(), getppid());
                        waitpid(pid1, &status1, 0);
                    }//suelo
                    waitpid(pidG, &statusG, 0);
                }
                printf("Soy el suelo (%d, hijo de %d)\n", getpid(), getppid());
                break;
            }
        } else {
        }
    }
    return 0;
}

void imprimirArbol(int numeroProceso) {

    char texto1[] = "pstree -snp ";
    char texto2[40];
    char texto3[] = " >> impresion2.txt";
    sprintf(texto2, "%d", numeroProceso);
    strcat(texto2, texto3);
    strcat(texto1, texto2);

    //   printf("la cadena es %s", texto1);
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


