#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>



#define MAX_PACIENTES 1000

#define TAM_NOME 100

#define TAM_SENHA 20



#define NORMAL 0

#define PREFERENCIAL 1

#define URGENTE 2



typedef struct {

  char nome[TAM_NOME];

  int idade;

  char genero;

  int gestante;

  int lactante;

  int necessidadeEspecial;

  int obeso;

  char senha[TAM_SENHA];

  int categoria;

} Paciente;



typedef struct {

  Paciente pacientes[MAX_PACIENTES];

  int inicio;

  int fim;

  int quantidade;

} Fila;



Fila filaNormal = {{0}, 0, 0, 0};

Fila filaPreferencial = {{0}, 0, 0, 0};

Fila filaUrgente = {{0}, 0, 0, 0};



int contadorNormal = 0;

int contadorPreferencial = 0;

int contadorUrgente = 0;



Paciente pacienteAtual;

int existeAtendimento = 0;



int lerInteiro(char mensagem[], int minimo, int maximo) {

  char entrada[100];

  char *fim;

  long valor;



  while (1) {

    printf("%s", mensagem);



    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {

      printf("Erro na leitura. Tente novamente.\n");

      continue;

    }



    valor = strtol(entrada, &fim, 10);



    if (fim == entrada || (*fim != '\n' && *fim != '\0')) {

      printf("Entrada invalida. Digite um numero inteiro.\n");

      continue;

    }



    if (valor < minimo || valor > maximo) {

      printf("Valor fora do intervalo permitido (%d a %d).\n",

          minimo, maximo);

      continue;

    }



    return (int) valor;

  }

}



void lerTexto(char mensagem[], char destino[], int tamanho) {

  while (1) {

    printf("%s", mensagem);



    if (fgets(destino, tamanho, stdin) == NULL) {

      continue;

    }



    destino[strcspn(destino, "\n")] = '\0';



    if (strlen(destino) == 0) {

      printf("O campo nao pode ficar vazio.\n");

      continue;

    }



    if (strchr(destino, '\n') == NULL &&

      strlen(destino) == tamanho - 1) {

      int caractere;



      while ((caractere = getchar()) != '\n' &&

          caractere != EOF);



      printf("Texto muito longo. Tente novamente.\n");

      continue;

    }



    return;

  }

}



int lerSimNao(char mensagem[]) {

  char resposta[20];



  while (1) {

    printf("%s (S/N): ", mensagem);



    if (fgets(resposta, sizeof(resposta), stdin) == NULL) {

      continue;

    }



    char opcao = toupper((unsigned char) resposta[0]);



    if ((opcao == 'S' || opcao == 'N') &&

      (resposta[1] == '\n' || resposta[1] == '\0')) {

      return opcao == 'S';

    }



    printf("Resposta invalida. Digite S ou N.\n");

  }

}



int classificarPaciente(Paciente paciente) {

  if (paciente.idade > 80) {

    return URGENTE;

  }



  if (paciente.gestante ||

    paciente.lactante ||

    paciente.necessidadeEspecial ||

    paciente.obeso) {

    return PREFERENCIAL;

  }



  if (paciente.genero == 'F' && paciente.idade >= 60) {

    return PREFERENCIAL;

  }



  if (paciente.genero == 'M' && paciente.idade >= 65) {

    return PREFERENCIAL;

  }



  return NORMAL;

}



void gerarSenha(Paciente *paciente) {

  if (paciente->categoria == URGENTE) {

    contadorUrgente++;

    snprintf(paciente->senha, TAM_SENHA,

         "U%03d", contadorUrgente);

  }

  else if (paciente->categoria == PREFERENCIAL) {

    contadorPreferencial++;

    snprintf(paciente->senha, TAM_SENHA,

         "P%03d", contadorPreferencial);

  }

  else {

    contadorNormal++;

    snprintf(paciente->senha, TAM_SENHA,

         "N%03d", contadorNormal);

  }

}



int adicionarFila(Fila *fila, Paciente paciente) {

  if (fila->quantidade >= MAX_PACIENTES) {

    return 0;

  }



  fila->pacientes[fila->fim] = paciente;

  fila->fim = (fila->fim + 1) % MAX_PACIENTES;

  fila->quantidade++;



  return 1;

}



