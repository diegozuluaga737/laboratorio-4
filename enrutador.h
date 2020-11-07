#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <iostream>
#include <map>

using namespace std;

class enrutador
{
private:
    string nombre;
    map <string,int> mapa_enrutador;

    //bool Comprobar_conexion(const string &name);
public:
    enrutador();
    ~enrutador();
    map<string, int> getMapa_enrutador() const;
    void setMapa_enrutador(const map<string, int> &value);
    string getNombre() const;
    void setNombre(const string &value);

    void Conectar_Enrutador(const string &name,int costo);
    void eliminar_Enrutador(const string &name);
};

#endif // ENRUTADOR_H

