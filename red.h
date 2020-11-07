#ifndef RED_H
#define RED_H
#include "enrutador.h"
#include <vector>

class red
{
private:
    vector <enrutador> n_enrutadores;

    void Conexiones_Iniciales(const string &router_name);
public:
    red();
    ~red();
    void agregar_Enrutador(const string &router_name);
    void quitar_Enrutador();
    void Costo();
    void MejorCamino();
    bool comprobar_Enrutador(const string &router_name);

    vector<enrutador> getN_enrutadores() const;
    void setN_enrutadores(const vector<enrutador> &value);
};

#endif // RED_H
