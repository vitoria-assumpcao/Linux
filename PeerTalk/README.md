PeerTalk – Sistema de Comunicação Peer-to-Peer
Projeto desenvolvido para a disciplina de Sistemas Operacionais do curso de Informática Biomédica - UFCSPA, com foco em Programação Concorrente e uso de mecanismos de IPC (Interprocess Communication) em C.

 Descrição
PeerTalk é um sistema de mensagens peer-to-peer onde cada processo é capaz de se comunicar diretamente com os demais, sem depender de um servidor central. A comunicação é feita por mecanismos de IPC como fila de mensagens, memória compartilhada e semáforos (mutexes).

 Estrutura do Projeto
.
├── peertalk.c      # Código principal do processo peertalker
├── ipc.c           # Implementação dos mecanismos de IPC (fila, memória, mutexes)
├── ipc.h           # Header com declarações das funções de IPC
├── makefile        # Script para compilar o projeto
├── peertalk        # Executável gerado após compilação
├── peertalk.o      # Objeto gerado da compilação
 Funcionalidades:
Login com nome de usuário (sem espaços)
Envio e recebimento de mensagens entre usuários logados
Listagem e exclusão de mensagens
Visualização de usuários conectados
Armazenamento local das mensagens recebidas

Comandos disponíveis
send <usuário>, <msg>:	Envia uma mensagem para outro usuário logado
recv:	Busca novas mensagens destinadas ao usuário atual
msgs:	Lista as mensagens armazenadas localmente
del msgs:	Apaga todas as mensagens locais
users:	Mostra os usuários logados
myid:	Mostra o identificador (PID) do usuário
exit:	Sai do sistema e remove o usuário da lista compartilhada

 Como executar
Compile o projeto usando o makefile:
make

Em terminais separados, execute o programa:
./peertalk
No login, informe seu nome de usuário (sem espaços). Use os comandos listados acima para interagir.
