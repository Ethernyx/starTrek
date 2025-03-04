/**
* File: main.cpp
* Project: star_strek
* File Created: Friday, 21st July 2023 2:06:12 pm
* Author: LALIN Romain 
* -----
* Last Modified: Thursday, 27th July 2023 10:20:00 pm
* Modified By: LALIN Romain
* -----
*/

#include    "../Controller.hh"

using namespace std;

Controller *ctrl = new Controller();

void *connection_handler(void *sock_fd) {
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
        char buffer[BUFFER_SIZE + 1] = {0};
        cJSON *parse;
        
        // response data
        char *response;
      //  string strRetour;
        cJSON *startrek;
        ctrl->init(nullptr);
        // read response continue
        while ((read_byte = recv(conn_id, buffer, BUFFER_SIZE, 0)) > 0) {
            buffer[read_byte] = '\0';
            string json = string(buffer, strlen(buffer));
            if (!List::checkJson(json)) {
                do {
                    memset(buffer, 0, BUFFER_SIZE);
                    read_byte = recv(conn_id, buffer, BUFFER_SIZE, 0);
                    buffer[read_byte] = '\0';
                    json += string(buffer, strlen(buffer));
                } while (!List::checkJson(json));
            }
            int code = 0;
            if ((parse = cJSON_Parse(json.c_str())) != NULL) {
                cJSON *key = cJSON_GetObjectItem(parse, "command");
                if ((code = List::isRequiredRootStructure(parse)) == 0) {  //response = List::returnJson(code);
                    startrek = cJSON_GetObjectItem(parse, "startrek");
                }
                if (strcmp(key->valuestring, "init") == 0) {
                    if ((code = List::isCorectToInitPrototype(parse)) == 0) ctrl->init(parse);
                    response = List::returnJson(code);
                }
                else if (strcmp(key->valuestring, "attack") == 0) {
                    if ((code = List::isCorrectToAttackPrototype(parse)) == 0) {
                        response = ctrl->j_attack(startrek);
                    }
                }
                else if (strcmp(key->valuestring, "exchangeItem") == 0) {
                    if ((code = List::isCorrectToExhangeItemPrototype(parse)) == 0) {
                        response = ctrl->j_exchangeItem(startrek);
                    }
                }
                else if (strcmp(key->valuestring, "getInfos") == 0) {
                    if ((code = List::isCorrectToGetInfosPrototype(parse)) == 0) {
                        response = ctrl->j_getInfos(startrek);
                    }
                }
                else if (strcmp(key->valuestring, "kill") == 0) {
                    if ((code = List::isCorrectToKillPrototype(parse)) == 0) {
                        response = ctrl->j_kill(startrek);
                    }
                }
                else if (strcmp(key->valuestring, "escape") == 0) {
                    if ((code = List::isCorrectToEscapePrototype(parse)) == 0) {
                        response = ctrl->j_escape(startrek);
                    }
                }
                else if (strcmp(key->valuestring, "addEntities") == 0) {
                    if ((code = List::isCorrectToGetAddEntitiesPrototype(parse)) == 0) {
                        response = ctrl->j_add_entities(startrek);
                    }
                } else if (strcmp(key->valuestring, "getHabitants") == 0) {
                    if ((code = List::isCorrectToGetHabitantsPrototype(parse)) == 0) {
                        response = ctrl->j_getHabitants(startrek);
                    }
                } else if (strcmp(key->valuestring, "getEquipage") == 0) {
                    if ((code = List::isCorrectToGetEquipagePrototype(parse)) == 0) {
                        response = ctrl->j_getEquipage(startrek);
                    }
                } else if (strcmp(key->valuestring, "getInventory") == 0) {
                    if ((code = List::isCorrectToGetInventoryPrototype(parse)) == 0) {
                        response = ctrl->j_getInventory(startrek);
                    }
                } else if (strcmp(key->valuestring, "promote") == 0) {
                    if ((code = List::isCorrectToPromotePrototype(parse)) == 0) {
                        response = ctrl->j_promote(startrek);
                    }
                } else if (strcmp(key->valuestring, "getHierarchy") == 0) {
                    if ((code = List::isCorrectToGetHierarchyPrototype(parse)) == 0) {
                        response = ctrl->j_getHierarchy(startrek);
                    }
                }
                else response = List::returnJson(-6);//response = List::returnJson(-6);
            } else response = List::returnJson(-5);//response = List::returnJson(-5);
            
            response = code != 0 ? List::returnJson(code) : response;
            std::cout << "[RECEIVED] " << json << "\n";
                
                // clear buffer data
                memset(buffer, 0, BUFFER_SIZE);
                
                // send response
                if (send(conn_id, response, strlen(response), 0) > 0) {
                        std::cout << "[SEND] " << response << "\n";
                } else {
                        std::cout << "[WARNING][SEND] " << strerror(errno) << "\n";
                }
                cJSON_Delete(parse);
                free(response);
                
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

int main()
{
    Serveur *serveur = ctrl->getServeur();
    serveur->init();
    
    

    socklen_t addrlen = sizeof(struct sockaddr_in);
    while (true)
    {
        // accept new connections
        serveur->conn_id = accept(serveur->master_socket, (struct sockaddr *)&serveur->client, (socklen_t *)&addrlen);

        // if connection acception failed
        if (serveur->conn_id == -1)
        {
            std::cout << "[WARNING] CAN'T ACCEPT NEW CONNECTION\n";
        }
        else
        {
            // if connection limit reached
            if (serveur->connection >= CONCURRENT_CONNECTION)
            {
                std::cout << "[WARNING] CONNECTION LIMITE REACHED\n";
                // send(conn_id, "server is busy. please try again later.", 39, 0);
                close(serveur->conn_id); // close connection
            }
            else
            {
                std::cout << "[INFO] NEW CONNECTION ACCEPTED FROM " << inet_ntoa(serveur->client.sin_addr) << ":" << ntohs(serveur->client.sin_port) << "\n";
                // create new thread for new connection
                if (pthread_create(&serveur->thread_id, &serveur->attr, connection_handler, new int(serveur->conn_id)) == -1)
                {
                    // std::cout << "[WARNING][THREAD] " << strerror(errno) << "\n";
                    std::cout << "[WARNING] CAN'T CREATE NEW THREAD\n";
                    close(serveur->conn_id);
                }
                else
                {
                    std::cout << "[INFO] NEW THREAD CREATED\n";

                    serveur->connection++; // increase connection count
                }
            }
        }
    }
    return 0;
}


/*
146.59.240.78:8085 toto virtus@83AJC
ssh -p 2243 gr3@193.253.53.72
sudo systemctl stop startrek.service
sudo systemctl restart startrek.service

nouvelle commande
    - getEquipage --> id ship
    - getHabitant --> id planet
    - getInventory --> entity type + entity id

gestion des combats 
    - endommager aussi bien la defense que les hp ?
    - random pour les degats ?
    - gestion d'xp ?
    - attaque corosive (degat sur dp)? 


- Item
    - nom
    - ? effet ?
    - stat
- Heros a un vector d'Item
- Gestion du fichier pour les Items
- Allied, pnj, enemi --> herite de personnage
    - allied evolu en montant de lvl
        - 
    - ennemy peut pas monté en lvl et attaque a vue pnj et militaire
    - pnj ne peut pas evolué en montant de lvl

*/