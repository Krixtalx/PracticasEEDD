#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include "VDinamico.h"

using namespace std;

void mostrarVDinInt(VDinamico<int> &vD){
    cout << "tamF: " << vD.getTamF() << " tamL:" << vD.getTamL() << endl;
    for (int i = 0; i < vD.getTamL(); i++) {
        cout << vD[i] << " - ";
    }
    cout <<endl;
}


int main(int argc, char** argv) {
    try{
        VDinamico<int> test(5);

        srand(time(NULL));
        for (int i = 0; i < 5; i++) {
            test[i] = (rand() % 100);
        }
        mostrarVDinInt(test);

        int illoPosUnIntRandomQueMeHeInventaoJaJaEkisde = 1;
        test.insertarDato(illoPosUnIntRandomQueMeHeInventaoJaJaEkisde, 3);
        test.insertarDato(34, 4);
        mostrarVDinInt(test);

        test.eliminarDato(3);
        mostrarVDinInt(test);    

        int o = 11;
        test.insertarDato(o).insertarDato(o);
        mostrarVDinInt(test);
        test.eliminarDato(0);
        mostrarVDinInt(test);
    }catch(std::out_of_range e){
        cerr<<e.what();
    }
    return 0;
}

    
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
    