int retirarFila(Fila *fila, Paciente *paciente) {

  if (fila->quantidade == 0) {

    return 0;

  }



  *paciente = fila->pacientes[fila->inicio];

  fila->inicio = (fila->inicio + 1) % MAX_PACIENTES;

  fila->quantidade--;



  return 1;

}



int consultarFila(Fila *fila, Paciente *paciente) {

  if (fila->quantidade == 0) {

    return 0;

  }



  *paciente = fila->pacientes[fila->inicio];



  return 1;

}



void cadastrarPaciente() {

  Paciente paciente;



  printf("\n========== CADASTRO DE PACIENTE ==========\n");



  lerTexto("Nome do paciente: ",

       paciente.nome, TAM_NOME);



  printf("\nGenero:\n");

  printf("1 - Feminino\n");

  printf("2 - Masculino\n");

  printf("3 - Outro\n");



  int genero = lerInteiro("Escolha: ", 1, 3);



  if (genero == 1) {

    paciente.genero = 'F';

  }

  else if (genero == 2) {

    paciente.genero = 'M';

  }

  else {

    paciente.genero = 'O';

  }



  paciente.idade = lerInteiro("Idade: ", 0, 120);



  paciente.gestante = 0;



  if (paciente.genero == 'F') {

    paciente.gestante =

      lerSimNao("A paciente esta gestante?");

  }



  paciente.lactante =

    lerSimNao("O paciente e lactante?");



  paciente.necessidadeEspecial =

    lerSimNao("Possui necessidade especial?");



  paciente.obeso =

    lerSimNao("Possui condicao de obesidade?");



  paciente.categoria = classificarPaciente(paciente);



  gerarSenha(&paciente);



  int sucesso = 0;



  if (paciente.categoria == URGENTE) {

    sucesso = adicionarFila(&filaUrgente, paciente);

  }

  else if (paciente.categoria == PREFERENCIAL) {

    sucesso = adicionarFila(&filaPreferencial, paciente);

  }

  else {

    sucesso = adicionarFila(&filaNormal, paciente);

  }



  if (!sucesso) {

    printf("\nFila cheia. Cadastro nao foi concluido.\n");

    return;

  }



  printf("\n========== CADASTRO CONCLUIDO ==========\n");

  printf("Paciente: %s\n", paciente.nome);

  printf("Senha gerada: %s\n", paciente.senha);



  if (paciente.categoria == URGENTE) {

    printf("Categoria: URGENTE\n");

  }

  else if (paciente.categoria == PREFERENCIAL) {

    printf("Categoria: PREFERENCIAL\n");

  }

  else {

    printf("Categoria: NORMAL\n");

  }

}



int consultarProximaSenha(Paciente *paciente) {

  if (consultarFila(&filaUrgente, paciente)) {

    return 1;

  }



  if (consultarFila(&filaPreferencial, paciente)) {

    return 1;

  }



  if (consultarFila(&filaNormal, paciente)) {

    return 1;

  }



  return 0;

}



void exibirProximaSenha() {

  Paciente paciente;



  printf("\n========== PROXIMA SENHA ==========\n");



  if (!consultarProximaSenha(&paciente)) {

    printf("Nao existem pacientes aguardando.\n");

    return;

  }



  printf("Senha: %s\n", paciente.senha);

  printf("Paciente: %s\n", paciente.nome);



  if (paciente.categoria == URGENTE) {

    printf("Categoria: URGENTE\n");

  }

  else if (paciente.categoria == PREFERENCIAL) {

    printf("Categoria: PREFERENCIAL\n");

  }

  else {

    printf("Categoria: NORMAL\n");

  }

}



void chamarProximaSenha() {

  if (existeAtendimento) {

    printf("\nFinalize o atendimento atual antes de chamar outro paciente.\n");

    return;

  }



  if (retirarFila(&filaUrgente, &pacienteAtual)) {

    existeAtendimento = 1;

  }

  else if (retirarFila(&filaPreferencial, &pacienteAtual)) {

    existeAtendimento = 1;

  }

  else if (retirarFila(&filaNormal, &pacienteAtual)) {

    existeAtendimento = 1;

  }

  else {

    printf("\nNao existem pacientes aguardando atendimento.\n");

    return;

  }



  printf("\n========== CHAMADA DE PACIENTE ==========\n");

  printf("SENHA: %s\n", pacienteAtual.senha);

  printf("PACIENTE: %s\n", pacienteAtual.nome);



  if (pacienteAtual.categoria == URGENTE) {

    printf("CATEGORIA: URGENTE\n");

  }

  else if (pacienteAtual.categoria == PREFERENCIAL) {

    printf("CATEGORIA: PREFERENCIAL\n");

  }

  else {

    printf("CATEGORIA: NORMAL\n");

  }



  printf("\nPaciente chamado para atendimento!\n");

}



