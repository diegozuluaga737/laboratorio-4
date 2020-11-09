#include "red.h"

red::red()
{

}

red::~red()
{

}

list<enrutador> red::getN_enrutadores() const
{
    return n_enrutadores;
}

void red::setN_enrutadores(const list<enrutador> &value)
{
    n_enrutadores = value;
}

void red::agregar_Enrutador(const string &router_name)
{
    enrutador *router = new enrutador;
    router->setNombre(router_name);
    router->Conectar_Enrutador(router->getNombre(),0);
    n_enrutadores.push_back(*router);
    Conexiones_Iniciales(router->getNombre());

    delete router;
}

void red::Conexiones_Iniciales(const string &router_name)
{
    for(auto router1=n_enrutadores.begin();router1!=n_enrutadores.end();router1++){
        if(router1->getNombre()==router_name){
            for(auto router2=n_enrutadores.begin();router2!=n_enrutadores.end();router2++){
                if(router1->getNombre()!=router2->getNombre()){
                    router1->Conectar_Enrutador(router2->getNombre(),-1);
                    router2->Conectar_Enrutador(router1->getNombre(),-1);
                }
            }
            break;
        }
    }
}

void red::eliminar_Enrutador(const string &router_name)
{
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()!=router_name)
            router->eliminar_Enrutador(router_name);
    }

    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==router_name){
            n_enrutadores.erase(router);
            break;
        }
    }
}

void red::Conectar2Enrutadores(const string &name1, const string &name2, int cost)
{
    for(auto router1=n_enrutadores.begin();router1!=n_enrutadores.end();router1++){
        if(router1->getNombre()==name1){
            for(auto router2=n_enrutadores.begin();router2!=n_enrutadores.end();router2++){
                if(router2  ->getNombre()==name2){
                    router1->Conectar_Enrutador(router2->getNombre(),cost);
                    router2->Conectar_Enrutador(router1->getNombre(),cost);
                }
            }
            break;
        }
    }
}

void red::Costo()
{

}

void red::MejorCamino()
{

}

bool red::comprobar_Enrutador(const string &router_name)
{
    for(auto it=n_enrutadores.begin();it!=n_enrutadores.end();it++){
        if(it->getNombre()==router_name) return true;
    }
    return false;
}

void red::AlgoritmoDijkstra(const string &nodoInicial)
{
    list<string> nodosVistos;
    string nodo = nodoInicial;
    int costo = 0, NoConectados = 0;
    NoConectados = NodosNoConectados();
    enrutador *router = new enrutador;
    //map<string,int> copy_conexiones;

    for(auto p=n_enrutadores.begin();p!=n_enrutadores.end();p++){
        if(p->getNombre()==nodoInicial){
            router->setNombre(p->getNombre());
            router->setConexiones(p->getConexiones());
            break;
        }
    }
    for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
        if(router->it->first==router->getNombre())
            router->Agregar_Conexion(router->getNombre(),"-",0);
        else if(router->it->second!=-1)
            router->Agregar_Conexion(router->it->first,router->getNombre(),router->it->second);
    }
    nodosVistos.push_back(nodo);
    while(true){
        //elegir el nodo de menor costo
        costo = 1000000000;
        for(router->it2=router->costoNodos.begin();router->it2!=router->costoNodos.end();router->it2++){
            if(find(nodosVistos.begin(),nodosVistos.end(),router->it2->first)==nodosVistos.end()){
                if(router->it2->second.first<costo){
                    costo = router->it2->second.first;
                    nodo = router->it2->first;
                }
            }
        }

        if(find(nodosVistos.begin(),nodosVistos.end(),nodo)!=nodosVistos.end())
            break;

        for(auto router2=n_enrutadores.begin();router2!=n_enrutadores.end();router2++){
            if(router2->getNombre()==nodo){
                for(router2->it=router2->conexiones.begin();router2->it!=router2->conexiones.end();router2->it++){
                    if(router2->it->first!=router->getNombre() and router2->it->second>0){
                        if(router->costoNodos.find(router2->it->first)==router->costoNodos.end()){
                            router->Agregar_Conexion(router2->it->first,router2->getNombre(),router2->it->second+costo);
                        }
                        else if(router2->it->second+costo < router->costoNodos.find(router2->it->first)->second.first){
                            router->Agregar_Conexion(router2->it->first,router2->getNombre(),router2->it->second+costo);
                        }
                    }
                }
                break;
            }
        }

        nodosVistos.push_back(nodo);
    }

    for(auto borrar=n_enrutadores.begin();borrar!=n_enrutadores.end();borrar++){
        if(borrar->getNombre()==router->getNombre()){
            n_enrutadores.erase(borrar);
            break;
        }
    }

    n_enrutadores.push_back(*router);
    OrdenarLista();
    delete router;
}

int red::NodosNoConectados()
{
    int NoConectados = 0;
    bool bandera;
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
            if(router->it->second>0){
                bandera = false;
                break;
            }
            bandera = true;
        }
        if(bandera)
            NoConectados ++;
    }
    return NoConectados;
}

void red::ActualizarTabla()
{
    list<string> router_name;
    string nodo;
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
            router_name.push_back(router->it->first);
        }
        break;
    }

    for(auto router=router_name.begin();router!=router_name.end();router++){
        nodo = *router;
        AlgoritmoDijkstra(nodo);
    }
}

void red::TablaConexionesRed()
{
    cout << " \t";
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        cout << router->getNombre() << "\t";
    }
    cout << endl << endl;
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        cout << router->getNombre() << "\t";
    }
}

void red::TablaCostosRed()
{

}

void red::TablaConexionesEnrutador(const string &nodo)
{
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==nodo){
            router->TablaConexiones();
        }
    }
}

void red::TablaCostosEnrutador(const string &nodo)
{
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==nodo){
            router->TablaCostos();
        }
    }
}

void red::OrdenarLista()
{
    list<string> orden;
    list<string>::iterator router_name;
    list<enrutador> ordenada;
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
            orden.push_back(router->it->first);
        }
        break;
    }

    while(ordenada.size()!=n_enrutadores.size()){
        router_name = orden.begin();
        for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
            if(router->getNombre()==*router_name)
                ordenada.push_back(*router);
        }
        orden.pop_front();
    }

    n_enrutadores = ordenada;
}
