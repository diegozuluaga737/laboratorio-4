#include <iostream>
#include "funciones.h"
using namespace std;

int main()
{
    short opc = 0,costo=0;
    red *network = new red;
    string nombre,nombre2;
    cout << "Ingrese:\n1.Ver tabla de la red.\n2.Ver tabla de un enrutador.\n3.Agregar enrutador.\n";
    cout << "4.Eliminar enrutador de la red.\n5.Conectar 2 enrutadores.\n6.Desconectar 2 enrutadores.\n";
    cout << "7.Conocer costo de envio.\n8.Camino a seguir de un paquete.\n";
    cout << "9.Cargar red desde un archivo.\n10.Generar red aleatoria.\n";
    cout << "0.Salir.\nSeleccione una opcion: ";cin >> opc;
    while(opc!=0){
        switch (opc) {
        case 1:{
            map<string, int> tabla;
            map<string, int>::iterator it;
            list<enrutador> lista;
            lista = network->getN_enrutadores();
            for(auto i=lista.begin();i!=lista.end();i++){
                tabla = i->getConexiones();
                cout << i->getNombre() << ":" << endl;
                for(it=tabla.begin();it!=tabla.end();it++){
                    cout << it->first << ": " << it->second << endl;
                }
                cout << endl;
            }
        }
            break;
        case 2:{
            cin.ignore(10000,'\n');
            cout <<"Nombre del enrutador: ";getline(cin,nombre);
            if(network->comprobar_Enrutador(nombre)){
                cout << "Tabla de conexiones: " << endl;
                cout << "\"Si el valor es -1 los enrutadores no se encunentran conectados directamente.\"\n";
                cout << endl;
                network->TablaConexionesEnrutador(nombre);
                cout << "\nTabla de costos: \n" << endl;
                network->TablaCostosEnrutador(nombre);
            }
            else
                cout << "El enrutador no existe.\n";
        }
            break;
        case 3:{
            cin.ignore(10000,'\n');
            cout <<"Nombre del enrutador: ";getline(cin,nombre);
            if(network->comprobar_Enrutador(nombre))
                cout << "EL enrutador \"" << nombre << "\" ya existe.\n";
            else{
                network->agregar_Enrutador(nombre);
                network->ActualizarTabla();
            }
        }
            break;
        case 4:{
            cin.ignore(10000,'\n');
            cout <<"Nombre del enrutador: ";getline(cin,nombre);
            if(network->comprobar_Enrutador(nombre)){
                network->eliminar_Enrutador(nombre);
                network->ActualizarTabla();
            }
            else
                cout << "EL enrutaodor \"" << nombre << "\" no existe.\n";
        }
            break;
        case 5:{
            cin.ignore(10000,'\n');
            cout << "Nombre del primer enrutador: ";getline(cin,nombre);
            cout << "Nombre del segundo enrutador: ";getline(cin,nombre2);
            cout << "costo de de envio: ";cin>>costo;
            if(costo<=0)
                cout << "El costo de envio no puede ser menor o igual a 0.\n";
            else if(network->comprobar_Enrutador(nombre) and network->comprobar_Enrutador(nombre2)){
                network->Conectar2Enrutadores(nombre,nombre2,costo);
                network->ActualizarTabla();
            }
            else
                cout << "Uno o ambos enrutados no existen.\n";
        }
            break;
        case 6:{

        }
            break;
        case 7:{

        }
            break;
        case 8:{

        }
            break;
        case 9:{

        }
            break;
        case 10:{

        }
            break;
        default:
            cout << "Opcion no valida.\n";
        }
        cout << "\nIngrese:\n1.Ver tabla de la red.\n2.Ver tabla de un enrutador.\n3.Agregar enrutador.\n";
        cout << "4.Eliminar enrutador de la red.\n5.Conectar 2 enrutadores.\n6.Conocer costo de envio.\n";
        cout << "7.Camino a seguir de un paquete.\n8.Cargar red desde un archivo.\n9.Generar red aleatoria.\n";
        cout << "0.Salir.\nSeleccione una opcion: ";cin >> opc;
    }

    delete network;
    return 0;
}