void finalizarAtendimento() {

  if (!existeAtendimento) {

    printf("\nNao existe atendimento em andamento.\n");

    return;

  }



  printf("\n========== ATENDIMENTO FINALIZADO ==========\n");

  printf("Paciente: %s\n", pacienteAtual.nome);

  printf("Senha: %s\n", pacienteAtual.senha);

  printf("Atendimento concluido com sucesso.\n");



  existeAtendimento = 0;



  printf("A fila foi atualizada.\n");

}



void exibirFila(Fila *fila) {

  for (int i = 0; i < fila->quantidade; i++) {

    int indice = (fila->inicio + i) % MAX_PACIENTES;



    printf(" %s - %s\n",

        fila->pacientes[indice].senha,

        fila->pacientes[indice].nome);

  }

}



void exibirPainel() {

  printf("\n");

  printf("============================================\n");

  printf("     PAINEL DE ATENDIMENTO      \n");

  printf("============================================\n");



  if (existeAtendimento) {

    printf("SENHA ATUAL: %s\n", pacienteAtual.senha);

    printf("PACIENTE: %s\n", pacienteAtual.nome);



    if (pacienteAtual.categoria == URGENTE) {

      printf("CATEGORIA: URGENTE\n");

    }

    else if (pacienteAtual.categoria == PREFERENCIAL) {

      printf("CATEGORIA: PREFERENCIAL\n");

    }

    else {

      printf("CATEGORIA: NORMAL\n");

    }

  }

  else {

    printf("SENHA ATUAL: Nenhuma\n");

  }



  printf("--------------------------------------------\n");

  printf("QUANTIDADE DE PACIENTES EM ESPERA\n");



  printf("Urgentes: %d\n", filaUrgente.quantidade);

  printf("Preferenciais: %d\n", filaPreferencial.quantidade);

  printf("Normais: %d\n", filaNormal.quantidade);



  printf("--------------------------------------------\n");

  printf("PROXIMAS SENHAS AGUARDANDO\n");



  if (filaUrgente.quantidade == 0 &&

    filaPreferencial.quantidade == 0 &&

    filaNormal.quantidade == 0) {

    printf("Nenhum paciente aguardando.\n");

  }



  printf("\n[URGENTES]\n");

  exibirFila(&filaUrgente);



  printf("\n[PREFERENCIAIS]\n");

  exibirFila(&filaPreferencial);



  printf("\n[NORMAIS]\n");

  exibirFila(&filaNormal);



  printf("============================================\n");

}



void exibirMenu() {

  printf("\n");

  printf("============================================\n");

  printf("  SISTEMA DE ATENDIMENTO CLINICO     \n");

  printf("============================================\n");



  printf("1 - Cadastrar paciente\n");

  printf("2 - Consultar proxima senha\n");

  printf("3 - Chamar proximo paciente\n");

  printf("4 - Finalizar atendimento\n");

  printf("5 - Exibir painel de atendimento\n");

  printf("0 - Encerrar sistema\n");



  printf("============================================\n");

}



int main() {

  int opcao;



  printf("Bem-vindo ao Sistema de Gerenciamento de Senhas!\n");



  do {

    exibirMenu();



    opcao = lerInteiro("Escolha uma opcao: ", 0, 5);



    switch (opcao) {

      case 1:

        cadastrarPaciente();

        break;



      case 2:

        exibirProximaSenha();

        break;



      case 3:

        chamarProximaSenha();

        break;



      case 4:

        finalizarAtendimento();

        break;



      case 5:

        exibirPainel();

        break;



      case 0:

        if (existeAtendimento) {

          printf("\nFinalize o atendimento atual antes de encerrar.\n");

        }

        else {

          printf("\nSistema encerrado. Ate logo!\n");

        }

        break;



      default:

        printf("\nOpcao invalida.\n");

    }



  } while (opcao != 0 || existeAtendimento);



  return 0;

}