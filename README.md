# Tratamento de Arquivos e Ordenação em Memória Secundária

## Descrição

Este projeto implementa um sistema para manipulação de arquivos binários e ordenação externa. Ele permite inserir, visualizar, alterar e trocar registros em um arquivo binário, além de realizar a leitura completa do arquivo.

## Estrutura do Projeto

- `classes.hpp`: Contém as definições das classes e a maior parte dos algoritmos do projeto, incluindo inserção, alteração e troca de registros.
- `conversao.cpp`: Implementa funções auxiliares para conversão de dados.
- `main.cpp`: Contém a função principal que gerencia a interação com o usuário.

## Funcionalidades

### Programa Principal (`main.cpp`)

1. **Inserir**: Adiciona um elemento em uma posição específica.
2. **Leitura Geral**: Exibe todos os registros do arquivo.
3. **Leitura em Determinado Espaço**: Visualiza registros de um ponto a outro.
4. **Trocar Posição**: Troca dois registros de posição.
5. **Alterar Dados**: Altera os dados de um registro específico.
6. **Sair**: Encerra o programa.

### Ordenação Externa

O projeto também inclui funcionalidades para ordenação externa de arquivos com registros repetidos e fora de ordem.

## Como Executar

1. Compile o projeto:
    ```sh
    g++ -o programa dev/main.cpp dev/conversao.cpp
    ```

2. Execute o programa:
    ```sh
    ./programa
    ```

## Arquivos de Dados

- Arquivo .csv disponível: [san_francisco_payroll_dataset.csv](https://drive.google.com/drive/folders/1WzGpaS9SNHUlrDSybl4WntzU7NMdYonE)
- Arquivo .csv com alguns ids repetidos e fora de ordem: [arquivo com ids repetidos](https://drive.google.com/file/d/1fGrcgVEWqtEsU_Gwp0d7he5VSd23L0Tn/view?usp=sharing)

## Contato

Para mais informações, entre em contato comigo, e se caso queira contribuir ao projeto, envie sua issue/PR.