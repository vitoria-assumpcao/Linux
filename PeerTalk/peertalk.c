#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include "ipc.h"

Message local_msgs[MAX_LOCAL_MSGS];
int local_msg_count = 0;

int main() {
    int shmid = get_shm();
    User *users = attach_shm(shmid);
    int semid = get_sem();
    int msqid = get_msgqueue();

    char username[MAX_NAME_LEN];
    printf("Digite seu nome de usuário: ");
    scanf("%s", username);

    lock(semid);
    if (find_user(users, username) != -1) {
        printf("Nome de usuário já está em uso.\n");
        unlock(semid);
        exit(1);
    }
    add_user(users, username, getpid());
    unlock(semid);

    printf("Login bem-sucedido. Use os comandos:\n");
    printf("send <nome> <msg> | recv | msgs | users | myid | del msgs | exit\n");

    char cmd[512];
    while (1) {
        printf("> ");
        fgets(cmd, sizeof(cmd), stdin);

        if (strncmp(cmd, "send ", 5) == 0) {
            char to[MAX_NAME_LEN], msg[MAX_MSG_LEN];
            sscanf(cmd + 5, "%s %[^\n]", to, msg);

            lock(semid);
            int idx = find_user(users, to);
            unlock(semid);

            if (idx == -1) {
                printf("Usuário não encontrado.\n");
            } else {
                Message m;
                m.msg_type = users[idx].pid;
                m.from_pid = getpid();
                strncpy(m.text, msg, MAX_MSG_LEN);
                msgsnd(msqid, &m, sizeof(m) - sizeof(long), 0);
                printf("Mensagem enviada para %s.\n", to);
            }

          } else if (strncmp(cmd, "recv", 4) == 0) {  // ← agora corretamente fora do "send"
            Message m;
            int received = 0;
            while (msgrcv(msqid, &m, sizeof(m) - sizeof(long), getpid(), IPC_NOWAIT) > 0) {
                if (local_msg_count < MAX_LOCAL_MSGS) {
                    local_msgs[local_msg_count++] = m;
                    printf("Nova mensagem de %d armazenada.\n", m.from_pid);
                }
                received = 1;
            }
            if (!received) {
                printf("Nenhuma nova mensagem recebida.\n");
            }

        } else if (strncmp(cmd, "msgs", 4) == 0) {
            if (local_msg_count == 0)
                printf("Nenhuma mensagem.\n");
            for (int i = 0; i < local_msg_count; i++)
                printf("[%d]: %s\n", local_msgs[i].from_pid, local_msgs[i].text);

        } else if (strncmp(cmd, "users", 5) == 0) {
            lock(semid);
            for (int i = 0; i < MAX_USERS; i++)
                if (users[i].pid != 0)
                    printf("%s (PID %d)\n", users[i].name, users[i].pid);
            unlock(semid);

        } else if (strncmp(cmd, "myid", 4) == 0) {
            printf("Usuário: %s | PID: %d\n", username, getpid());

        } else if (strncmp(cmd, "del msgs", 8) == 0) {
            if (local_msg_count == 0) {
        printf("Nenhuma mensagem para apagar. \n");
        }
           else{
         local_msg_count = 0;
         printf("Mensagens locais apagadas.\n");
         }

        } else if (strncmp(cmd, "exit", 4) == 0) {
            lock(semid);
            remove_user(users, getpid());
            unlock(semid);
            printf("Logout concluído.\n");
            break;

        } else {
            printf("Comando não reconhecido.\n");
        }
    }

    return 0;
}

