
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

struct musica
{
    int codigo_musica;
    char nome_musica[20];
    char artista[20];
    char genero[20];
    float duracao;
};

struct playlist
{
    int codigo_playlist;
    char nome_playlist[20];
    char descricao[40];
    char data_criacao[10];
};

struct musica_playlist
{
    int codigo_playlist;
    int codigo_musica;
};

int menu()
{
    int op;
    printf("Menu principal:\n");
    printf("\t1. Submenu de Músicas \n");
    printf("\t2. Submenu de Playlist \n");
    printf("\t3. Submenu de Musicas_playlist \n");
    printf("\t4. Submenu Relatórios \n");
    printf("\t5. Sair \n");
    scanf("%d", &op);
    return op;
}

// #########################    MÚSICAS    ####################################

struct musica *alocar_memoria_musica(int qtd)
{
    struct musica *vet;
    vet = (struct musica *)malloc(qtd * sizeof(struct musica));
    return vet;
}

void libera_memoria_musica(struct musica *cont_musica)
{
    free(cont_musica);
}

void listar_todas_musicas(struct musica vetor_musica[], int cont_musica)
{
    int i;
    for (i = 0; i < cont_musica; i++)
    {
        printf("\nCódigo da Música: %d", vetor_musica[i].codigo_musica);
        printf("\nNome da Música: %s", vetor_musica[i].nome_musica);
        printf("\nArtista: %s", vetor_musica[i].artista);
        printf("\nGênero da Música: %s", vetor_musica[i].genero);
        printf("\nDuracão da Música: %f", vetor_musica[i].duracao);
    }
    system("pause");
}

int listar_uma_musica(struct musica vetor_musica[], int cont_musica)
{
    int codigo, i;
    scanf("%d", &codigo);
    for (i = 0; i < cont_musica; i++)
    {
        if (codigo == vetor_musica[i].codigo_musica)
        {
            printf("\nNome da Música: %s ", vetor_musica[i].nome_musica);
            printf("\nArtista: %s ", vetor_musica[i].artista);
            printf("\nGênero da Música: %d ", vetor_musica[i].genero);
            printf("\nDuracão da Música: %d ", vetor_musica[i].duracao);
            return 1;
        }
    }
    return 0;
}

int incluir_musica(struct musica vetor_musica[], int *cont_musica, int qtd)
{
    if (*cont_musica < qtd) 
    {
        printf("\nDigite o código da música");
        scanf("%d", &vetor_musica[*cont_musica].codigo_musica);
        getchar();

        printf("\nDigite o nome da música");
        fgets(vetor_musica[*cont_musica].nome_musica, (sizeof(vetor_musica[*cont_musica].nome_musica)), stdin);
        vetor_musica[*cont_musica].nome_musica[strcspn(vetor_musica[*cont_musica].nome_musica, "\n")] = '\0'; 

        printf("\nDigite o artista da música");
        fgets(vetor_musica[*cont_musica].artista, sizeof(vetor_musica[*cont_musica].artista), stdin);
        vetor_musica[*cont_musica].artista[strcspn(vetor_musica[*cont_musica].artista, "\n")] = '\0'; 

        printf("\nDigite o gênero da música");
        fgets(vetor_musica[*cont_musica].genero, (sizeof(vetor_musica[*cont_musica].genero)), stdin);
        vetor_musica[*cont_musica].genero[strcspn(vetor_musica[*cont_musica].genero, "\n")] = '\0'; 

        printf("\nDigite a duracao da música");
        scanf("%f", &vetor_musica[*cont_musica].duracao);
        getchar();
        (*cont_musica)++;
        return 1;
    }
    return 0;
}

void alterar_musica(struct musica vetor_musica[], int cont_musica)
{
    int achou = 0;
    int codigo, i;
    char novo_nome[20], novo_artista[20], novo_genero[20];
    float nova_duracao = 0;
    printf("Digite o código da música que deseja alterar");
    scanf("%d", &codigo);
    getchar();
    for (i = 0; i < cont_musica; i++)
    {
        if (vetor_musica[i].codigo_musica == codigo)
        {
            printf("Digite o novo nome da música");         
            fgets(novo_nome, sizeof(novo_nome), stdin);     
            novo_nome[strcspn(novo_nome, "\n")] = '\0';     
            strcpy(vetor_musica[i].nome_musica, novo_nome); 

            printf("Digite o Artista:");
            fgets(novo_artista, sizeof(novo_artista), stdin);
            novo_artista[strcspn(novo_artista, "\n")] = '\0'; 
            strcpy(vetor_musica[i].artista, novo_artista);

            printf("Digite o gênero:");
            fgets(novo_genero, sizeof(novo_genero), stdin);
            novo_genero[strcspn(novo_genero, "\n")] = '\0'; 
            strcpy(vetor_musica[i].genero, novo_genero);

            printf("Digite a duracão:");
            scanf("%f", &nova_duracao);
            getchar();
            vetor_musica[i].duracao = nova_duracao;
            achou = 1;
            break;
        }
    }
    if (achou == 0)
        printf("Música não encontrada!\n");
}

