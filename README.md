# Aplicativo de músicas
Desenvolvido na diciplina de algoritmos de programacao, cursado no Instituto Federal de São Paulo. 

🎵 Sistema de Gerenciamento de Músicas e Playlists
(Música ↔ Playlist + Relatórios + Persistência em Arquivos)

Este projeto implementa um sistema completo para organizar músicas, playlists e as associações entre elas.
O programa funciona totalmente em C, usando arquivos binários e texto para salvar informações de forma permanente.

📌 Funcionalidades Principais
🔹 1. Módulo de Músicas

Cadastrar música (código, nome, artista, duração…)

Listar todas as músicas

Buscar música pelo código

Alterar dados da música

Excluir música

Armazenamento persistente em musicas.dat

🔹 2. Módulo de Playlists

Cadastrar playlists (código, nome, descrição, data)

Listar playlists

Buscar playlist pelo código

Alterar dados

Excluir playlist

Armazenamento em playlist.dat

🔹 3. Módulo Música ↔ Playlist

Gerencia a associação entre uma música e uma playlist.

Permite:

Associar uma música existente a uma playlist existente

Listar todas as associações

Buscar por código de música ou playlist

Alterar uma associação

Excluir associação

Salvo em musica_playlist.dat

Esse módulo garante:
✔ Não repetir código
✔ Verificar música antes de associar
✔ Verificar playlist antes de associar
✔ Impedir duplicações (evitar “mesma música na mesma playlist duas vezes”)

📊 Relatórios

Os relatórios são gerados em arquivos TXT, como exigido no projeto.

📄 1. Relatório de Playlists que contêm uma música

Usuário informa o código da música

O sistema lista:

Nome da playlist

Descrição

Gera relatorio_playlist.txt

📄 2. Relatório de músicas de uma playlist

Usuário informa o código da playlist

O sistema lista:

Nome da música

Artista

Gera relatorio_musicas.txt

📄 3. Relatório de playlists dentro de um intervalo de datas

Usuário informa data inicial e final

O sistema compara datas no formato dd/mm/aaaa

Lista playlists com:

Nome

Data de criação

Gera relatorio_datas.txt

💾 Persistência de Dados

O programa utiliza arquivos binários (.dat) para armazenar os vetores de estruturas:

Arquivo	Conteúdo
musicas.dat	músicas cadastradas
playlist.dat	playlists cadastradas
musica_playlist.dat	relação música ↔ playlist
relatorio_*.txt	relatórios exportados

A leitura e gravação são feitas por:

fwrite()

fread()

E os relatórios são gerados com:

fopen(...,"w")

fputs()
