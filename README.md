# Sistema de Gerenciamento de Senhas de Atendimento Clínico



## 1. Objetivo do Projeto



O projeto tem como objetivo desenvolver um sistema de gerenciamento de senhas para atendimento clínico, utilizando a linguagem de programação C.



O sistema permite cadastrar pacientes, classificá-los automaticamente conforme suas condições e organizar as filas de atendimento de acordo com as prioridades estabelecidas.



## 2. Funcionalidades



O sistema apresenta as seguintes funcionalidades:



- Cadastro de pacientes.

- Registro do gênero e da idade.

- Identificação de pacientes gestantes.

- Identificação de pacientes lactantes.

- Identificação de pessoas com necessidades especiais.

- Identificação de pessoas com condição de obesidade.

- Classificação automática dos pacientes.

- Geração de senhas sequenciais independentes.

- Consulta da próxima senha.

- Chamada do próximo paciente.

- Identificação do paciente em atendimento.

- Finalização do atendimento.

- Atualização automática das filas.

- Painel textual com informações dos atendimentos.

- Contagem de pacientes aguardando por categoria.



## 3. Categorias de Atendimento



O sistema trabalha com três categorias de atendimento:



| Código | Categoria | Condição |

|---|---|---|

| N001 | Normal | Pacientes sem condições de prioridade cadastradas |

| P001 | Preferencial | Gestantes, lactantes, pessoas com necessidades especiais, pessoas obesas, mulheres com 60 anos ou mais e homens com 65 anos ou mais |

| U001 | Urgente | Pacientes com idade superior a 80 anos |



A prioridade de atendimento segue a seguinte ordem:



1. Urgente.

2. Preferencial.

3. Normal.



A numeração das senhas é independente para cada categoria. Por exemplo:



- Normal: N001, N002, N003.

- Preferencial: P001, P002, P003.

- Urgente: U001, U002, U003.



As regras de classificação são exclusivamente didáticas e não representam uma classificação médica de risco.



## 4. Estruturas e Conceitos Utilizados



O desenvolvimento utiliza os seguintes recursos da linguagem C:



- Struct: armazenamento dos dados dos pacientes.

- Vetores: armazenamento dos pacientes nas filas.

- Filas FIFO: organização dos atendimentos por ordem de chegada.

- Variáveis inteiras: controle das idades, quantidades e contadores.

- Variáveis do tipo char: armazenamento do gênero e das senhas.

- Condicionais: classificação dos pacientes e controle das prioridades.

- Laços de repetição: execução do menu e processamento das filas.

- Funções: modularização e organização do programa.



## 5. Funções Implementadas



| Função | Descrição |

|---|---|

| lerInteiro() | Realiza a leitura e validação de números inteiros. |

| lerTexto() | Realiza a leitura e validação de textos. |

| lerSimNao() | Valida respostas afirmativas e negativas. |

| classificarPaciente() | Determina a categoria de atendimento do paciente. |

| gerarSenha() | Gera senhas sequenciais de acordo com a categoria. |

| adicionarFila() | Adiciona um paciente à fila correspondente. |

| retirarFila() | Retira o próximo paciente da fila. |

| consultarFila() | Consulta o primeiro paciente da fila. |

| cadastrarPaciente() | Realiza o cadastro completo de um paciente. |

| consultarProximaSenha() | Identifica a próxima senha a ser chamada. |

| exibirProximaSenha() | Apresenta as informações da próxima senha. |

| chamarProximaSenha() | Realiza a chamada do próximo paciente. |

| finalizarAtendimento() | Finaliza o atendimento atual. |

| exibirFila() | Apresenta os pacientes aguardando atendimento. |

| exibirPainel() | Exibe o painel geral de atendimento. |

| exibirMenu() | Apresenta as opções disponíveis no sistema. |

| main() | Coordena a execução e o funcionamento do programa. |



## 6. Menu do Sistema



Ao executar o programa, o usuário terá acesso às seguintes opções:



1. Cadastrar paciente.

2. Consultar próxima senha.

