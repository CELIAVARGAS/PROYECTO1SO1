/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Esmeralda
 *
 * Created on 23 de marzo de 2021, 17:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <estructuraPlanta.h>
/*
 * 
 */
void lecturaArchivoTexto();
void analisisLinea(char cadena[]);

void lecturaArchivoTexto() { ///metodo para leer el archivo de texto con instrucciones
    FILE *archivo;

    char cadena[21]; //max de caracteres en una linea

    archivo = fopen("instrucciones.txt", "r"); //lleva r para abrir en archivo y leer, debe existir

    if (archivo == NULL)
        printf("\n-->Error no existe el archivo de para analizar instrucciones \n\n");
    else {
        printf("\nEl contenido del archivo de prueba es \n\n");
        while (feof(archivo) == 0) {
            fgets(cadena, 100, archivo);
            analisisLinea(cadena);
        }
    }
    fclose(archivo);

}

void analisisLinea(char str[]) {
    printf("\n la cadena es %s", str);
    //  evaluamos la cadena
    /* 
     * (P,1,2,3) 
     * pos 0 ( 
     *  pos 1 INSTRUCCION4
     *  Pos 2 coma
     *  pos 3  #planta
     *  de 4 en adelante es opcional
     * 4 coma
     * 5 ramas
     * 6 coma
     * 7 hojas
     * 8 )
     * 
     */

    //Determinamos size de la cadena 
    //creamos un ciclo para evaluar cada posicion de la cadena

    int init_size = strlen(str);
    char delim[] = "(,)\n\b";

    char *ptr = strtok(str, delim);
    int i = 0;
    char *instruccion;
    char *numeroPlanta;
    char *numeroRamas;
    char *numeroHojas;

    while (ptr != NULL) {
        i++;
        //        printf("-> cadena %s \n", ptr);
        //      printf("-> iteracion %d \n", i);
        switch (i) {
            case 1:
                //instruccion
                instruccion = ptr;
                break;
            case 2:
                //planta
                numeroPlanta = ptr;
                break;
            case 3:
                //ramas
                if (ptr == NULL) {
                } else {
                    numeroRamas = ptr;
                }
                break;
            case 4:
                //hojas
                if (ptr == NULL) {
                } else {
                    numeroHojas = ptr;
                }
                break;
            default: break;
        }
        ptr = strtok(NULL, delim);
    }
//    printf("\n%d", i);
    if (i == 2) {
        printf("\n La instruccion es %s", instruccion);
        printf("\n  La planta es %s", numeroPlanta);
        //verificar si es crear mostrar o imprimir
    }
    if (i == 3) {
        printf(" La instruccion es %s", instruccion);
        printf("\n  La planta es %s", numeroPlanta);
        printf("\n  La rama es %s", numeroRamas);
        //recrear planta
    }
    if (i == 4) {
        printf(" La instruccion es %s", instruccion);
        printf("\n  La planta es %s", numeroPlanta);
        printf("\n  La rama es %s", numeroRamas);
        printf("\n  La hoja es %s", numeroHojas);
        //
    } else {
    }
}

void operacionPlanta() {
    //puede ser crear , mostrar o imprimir.
    
}

int main(int argc, char** argv) {
    int n, opcion;
    printf("\n###############################  BIENVENIDO ####################################");
    do {
        printf("\n Seleccione una opcion");
        printf("\n   1. Modo interactivo.");
        printf("\n   2. Modo texto.");
        printf("\n   3. Salir.");
        printf("\n\n   Introduzca opcion (1-3): ");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1: printf("\n---------------- MODO INTERACTIVO -----------------");
                lecturaArchivoTexto();
                break;

            case 2: printf("\n---------------- MODO TEXTO: ---------------------- ");
                break;
        }

        /* Fin del anidamiento */

    } while (opcion != 3);

    return 0;
}
