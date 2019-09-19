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

    VDinamico<int> a(5);
    int xd;
    for (int i = 0; i < 5; i++) {
        xd = rand() % 100;
        a[i] = xd;
    }
    cout << a[0] << "-" << a[1] << "-" << a[2] << "-" << a[3] << "-" << a[4] << endl;
    a.eliminarDato(2);
    cout << a[0] << "-" << a[1] << "-" << a[2] << "-" << a[3] << "-" << a[4] << endl;



    return 0;
}