int buscar_musica(struct musica vetor_musica[], int cont_musica, int codigo)
{
    int i;
    printf("Digite o código da musica:");
    scanf("%d", &codigo);
    getchar();
    for (i = 0; i < cont_musica; i++)
    {
        if (codigo == vetor_musica[i].codigo_musica)
            return i;
    }
    return -1;
}

int excluir_musica(struct musica vetor_musica[], int *cont_musica, int codigo)
{
    int i, res;
    res = buscar_musica(vetor_musica, *cont_musica, codigo);
    if (res != 0)
    {
        for (i = res; i < (*cont_musica) - 1; i++)
        {
            vetor_musica[i] = vetor_musica[i + 1];
        }
        (*cont_musica)--;
        return 1;
    }
    return 0;
}

void salvar_musicas(struct musica vetor_musica[], int cont_musica)
{
    FILE *arq_musica;
    arq_musica = fopen("musicas.dat", "wb");
    if (arq_musica == NULL)
    {
        printf("Não foi possível abrir o arquivo. \n");
        return;
    }
    else
        fwrite(vetor_musica, sizeof(struct musica), cont_musica, arq_musica);
    fclose(arq_musica);
}

void carregar_musicas(struct musica vetor_musica[], int *cont_musica, int qtd)
{
    FILE *arq_musica;
    arq_musica = fopen("musicas.dat", "rb");

    if (arq_musica == NULL)
    {
        printf("Arquivo não encontrado (será criado ao salvar). \n");
        *cont_musica = 0;
        return;
    }

    *cont_musica = fread(vetor_musica, sizeof(struct musica), qtd, arq_musica);

    fclose(arq_musica);
}

void submenu_musica(struct musica vetor_musica[], int *cont_musica, int qtd)
{
    int opc, res, exclusao, codigo;

    do
    {
        printf("\n--- Submenu Músicas ---\n");
        printf("\t1. Listar todas as músicas\n");
        printf("\t2. Listar uma música\n");
        printf("\t3. Incluir Música\n");
        printf("\t4. Alterar Música\n");
        printf("\t5. Excluir Música\n");
        printf("\t6. Voltar ao menu principal\n");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            printf("\nListagem de músicas...\n");
            listar_todas_musicas(vetor_musica, *cont_musica);
            break;

        case 2:
            printf("Listar uma música:\n");
            listar_uma_musica(vetor_musica, *cont_musica);
            break;

        case 3:
            printf("Inclusão de música:\n");
            incluir_musica(vetor_musica, cont_musica, qtd);
            break;

        case 4:
            printf("Alterando música:\n");
            alterar_musica(vetor_musica, *cont_musica);
            break;

        case 5:
            printf("Digite o código para excluir: ");
            scanf("%d", &codigo);
            exclusao = excluir_musica(vetor_musica, cont_musica, codigo); 
            if (exclusao == 1)
                printf("Sucesso!\n");
            else
                printf("Erro.\n");
            salvar_musicas(vetor_musica, *cont_musica);
            break;

        case 6:
            printf("Voltando...\n");
            break;

        default:
            printf("Opcao inválida!");
        }
    } while (opc != 6);
    salvar_musicas(vetor_musica, *cont_musica);
}

// ############################    PLAYLIST    ###################################

struct playlist *alocar_memoria_playlist(int qtd)
{
    struct playlist *vet;
    vet = (struct playlist *)malloc(qtd * sizeof(struct playlist));
    return vet;
}

void libera_memoria_playlist(struct playlist *cont_playlist)
{
    free(cont_playlist);
}

