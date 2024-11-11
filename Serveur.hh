/**
* File: Serveur.hh
* Project: star_strek
* File Created: Wednesday, 12th July 2023 12:25:08 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 10:00:50 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef SERVEUR_HH_
#define SERVEUR_HH_

#include <iostream> // input output
#include <string> // strlen string
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> // multi threading
#include <errno.h>
#include <signal.h>
#include <string.h>

// Included for count execution time
#include <time.h>
#include <iomanip>
#include    "lib_func/cJSON.hh"

// server address
#define ADDRESS "0.0.0.0"//"146.59.240.78"

#define PORT 8888

// maximum concurrent connections
#define CONCURRENT_CONNECTION 10

// maximum connection requests queued
#define QUEUE_CONNECTION 20

// buffer size 1KB
#define BUFFER_SIZE 1024

// Thread stack size 64KB
#define THREAD_STACK_SIZE 65536

class Serveur
{
private:


public:
        static int connection;
    pthread_t thread_id;
        // thread attribute
    pthread_attr_t attr;
    int master_socket;
    int conn_id;
    struct sockaddr_in server;
    struct sockaddr_in client;
    Serveur();
    ~Serveur();
    int init();
    void Loop();
    static void *connection_handler(void *sock_fd);
};

#endif