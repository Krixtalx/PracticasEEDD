/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jcfer
 *
 * Created on 18 September 2019, 18:03
 */

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include "VDinamico.h"

using namespace std;

void mostrarVDinInt(VDinamico<int> &vD){
    cout << "tamF: " << vD.getTamF() << " tamL:" << vD.getTamL() << endl;
    for (int i = 0; i < vD.getTamL(); i++) {
        cout << vD[i] << endl;
    }
}


int main(int argc, char** argv) {

    VDinamico<int> a(5);

    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        a[i] = rand() % 100;
    }
    mostrarVDinInt(a);
    
    int illoPosUnIntRandomQueMeHeInventaoJaJaEkisde = 1;
    a.insertarDato(illoPosUnIntRandomQueMeHeInventaoJaJaEkisde, 3);
    mostrarVDinInt(a);
    
    a.eliminarDato(3);
    mostrarVDinInt(a);    
    
//    cout << "    OOOOOOOOOO    " << endl <<
//            "  OOOOOOOOOOOOOO  " << endl << 
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "  OOOOOOOOOOOOOO  " << endl <<
//            "    OOOOOOOOOO    " << endl << endl <<
//            "WW      WW      WW" << endl <<
//            " WW    WWWW    WW " << endl <<
//            "  WW  WW  WW  WW  " << endl <<
//            "   WWWW    WWWW   " << endl <<
//            "    WW      WW    " << endl << endl <<
//            "    OOOOOOOOOO    " << endl <<
//            "  OOOOOOOOOOOOOO  " << endl << 
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "OOOO          OOOO" << endl <<
//            "  OOOOOOOOOOOOOO  " << endl <<
//            "    OOOOOOOOOO    " << endl;
    
    int o = 11;
    a.insertarDato(o).insertarDato(o).insertarDato(o).insertarDato(o);
    mostrarVDinInt(a);
    a.eliminarDato(0).eliminarDato(0).eliminarDato(0).eliminarDato(0).eliminarDato(0);
    mostrarVDinInt(a);
    
    return 0;
}

