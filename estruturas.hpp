#ifndef _HPP_ESTRUTURA
#define _HPP_ESTRUTURA

#include <iostream>
#include <string>

using namespace std;

struct estruturaPessoa
{
    string nomePessoa;
    char sexo;
    string cpf;
    int idade;
    bool pcd;
    bool gestante;
};

struct estruturaObjeto
{
    char tipo;
    string descricao;
};

struct estruturaEmpresa
{
    string nomeEmpresa;
    string cnpj;
    char tipo;
};

#endif /// _HPP_ESTRUTURA