3. Chamar próximo paciente.

4. Finalizar atendimento.

5. Exibir painel de atendimento.

0. Encerrar sistema.



O sistema permite realizar vários cadastros e atendimentos durante a mesma execução.



## 7. Compilação



Para compilar o programa, é necessário possuir um compilador C, como o GCC.



Abra o terminal na pasta onde está localizado o arquivo main.c e execute:



```bash

gcc main.c -o clinica -std=c99 -Wall -Wextra -pedantic

```



## 8. Execução



Após a compilação, execute o programa de acordo com o sistema operacional.



Windows:



```bash

clinica.exe

```



Linux:



```bash

./clinica

```



## 9. Exemplos de Utilização



### Exemplo 1 - Paciente Normal



Dados informados:



- Nome: Pedro.

- Gênero: Masculino.

- Idade: 30 anos.

- Gestante: Não.

- Lactante: Não.

- Necessidade especial: Não.

- Obesidade: Não.



Resultado:



```text

Paciente: Pedro

Senha gerada: N001

Categoria: NORMAL

```



### Exemplo 2 - Paciente Preferencial



Dados informados:



- Nome: Maria.

- Gênero: Feminino.

- Idade: 60 anos.

- Gestante: Não.

- Lactante: Não.

- Necessidade especial: Não.

- Obesidade: Não.



Resultado:



```text

Paciente: Maria

Senha gerada: P001

Categoria: PREFERENCIAL

```



### Exemplo 3 - Paciente Urgente



Dados informados:



- Nome: Carlos.

- Gênero: Masculino.

- Idade: 85 anos.

- Necessidade especial: Não.

- Obesidade: Não.



Resultado:



```text

Paciente: Carlos

Senha gerada: U001

Categoria: URGENTE

```



### Exemplo 4 - Ordem de Atendimento



Considerando os três pacientes cadastrados anteriormente, a ordem de chamada será:



```text

1 - Carlos (U001) - URGENTE

2 - Maria (P001) - PREFERENCIAL

3 - Pedro (N001) - NORMAL

```



Essa ordem respeita as prioridades estabelecidas e a sequência de emissão das senhas dentro de cada categoria.



## 10. Painel de Atendimento



O painel textual apresenta:



- Senha atualmente chamada.

- Nome do paciente em atendimento.

- Categoria do atendimento atual.

- Quantidade de pacientes aguardando por categoria.

- Lista das próximas senhas nas filas.



Exemplo:



```text

============================================

     PAINEL DE ATENDIMENTO

============================================

SENHA ATUAL: U001

PACIENTE: Carlos

CATEGORIA: URGENTE

--------------------------------------------

QUANTIDADE DE PACIENTES EM ESPERA

Urgentes: 0

Preferenciais: 1

Normais: 1

--------------------------------------------

PROXIMAS SENHAS AGUARDANDO



[URGENTES]



[PREFERENCIAIS]

 P001 - Maria



[NORMAIS]

 N001 - Pedro

============================================

```



## 11. Regras de Funcionamento



- Pacientes urgentes possuem prioridade sobre preferenciais e normais.

- Pacientes preferenciais possuem prioridade sobre normais.

- A ordem de chegada é respeitada dentro de cada categoria.

- Pacientes que já foram chamados não retornam à fila.

- Um novo paciente somente poderá ser chamado após a finalização do atendimento anterior.

- O sistema permite o cadastro de vários pacientes durante sua execução.

- As entradas são validadas para evitar dados inválidos.

- O sistema possui limite de armazenamento de 1000 pacientes por fila.



## 12. Considerações Finais



O desenvolvimento deste projeto permitiu aplicar conceitos fundamentais da programação estruturada em linguagem C.



Foram utilizados estruturas de dados, vetores, filas, funções, condicionais e estruturas de repetição para desenvolver uma solução funcional de gerenciamento de atendimento clínico.



A aplicação busca organizar o processo de atendimento, respeitando as categorias de prioridade e a ordem de chegada dos pacientes.
