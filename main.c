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
    printf("Estrutura e Recuperacao de Dados II\nTrabalho de Grafos.\n\n");
    adicionar_node(grafo, "GRU", 1); // adicionando aeroportos eba(esse é de SP)
    adicionar_node(grafo, "GIG", 2); // RJ
    adicionar_node(grafo, "BSB", 3); // Brasilia
    adicionar_node(grafo, "SSA", 4); // Salvador
    adicionar_node(grafo, "CNF", 5); //Belo Horizonte

    int op;
    do {
        printf("\nEscolha uma opcao:\n");
        printf("[1] Registrar novo aeroporto;\n");
        printf("[2] Registrar novo voo entre aeroportos;\n");
        printf("[3] Remover voo;\n");
        printf("[4] Listar voos que partem de um aeroporto;\n");
        printf("[5] Listar possiveis trajetos que passam por um aeroporto;\n");
        printf("[0] Sair.\n");

        scanf("%d", &op);
        
        switch (op)
        {
        case 1:
            printf("Registro de aeroporto\n\n"); 
            U8 sigla[3];
            U32 codigo;
            printf("Digite a sigla do aeroporto: ");
            scanf("%s", sigla);
            printf("\nDigite o codigo do aeroporto: ");
            scanf("%u", &codigo);
            if(adicionar_node(grafo, sigla, codigo)) {
                printf("eba :3 ta tendo %s \n", sigla);
                listaAeroportos(grafo);
            } else {
                printf("Deu erro :c\n");
            }
            break;
        case 2:
            printf("Registro de voo\n\n");
            U32 origem, destino;
            printf("Digite o codigo do aeroporto de origem: ");
            scanf("%u", &origem);
            printf("Digite o codigo do aeroporto de destino: ");
            scanf("%u", &destino);
            U32 id = 0;
            Relacionamento rel = {id, origem, destino};
            if (adicionar_rel(grafo, rel)) {
                printf("ta tendo :3\n");
            } else {
                printf("noggers\n");
            }
            break;
        case 3:
           printf("Remoção de voo\n\n");
           printf("Digite o codigo do voo a ser removido: ");
              scanf("%u", &codigo);
            Relacionamento remover = {0, 
                codigo,
                 0}; 
            if (remove_rel(grafo, remover)) {
                printf("comi");
            } else {
                printf("nao existe explodiu");
            }
            break;
        case 4:
            /* Listar voos partindo */
            break;
        case 5:
            /* Listar voos passando */
            break;
        case 0:
            printf("tchau :(\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 0);

    removerGrafo(grafo);
    return 0;
}