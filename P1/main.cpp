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

/*
 * 
 */
int main(int argc, char** argv) {

    VDinamico<int> a;
    int xd;
    for (int i = 0; i < 3; i++) {
        xd = rand() % 100;
        a.insertarDato(xd, i);
        cout << a.getTamF() << "-" << a.getTamL() << endl;
        cout << a[i] << endl;
    }




    return 0;
}

