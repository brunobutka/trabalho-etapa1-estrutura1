#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#include "pilhaDinamica.hpp"
#include "filaDinamicaPessoa.hpp"
#include "filaDinamicaEmpresa.hpp"

int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    ///Filas e pilhas utilizadas
    FilaPessoa fDoacaoPrio, fDoacaoNaoPrio;
    FilaEmpresa fRetiradaPrio, fRetiradaNaoPrio;
    Pilha pLivro, pEquipamento, pCPF;

    ///Estruturas
    estruturaPessoa pessoa;
    estruturaObjeto objeto;
    estruturaEmpresa empresa;

    ///Arquivos texto
    ifstream leitura;
    fstream escreveDoacao("doacao.txt", fstream::out | fstream::trunc);
    escreveDoacao.close();
    fstream escreveRetirada("retiradas.txt", fstream::out | fstream::trunc);
    escreveRetirada.close();

    inicializaP(&pLivro);
    inicializaP(&pEquipamento);
    inicializaP(&pCPF);

    ///Controle do menu
    char menu;

    ///Controle inserir pessoa com deficiencia ou gestante
    char deficiencia, gestante;

    ///Verifica se ocorreu o atendimento com retirada
    bool atendimentoPessoa, atendimentoEmpresa;

    ///Controle de objetos
    int qtdLivros = 0, qtdEquipamentos = 0;
    int qtdRetiradaEmpresa;
    int contadorRetirada;

    ///Para a op��o G
    int totalPessoas = 0, pessoasSexoF = 0, pessoasSexoM = 0, pessoasDeficiencia = 0, mulheresGravidas = 0;

    ///Para a op��o H
    int totalEmpresas = 0, empresaEspLivro = 0, empresaEspEquip = 0;

    ///Para a op��o L
    string verificarCPF;

    ///Para a op��o K
    int contDoacaoPrio = 0, totalDoadores = 0;
    float idadeTotal = 0;
    float idadeMedia = 0;
    char x;

    while(menu != 'N'){
        cout << "################################ MENU ################################" << endl;
        cout << "#                                                                    #" << endl;
        cout << "# A) Incluir PESSOA na FILA DE DOA��O;                               #" << endl;
        cout << "# B) Incluir EMPRESA na FILA DE RETIRADA;                            #" << endl;
        cout << "# C) Atender uma PESSOA da FILA;                                     #" << endl;
        cout << "# D) Atender uma EMPRESA da FILA;                                    #" << endl;
        cout << "# E) Listar todas as PESSOAS das FILAS(ambas as filas);              #" << endl;
        cout << "# F) Listar todas as EMPRESAS das FILAS(ambas as filas);             #" << endl;
        cout << "# G) Listar informa��es sobre a FILA DE PESSOAS de forma unificada;  #" << endl;
        cout << "# H) Listar informa��es sobre a FILA DE EMPRESAS de forma unificada; #" << endl;
        cout << "# I) Listar estoque de EQUIPAMENTOS na ordem em que foram doados;    #" << endl;
        cout << "# J) Listar estoque de LIVROS na ordem em que foram doados;          #" << endl;
        cout << "# K) Listar todas as DOA��ES, o n�mero de pessoas com prioridade que #" << endl;
        cout << "#        realizaram doa��es e a idade m�dia dos doadores;            #" << endl;
        cout << "# L) Verifica o n�mero de doa��es realizadas por um determinado CPF; #" << endl;
        cout << "# M) Listar todas as RETIRADAS realizadas;                           #" << endl;
        cout << "# N) Encerrar programa.                                              #" << endl;
        cout << "#                                                                    #" << endl;
        cout << "######################################################################" << endl << endl;
        cout << "Escolha uma opcao: ";
        cin >> menu;
        fflush(stdin);
        menu = toupper(menu);

        switch(menu) {
            case 'N':
                system("cls");
                cout << "Programa encerrado." << endl << endl;
                break;

            case 'A':
                system("cls");

                cout << "\tA - INCLUIR PESSOA NA FILA DE DOA��O\n" << endl << endl;

                ///Inserir Nome
                cout << "Nome: ";
                getline(cin, pessoa.nomePessoa);
                fflush(stdin);

                ///Inserir Sexo
                cout << "Sexo (M = Masculino | F = Feminino): ";
                cin >> pessoa.sexo;
                fflush(stdin);
                pessoa.sexo = toupper(pessoa.sexo);
                while(pessoa.sexo != 'M' && pessoa.sexo != 'F'){
                    cout << "Escolha M ou F: ";
                    cin >> pessoa.sexo;
                    pessoa.sexo = toupper(pessoa.sexo);
                    fflush(stdin);
                }

                ///Inserir CPF
                cout << "CPF (11 d�gitos | Insira somente os n�meros): ";
                getline(cin, pessoa.cpf);
                fflush(stdin);
                while(pessoa.cpf.size() != 11){
                    cout << "CPF deve conter 11 d�gitos: ";
                    getline(cin, pessoa.cpf);
                    fflush(stdin);
                }

                ///Inserir Idade
                cout << "Idade: ";
                cin >> pessoa.idade;
                fflush(stdin);
                while(pessoa.idade < 0 || pessoa.idade > 130){
                    cout << "Idade deve estar entre 0 e 130 anos: ";
                    cin >> pessoa.idade;
                    fflush(stdin);
                }

                ///Inserir se possui defici�ncia
                cout << "Pessoa com defici�ncia (N = N�o | S = Sim): ";
                cin >> deficiencia;
                deficiencia = toupper(deficiencia);
                fflush(stdin);
                if(deficiencia == 'N')
                    pessoa.pcd = false;
                else if(deficiencia == 'S')
                    pessoa.pcd = true;
                while(deficiencia != 'S' && deficiencia != 'N'){
                    cout << "Informe N ou S: ";
                    cin >> deficiencia;
                    deficiencia = toupper(deficiencia);
                    fflush(stdin);
                    if(deficiencia == 'N')
                        pessoa.pcd = false;
                    else if(deficiencia == 'S')
                        pessoa.pcd = true;
                }

                ///Inserir gestante
                cout << "Gestante (N = N�o | S = Sim): ";
                cin >> gestante;
                gestante = toupper(gestante);
                fflush(stdin);
                if(gestante == 'N')
                    pessoa.gestante = false;
                else if(gestante == 'S')
                    pessoa.gestante = true;
                if(pessoa.sexo == 'M'){
                    while(gestante != 'N'){
                    cout << "Informe N (sexo masculino): ";
                    cin >> gestante;
                    gestante = toupper(gestante);
                    fflush(stdin);
                    if(gestante == 'N')
                        pessoa.gestante = false;
                    }
                } else if(pessoa.sexo == 'F'){
                    while(gestante != 'S' && gestante != 'N'){
                        cout << "Informe N ou S: ";
                        cin >> gestante;
                        gestante = toupper(gestante);
                        fflush(stdin);
                        if(gestante == 'N')
                            pessoa.gestante = false;
                        else if(gestante == 'S')
                            pessoa.gestante = true;
                    }
                }

                ///Verifica em qual fila a pessoa ser� inserida
                if(pessoa.idade > 65 || pessoa.pcd == true || pessoa.gestante == true) {
                    if(enfileiraFPessoa(&fDoacaoPrio, pessoa))
                        cout << "\n" << pessoa.nomePessoa << " foi inserido na FILA PRIORIT�RIA." << endl << endl;
                } else {
                    if(enfileiraFPessoa(&fDoacaoNaoPrio, pessoa))
                        cout << "\n" << pessoa.nomePessoa << " foi inserido na FILA N�O PRIORIT�RIA." << endl << endl;
                }

                ///Controle de pessoas nas filas
                totalPessoas++;
                if(pessoa.sexo == 'F')
                    pessoasSexoF++;
                else if(pessoa.sexo == 'M')
                    pessoasSexoM++;
                if(pessoa.pcd == true)
                    pessoasDeficiencia++;
                if(pessoa.gestante == true)
                    mulheresGravidas++;

                break;

            case 'B':
                system("cls");

                cout << "\tB - INCLUIR EMPRESA NA FILA DE RETIRADA\n" << endl << endl;

                ///Inserir nome da empresa
                cout << "Nome: ";
                getline(cin, empresa.nomeEmpresa);
                fflush(stdin);

                ///Inserir CNPJ da empresa
                cout << "CNPJ (14 d�gitos | Insira somente os n�meros): ";
                getline(cin, empresa.cnpj);
                fflush(stdin);
                while(empresa.cnpj.size() != 14){
                    cout << "CNPJ deve conter 14 d�gitos: ";
                    getline(cin, empresa.cnpj);
                    fflush(stdin);
                }

                ///Inserir tipo de objeto transportado pela empresa
                cout << "Tipo de transporte (L - Livros | E - Equipamentos): ";
                cin >> empresa.tipo;
                fflush(stdin);
                empresa.tipo = toupper(empresa.tipo);
                while(empresa.tipo != 'L' && empresa.tipo != 'E'){
                    cout << "Escolha L ou E: ";
                    cin >> empresa.tipo;
                    fflush(stdin);
                    empresa.tipo = toupper(empresa.tipo);
                }

                ///Verifica o tipo de objeto transportado e insere a empresa na determinada fila
                if(empresa.tipo == 'L') {
                    if(enfileiraFEmpresa(&fRetiradaPrio, empresa))
                        cout << "\nA empresa " << empresa.nomeEmpresa << " foi inserida na FILA PRIORIT�RIA." << endl << endl;
                } else {
                    if(enfileiraFEmpresa(&fRetiradaNaoPrio, empresa))
                        cout << "\nA empresa " << empresa.nomeEmpresa << " foi inserida na FILA N�O PRIORIT�RIA." << endl << endl;
                }

                ///Controle de empresas nas filas
                totalEmpresas++;
                if(empresa.tipo == 'L')
                    empresaEspLivro++;
                else if(empresa.tipo == 'E')
                    empresaEspEquip++;

                break;

            case 'C':
                system("cls");

                cout << "\tC - ATENDER UMA PESSOA NA FILA\n" << endl << endl;
                atendimentoPessoa = false;

                ///Verifica de qual fila vai ser atendida a pessoa
                if(!vaziaFPessoa(&fDoacaoPrio)) {
                    controlePessoas(&fDoacaoPrio, &pessoa, &totalPessoas, &pessoasSexoF, &pessoasSexoM, &pessoasDeficiencia, &mulheresGravidas);
                    desenfileiraFPessoa(&fDoacaoPrio, &pessoa);
                    atendimentoPessoa = true;
                    empilhaPCPF(&pCPF, pessoa);
                    contDoacaoPrio++;
                    cout << pessoa.nomePessoa << ", da FILA PRIORIT�RIA, foi atendido(a)." << endl << endl;
                } else if(!vaziaFPessoa(&fDoacaoNaoPrio)) {
                    controlePessoas(&fDoacaoNaoPrio, &pessoa, &totalPessoas, &pessoasSexoF, &pessoasSexoM, &pessoasDeficiencia, &mulheresGravidas);
                    desenfileiraFPessoa(&fDoacaoNaoPrio, &pessoa);
                    atendimentoPessoa = true;
                    empilhaPCPF(&pCPF, pessoa);
                    cout << pessoa.nomePessoa << ", da FILA N�O PRIORIT�RIA, foi atendido(a)." << endl << endl;
                } else
                    cout << "As FILAS PRIORIT�RIA e N�O PRIORIT�RIA est�o vazias." << endl << endl;

                ///Caso uma pessoa seja atendida, as condi��es abaixo
                if(atendimentoPessoa){
                    ///Para verificar o total de doadores e a idade;
                    totalDoadores++;
                    idadeTotal += pessoa.idade;

                    ///Insere o tipo de doa��o
                    cout << "Tipo da doa��o (L - Livro | E - Equipamento): ";
                    cin >> objeto.tipo;
                    fflush(stdin);
                    objeto.tipo = toupper(objeto.tipo);
                    while(objeto.tipo != 'L' && objeto.tipo != 'E'){
                        cout << "Escolha L ou E: ";
                        cin >> objeto.tipo;
                        fflush(stdin);
                        objeto.tipo = toupper(objeto.tipo);
                    } ;

                    ///Descri��o do objeto doado
                    cout << "Descri��o do objeto: ";
                    getline(cin, objeto.descricao);
                    fflush(stdin);
                    while(objeto.descricao.empty()){
                        cout << "Adicione uma descri��o: ";
                        getline(cin, objeto.descricao);
                        fflush(stdin);
                    }

                    cout << endl;

                    ///Verifica o tipo de objeto doado e em qual pilha ser� empilhado (Incrementa qtdLivros na pilha)
                    if(objeto.tipo == 'L'){
                        empilhaP(&pLivro, pessoa, objeto);
                        qtdLivros++;
                        cout << objeto.descricao << " empilhado na PILHA LIVROS." << endl << endl;
                    } else{
                        empilhaP(&pEquipamento, pessoa, objeto);
                        qtdEquipamentos++;
                        cout << objeto.descricao << " empilhado na PILHA EQUIPAMENTOS." << endl << endl;
                    }

                    ///Escreve no arquivo texto
                    escreveDoacao.open("doacao.txt", fstream::out | fstream::app);
                    if(escreveDoacao.is_open()){
                        escreveDoacao << "# " << pessoa.nomePessoa << " # ";
                        escreveDoacao << pessoa.sexo << " # ";
                        escreveDoacao << pessoa.cpf << " # ";
                        escreveDoacao << pessoa.idade << " # ";
                        escreveDoacao << pessoa.pcd << " # ";
                        escreveDoacao << pessoa.gestante << " # ";
                        escreveDoacao << objeto.tipo << " # ";
                        escreveDoacao << objeto.descricao << "\n";
                    } else
                        cout << "Falha ao abrir arquivo" << endl;

                    escreveDoacao.close();

                }

                break;

            case 'D':
                system("cls");

                cout << "\tD - ATENDER UMA EMPRESA NA FILA\n" << endl << endl;
                atendimentoEmpresa = false;
                contadorRetirada = 0;

                ///Verifica qual empresa vai ser atendida
                if(!vaziaFEmpresa(&fRetiradaPrio) && vaziaP(&pLivro)){
                    controleEmpresas(&fRetiradaPrio, &empresa, &totalEmpresas, &empresaEspLivro, &empresaEspEquip);
                    desenfileiraFEmpresa(&fRetiradaPrio, &empresa);
                    cout << empresa.nomeEmpresa << " foi atendia por�m n�o h� LIVROS no estoque." << endl << endl;
                    break;
                }else if(!vaziaFEmpresa(&fRetiradaPrio) && !vaziaP(&pLivro)) {
                    controleEmpresas(&fRetiradaPrio, &empresa, &totalEmpresas, &empresaEspLivro, &empresaEspEquip);
                    desenfileiraFEmpresa(&fRetiradaPrio, &empresa);
                    atendimentoEmpresa = true;
                    cout << "A empresa " << empresa.nomeEmpresa << " ,da FILA PRIORIT�RIA, foi atendida." << endl << endl;
                } else if(!vaziaFEmpresa(&fRetiradaNaoPrio) && vaziaP(&pEquipamento)){
                    controleEmpresas(&fRetiradaNaoPrio, &empresa, &totalEmpresas, &empresaEspLivro, &empresaEspEquip);
                    desenfileiraFEmpresa(&fRetiradaNaoPrio, &empresa);
                    cout << empresa.nomeEmpresa << " foi atendida por�m n�o h� EQUIPAMENTOS no estoque." << endl << endl;
                    break;
                } else if(!vaziaFEmpresa(&fRetiradaNaoPrio) && !vaziaP(&pEquipamento)) {
                    controleEmpresas(&fRetiradaNaoPrio, &empresa, &totalEmpresas, &empresaEspLivro, &empresaEspEquip);
                    desenfileiraFEmpresa(&fRetiradaNaoPrio, &empresa);
                    atendimentoEmpresa = true;
                    cout << "A empresa " << empresa.nomeEmpresa << " da FILA N�O PRIORIT�RIA, foi atendida." << endl << endl;
                } else
                    cout << "N�o � poss�vel realizar o atendimento pois n�o empresas na FILA de atendimento." << endl << endl;

                ///Verifica se uma empresa foi atendida, se sim realiza as condi��es
                if(atendimentoEmpresa){
                    ///Se a empresa foi do tipo 'L' ou 'E', solicida a qtdRetirada
                    if(empresa.tipo == 'L'){
                        cout << "Quantia no estoque: " << qtdLivros << endl;
                        cout << "Informe a quantidade de objetos (Livros) a serem retirados: ";
                        cin >> qtdRetiradaEmpresa;
                        while(qtdRetiradaEmpresa > qtdLivros){
                            cout << "O n�mero de retiradas deve ser igual ou menor que os objetos dispon�veis: ";
                            cin >> qtdRetiradaEmpresa;
                            fflush(stdin);
                        }
                    }
                    if(empresa.tipo == 'E'){
                        cout << "Quantia no estoque: " << qtdEquipamentos << endl;
                        cout << "Informe a quantidade de objetos (Equipamentos) a serem retirados: ";
                        cin >> qtdRetiradaEmpresa;
                        while(qtdRetiradaEmpresa > qtdEquipamentos){
                            cout << "O n�mero de retiradas deve ser igual ou menor que os objetos dispon�veis: ";
                            cin >> qtdRetiradaEmpresa;
                            fflush(stdin);
                        }
                    }

                    cout << endl;

                    ///Escreve no arquivo a empresa e o objeto retirado
                    escreveRetirada.open("retiradas.txt", fstream::out | fstream::app);
                    ///Vai escrever os dados da empresa e os objetos o seguindo o n�mero de objetos a serem retirados
                    ///A cada objeto retirado, o contador de livros e equipamentos � diminu�do
                    while(contadorRetirada < qtdRetiradaEmpresa){
                        if(empresa.tipo == 'L'){
                            desempilhaP(&pLivro, &pessoa, &objeto);
                            qtdLivros--;
                        }
                        if(empresa.tipo == 'E'){
                            desempilhaP(&pEquipamento, &pessoa, &objeto);
                            qtdEquipamentos--;
                        }

                        if(escreveRetirada.is_open()){
                            escreveRetirada << "# " << empresa.nomeEmpresa << " # ";
                            escreveRetirada << empresa.cnpj << " # ";
                            escreveRetirada << empresa.tipo << " # ";
                            escreveRetirada << objeto.tipo << " # ";
                            escreveRetirada << objeto.descricao << "\n";
                        } else
                            cout << "Falha ao abrir arquivo" << endl;

                        contadorRetirada++;
                    }
                    escreveRetirada.close();
                }

                break;

            case 'E':
                system("cls");
                cout << "\tE - LISTAR TODAS AS PESSOAS\n" << endl << endl;
                ///Mostra as filas, 1-priorit�ria, 2-n�o priorit�tia
                cout << "Fila de PESSOA PRIORIT�RIA: ";
                mostraFPessoa(&fDoacaoPrio);
                cout << "Fila de PESSOA N�O PRIORIT�RIA: ";
                mostraFPessoa(&fDoacaoNaoPrio);
                break;

            case 'F':
                system("cls");
                cout << "\tF - LISTAR TODAS AS EMPRESAS\n" << endl << endl;
                ///Mostra as filas, 1-priorit�ria, 2-n�o priorit�ria
                cout << "Fila de EMPRESAS PRIORIT�RIA: ";
                mostraFEmpresa(&fRetiradaPrio);
                cout << "Fila de EMPRESAS N�O PRIORIT�RIA: ";
                mostraFEmpresa(&fRetiradaNaoPrio);
                break;

            case 'G':
                system("cls");
                cout << "\tG - MOSTRAS AS INFORMA��ES SOBRE A FILA DE PESSOAS DE FORMA UNIFICADA\n" << endl << endl;
                ///Exibe o controle de pessoas n
                cout << "Total de pessoas: " << totalPessoas << endl;
                cout << "N�mero de pessoas do sexo feminino: " << pessoasSexoF << endl;
                cout << "N�mero de pessoas do sexo masculino: " << pessoasSexoM << endl;
                cout << "N�mero de pessoas com alguma defici�ncia: " << pessoasDeficiencia << endl;
                cout << "N�mero de gestantes: " << mulheresGravidas << endl << endl;
                break;

            case 'H':
                system("cls");
                cout << "\tH - MOSTRAS AS INFORMA��ES SOBRE A FILA DE EMPRESAS DE FORMA UNIFICADA\n" << endl << endl;
                cout << "Total de empresas: " << totalEmpresas << endl;
                cout << "N�mero de pessoas especializadas no transporte de livros: " << empresaEspLivro << endl;
                cout << "N�mero de pessoas especializadas no transporte de livros: " << empresaEspEquip << endl << endl;
                break;

            case 'I':
                system("cls");
                cout << "\tI - LISTAR O ESTOQUE DE EQUIPAMENTOS NA ORDEM EM QUE FORAM DOADOS\n" << endl << endl;
                inverterPilha(&pEquipamento, pessoa, objeto);
                break;

            case 'J':
                system("cls");
                cout << "\tJ - LISTAR O ESTOQUE DE LIVROS NA ORDEM EM QUE FORAM DOADOS\n" << endl << endl;
                inverterPilha(&pLivro, pessoa, objeto);
                break;

            case 'K':
                system("cls");
                cout << "\tK - LISTAR TODAS AS DOA��ES, O N�MERO DE PESSOAS COM PRIORIDADE QUE DOARAM " << endl;
                cout << "\t                    E A M�DIA DA IDADE DOS DOADORES\n" << endl << endl;

                idadeMedia = idadeTotal / totalDoadores;
                if(idadeTotal == 0 && totalDoadores == 0)
                    idadeMedia = 0;
                cout << "N�mero de pessoas com prioridade que doaram: " << contDoacaoPrio << endl;
                cout << "Idade m�dia dos doadores: " << idadeMedia << endl << endl;

                cout << "\tLEITURA DO ARQUIVO TEXTO" << endl;
                leitura.open("doacao.txt", ios::in);
                if(leitura.is_open()){
                    while(leitura.get(x)){
                            cout << x;
                    }

                }
                leitura.close();
                cout << endl;
                break;

            case 'L':
                system("cls");
                cout << "\tL - VERIFICAR N�MERO DE DOA��ES DE DETERMINADO CPF\n" << endl << endl;
                cout << "Informe o CPF a ser pesquisado (11 D�gitos | Inserir somente os n�meros): ";
                getline(cin, verificarCPF);
                fflush(stdin);
                while(verificarCPF.size() != 11){
                    cout << "CPF deve conter 11 d�gitos: ";
                    getline(cin, verificarCPF);
                    fflush(stdin);
                }
                cout << "\nCPF analisado: " << verificarCPF << endl;
                cout << "N�mero de doa��es realizadas: " << buscarCPF(&pCPF, pessoa, verificarCPF) << endl << endl;
                break;

            case 'M':
                system("cls");
                cout << "\tM - LISTAR TODAS AS RETIRADAS REALIZADAS\n" << endl << endl;
                cout << "\tLEITURA DO ARQUIVO TEXTO" << endl;
                leitura.open("retiradas.txt", ios::in);
                if(leitura.is_open()){
                    while(leitura.get(x)){
                            cout << x;
                    }
                }
                leitura.close();
                cout << endl;
                break;

            default:
                system("cls");
                cout << "Op��o Inv�lida.\n" << endl << endl;
                break;
        }
        system("pause");
        system("cls");
    }
    destroiP(&pLivro);
    destroiP(&pEquipamento);
    destroiPCPF(&pCPF);
    destroiFPessoa(&fDoacaoPrio);
    destroiFPessoa(&fDoacaoNaoPrio);
    destroiFEmpresa(&fRetiradaPrio);
    destroiFEmpresa(&fRetiradaNaoPrio);
}
