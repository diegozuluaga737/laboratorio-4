#include <iostream>
#include "funciones.h"
using namespace std;

int main()
{
    short opc = 0;
    red *network = new red;
    enrutador *router = new enrutador;
    string nombre;
    cout << "Ingrese:\n1.Agregar enrutador a la red.\n2.Quitar enrutador de la red.\n";

    cout << "0.Salir.\nSeleccione una opcion: ";cin >> opc;
    while(opc!=0){
        switch (opc) {
        case 1:{
            cin.ignore(10000,'\n');
            cout <<"Nombre del enrutaodor: ";getline(cin,nombre);
            if(network->comprobar_Enrutador(nombre))
                cout << "EL enrutaodor " << nombre << " ya existe.\n";
            else
                network->agregar_Enrutador(nombre);
        }
            break;
        case 2:{

        }
            break;
        case 3:{

        }
            break;
        default:
            cout << "Opcion no valida.\n";
        }
        cout << "Ingrese:\n1.Agregar enrutador a la red.\n2.Quitar enrutador de la red.\n";

        cout << "0.Salir.\nSeleccione una opcion: ";cin >> opc;
    }
    vector<enrutador> lista;
    lista = network->getN_enrutadores();
    for(auto p=lista.begin();p!=lista.end();p++){
        cout << p->getNombre() << endl;
    }
    delete network;
    delete router;
    return 0;
}
