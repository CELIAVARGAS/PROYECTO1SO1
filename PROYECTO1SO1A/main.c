
/* 
 * File:   main.c
 * Author: Esmeralda
 *
 * Created on 23 de marzo de 2021, 17:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuraPlanta.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>// Booleanos
#include "estructuraWIdget.h"
#include <gtk/gtk.h>
#include "estructuraPlanta.h"


#include <gtk-2.0/gtk/gtkentry.h>

/*
 * 
 */
//#####################################---FUNCIONES/PROCESOS---###################################################################
//METODOS EN MAIN
void lecturaArchivoTexto();
void operacionPlanta2Posiciones(char *operacion, char *idPlanta);
void operacionPLanta3Posiciones(char* operacion, char* idPlanta, char* cantidadRamas);
void operacionPLanta4Posiciones(char* operacion, char* idPlanta, char* cantidadPlantas, char* cantidadRamas);
void solicitudInstrucciones();

//METODOS EN ESTRUCTURAPLANTA.H
void crearPlanta(char* numeroPlanta);
pid_t crearProcesoSuelo();
void crearProcesoHijo(pid_t pidPadre);
void recrearPlantaYRama(int numeroPlanta, int numeroRama);
void recrearPlantaRamasYHojas(int numeroPlanta, int numeroRama, int numeroHojas);

//METODOS DE ESTRUCTURAWIDGET
void on_boton_clicked(GtkButton *button, widgets *widg);
void on_proyecto1so1_destroy();

// variables
pid_t procesoPadre;
char cadena[21]; //max de caracteres en una linea
bool estaEnModoGrafico = false;


//########################################---OPERACIONES DE MAIN---#########################################################################

void lecturaArchivoTexto() { ///metodo para leer el archivo de texto con instrucciones
    FILE *archivo;


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
    //printf("\n\n la cadena es %s", str);
    //  evaluamos la cadena
    /* 
     * (P,1,2,3) 
     * pos 0 ( 
     *  pos 1 INSTRUCCION
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

    char delim[] = "(,)\n\b";

    char *ptr = strtok(str, delim);
    int i = 0;
    char *instruccion;
    char *numeroPlanta;
    char *numeroRamas;
    char *numeroHojas;

    while (ptr != NULL) {
        i++;
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
        //verificar si es crear mostrar o imprimir
        operacionPlanta2Posiciones(instruccion, numeroPlanta);
    }
    if (i == 3) {
        //recrear planta
        operacionPLanta3Posiciones(instruccion, numeroPlanta, numeroRamas);
    }
    if (i == 4) {
        operacionPLanta4Posiciones(instruccion, numeroPlanta, numeroRamas, numeroHojas);
    } else {
        //la linea es incorrecta puede tener mas o menos parametros.
    }
}

void operacionPlanta2Posiciones(char *operacion, char *idPlanta) {
    //puede ser crear , mostrar o imprimir.
    //clasificamos la operacion 

    switch (*operacion) {
        case 80: //en caso de ser P o p se creara la planta
            //           printf("es un P");
            crearPlanta(idPlanta);
            break;
        case 112:
            //        printf("es un p");
            crearPlanta(idPlanta);
            break;
        case 73: //en caso de ser I o i imprimira ambos casos
            //         printf("es un I");
             imprimirPlantas(idPlanta);
            break;
        case 105:
            //         printf("es un i");
             imprimirPlantas(idPlanta);
            break;
        case 77: //en caso de ser M o m
            //        printf("es un M");
            if (estaEnModoGrafico == true) { //dibujamos la planta
                mostrarPlantas(idPlanta);
           
            } else {//no muestra nada esta en modo texto
            }
            break;
        case 109:
            //       printf("es un m");
            if (estaEnModoGrafico == true) { //dibujamos la planta
                mostrarPlantas(idPlanta);
            } else {//no muestra nada esta en modo texto
            }
            break;
        default:
            //      printf("no es ninguna instruccion de dos posiciones");
            break;
    }

}

void operacionPLanta3Posiciones(char *operacion, char *idPlanta, char *cantidadRamas) {
    //si la rama tiene x hojas se seguira con cantidad de hojas , lo que se modifica es la cantidad de ramas
    int numeroPlantaABuscar = 0;
    int numeroRama = 0;
    //obtenermos el int de los caracteres
    numeroPlantaABuscar = atoi(idPlanta);
    numeroRama = atoi(cantidadRamas);
    switch (*operacion) {
        case 80: // Instruccion -> P
            //procedemos a recrear la planta
            recrearPlantaYRama(numeroPlantaABuscar, numeroRama);
            break;
        case 112: // Instruccion -> p
            //procedemos a recrear la planta
            recrearPlantaYRama(numeroPlantaABuscar, numeroRama);
            break;
        default:
            //      printf("no es ninguna instruccion de tres posiciones");
            break;
    }
}

void operacionPLanta4Posiciones(char *operacion, char *idPlanta, char *cantidadRamas, char *cantidadHOjas) {
    //define la planta con ramas y cantidad de hojas, reescribe la planta completamente
    int numeroPlantaABuscar = 0;
    int numeroRamas = 0;
    int numeroHojas = 0;
    //obtenermos el int de los caracteres
    numeroPlantaABuscar = atoi(idPlanta);
    numeroRamas = atoi(cantidadRamas);
    numeroHojas = atoi(cantidadHOjas);
    switch (*operacion) {
        case 80: // Instruccion -> P
            //procedemos a recrear la planta
            recrearPlantaRamasYHojas(numeroPlantaABuscar, numeroRamas, numeroHojas);
            break;
        case 112://  Instruccion -> p
            //procedemos a recrear la planta
            recrearPlantaRamasYHojas(numeroPlantaABuscar, numeroRamas, numeroHojas);
            break;
        default:
            //      printf("no es ninguna instruccion de tres posiciones");
            break;
    }
}

void solicitudInstrucciones() {
    do {
        printf("\n\n Ingrese instruccion ----- Para salir 's' ----- ");
        scanf("\n %[^\n]", cadena);
        analisisLinea(cadena);
    } while (*cadena != 's');

}

int main(int argc, char *argv[]) {
    int opcion;
    //creamos un arreglo de plantas para ir agregando cada planta que creamos.

    printf("\n###############################  BIENVENIDO ####################################");
    do {
        printf(RESET_COLOR);
        printf("\n Seleccione una opcion");
        printf("\n   1. Modo interactivo.");
        printf("\n   2. Modo texto.");
        printf("\n   3. Salir.");
        printf("\n\n   Introduzca opcion (1-3): ");

        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                printf(AZUL_T);
                printf("\n######################################################## MODO INTERACTIVO ######################################################## ");
                estaEnModoGrafico = true;

                GtkBuilder *builder;
                GtkWidget *window;
                widgets widg;


                gtk_init(&argc, &argv);
                builder = gtk_builder_new_from_file("proyecto1so1.glade");

                window = GTK_WIDGET(gtk_builder_get_object(builder, "proyecto1so1"));
                widg.e1 = GTK_ENTRY(gtk_builder_get_object(builder, "entrada"));
   
                gtk_builder_connect_signals(builder, &widg);

                g_object_unref(G_OBJECT(builder));

                gtk_widget_show(window);
                gtk_main();
                //                mostrarVentanaModoGrafico();
                break;

            case 2: printf("\n---------------- MODO TEXTO: ---------------------- ");
                estaEnModoGrafico = false;
                lecturaArchivoTexto();
                break;
            default: break;
        }

    } while (opcion != 3);

    return 0;
}

