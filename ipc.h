#ifndef IPC_H
#define IPC_H

#include <sys/types.h>

#define MAX_USERS 20
#define MAX_NAME_LEN 20
#define MAX_MSG_LEN 256
#define MAX_LOCAL_MSGS 50

#define SHM_KEY 1234
#define MSG_KEY 5678
#define SEM_KEY 9101

typedef struct {
    char name[MAX_NAME_LEN];
    pid_t pid;
} User;

typedef struct {
    long msg_type;           // PID do destinatário
    pid_t from_pid;          // quem enviou
    char text[MAX_MSG_LEN];  // conteúdo da mensagem
} Message;

// Funções utilitárias
int get_shm();
User* attach_shm(int shmid);
int get_sem();
void lock(int semid);
void unlock(int semid);
int get_msgqueue();
int find_user(User *users, const char *name);
int add_user(User *users, const char *name, pid_t pid);
int remove_user(User *users, pid_t pid);

#endif
