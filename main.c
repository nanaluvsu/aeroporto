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
    printf("[2] Registrar novo voo entre aeroportos;\n"); //através do número do voo e dos códigos dos aeroportos de origem e destino
    printf("[3] Remover voo;\n"); //através do número
    printf("[4] Listar voos que partem de um aeroporto;\n"); //listar número e nome da cidade de destino
    printf("[5] Listar possíveis trajetos que passam por um aeroporto;\n"); //não apenas chegar no aeroporto, mas também passar por ele
    printf("[0] Sair.\n");

    int op;
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        /* Reg aeroporto */
        break;
    case 2:
        /* Reg voo */
        break;
    case 3:
        /* Remover voo */
        break;
    case 4:
        /* Listar voos partindo */
        break;
    case 5:
        /* Listar voos passando */
        break;
    case 0:
        exit(0);
        break;
    default:
        break;
    }
    removerGrafo(grafo);
}