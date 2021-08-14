#ifndef _HPP_PILHA_DINAMICA
#define _HPP_PILHA_DINAMICA

#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#include "estruturas.hpp"

typedef estruturaObjeto DadoNoPilhaObjeto;
typedef estruturaPessoa DadoNoPilhaPessoa;

struct NoPilha{
    DadoNoPilhaObjeto objeto;
    DadoNoPilhaPessoa pessoa;

    NoPilha *prox;
};

struct Pilha{
    NoPilha *topo;

    Pilha(){
        topo = nullptr;
    }
};

///inicialização dos dados da pilha
void inicializaP(Pilha *p){
    p->topo = nullptr;
}

bool vaziaP(Pilha *p){
    if (!p->topo)
        return true;
    else
        return false;
}

bool empilhaP(Pilha *p, DadoNoPilhaPessoa pessoa, DadoNoPilhaObjeto objeto){
    NoPilha *novo =  new NoPilha();
    if (!novo)
        return false;

    novo->pessoa.nomePessoa = pessoa.nomePessoa;
    novo->pessoa.sexo = pessoa.sexo;
    novo->pessoa.cpf = pessoa.cpf;
    novo->pessoa.idade = pessoa.idade;
    novo->pessoa.pcd = pessoa.pcd;
    novo->pessoa.gestante = pessoa.gestante;

    novo->objeto.tipo = objeto.tipo;
    novo->objeto.descricao = objeto.descricao;

    novo->prox = p->topo;
    p->topo = novo;
    return true;
}

bool desempilhaP(Pilha *p, DadoNoPilhaPessoa *pessoa,DadoNoPilhaObjeto *objeto){
    if (!vaziaP(p)){
        *pessoa = p->topo->pessoa;
        *objeto = p->topo->objeto;
        NoPilha *apagar = p->topo;
        p->topo = p->topo->prox;
        delete apagar;

        return true;
    }
    else
        return false;
}

bool desempilhaPCPF(Pilha *p, DadoNoPilhaPessoa *pessoa){
    if (!vaziaP(p)){
        *pessoa = p->topo->pessoa;
        NoPilha *apagar = p->topo;
        p->topo = p->topo->prox;
        delete apagar;
        return true;
    }
    else
        return false;
}

/*bool espiaP(Pilha* p, DadoNoPilhaObjeto *dado){
    if (p->topo){
        *dado= p->topo->dado;
        return true;
    }
    else
        return false;
}*/

void mostraP(Pilha *p){
    if(!vaziaP(p)){
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << setfill(' ') << std::setw(12) << "Nome" << " | ";
        cout << setfill(' ') << std::setw(2) << "Sexo(M ou F)" << " | ";
        cout << setfill(' ') << std::setw(12) << "CPF" << " | ";
        cout << setfill(' ') << std::setw(1) << "Idade" << " | ";
        cout << setfill(' ') << std::setw(1) << "PCD(0 ou 1)" << " | ";
        cout << setfill(' ') << std::setw(9) << "Gestante(0 ou 1)" << " | ";
        cout << setfill(' ') << std::setw(9) << "Objeto(L ou E)" << " | ";
        cout << setfill(' ') << std::setw(14) << "Descricao" << " | " << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        NoPilha *no = p->topo;
        while (no != NULL){
            cout << setfill(' ') << std::setw(12) << no->pessoa.nomePessoa << " | ";
            cout << setfill(' ') << std::setw(12) << no->pessoa.sexo << " | ";
            cout << setfill(' ') << std::setw(12) << no->pessoa.cpf << " | ";
            cout << setfill(' ') << std::setw(5) << no->pessoa.idade << " | ";
            cout << setfill(' ') << std::setw(11) << no->pessoa.pcd << " | ";
            cout << setfill(' ') << std::setw(16) << no->pessoa.gestante << " | ";
            cout << setfill(' ') << std::setw(14) << no->objeto.tipo << " | ";
            cout << setfill(' ') << std::setw(14) << no->objeto.descricao << " | " << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            no = no->prox;
        }
        cout << endl;
    } else
        cout << "A pilha esta vazia" << endl << endl;
}

void destroiP(Pilha *p){
    DadoNoPilhaPessoa pessoa;
    DadoNoPilhaObjeto objeto;
    while(!vaziaP(p))
        desempilhaP(p, &pessoa, &objeto);
}

void destroiPCPF(Pilha *p){
    DadoNoPilhaPessoa pessoa;
    while(!vaziaP(p))
        desempilhaPCPF(p, &pessoa);
}

bool empilhaPCPF(Pilha *p, DadoNoPilhaPessoa pessoa){
    NoPilha *novo =  new NoPilha();
    if (!novo)
        return false;

    novo->pessoa.cpf = pessoa.cpf;
    novo->prox = p->topo;
    p->topo = novo;
    return true;
}


int buscarCPF(Pilha *p, DadoNoPilhaPessoa pessoa, string cpf){
    int contador = 0;

    NoPilha *no = p->topo;

    while (no != NULL){
        if(no->pessoa.cpf == cpf)
            contador++;

        no = no->prox;
    }

    return contador;
}

void inverterPilha(Pilha *p, DadoNoPilhaPessoa pessoa, DadoNoPilhaObjeto objeto){
    Pilha aux;

    NoPilha *no = p->topo;

    while(!vaziaP(p)){
        desempilhaP(p, &pessoa, &objeto);
        empilhaP(&aux, pessoa, objeto);
    }

    mostraP(&aux);

    while(!vaziaP(&aux)){
        desempilhaP(&aux, &pessoa, &objeto);
        empilhaP(p, pessoa, objeto);
    }

}

#endif // _HPP_PILHA_DINAMICA
