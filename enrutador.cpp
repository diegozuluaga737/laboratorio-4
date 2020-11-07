#include "enrutador.h"

map<string, int> enrutador::getMapa_enrutador() const
{
    return mapa_enrutador;
}

void enrutador::setMapa_enrutador(const map<string, int> &value)
{
    mapa_enrutador = value;
}

string enrutador::getNombre() const
{
    return nombre;
}

void enrutador::setNombre(const string &value)
{
    nombre = value;
}

void enrutador::Conectar_Enrutador(const string &name, int costo)
{
    mapa_enrutador[name] = costo;
}

void enrutador::eliminar_Enrutador(const string &name)
{
    mapa_enrutador.erase(name);
}

enrutador::enrutador()
{
    string nombre = "";
    mapa_enrutador.clear();
}

enrutador::~enrutador()
{

}
