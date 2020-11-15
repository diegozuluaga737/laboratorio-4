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

int red::Costo(const string &salida, const string &llegada)
{
    int costo = -1;
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==salida){
            for(router->it2=router->costoNodos.begin();router->it2!=router->costoNodos.end();router->it2++){
                if(router->it2->first==llegada){
                    costo = router->it2->second.first;
                    break;
                }
            }
            break;
        }
    }
    return costo;
}

void red::MejorCamino(const string &salida, const string &llegada)
{
    list<string> ruta;
    string nodo;
    nodo = llegada;
    ruta.push_back(nodo);
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==salida){
            while(nodo!=salida){
                for(router->it2=router->costoNodos.begin();router->it2!=router->costoNodos.end();router->it2++){
                    if(router->it2->first==nodo){
                        nodo = router->it2->second.second;
                        ruta.push_front(nodo);
                        break;
                    }
                }
            }
            break;
        }
    }

    for(auto router=ruta.begin();router!=ruta.end()--;router++){
        if(router==ruta.begin())
            cout << *router;
        else
            cout << " --> " << *router;
    }
    cout << endl;
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
    int costo = 0;
    enrutador *router = new enrutador;

    for(auto p=n_enrutadores.begin();p!=n_enrutadores.end();p++){
        if(p->getNombre()==nodoInicial){
            router->setNombre(p->getNombre());
            router->conexiones = p->conexiones;
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
                    if(find(nodosVistos.begin(),nodosVistos.end(),router2->it->first)!=nodosVistos.end()){}
                    else if(router2->it->first!=router->getNombre() and router2->it->second>0){
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
        for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
            cout << router->it->second << "\t";
        }
        cout << endl << endl;
    }
}

void red::TablaCostosRed()
{
    cout << " \t";
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        cout << router->getNombre() << "\t";
    }
    cout << endl << endl;

    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        cout << router->getNombre() << "\t";
        for(auto router2=n_enrutadores.begin();router2!=n_enrutadores.end();router2++){
            cout << Costo(router->getNombre(),router2->getNombre()) << "\t";
        }
        cout << endl << endl;
    }
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


void leertexto(string nombretexto, red *network){

    string nodos="",linea="";
        fstream lectura;



        lectura.open(nombretexto,fstream::in|fstream::binary);
        if(lectura.fail()){
            cout<<"No se pudo abrir el archivo." << endl;

        }
        while(lectura.good()){
            linea=lectura.get();
            nodos.append(linea);
        }

        lectura.close();
        nodos.pop_back();


        int pos=0;

        for(int num=0 ;pos!=-1;num++){
                string nodo1,nodo2,costo;

                pos = nodos.find(' ');
                nodo1 = nodos.substr(0,pos);
                pos = nodos.find(' ',pos+1);
                nodo2 = nodos.substr(0,pos);
                nodo2 = nodo2.substr(nodo1.size()+1);
                pos = nodos.find('\r');
                costo = nodos.substr(0,pos);
                costo = costo.substr(nodo1.size()+nodo2.size()+2);

                int costodomod = stoi(costo, nullptr, 10);


                if (true!=network->comprobar_Enrutador(nodo1)) network->agregar_Enrutador(nodo1);
                if (true!=network->comprobar_Enrutador(nodo2)) network->agregar_Enrutador(nodo2);
                network->Conectar2Enrutadores(nodo1, nodo2, costodomod);

                network->ActualizarTabla();




                pos = nodos.find('\n');
                nodos = nodos.substr(pos+1);


    }

}


void generar_aleatoria(red *network){
    srand(time(NULL));
   // int  num=2+rand()%(101-2);
int num=5;

   string nodo,aux;


    for (int i=0,j=65;i<num ; i++,j++) {
       if(j==91) j=97;
       if(j==123) j=65;
       nodo=j;
       aux=j;
       if (network->comprobar_Enrutador(nodo)) {
           nodo = nodo+aux;
           network->agregar_Enrutador(nodo);


       }
       else {
         network->agregar_Enrutador(nodo);

       }
    }
    network->ActualizarTabla();

    for (int i=0,j=65;i<num ; i++,j++) {
        int num_enlaces=1+rand()%(num-i);
        if(j==91) j=97;
        if(j==123) j=65;
        nodo=j;
        aux=j;
        if (num>50) {
            nodo = nodo+aux;
        }
        string nodo2;
        string aux2;
        for (int l=0;l<num_enlaces ;l++ ) {
            int numnodo2=1+rand()%(num-1);
            int costo=1+rand()%(99);
            for (int o=0,k=65;o<=numnodo2 ;o++,k++ ) {

                if(k==91) k=97;
                if(k==123) k=65;
                 nodo2=k;
                 aux2=k;
                if (num>50) {
                    nodo2 = nodo2+aux2;
                }
                if(numnodo2==o) {
                    if (-1==network->Costo(nodo,nodo2)) {

                        network->Conectar2Enrutadores(nodo,nodo2,costo);
                    }
                    else {
                        l=l-1;
                    }
                }
            }
        }
}






}







