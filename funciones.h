#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "red.h"

void TablaConexiones(red network);
void TablaCostos(red network);
void ConexionesEnrutador(red network,const string nodo);
void CostosEnrutador(red network, const string nodo);
#endif // FUNCIONES_H
