#include <iostream>
#include <string>

using namespace std;

const int TAM = 10000; 
int acao = 0;
string gNomes[TAM];//variáveis globais para serem acessadas em todos os menus
string gCidades[TAM];
string gEstados[TAM];
string gCpfs[TAM];
bool gStatus[TAM];//se o paciente tem status de ativo ou desativado no sistema

int showMenu(){//Menu principal
    system("cls");

    cout << "\n==================================================================\n";
    cout << "=========================== BEM VINDO ============================\n";
    cout << "==================================================================\n\n";
    cout << "1......................................Criar Novo Cadastro\n";
    cout << "2......................................Pesquisar Paciente\n";
    cout << "3......................................Atualizar Cadastro Existente\n";
    cout << "4......................................Desativar um Cadastro\n";
    cout << "5......................................Listar\n";
    cout << "6......................................Sair\n\n";
    cout << "Digite sua ação:_\b";
    cin >> acao;

    return acao;//retorna a ação escolhida pelo usuário
}

int proximaPosicao = 0;//passa as posições e guarda quando pacientes foram cadastrados

bool executarCadastramento(string nome, string cidade, string estado, string cpf){//ETAPA CADASTRAMENTO - recebe os dados do paciente e retorna se deu certo ou não
    if(proximaPosicao < TAM){//se tiver espaço no sistema
        for(int i = 0; i < proximaPosicao; i++){//teste para saber se o cpf já esta em uso no sistema
            if(cpf == gCpfs[i]){//verificar se tem o cpf no sistema
               return false;//cpf em uso por outro paciente
               break;
            }
        }
        gNomes[proximaPosicao] = nome;//inserir dados
        gCidades[proximaPosicao] = cidade;
        gEstados[proximaPosicao] = estado;
        gCpfs[proximaPosicao] = cpf;
        gStatus[proximaPosicao] = true;
        proximaPosicao++;//mudar a posição do vetor para quando vir o próxima paciente
        return true;//cadastrado com sucesso
    }
    else{
        return false;//erro
    }
}
int verificarCpf(string cpf){//verifica a existência do cpf no sistema e retorna a posicao do cpf no vetor ou retorna -1 se não existir no sistema
    for(int i = 0; i < proximaPosicao; i++){
        if(cpf == gCpfs[i]){
            return i;//existe e retorna a posição que está o cpf
            break;
        }
    }
    return -1;//não existe pq nunca foi criado um cadastro com esse cpf
}
bool verificarStatus(string cpf){//verifica o status do paciente -> true - ativo | false - desativado
    int verificacao = verificarCpf(cpf);

    if(verificacao >= 0){
        if(gStatus[verificacao == true]){
            return true;//Status de ativo
        }
        else{
            return false;//Status de desativado
        }
    }
}
void formatarSaida(int posicao){//recebe a posição do paciente e monta seus dados
    system("cls");

    cout << "\n======= Dados do Paciente =======\n";
    cout << "Nome:" << gNomes[posicao] << endl;
    cout << "Cidade:" << gCidades[posicao] << endl;
    cout << "Estado:" << gEstados[posicao] <<endl;
    cout << "CPF:" << gCpfs[posicao] << endl;

    int verificacao = verificarStatus(gCpfs[posicao]);

    if(verificacao == true){
        cout << "Status: ATIVO\n"; 
    }
    else{
        cout << "Status: DESATIVADO\n";
    }
    cout << "=================================\n";
}
int pesquisarPaciente(string cpf){//verifica se existe e se existir exibe os dados do paciente
    int verificacao = verificarCpf(cpf);
    
    if(verificacao < 0){
        return verificacao;// -1 = não existe
    }
    else{
        int posicao = verificacao; //a função retornou a posicao do cpf e dos outros dados do paciente

        formatarSaida(posicao);//exibir dados
    }
}
bool atualizarCadastro(int posicao, int acao, string novoDado){//ETAPA ATUALIZAÇÃO DE CADASTRO --> recebe a posição do vetor para altera-lo, o que alterar e pelo que substituir
    const int NOME = 1, CIDADE = 2, ESTADO = 3, CPF = 4, STATUS = 5;//opções de ações a serem recebidas

    if(acao == NOME){
        gNomes[posicao] = novoDado;
        return true;
    }
    else if(acao == CIDADE){
        gCidades[posicao] = novoDado;
        return true;
    }
    else if(acao == ESTADO){
        gEstados[posicao] = novoDado;
        return true;
    }
    else if(acao == CPF){
        gCpfs[posicao] = novoDado;
        return true;
    }
    else if(acao == STATUS){
        gStatus[posicao] = true;
        return true;
    }
    else{
        return false;
    }
    //retorna "true" se der certo e "false" se deu errado
}
void listar(){//mostra todos os pacientes cadastrados no sistema
    cout << "======== PACIENTES ATIVOS ========\n\n";
    for(int i = 0; i < proximaPosicao; i++){
        if(gStatus[i] == true){
            cout << "\n-----------------------------\n";
            cout << "Nome: " << gNomes[i] << endl;
            cout << "Cidade: " << gCidades[i] << endl;
            cout << "Estado: " << gEstados[i] << endl;
            cout << "CPF: " << gCpfs[i] << endl;
            cout <<"-----------------------------\n";
        }
    }
    cout << "\n======== PACIENTES DESATIVADOS ========\n\n";

    for(int i = 0; i < proximaPosicao; i++){
        if(gStatus[i] == false){
            cout << "\n-----------------------------\n";
            cout << "Nome: " << gNomes[i] << endl;
            cout << "Cidade: " << gCidades[i] << endl;
            cout << "Estado: " << gEstados[i] << endl;
            cout << "CPF: " << gCpfs[i] << endl;
            cout <<"-----------------------------\n";
        }
    }
}
bool desativarCadastro(string cpf){//ETAPA DELETAR CADASTRO
    int resultado = verificarCpf(cpf);//verificar se o cpf existe no sistema

    if(resultado >= 0){//existe
        gStatus[resultado] = false;//paciente desativado do sistema
        return true;
    }
    else{//cpf não existe no sistema
        return false;
    }
}