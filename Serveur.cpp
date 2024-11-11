/**
* File: Serveur.cpp
* Project: star_strek
* File Created: Wednesday, 12th July 2023 12:20:59 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 10:00:35 pm
* Modified By: LALIN Romain
* -----
*/

#include    "Serveur.hh"

int Serveur::connection = 0;

Serveur::Serveur() {}

Serveur::~Serveur() {}

int Serveur::init() {
        if (pthread_attr_init(&this->attr) != 0) {
                std::cout << "[ERROR][THREAD][INIT] " << strerror(errno) << "\n";
                return -1;
        }
        
        // stack size 1MB
        if (pthread_attr_setstacksize(&this->attr, THREAD_STACK_SIZE) != 0) {
                std::cout << "[ERROR][THREAD][STACK] " << strerror(errno) << "\n";
                return -1;
        }
        
        if (pthread_attr_setdetachstate(&this->attr, PTHREAD_CREATE_DETACHED) != 0) {
                std::cout << "[ERROR][THREAD][DETACH] " << strerror(errno) << "\n";
                return -1;
        }
        
        memset(&this->server, 0, sizeof(this->server));
        memset(&this->client, 0, sizeof(this->client));
        
        signal(SIGPIPE, SIG_IGN);
        
        // creating master socket
        if ((this->master_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                std::cout << "[ERROR] CAN'T CREATE TO SOCKET\n";
            return -1;
        } else {
                std::cout << "[NOTE] SOCKET CREATED DONE\n";
        }
        
        
     // Prepare the sockaddr_in structure
        this->server.sin_family = AF_INET;
        this->server.sin_addr.s_addr = inet_addr(ADDRESS);
        this->server.sin_port = htons(PORT);
    
        // binding address and port
        if (bind(this->master_socket, (struct sockaddr *)&this->server , sizeof(this->server)) == -1) {
                std::cout << "[ERROR][BIND] " << strerror(errno) << "\n";
            return -1;
        } else {
                std::cout << "[NOTE] BIND " << ADDRESS << ":" << PORT << "\n";
        }
        
        // Listen on the socket, with 20 max connection requests queued
        if (listen(this->master_socket, QUEUE_CONNECTION) == -1) {
                std::cout << "[ERROR][LISTEN] " << strerror(errno) << "\n";
                return -1;
        } else {
                std::cout << "[INFO] WAITING FOR INCOMING CONNECTIONS\n";
        }
        return 0;
}

void    Serveur::Loop() {
        socklen_t addrlen = sizeof(struct sockaddr_in);
    while (true) {
                // accept new connections
                this->conn_id = accept(this->master_socket, (struct sockaddr*)&this->client, (socklen_t*)&addrlen);
                
        // if connection acception failed
        if (this->conn_id == -1) {
                std::cout << "[WARNING] CAN'T ACCEPT NEW CONNECTION\n";
        } else {
                 // if connection limit reached
                 if (this->connection >= CONCURRENT_CONNECTION) {
                     std::cout << "[WARNING] CONNECTION LIMITE REACHED\n";
                     // send(conn_id, "server is busy. please try again later.", 39, 0);
                     close(this->conn_id); // close connection
                 } else {
                     std::cout << "[INFO] NEW CONNECTION ACCEPTED FROM " << inet_ntoa(this->client.sin_addr) << ":" << ntohs(this->client.sin_port) << "\n";
                     // create new thread for new connection
                     if (pthread_create(&this->thread_id, &this->attr, Serveur::connection_handler, new int(this->conn_id)) == -1) {
                         // std::cout << "[WARNING][THREAD] " << strerror(errno) << "\n";
                             std::cout << "[WARNING] CAN'T CREATE NEW THREAD\n";
                         close(this->conn_id);
                     } else {
                             std::cout << "[INFO] NEW THREAD CREATED\n";
                             
                         this->connection++; // increase connection count
                     }
                 }
             }
        }
}

// This will handle connection for each client
void *Serveur::connection_handler(void *sock_fd) {
        /* clock_t clock(void) returns the number of clock ticks 
           elapsed since the program was launched.To get the number  
           of seconds used by the CPU, you will need to divide by  
           CLOCKS_PER_SEC.where CLOCKS_PER_SEC is 1000000 on typical 
           32 bit system.  */
        clock_t start, end; 
        
        // Recording the starting clock tick.
        start = clock(); 
        
        // byte size
        int read_byte = 0;
        
        // Get the socket descriptor
        int conn_id = *(int*)sock_fd;
        
        // request data
        char buffer[BUFFER_SIZE] = {0};
        
        // response data
        char response[] = "Hello";
        
        // read response continue
        while ((read_byte = recv(conn_id, buffer, BUFFER_SIZE, 0)) > 0) {
                //cJSON *key = cJSON_GetObjectItem(cJSON_Parse(buffer), "key");
               /* switch (key->valuestring)
                {
                case "init":
                        break;
                
                default:
                        break;
                }*/
// ...          
// Convertir buffer en std::string pour une manipulation facile  EXEMPLE !!!!!
                FILE *f;
                f = fopen("bdd.json","w");
                fprintf(f,"%s\n",cJSON_Print(cJSON_Parse(buffer)));
                fclose(f);

                /* code pour recevoir a faire */

                std::cout << "[RECEIVED] " << buffer << "\n";
                // clear buffer data
                memset(buffer, 0, BUFFER_SIZE);
                
                // send response
                if (send(conn_id, response, strlen(response), 0) > 0) {
                        std::cout << "[SEND] " << response << "\n";
                } else {
                        std::cout << "[WARNING][SEND] " << strerror(errno) << "\n";
                }
                
        }
        
        // terminate connection
        close(conn_id);
        std::cout << "[INFO] CONNECTION CLOSED\n";
        
        // decrease connection counts
        Serveur::connection--;
        
        // thread automatically terminate after exit connection handler
        std::cout << "[INFO] THREAD TERMINATED" << std::endl;
        
        delete (int*)sock_fd;
        
        // Recording the end clock tick. 
        end = clock();
    
        // Calculating total time taken by the program. 
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    
        // print process time
        std::cout << "[TIME] PROCESS COMPLETE IN " << std::fixed << time_taken << std::setprecision(5); 
        std::cout << " SEC\n";
        
        // print line
        std::cout << "------------------------\n";
        
        // exiting
        pthread_exit(NULL);
} 