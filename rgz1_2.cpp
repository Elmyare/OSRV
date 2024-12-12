// server_client_thread_different_process.cpp

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <time.h>
#include <stdlib.h>
#include <sys/syspage.h>
#include <limits>

using namespace std;

int *idClient, *idServer;
unsigned int *time1, *time2;
int *pid;

void *Server(void *arg) {
    *pid = getpid();
    *idServer = ChannelCreate(0);
    int rcvid = MsgReceive(*idServer, NULL, NULL, NULL);
    *time2 = ClockCycles();
    cout << "Clock2\n";
    MsgReply(rcvid, 0, 0, 0);
}

void *Client(void *arg) {
    *idClient = ConnectAttach(0, *pid, *idServer, 0, 0);
    cout << "Clock1\n";
    *time1 = ClockCycles();
    MsgSend(*idClient, NULL, NULL, NULL, NULL);
}

typedef numeric_limits<double> dbl;

int main() {
    time1 = (unsigned int*)mmap(NULL, sizeof *time1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    time2 = (unsigned int*)mmap(NULL, sizeof *time2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    idServer = (int*)mmap(NULL, sizeof *idServer, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    idClient = (int*)mmap(NULL, sizeof *idClient, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    pid = (int*)mmap(NULL, sizeof *pid, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    int pid2 = fork();
    if (!pid2) {  // В серверном процессе
        pthread_t id;
        pthread_create(&id, NULL, Server, NULL);
        pthread_join(id, NULL);
    } else {  // В клиентском процессе
        pthread_t id2;
        sleep(4);  // небольшая задержка для старта сервера
        pthread_create(&id2, NULL, Client, NULL);
        pthread_join(id2, NULL);
        sleep(1);  // задержка перед выводом результата
        cout << "time1: " << *time1 << "\n";
        cout << "time2: " << *time2 << "\n";
        cout << "Result (nsec): " << ((*time2 - *time1) / (double)SYSPAGE_ENTRY(qtime)->cycles_per_sec) * 1000000000 << "\n";
        cout << "Result (sec): " << ((*time2 - *time1) / (double)SYSPAGE_ENTRY(qtime)->cycles_per_sec) << "\n";
    }

    return 0;
}
