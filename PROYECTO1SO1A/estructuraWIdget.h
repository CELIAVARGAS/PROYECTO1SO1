/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estructuraWIdget.h
 * Author: Esmeralda
 *
 * Created on 7 de abril de 2021, 16:33
 */

#ifndef ESTRUCTURAWIDGET_H
#define ESTRUCTURAWIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuraPlanta.h"
#include <sys/types.h>
#include <unistd.h>
#include<stdbool.h>// Booleanos
#include <gtk/gtk.h>
#include <gtk-2.0/gtk/gtkentry.h>
void analisisLinea(char cadena[]);

struct login_window {
    GtkEntry *e1; //textbox1
};
typedef struct login_window widgets;

void on_proyecto1so1_destroy() {
    gtk_main_quit();
}

typedef struct {
    GtkEntry *entrada;      
    GtkWidget *salida;       
    GtkTextBuffer *bufferT;     
} app_widgets;

 void on_boton_clicked(GtkButton *button, widgets *widg) {
     char ch1[21];
    //getting text from the text boxes
    const gchar *text1 = gtk_entry_get_text(widg->e1);

    //copying the text of textbox into an array
    strcpy(ch1, text1);
    printf("\n Pintando planta");
    printf("\n%s",ch1);
    analisisLinea(ch1);
                    
}




#endif /* ESTRUCTURAWIDGET_H */

