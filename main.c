#include "grafo.c"
#include <stdio.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Portuguese");
    Grafo* grafo = criar_grafo();
    if (!grafo) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }
    printf("Estrutura e Recuperação de Dados II\nTrabalho de Grafos.\n\n");

    printf("Escolha uma opção:\n");
    printf("[1] Registrar novo aeroporto;\n");
    printf("[2] Registrar nova rota entre aeroportos;\n");
    printf("[3] Listar rotas que partem de um aeroporto;\n");
    printf("[4] Listar possíveis trajetos que passam por um aeroporto;\n"); //não apenas chegar no aeroporto, mas também passar por ele
    printf("[0] Sair.\n");

    int op;
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        /* Reg aeroporto */
        break;
    case 2:
        /* Reg rota */
        break;
    case 3:
        /* Listar rotas */
        break;
    case 4:
        /* Listar trajetos */
        break;
    case 0:
        exit(0);
        break;
    default:
        break;
    }
    removerGrafo(grafo);
}