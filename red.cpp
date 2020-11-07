#include "red.h"

vector<enrutador> red::getN_enrutadores() const
{
    return n_enrutadores;
}

void red::setN_enrutadores(const vector<enrutador> &value)
{
    n_enrutadores = value;
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
        }
    }
}

red::red()
{
    
}

red::~red()
{

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

void red::quitar_Enrutador()
{

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
