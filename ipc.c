#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <unistd.h>
#include "ipc.h"

// Memória compartilhada
int get_shm() {
    return shmget(SHM_KEY, sizeof(User) * MAX_USERS, IPC_CREAT | 0666);
}

User* attach_shm(int shmid) {
    return (User *)shmat(shmid, NULL, 0);
}

// Semáforo (mutex)
int get_sem() {
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1);  // inicializa com 1
    return semid;
}

void lock(int semid) {
    struct sembuf op = {0, -1, 0};
    semop(semid, &op, 1);
}

void unlock(int semid) {
    struct sembuf op = {0, 1, 0};
    semop(semid, &op, 1);
}

// Fila de mensagens
int get_msgqueue() {
    return msgget(MSG_KEY, IPC_CREAT | 0666);
}

// Busca usuário na lista
int find_user(User *users, const char *name) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].name, name) == 0)
            return i;
    }
    return -1;
}

// Adiciona novo usuário
int add_user(User *users, const char *name, pid_t pid) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (users[i].pid == 0) {
            strncpy(users[i].name, name, MAX_NAME_LEN);
            users[i].pid = pid;
            return 0;
        }
    }
    return -1; // Lista cheia
}

// Remove usuário da lista
int remove_user(User *users, pid_t pid) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (users[i].pid == pid) {
            users[i].pid = 0;
            users[i].name[0] = '\0';
            return 0;
        }
    }
    return -1;
}

