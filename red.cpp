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