void listar_todas_playlist(struct playlist vetor_playlist[], int cont_playlist)
{
    int i;
    for (i = 0; i < cont_playlist; i++)
    {
        printf("\nCódigo da playlist: %d", vetor_playlist[i].codigo_playlist);
        printf("\nNome da Playlist: %s", vetor_playlist[i].nome_playlist);
        printf("\nDescricao: %s", vetor_playlist[i].descricao);
        printf("\nData de criacao: %s", vetor_playlist[i].data_criacao);
    }
    getchar();
}
int listar_uma_playlist(struct playlist vetor_playlist[], int cont_playlist, int codigo)
{
    int i;
    for (i = 0; i < cont_playlist; i++)
    {
        if (codigo == vetor_playlist[i].codigo_playlist)
        {
            printf("\nNome da playlist: %s", vetor_playlist[i].nome_playlist);
            printf("\nDescricao da playlist: %s", vetor_playlist[i].descricao);
            printf("\nData de criacao: %s", vetor_playlist[i].data_criacao);
            return 1;
        }
    }
    return 0;
}
int incluir_playlist(struct playlist vetor_playlist[], int *cont_playlist, int codigo, int qtd)
{
    if (*cont_playlist < qtd)
    {
        vetor_playlist[*cont_playlist].codigo_playlist = codigo;
        printf("Digite o nome da playlist");
        fgets(vetor_playlist[*cont_playlist].nome_playlist, (sizeof(vetor_playlist[*cont_playlist].nome_playlist)), stdin);
        vetor_playlist[*cont_playlist].nome_playlist[strcspn(vetor_playlist[*cont_playlist].nome_playlist, "\n")] = '\0';

        printf("Digite a descricao da playlist");
        fgets(vetor_playlist[*cont_playlist].descricao, (sizeof(vetor_playlist[*cont_playlist].descricao)), stdin);
        vetor_playlist[*cont_playlist].descricao[strcspn(vetor_playlist[*cont_playlist].descricao, "\n")] = '\0';

        printf("Digite a data de criacao");
        fgets(vetor_playlist[*cont_playlist].data_criacao, (sizeof(vetor_playlist[*cont_playlist].data_criacao)), stdin);
        vetor_playlist[*cont_playlist].data_criacao[strcspn(vetor_playlist[*cont_playlist].data_criacao, "\n")] = '\0';

        (*cont_playlist)++;
        return 1;
    }
    return 0;
}

int buscar_playlist(struct playlist vetor_playlist[], int cont_playlist, int codigo)
{
    int i;
    for (i = 0; i < cont_playlist; i++)
    {
        if (codigo == vetor_playlist[i].codigo_playlist)
            return i;
    }
    return -1;
}

void alterar_playlist(struct playlist vetor_playlist[], int cont_playlist, int codigo, int res)
{
    char novo_nome[20], nova_descricao[20], nova_data[20];

    printf("Digite o novo nome da playlist: \n");
    fgets(novo_nome, sizeof(novo_nome), stdin);
    strcpy(vetor_playlist[res].nome_playlist, novo_nome);

    printf("Digite a nova descricao: \n");
    fgets(nova_descricao, sizeof(nova_descricao), stdin);
    nova_descricao[strcspn(nova_descricao, "\n")] = '\0';
    strcpy(vetor_playlist[res].descricao, nova_descricao);

    printf("Digite a nova data: \n");
    fgets(nova_data, sizeof(nova_data), stdin);
    nova_data[strcspn(nova_data, "\n")] = '\0';
    strcpy(vetor_playlist[res].data_criacao, nova_data);
}

int excluir_playlist(struct playlist vetor_playlist[], int *cont_playlist, int res)
{
    int i;
    for (i = res; i < (*cont_playlist) - 1; i++)
    {
        vetor_playlist[i] = vetor_playlist[i + 1];
    }
    (*cont_playlist)--;
    return 1;
}

void salvar_playlist(struct playlist vetor_playlist[], int *cont_playlist)
{
    FILE *arq_playlist;
    arq_playlist = fopen("playlist.dat", "wb");
    if (arq_playlist == NULL)
    {
        printf("Não foi possível abrir o arquivo. \n");
        return;
    }
    else
        fwrite(vetor_playlist, sizeof(struct playlist), *cont_playlist, arq_playlist);
    fclose(arq_playlist);
}

void carregar_playlist(struct playlist vetor_playlist[], int *cont_playlist)
{
    FILE *arq_playlist;
    arq_playlist = fopen("playlist.dat", "rb");
    if (arq_playlist == NULL)
    {
        printf("Não foi possível carregar o arquivo. \n");
        return;
    }
    else
        fread(vetor_playlist, sizeof(struct playlist), *cont_playlist, arq_playlist);
    fclose(arq_playlist);
}

