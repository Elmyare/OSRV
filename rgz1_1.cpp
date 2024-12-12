// server_client_thread_same_process.cpp

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

int idServer, idClient;
unsigned int time1, time2;

void *Server(void *arg) {
    idServer = ChannelCreate(0);
    int rcvid = MsgReceive(idServer, NULL, NULL, NULL);
    time2 = ClockCycles();
    cout << "Clock2\n";
    MsgReply(rcvid, 0, 0, 0);
}

void *Client(void *arg) {
    idClient = ConnectAttach(0, 0, idServer, 0, 0);
    cout << "Clock1\n";
    time1 = ClockCycles();
    MsgSend(idClient, NULL, NULL, NULL, NULL);
}

typedef numeric_limits<double> dbl;

int main() {
    pthread_t id, id2;
    pthread_create(&id, NULL, Server, NULL);
    sleep(1);  // добавляем задержку, чтобы сервер успел начать
    pthread_create(&id2, NULL, Client, NULL);
    pthread_join(id, NULL);
    pthread_join(id2, NULL);

    cout << "time1: " << time1 << "\n";
    cout << "time2: " << time2 << "\n";
    cout << "Result (nsec): " << ((time2 - time1) / (double)SYSPAGE_ENTRY(qtime)->cycles_per_sec) * 1000000000 << "\n";
    cout << "Result (sec): " << ((time2 - time1) / (double)SYSPAGE_ENTRY(qtime)->cycles_per_sec) << "\n";
    return 0;
}
