#include <iostream>
#include "diccionario.h"
#include "tipos_datos.h"
#include "funciones_impresion.h"

using namespace std;

diccionario::diccionario(const int & size)
{
    int size_aux = size; 
    if (size < CANT_ASCII)
    {
      imprimir_error(ERROR_SIZE_DIC);
      size_aux = CANT_ASCII;  
    }  
    dic_ = new arreglo(size_aux);
    size_ = size_aux;
}

diccionario::~diccionario()
{
    if( dic_ )
        delete dic_;
}

//Obtiene una secuencia del diccionario de tipo [int Prefijo, char Sufijo] y la retorna.
secuencia & diccionario::obtener_secuencia(const int i)
{
    if( i < 0 || i > ult_ )
        imprimir_error(ERROR_OBTENER_SEC);
    return dic_ -> obtener_dato(i);
}

//Copia una secuencia del tipo [int Prefijo, char Sufijo] a una posición del diccionario.
estado_t diccionario::asignar_secuencia(const int pos, const secuencia & dato)
{
    if( pos < 0 || pos > MAX_VECTOR - 1 )
        return ERROR_ASIGNAR_SEC;
    (*dic_)[pos] = dato;
    return OK;
}

//Asigna un int P (Prefijo) y un char S (Sufijo) a una secuencia de cierta posición del diccionario.
estado_t diccionario::asignar_secuencia(const int pos, const int & P, const char & S)
{
    if( pos < 0 || pos > MAX_VECTOR - 1 )
        return ERROR_ASIGNAR_SEC;
    (*dic_)[pos].asignarP(P);
    (*dic_)[pos].asignarS(S);
    return OK;
}

//Obtiene el prefijo de cierta posición del diccionario.
int diccionario::obtener_P(const int pos) const
{
    return (*dic_)[pos].obtenerP();
}

//Obtiene el sufijo de cierta posición del diccionario.
char diccionario::obtener_S(const int pos) const 
{
    return (*dic_)[pos].obtenerS();
}

//Obtiene la ultima posición
int diccionario::obtener_ult_()
{
    return ult_;
}

//Vacía el diccionario.
void diccionario::resetear_diccionario()
{
    ult_ = 255;
}

//Asigna un int P (Prefijo) y un char S (Sufijo) a la secuencia de la primera posición vacía del diccionario.
int diccionario::agregar_secuencia(const int & P, const char & S)
{
    //int size = size_;
    if( ult_ >= size_ - 1){
        imprimir_mensaje(MSJ_ESTADO_DIC_LLENO);
        this -> resetear_diccionario();
    }
    this -> asignar_secuencia(ult_ + 1, P, S);
    ult_++;
    
    return ult_;
}

//Búsqueda secuencial de la primer secuencia que coincida con el prefijo y el sufijo suministrado. Retorna índice.
const int diccionario::buscar_secuencia(const int & P, const char & S)
{
    //int size = size_;
    for( int i = 0; i >= 0 && i <= size_ && i <= ult_; i++ )
    {
        if( this->obtener_P(i) == P && this->obtener_S(i) == S )
            return i;
    }
    return -1;
}

//Devuelve el primer caracter del diccionario de la ubicación buscada.
int diccionario::obtener_indice(const int & ubic)
{
    if (ubic <= CANT_ASCII)
        return ubic;
    else
    {
        int aux_P;
        aux_P = this -> obtener_P(ubic);
        return  this -> obtener_indice(aux_P);
    }
        
}

//Imprime cadena de caracteres según indice.
estado_t diccionario::imprimir_indice(const int & ubic, ostream * oss)
{
    int aux_P;
    //Como el S es char va del -127 al 127 por ende del 128 al 255 los toma como negativos.
    unsigned char aux_S;
    if (ubic <= CANT_ASCII)
    {
        *oss << this -> obtener_S(ubic);
        	if((*oss).fail())
		return ERROR_ESCRITURA;
    }
    else
    {
        aux_P = this -> obtener_P(ubic);
        aux_S = this -> obtener_S(ubic);
        this -> imprimir_indice (aux_P, oss);
        this -> imprimir_indice (aux_S, oss);
    }
    return OK;      
}

//Carga tabla ASCII extendida desde 0 hasta 255.
bool diccionario::cargar_ASCII()
{
    for(int i=0; i<=CANT_ASCII; i++)
	    this -> asignar_secuencia(i,-1,char(i));
    ult_ = CANT_ASCII;        
    return true;
}