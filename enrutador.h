#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

class enrutador
{
private:
    string nombre;
    //map<string,int> conexiones;
    //map<string,pair<int,string>> costoNodos;

public:
    map<string,int> conexiones;
    map<string,pair<int,string>> costoNodos;
    map<string,int>::iterator it;
    map<string,pair<int,string>>::iterator it2;


    enrutador();
    ~enrutador();
    map<string, int> getConexiones() const;
    void setConexiones(const map<string, int> &value);
    string getNombre() const;
    void setNombre(const string &value);
    map<string, pair<int, string> > getCostoNodos() const;
    void setCostoNodos(const map<string, pair<int, string> > &value);

    void Conectar_Enrutador(const string &name,int costo);
    void eliminar_Enrutador(const string &name);
    void Agregar_Conexion(const string &name,const string &anterior, int cost);
    void TablaConexiones();
    void TablaCostos();
};

#endif // ENRUTADOR_H

