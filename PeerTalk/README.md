# PeerTalk – Sistema de Comunicação Peer-to-Peer

Projeto desenvolvido para a disciplina de **Sistemas Operacionais** do curso de Informática Biomédica da **UFCSPA**, com foco em Programação Concorrente e uso de mecanismos de IPC (Interprocess Communication) em C.

---

## 📌 Descrição

PeerTalk é um sistema de mensagens peer-to-peer onde cada processo é capaz de se comunicar diretamente com os demais, sem depender de um servidor central. A comunicação é realizada através de mecanismos de IPC do sistema operacional, como fila de mensagens, memória compartilhada e semáforos (mutexes).

## 🧩 Estrutura do Projeto

```bash
.
├── peertalk.c      # Código principal do processo peertalker
├── ipc.c           # Implementação dos mecanismos de IPC (fila, memória, mutexes)
├── ipc.h           # Header com declarações das funções de IPC
├── makefile        # Script para compilar o projeto
├── peertalk        # Executável gerado após compilação
├── peertalk.o      # Objeto gerado da compilação
