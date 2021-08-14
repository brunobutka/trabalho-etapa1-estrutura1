#ifndef _HPP_FILAEMPRESA_DINAMICA
#define _HPP_FILAEMPRESA_DINAMICA

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "estruturas.hpp"

typedef estruturaEmpresa DadoNoFilaEmpresa;

struct NoFilaEmpresa{
    DadoNoFilaEmpresa dado;
    NoFilaEmpresa *prox;
};

struct FilaEmpresa{
    NoFilaEmpresa *inicio;
    NoFilaEmpresa *fim;

    FilaEmpresa() {
        inicio = nullptr;
        fim = nullptr;
    }
};

void inicializaFEmpresa(FilaEmpresa *f){
    f->inicio = nullptr;
    f->fim = nullptr;
}

bool vaziaFEmpresa(FilaEmpresa *f){
    if (!f->inicio)
        return true;
    else
        return false;
}

bool enfileiraFEmpresa(FilaEmpresa *f, DadoNoFilaEmpresa dado){
    NoFilaEmpresa *novo = new NoFilaEmpresa();
    if (!novo)
        return false;

    novo->dado = dado;
    novo->prox = nullptr;
    if (!f->inicio)
        f->inicio = novo;
    else
        f->fim->prox = novo;

    f->fim = novo;
    return true;
}

bool desenfileiraFEmpresa(FilaEmpresa *f, DadoNoFilaEmpresa *dado){
    if (f->inicio){

        *dado = f->inicio->dado;
        NoFilaEmpresa *apagar = f->inicio;
        f->inicio = f->inicio->prox;
        delete apagar;

        if (!f->inicio)
            f->fim = nullptr;

        return true;
    } else
        return false;
}

bool espiaFEmpresa(FilaEmpresa* f, DadoNoFilaEmpresa *dado){
    if (f->inicio){
        *dado = f->inicio->dado;
        return true;
    }
    else
        return false;
}

void mostraFEmpresa(FilaEmpresa *f){
    if(f->inicio){

        cout << "{";

        NoFilaEmpresa *no = f->inicio;
        while (no){

            cout << "[" << no->dado.nomeEmpresa;
            cout << ", " << no->dado.cnpj;
            cout << ", " << no->dado.tipo << "]";
            no = no->prox;

            if(no)
                cout << ", ";
        }
        cout << "}" << endl << endl;
    } else
        cout << "Fila vazia.\n\n";
}

/*bool buscaFPessoa(FilaPessoa *f, DadoNoFilaPessoa valor){
    NoFilaPessoa *no = f->inicio;
    while (no){
        if(no->dado == valor)
            return true;

        no = no->prox;
    }

    return false;
}*/

void destroiFEmpresa(FilaEmpresa *f){
    NoFilaEmpresa *no = f->inicio;
    while (no){
        NoFilaEmpresa *apagar = no;
        no = no->prox;
        delete apagar;
    }
    f->inicio = nullptr;
    f->fim = nullptr;
}

void controleEmpresas(FilaEmpresa *f, DadoNoFilaEmpresa *dado, int *tE, int *tEL, int *tEE){
    NoFilaEmpresa *no = f->inicio;

    (*tE)--;
    if(no->dado.tipo == 'L')
        (*tEL)--;
    else if(no->dado.tipo == 'E')
        (*tEE)--;
}


#endif /// _HPP_FILAEMPRESA_DINAMICA
