#ifndef _HPP_FILAPESSOA_DINAMICA
#define _HPP_FILAPESSOA_DINAMICA

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#include "estruturas.hpp"

typedef estruturaPessoa DadoNoFilaPessoa;

struct NoFilaPessoa{
    DadoNoFilaPessoa dado;
    NoFilaPessoa *prox;
};

struct FilaPessoa{
    NoFilaPessoa *inicio;
    NoFilaPessoa *fim;

    FilaPessoa() {
        inicio = nullptr;
        fim = nullptr;
    }
};

void inicializaFPessoa(FilaPessoa *f){
    f->inicio = nullptr;
    f->fim = nullptr;
}

bool vaziaFPessoa(FilaPessoa *f){
    if (!f->inicio)
        return true;
    else
        return false;
}

bool enfileiraFPessoa(FilaPessoa *f, DadoNoFilaPessoa dado){
    NoFilaPessoa *novo = new NoFilaPessoa();
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

bool desenfileiraFPessoa(FilaPessoa *f, DadoNoFilaPessoa *dado){
    if (f->inicio){
        *dado = f->inicio->dado;
        NoFilaPessoa *apagar = f->inicio;
        f->inicio = f->inicio->prox;
        delete apagar;

        if (!f->inicio)
            f->fim = nullptr;

        return true;
    } else
        return false;
}

bool espiaFPessoa(FilaPessoa* f, DadoNoFilaPessoa *dado){
    if (f->inicio){
        *dado = f->inicio->dado;
        return true;
    }
    else
        return false;
}

void mostraFPessoa(FilaPessoa *f){
    if(f->inicio){

        cout << "{";

        NoFilaPessoa *no = f->inicio;
        while (no){
            cout << "[" << no->dado.nomePessoa;
            cout << ", " << no->dado.sexo;
            cout << ", " << no->dado.cpf;
            cout << ", " << no->dado.idade;
            cout << ", " << no->dado.pcd;
            cout << ", " << no->dado.gestante << "]";
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

void destroiFPessoa(FilaPessoa *f){
    NoFilaPessoa *no = f->inicio;
    while (no){
        NoFilaPessoa *apagar = no;
        no = no->prox;
        delete apagar;
    }
    f->inicio = nullptr;
    f->fim = nullptr;
}

void controlePessoas(FilaPessoa *f, DadoNoFilaPessoa *dado, int *tP, int *pSF, int *pSM, int *pD, int *mG){
    NoFilaPessoa *no = f->inicio;

    (*tP)--;
    if(no->dado.sexo == 'F')
        (*pSF)--;
    else if(no->dado.sexo == 'M')
        (*pSM)--;
    if(no->dado.pcd == true)
        (*pD)--;
    if(no->dado.gestante == true)
        (*mG)--;
}

#endif /// _HPP_FILAPESSOA_DINAMICA
