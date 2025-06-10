#include "grafo.c"
#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Grafo *grafo = criar_grafo();
    if (!grafo)
    {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }
    printf("Estrutura e Recuperacao de Dados II\nTrabalho de Grafos.\n\n");
    adicionar_node(grafo, "GRU", 1, "Sao Paulo");      // adicionando aeroportos eba(esse é de SP)
    adicionar_node(grafo, "GIG", 2, "Rio de Janeiro"); // RJ
    adicionar_node(grafo, "BSB", 3, "Brasilia");       // Brasilia
    adicionar_node(grafo, "SSA", 4, "Salvador");       // Salvador
    adicionar_node(grafo, "CNF", 5, "Belo Horizonte"); // Belo Horizonte

    int op;
    do
    {
        printf("\n---------------------------------\n");
        printf("\nEscolha uma opcao:\n");
        printf("[1] Registrar novo aeroporto;\n");
        printf("[2] Registrar novo voo entre aeroportos;\n");
        printf("[3] Remover voo;\n");
        printf("[4] Listar voos que partem de um aeroporto;\n");
        printf("[5] Listar possiveis trajetos que passam por um aeroporto;\n");
        printf("[0] Sair.\n");
        printf("Opcao: ");
        /*if (scanf("%d", &op) != 1)
        {
            printf("Entrada invalida. Certifique-se de digitar um numero.\n");
            op = 0; // Force exit to prevent infinite loop
            while (getchar() != '\n')
                ; // Clear buffer
            continue;
        }*/

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("Registro de aeroporto\n\n");
            U8 sigla[4];
            U32 codigo;
            char estado[50];
            printf("\nDigite o codigo do aeroporto: ");
            scanf("%u", &codigo);
            printf("Digite a sigla do aeroporto: ");
            scanf("%s", sigla);
            printf("\nDigite o estado do aeroporto(pode ser abreviacao. Exemplo: Sao Paulo -> SP): ");
            scanf("%s", estado);

            if (adicionar_node(grafo, sigla, codigo, estado))
            {
                printf("eba :3 ta tendo %s \n", sigla);
                listaAeroportos(grafo);
            }
            else
            {
                printf("Deu erro :c\n");
            }
            break;
        case 2:
            printf("Registro de voo\n\n");
            U32 id, origem, destino;
            printf("Digite o codigo do voo: ");
            scanf("%u", &id);
            printf("Digite o codigo do aeroporto de origem: ");
            scanf("%u", &origem);
            printf("Digite o codigo do aeroporto de destino: ");
            scanf("%u", &destino);
            Relacionamento rel = {id, origem, destino};
            if (adicionar_rel(grafo, rel))
            {
                printf("ta tendo :3\n");
            }
            else
            {
                printf("noggers\n");
            }
            break;
        case 3:
            printf("Remocao de voo\n\n");
            printf("Digite o codigo do voo a ser removido: ");
            scanf("%u", &codigo);
            Relacionamento remover = cade(grafo, codigo);
            if (remover.id != 0)
            {
                if (remover_rel(grafo, remover))
                {
                    printf("comi :3\n");
                }
                else
                {
                    printf("explodiu\n");
                }
            }
            else
            {
                printf("nao ta tendo\n");
            }

            // printf("Remocao de voo não implementada\n\n"); // ta implementada eu so fui burra nao consegui fazer funcionar(provavelmente o do augusto vai dar certo espero)
            break;
        case 4:
            printf("Listar voos que partem de um aeroporto\n\n");
            U32 origem_codigo;
            printf("Digite o codigo do aeroporto de origem: ");
            scanf("%u", &origem_codigo);
            if (!busca_og(grafo, origem_codigo))
            {
                printf("Nenhum voo encontrado com origem no aeroporto especificado.\n");
            }
            break;
        case 5:
            /* Listar voos passando */
            break;
        case 0:
            printf("tchau :(\n");
            removerGrafo(grafo);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (op != 0);

    removerGrafo(grafo);
    return 0;
}