int submenu_playlist(struct playlist vetor[], int *cont, int qtd)
{
    struct playlist *vetor_playlist;
    int opc, res, codigo, exclusao, cont_playlist = 0;
    do
    {
        printf("\n");
        printf("\t1. Listar todas as playlist\n");
        printf("\t2. Listar uma playlist\n");
        printf("\t3. Incluir Playlist\n");
        printf("\t4. Alterar Playlist\n");
        printf("\t5. Excluir Playlist\n");
        printf("\t6. Sair\n");
        scanf("%d", &opc);
        getchar();
        switch (opc)
        {
        case 1:
            printf(" Listagem das playlists");
            listar_todas_playlist(vetor_playlist, cont_playlist);
            break;

        case 2:
            printf("Digite o codigo da playlist que deseja buscar");
            scanf("%d", &codigo);
            getchar();
            if (listar_uma_playlist(vetor_playlist, cont_playlist, codigo) == 1)
                printf("\n");
            else
                printf("Musica nao encontrada");
            break;

        case 3:
            printf("Digite o codigo da playlist que deseja incluir:");
            scanf("%d", &codigo);
            getchar();
            res = buscar_playlist(vetor_playlist, cont_playlist, codigo);
            if (res == -1)
            {
                incluir_playlist(vetor_playlist, &cont_playlist, codigo, qtd);
                printf("\n-----------------Playlist incluida com sucesso!-------------------\n");
            }
            else
                printf("Não foi possível incluir essa música");
            break;

        case 4:
            printf("Qual o codigo da playlist que deseja fazer a alteracao: \n");
            scanf("%d", &codigo);
            getchar();
            res = buscar_playlist(vetor_playlist, cont_playlist, codigo);
            if (res != -1)
            {
                alterar_playlist(vetor_playlist, cont_playlist, codigo, res);
                printf("Alteracao feita com sucesso!");
            }
            else
                printf("Não foi possível alterar.");
            break;

        case 5:
            printf("Digite o código da playlist que deseja excluir");
            scanf("%d", &codigo);
            getchar();
            res = buscar_playlist(vetor_playlist, cont_playlist, codigo);
            if (res != -1)
            {
                exclusao = excluir_playlist(vetor_playlist, &cont_playlist, res);
                printf("Exclusão realizada com sucesso!");
            }
            else
                printf("Nao foi possível fazer a exclusão");

            break;
        case 6:
            printf("Saindo do submenu musicas");
            break;
        default:
            printf("Opcao inválida");
        }

    } while (opc != 6);
    salvar_playlist(vetor_playlist, &cont_playlist);
}

// ##########################    MUSICAS PLAYLIST    ##############################

int buscar_musica_playlist_mus(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, int codigo)
{
    int i;
    for (i = 0; i < cont_musica_playlist; i++)
    {
        if (vetor_musica_playlist[i].codigo_musica == codigo)
            return i;
    }
    return -1;
}

int buscar_musica_playlist_play(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, int codigo)
{
    int i;
    for (i = 0; i < cont_musica_playlist; i++)
    {
        if (vetor_musica_playlist[i].codigo_playlist == codigo)
            return i;
    }
    return -1;
}
void listar_codigos_musica(struct musica vetor_musica[], int cont_musica)
{
    for (int i = 0; i < cont_musica; i++)
        printf("Código da música: %d\n", vetor_musica[i].codigo_musica);
}

void listar_codigos_playlist(struct playlist vetor_playlist[], int cont_playlist)
{
    for (int i = 0; i < cont_playlist; i++)
        printf("Código da playlist: %d\n", vetor_playlist[i].codigo_playlist);
}

void listar_todos_codigos_musica_playlist(struct musica vetor_musica[], struct playlist vetor_playlist[], struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist)
{
    int i;
    for (i = 0; i < cont_musica_playlist; i++)
    {
        vetor_musica_playlist[i].codigo_musica = vetor_musica[i].codigo_musica;
        vetor_musica_playlist[i].codigo_playlist = vetor_playlist[i].codigo_playlist;
        printf("\nRegistro %d:\n", i);
        printf("  codigo_musica: %d\n", vetor_musica_playlist[i].codigo_musica);
        printf("  codigo_playlist: %d\n", vetor_musica_playlist[i].codigo_playlist);
    }
    getchar();
}

