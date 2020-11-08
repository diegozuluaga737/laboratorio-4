#include "enrutador.h"

map<string, int> enrutador::getConexiones() const
{
    return conexiones;
}

void enrutador::setConexiones(const map<string, int> &value)
{
    conexiones = value;
}

string enrutador::getNombre() const
{
    return nombre;
}

void enrutador::setNombre(const string &value)
{
    nombre = value;
}

map<string, pair<int, string> > enrutador::getCostoNodos() const
{
    return costoNodos;
}

void enrutador::setCostoNodos(const map<string, pair<int, string> > &value)
{
    costoNodos = value;
}

void enrutador::Conectar_Enrutador(const string &name, int costo)
{
    conexiones[name] = costo;
}

void enrutador::eliminar_Enrutador(const string &name)
{
    conexiones.erase(name);
}

void enrutador::Agregar_Conexion(const string &name, const string &anterior, int costo)
{
    costoNodos[name] = make_pair(costo,anterior);
}

enrutador::enrutador()
{
    string nombre = "";
    conexiones.clear();
}

enrutador::~enrutador()
{

}
