#include <iostream>
#include <string>
#include "sistemaCRUD.h"

using namespace std;

main(){
    setlocale(LC_ALL, "");
    int acao = 0;
    string pesquisarCpf;
    char resposta;

    do{
        acao = showMenu();//mostrar menu principal e recebe sua ação

        const int CADASTRO = 1, PESQUISA = 2, ATUALIZAR = 3, DESATIVAR = 4, LISTA = 5, SAIR = 6;//opções de ações no menu principal

        switch(acao){//identificar ação
            case CADASTRO:{
                system("cls");

                string nomePaciente, cidade, estado, cpf;//informações a serem recebidas

                cout << "\n======================================================================\n";
                cout << "=========================== CADASTRAMENTO ============================\n";
                cout << "======================================================================\n\n";    
                cout << "Digite o nome completo: \n";
                cin.ignore();
                getline(cin, nomePaciente);//string passa a aceitar espaços

                cout << "Digite a cidade: \n";
                getline(cin, cidade);

                cout << "Digite o estado: \n";
                getline(cin, estado);

                cout << "Digite o CPF: ___.___.___-__\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                cin >> cpf;

                bool resultado = executarCadastramento(nomePaciente, cidade, estado, cpf);//mandar informações para cadastro

                if(resultado == true){
                    cout << "\n\n=== Cadastro feito com sucesso! ===\n";
                }
                else{
                    cout << "\n\nErro ao executar cadastro\n";
                }
                break;
            }
            case PESQUISA:{
                system("cls");
                
                cout << "=====================================================\n";
                cout << "===================== PESQUISAR =====================\n";
                cout << "===================================================\n\n";
                cout << "Digite o CPF: ___.___.___-__\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                cin >> pesquisarCpf;//recolhe o cpf
                
                int resultado = pesquisarPaciente(pesquisarCpf);//verificar se existe e, se existir, exibi os dados
                
                if(resultado == -1){//não existe
                    cout << "\n\nPaciente não existe!\n";
                }
                else{//existe e retorna sua posição
                    pesquisarPaciente(pesquisarCpf);//mostrar os dados do paciente pesquisado
                }
                break;
            }
            case ATUALIZAR:{
                system("cls");

                cout << "\n===============================================\n";
                cout << "============== ATUALIZAR CADASTRO ==============\n";
                cout << "================================================\n\n";
                cout << "Digite o CPF: ___.___.___-__\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                cin >> pesquisarCpf;

                int resultado = verificarCpf(pesquisarCpf);//verificar se existe no sistema e, se existir, retorna sua posição

                if(resultado == -1){//não existe no sistema
                    cout << "\n\nPaciente não existe!\n";
                }
                else{//existe
                    int posicao = resultado;//o retorno, (resultado), foi a posicao do cpf nos vetores

                    formatarSaida(posicao);//mostrar os dados do dono do cpf digitado a partir de sua posição 
                    
                    const int NOME = 1, CIDADE = 2, ESTADO = 3, CPF = 4, STATUS = 5;//opções de itens alteráveis
                    
                    if(verificarStatus(pesquisarCpf) == false){//so tem lógica ter a opção de ativar se estever desativado o status do paciente
                        cout << "\n1.........................Nome\n";
                        cout << "2.......................Cidade\n";
                        cout << "3.......................Estado\n";
                        cout << "4..........................CPF\n";
                        cout << "5.......................Ativar Status\n";
                        cout << "Digite o que deseja altera:_\b";
                        cin >> acao;//definir a ação
                    }
                    else{//paciente ativo, portanto, não tem a opção para ativar o cadastro
                        cout << "\n1.........................Nome\n";
                        cout << "2.......................Cidade\n";
                        cout << "3.......................Estado\n";
                        cout << "4..........................CPF\n";
                        cout << "Digite o que deseja altera:_\b";
                        cin >> acao;//definir a ação
                    }

                    string novoDado;//recebe a alteração a ser feita

                    switch(acao){//identificar ação desejada para atualização
                        case NOME:
                            cout << "\n\nDigite o novo nome:";
                            cin.ignore();
                            getline(cin, novoDado);
                            break;
                        case CIDADE:
                            cout << "Digite a nova cidade:";
                            cin.ignore();
                            getline(cin, novoDado);
                            break;
                        case ESTADO:
                            cout << "Digite o novo estado:";
                            cin.ignore();
                            getline(cin, novoDado);
                            break;
                        case CPF:
                            cout << "Digite o novo CPF: ___.___.___-__\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                            cin >> novoDado;
                            break;
                        case STATUS:
                            novoDado = "ativar ";//so pra preencher o novoDado
                            break;
                    }
                    bool resultado = atualizarCadastro(posicao, acao, novoDado);//manda as informações necessárias para a função e nela altera oq foi pedido

                    if(resultado == true){
                        cout << "\nCadastro atualizado com sucesso!\n\n";
                    }
                    else{
                        cout << "\nERRO ao atualizar cadastro!\n\n";
                    }

                }
                break;
            }
            case DESATIVAR:{
                system("cls");

                cout << "\n========================================================================\n";
                cout << "=========================== DESATIVAR CADASTRO ============================\n";
                cout << "=========================================================================\n\n";
                cout << "Digite o CPF: ___.___.___-__\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                cin >> pesquisarCpf;

                bool resultado = desativarCadastro(pesquisarCpf);//procura o cpf a ser deletado e verifica sua existência 

                if(resultado == true){//existe e foi deletado
                    cout << "\n\nCadastro desativado com sucesso!\n";
                }
                else{//não existe ou já foi deletado
                    cout << "\n\nERRO ao desativar cadastro\n";
                }
                break;
            }
            case LISTA:{
                system("cls");
                cout << "=====================================================\n";
                cout << "================= LISTA DE PACIENTE =================\n";
                cout << "=====================================================\n\n";

                listar();
                break;
            }
            case SAIR:{
                resposta = 'n';//sair do Do While
                break;
            }
        }
        if(acao != 6){//exibir esta mensagem caso a ação n tenham sido "SAIR"
            cout << "\n\nDeseja executar mais alguma ação?\n";
            cout << "[S] para sim e [N] para não: \b";//solicitação para rodar novamente o programa
            cin >> resposta;
        }
    }while(resposta == 's' || resposta == 'S');
    system("cls");

    cout << "========================================================\n";
    cout << "================== PROGRAMA ENCERRADO ==================\n";
    cout << "========================================================\n\n";

    system("pause");
    return 0;
}