void listar_um_codigo_musica_playlist(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, int codigo)
{
    int pos = buscar_musica_playlist_mus(vetor_musica_playlist, cont_musica_playlist, codigo);

    if (pos == -1)
        pos = buscar_musica_playlist_play(vetor_musica_playlist, cont_musica_playlist, codigo);

    if (pos == -1)
        printf("Código não encontrado.");
    else
    {
        printf("codigo_musica: %d\n", vetor_musica_playlist[pos].codigo_musica);
        printf("codigo_playlist: %d\n", vetor_musica_playlist[pos].codigo_playlist);
    }
}

void incluir_musica_playlist(struct musica_playlist vetor_musica_playlist[], int *cont_musica_playlist, int qtd, int codigo, int codigo_playlist)
{
    if (*cont_musica_playlist < qtd)
    {
        vetor_musica_playlist[*cont_musica_playlist].codigo_musica = codigo;
        vetor_musica_playlist[*cont_musica_playlist].codigo_playlist = codigo_playlist;
        (*cont_musica_playlist)++;
        printf("Música adicionada à playlist com sucesso!\n");
    }
}

void alterar_musica_playlist_play(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, int novo_codigo)
{
    int i;
    for (i = 0; i <= cont_musica_playlist; i++)
        vetor_musica_playlist[i].codigo_musica = novo_codigo;
}

void alterar_musica_playlist_mus(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, int novo_codigo)
{
    int i;
    for (i = 0; i <= cont_musica_playlist; i++)
        vetor_musica_playlist[i].codigo_playlist = novo_codigo;
}

int excluir_musica_playlist_play(struct musica_playlist vetor_musica_playlist[], int *cont_musica_playlist, int res2)
{
    int i;
    for (i = res2; i < (*cont_musica_playlist) - 1; i++)
    {
        vetor_musica_playlist[i] = vetor_musica_playlist[i + 1];
    }
    (*cont_musica_playlist)--;
    return 1;
}

int excluir_musica_playlist_mus(struct musica_playlist vetor_musica_playlist[], int *cont_musica_playlist, int res)
{
    int i;
    for (i = res; i < (*cont_musica_playlist) - 1; i++)
    {
        vetor_musica_playlist[i] = vetor_musica_playlist[i + 1];
    }
    (*cont_musica_playlist)--;
    return 1;
}

struct musica_playlist *alocar_memoria_musica_playlist(int qtd)
{
    struct musica_playlist *vet;
    vet = (struct musica_playlist *)malloc(qtd * sizeof(struct musica_playlist));
    return vet;
}

void libera_memoria_musica_playlist(struct musica_playlist *cont_musica_playlist)
{
    free(cont_musica_playlist);
}

void carregar_musica_playlist(struct musica_playlist vetor_musica_playlist[], int *cont_musica_playlist, int qtd)
{
    FILE *arq_playlist;
    arq_playlist = fopen("playlist.dat", "rb");
    if (arq_playlist == NULL)
    {
        printf("Não foi possível carregar o arquivo. \n");
        return;
    }
    else
        fread(vetor_musica_playlist, sizeof(struct playlist), *cont_musica_playlist, arq_playlist);
    fclose(arq_playlist);
}

void salvar_musica_playlist(struct musica_playlist vetor_musica_playlist[], int *cont_musica_playlist)
{
    FILE *arq_musica_playlist;
    arq_musica_playlist = fopen("musica_playlist.dat", "wb");
    if (arq_musica_playlist == NULL)
    {
        printf("Não foi possível abrir o arquivo. \n");
        return;
    }

    fwrite(vetor_musica_playlist, sizeof(struct musica_playlist), *cont_musica_playlist, arq_musica_playlist);
    fclose(arq_musica_playlist);
}

