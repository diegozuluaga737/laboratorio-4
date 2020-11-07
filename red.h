#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <list>

class red
{
private:
    list <enrutador> n_enrutadores;

    void Conexiones_Iniciales(const string &router_name);
public:
    red();
    ~red();
    void agregar_Enrutador(const string &router_name);
    void eliminar_Enrutador(const string &router_name);
    void Conectar2Enrutadores(const string &name1,const string &name2,int cost);
    void Costo();
    void MejorCamino();
    bool comprobar_Enrutador(const string &router_name);

    list<enrutador> getN_enrutadores() const;
    void setN_enrutadores(const list<enrutador> &value);
};

#endif // RED_H
