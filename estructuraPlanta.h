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

struct hoja{
    int pidHoja;
};

struct rama{
    struct hoja arregloHojas[10];
    int pidRama;
};

struct planta{
    struct rama arregloRamas[5];
    int pidPlanta;
    int numeroPlanta;
};


//CREACION DE NUEVA PLANTA
void crearPlanta();
void buscarPlantaExistente();

void crearPlanta()
{
    //creamos nueva planta. sin 
}
#endif /* ESTRUCTURAPLANTA_H */