int submenu_musica_playlist(int qtd, struct musica vetor_musica[], int cont_musica, struct playlist vetor_playlist[], int cont_playlist)
{
    struct musica_playlist *vetor_musica_playlist;
    int opc, res, res2, codigo_playlist, res3, num, novo_codigo, codigo = 0, cont_musica_playlist = 0;
    vetor_musica_playlist = alocar_memoria_musica_playlist(qtd);
    carregar_musica_playlist(vetor_musica_playlist, &cont_musica_playlist, qtd);
    do
    {
        printf("\t1. Listar todos os codigos de musica/playlist\n");
        printf("\t2. Listar um código de musica/playlist\n");
        printf("\t3. Associar uma musica a uma playlist\n");
        printf("\t4. Alterar código de musica/playlist\n");
        printf("\t5. Excluir código de musica/playlist\n");
        printf("\t6. sair do submenu musica/playlist\n");
        scanf("%d", &opc);
        getchar();
        switch (opc)
        {
        case 1:
            printf("Listando todos os códigos de musica/playlist:");
            listar_todos_codigos_musica_playlist(vetor_musica, vetor_playlist, vetor_musica_playlist, cont_musica_playlist);
            break;

        case 2:
            printf("Digite o código que deseja listar:");
            scanf("%d", &codigo);
            res = buscar_musica_playlist_mus(vetor_musica_playlist, cont_musica_playlist, codigo);
            res2 = buscar_musica_playlist_play(vetor_musica_playlist, cont_musica_playlist, codigo);
            if (res != -1)
            {
                printf("Codigo musica encontrado: %d", vetor_musica_playlist[res].codigo_musica);
            }
            else if (res2 != -1)
            {
                printf("Codigo playlist encontrado: %d", vetor_musica_playlist[res2].codigo_playlist);
            }
            else
                printf("Código não encontrado.");
            break;

        case 3:
            printf("\n--- Códigos disponíveis de músicas ---\n");
            listar_codigos_musica(vetor_musica, cont_musica);

            printf("\nDigite o código da música que deseja associar: ");
            scanf("%d", &codigo);
            getchar();

            res = buscar_musica(vetor_musica, cont_musica, codigo);
            if (res == -1)
            {
                printf("Música não encontrada!\n");
                break;
            }

            printf("\n--- Códigos disponíveis de playlists ---\n");
            listar_codigos_playlist(vetor_playlist, cont_playlist);

            printf("\nDigite o código da playlist: ");
            scanf("%d", &codigo_playlist);
            getchar();

            res2 = buscar_playlist(vetor_playlist, cont_playlist, codigo_playlist);
            if (res2 == -1)
            {
                printf("Playlist não encontrada!\n");
                break;
            }

            incluir_musica_playlist(vetor_musica_playlist, &cont_musica_playlist, qtd, codigo, codigo_playlist);
            break;

        case 4:
            printf("\nDigite o código que deseja alterar:");
            scanf("%d", &codigo);
            res = buscar_musica_playlist_mus(vetor_musica_playlist, cont_musica_playlist, codigo);
            res2 = buscar_musica_playlist_play(vetor_musica_playlist, cont_musica_playlist, codigo);
            if (res != -1)
            {
                printf("Digite o novo codigo");
                scanf("%d", &novo_codigo);
                alterar_musica_playlist_mus(vetor_musica_playlist, cont_musica_playlist, novo_codigo);
            }
            else if (res2 != -1)
            {
                printf("Digite o novo codigo");
                scanf("%d", &novo_codigo);
                alterar_musica_playlist_mus(vetor_musica_playlist, cont_musica_playlist, res2);
            }
            else
                printf("codigo nao encontrado");
            break;

        case 5:
            printf("\nExclusao de código de musica/playlist");
            printf("\nDigite o código que deseja excluir");
            scanf("%d", &codigo);
            res = buscar_musica_playlist_play(vetor_musica_playlist, cont_musica_playlist, codigo);
            res2 = buscar_musica_playlist_mus(vetor_musica_playlist, cont_musica_playlist, codigo);
            if (res != -1)
            {
                res3 = excluir_musica_playlist_mus(vetor_musica_playlist, &cont_musica_playlist, res);
            }
            else if (res2 != -1)
            {
                res3 = excluir_musica_playlist_play(vetor_musica_playlist, &cont_musica_playlist, res2);
            }
            else
                printf("Codigo nao encontrado");
            break;

        case 6:
            printf("Saindo do submenu...");
            break;

        default:
            printf("Opcao inválida");
            break;
        }
    } while (opc != 6);
    salvar_musica_playlist(vetor_musica_playlist, &cont_musica_playlist);
    libera_memoria_musica_playlist(vetor_musica_playlist);
}

// ######################################    RELATÓRIOS    ########################################

long converterDataParaInteiro(char *data)
{
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3)
    {
        return 0;
    }
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100)
    {
        return 0;
    }

    return (ano * 10000) + (mes * 100) + dia;
}

void relatorio_musicas(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, struct musica vetor_musica[], int cont_musica, struct playlist vetor_playlist[], int cont_playlist, int codigo)
{
    int i, indice_musica, indice_playlist;
    FILE *arq;

    arq = fopen("Relatorio_Musica_em_Playlists.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    printf("Digite o código da música para ver em quais playlists ela está: ");
    scanf("%d", &codigo);
    getchar();

    indice_musica = buscar_musica(vetor_musica, cont_musica, codigo);
    if (indice_musica == -1)
    {
        printf("Música não encontrada!\n");
        fclose(arq);
        return;
    }

    printf("\n--- Playlists que contêm a música: %s ---\n", vetor_musica[indice_musica].nome_musica);
    fprintf(arq, "--- Playlists que contêm a música: %s ---\n\n", vetor_musica[indice_musica].nome_musica);

    int encontrou = 0;
    for (i = 0; i < cont_musica_playlist; i++)
    {
        if (vetor_musica_playlist[i].codigo_musica == codigo)
        {
            indice_playlist = buscar_playlist(vetor_playlist, cont_playlist, vetor_musica_playlist[i].codigo_playlist);

            if (indice_playlist != -1)
            {
                printf("Playlist: %s (Código: %d)\n", vetor_playlist[indice_playlist].nome_playlist, vetor_playlist[indice_playlist].codigo_playlist);
                fprintf(arq, "Playlist: %s (Código: %d)\n", vetor_playlist[indice_playlist].nome_playlist, vetor_playlist[indice_playlist].codigo_playlist);
                encontrou = 1;
            }
        }
    }

    if (!encontrou)
    {
        printf("Esta música não está em nenhuma playlist.\n");
        fprintf(arq, "Esta música não está em nenhuma playlist.\n");
    }
}

void relatorio_playlist(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, struct playlist vetor_playlist[], int cont_playlist, struct musica vetor_musica[], int cont_musica, int codigo)
{
    int i, indice_playlist, indice_musica;
    FILE *arq;

    arq = fopen("Relatorio_Musicas_da_Playlist.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    printf("Digite o código da playlist para listar suas músicas: ");
    scanf("%d", &codigo);
    getchar();

    indice_playlist = buscar_playlist(vetor_playlist, cont_playlist, codigo);
    if (indice_playlist == -1)
    {
        printf("Playlist não encontrada!\n");
        fclose(arq);
        return;
    }
    printf("\n--- Músicas da Playlist: %s ---\n", vetor_playlist[indice_playlist].nome_playlist);
    fprintf(arq, "--- Músicas da Playlist: %s ---\n\n", vetor_playlist[indice_playlist].nome_playlist);

    int encontrou = 0;
    for (i = 0; i < cont_musica_playlist; i++)
    {
        if (vetor_musica_playlist[i].codigo_playlist == codigo)
        {
            indice_musica = buscar_musica(vetor_musica, cont_musica, vetor_musica_playlist[i].codigo_musica);

            if (indice_musica != -1)
            {
                printf("Música: %s | Artista: %s\n", vetor_musica[indice_musica].nome_musica, vetor_musica[indice_musica].artista);
                fprintf(arq, "Música: %s | Artista: %s\n", vetor_musica[indice_musica].nome_musica, vetor_musica[indice_musica].artista);
                encontrou = 1;
            }
        }
    }

    if (!encontrou)
    {
        printf("Esta playlist está vazia.\n");
        fprintf(arq, "Esta playlist está vazia.\n");
    }

    fclose(arq);
}

void relatorio_datas(struct musica_playlist vetor_musica_playlist[], int cont_musica_playlist, struct playlist vetor_playlist[], int cont_playlist)
{
    char ini[20], fim[20];
    long data_ini_inteiro, data_fim_inteiro, data_atual_inteiro;
    int i, encontrou = 0;
    FILE *arq;

    arq = fopen("RelatorioDatas.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao criar o arquivo de relatório!\n");
        return;
    }

    printf("Digite a data inicial (dd/mm/aaaa): ");
    fgets(ini, sizeof(ini), stdin);
    ini[strcspn(ini, "\n")] = '\0';

    printf("Digite a data final (dd/mm/aaaa): ");
    fgets(fim, sizeof(fim), stdin);
    fim[strcspn(fim, "\n")] = '\0';

    data_ini_inteiro = converterDataParaInteiro(ini);
    data_fim_inteiro = converterDataParaInteiro(fim);

    if (data_ini_inteiro == 0 || data_fim_inteiro == 0)
    {
        printf("\nUma das datas inseridas é inválida ou está no formato errado!\n");
        fclose(arq);
        return;
    }

    if (data_ini_inteiro > data_fim_inteiro)
    {
        printf("Intervalo inválido! A data inicial é maior que a final.\n");
        fclose(arq);
        return;
    }

    printf("\n--- Playlists criadas entre %s e %s ---\n", ini, fim);
    fprintf(arq, "--- Relatório de Playlists (%s a %s) ---\n\n", ini, fim);

    for (i = 0; i < cont_playlist; i++)
    {
        data_atual_inteiro = converterDataParaInteiro(vetor_playlist[i].data_criacao);

        if (data_atual_inteiro >= data_ini_inteiro && data_atual_inteiro <= data_fim_inteiro)
        {
            printf("\nCódigo: %d", vetor_playlist[i].codigo_playlist);
            printf("\nNome: %s", vetor_playlist[i].nome_playlist);
            printf("\nData: %s\n", vetor_playlist[i].data_criacao);
            printf("--------------------------------");
            fprintf(arq, "Código: %d\n", vetor_playlist[i].codigo_playlist);
            fprintf(arq, "Nome: %s\n", vetor_playlist[i].nome_playlist);
            fprintf(arq, "Data Criação: %s\n", vetor_playlist[i].data_criacao);
            fprintf(arq, "--------------------------------\n");

            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("\nNenhuma playlist encontrada neste período.\n");
        fprintf(arq, "Nenhuma playlist encontrada neste período.\n");
    }

    fclose(arq);
    printf("\n\nRelatório gerado com sucesso em 'RelatorioDatas.txt'.\n");
}

int submenu_relatorio()
{
    struct musica_playlist *vetor_musica_playlist;
    struct playlist *vetor_playlist;
    struct musica *vetor_musica;
    int musica, codigo, playlist, opc;
    int cont_musica_playlist = 0, cont_playlist = 0, cont_musica = 0;
    do
    {
        printf("\t1. Listar todas as playlists de uma música específica\n");
        printf("\t2. Listar todas as músicas de uma playlist\n");
        printf("\t3. Listar todas as playlists entre um intervalo de datas\n");
        printf("\t4. Sair deste submenu");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            relatorio_playlist(vetor_musica_playlist, cont_musica_playlist, vetor_playlist, cont_playlist, vetor_musica, cont_musica, codigo);
            break;
        case 2:
            relatorio_musicas(vetor_musica_playlist, cont_musica_playlist, vetor_musica, cont_musica, vetor_playlist, cont_playlist, codigo);
            break;
        case 3:
            relatorio_datas(vetor_musica_playlist, cont_musica_playlist, vetor_playlist, cont_playlist);
            break;
        case 4:
            printf("");
            break;
        }
    } while (opc <= 4);
}

void menu()
{
    int opc, cont_playlist = 0, cont_musica = 0;
    int qtd = 100;
    int opc_submenu;

    setlocale(LC_ALL, "Portuguese");

    struct musica *vetor_musica = malloc(qtd * sizeof(struct musica));
    struct playlist *vetor_playlist = malloc(qtd * sizeof(struct playlist));

    carregar_musicas(vetor_musica, &cont_musica, qtd);
    carregar_playlist(vetor_playlist, &cont_playlist);

    do
    {
        printf("Menu principal:\n");
        printf("\t1. Submenu de Músicas \n");
        printf("\t2. Submenu de Playlist \n");
        printf("\t3. Submenu de Musicas_playlist \n");
        printf("\t4. Submenu Relatórios \n");
        printf("\t5. Sair \n");
        scanf("%d", &opc);
        opc = menu();
        switch (opc)
        {
        case 1:
            printf("\nSubmenu de Músicas\n");
            submenu_musica(vetor_musica, &cont_musica, qtd);
            break;

        case 2:
            printf("Submenu de Playlist\n");
            submenu_playlist(vetor_playlist, &cont_playlist, qtd);
            break;

        case 3:
            printf("Submenu de Músicas/playlist\n");
            submenu_musica_playlist(qtd, vetor_musica, cont_musica, vetor_playlist, cont_playlist);
            break;

        case 4:
            printf("Submenu Relatórios\n");
            submenu_relatorio(qtd, vetor_musica, cont_musica, vetor_playlist, cont_playlist);
            break;

        case 5:
            // Salvar tudo antes de sair
            printf("Saindo do programa\n");
            salvar_musicas(vetor_musica, cont_musica);
            salvar_playlist(vetor_playlist, &cont_playlist);
            break;

        default:
            printf("Opcao inválida\n");
        }

    } while (opc != 5);

    free(vetor_musica);
    free(vetor_playlist);
}
int main()
{
    menu();
}