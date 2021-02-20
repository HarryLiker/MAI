#include <iostream>
#include <unistd.h>
#include <sstream>
#include <set>
#include <zmq.hpp>
#include <chrono>
#include <vector>

#include "topology.h"
#include "zmq_functions.h"

int main() {
    Topology network;
    std::vector<zmq::socket_t> branches;
    zmq::context_t context;

    std::string comand;

    std::string message;


    while (std::cin >> comand) {
        if (comand == "create") {
            int node_id, parent_id;
            std::cin >> node_id >> parent_id;

            if (network.Find(node_id) != -1) { // Поиск id выч. узла среди существующих
                std::cout << "Error: already exists!\n";
            } else if (parent_id == -1) {
                pid_t pid = fork(); // Создание дочернего узла
                if (pid < 0) {
                    perror("Can't create new process!\n");
                    exit(EXIT_FAILURE);
                }
                if (pid == 0) {
                    execl("./count", "./count", std::to_string(node_id).c_str(), NULL);
                    perror("Can't execute new process!\n");
                    exit(EXIT_FAILURE);
                }

                branches.emplace_back(context, ZMQ_REQ);
                branches[branches.size() - 1].setsockopt(ZMQ_SNDTIMEO, 5000);
                bind(branches[branches.size() - 1], node_id);
                send_message(branches[branches.size() - 1], std::to_string(node_id) + "pid");

                std::string reply = receive_message(branches[branches.size() - 1]);
                std::cout << reply << "\n";
                network.Insert(node_id, parent_id);

            } else if (network.Find(parent_id) == -1) {
                std::cout << "Error: parent not found!\n";
            } else {
                int branch = network.Find(parent_id); 
                send_message(branches[branch], std::to_string(parent_id) + "create " + std::to_string(node_id));

                std::string reply = receive_message(branches[branch]);
                std::cout << reply << "\n";
                network.Insert(node_id, parent_id);
            }
        } else if (comand == "remove") {
            int id;
            std::cin >> id;
            int branch = network.Find(id); // Проверка, существует ли узел
            if (branch == -1) {
                std::cout << "Error: incorrect node id!\n";
            } else {
                bool is_first = (network.GetFirstId(branch) == id);
                send_message(branches[branch], std::to_string(id) + " remove");

                std::string reply = receive_message(branches[branch]);
                std::cout << reply << "\n";
                network.Erase(id);
                if (is_first) {
                    unbind(branches[branch], id);
                    branches.erase(branches.begin() + branch);
                }
            }
        } else if (comand == "exec") {
            int dest_id;
            std::string subcomand;
            std::cin >> dest_id >> subcomand;
            int branch = network.Find(dest_id);
            if (branch == -1) {
                std::cout << "Error: incorrect node id!\n";
            } else {
                if (subcomand == "start") {
                    send_message(branches[branch], std::to_string(dest_id)  + "exec " + " start");
                } else if (subcomand == "stop") {
                    send_message(branches[branch], std::to_string(dest_id)  +  "exec " + " stop");
                } else if (subcomand == "time") {
                    send_message(branches[branch], std::to_string(dest_id)  + "exec " + " time");
                }

                std::string reply = receive_message(branches[branch]);
                std::cout << reply << "\n";
            }
        } else if (comand == "ping") {
            int dest_id;
            std::set<int> available_nodes;
            std::cin >> dest_id;
            if (network.Find(dest_id) == -1) {
                std::cout << "Error: Not found!\n";
            } else {
                int yes = 0;
                for (int i = 0; i < branches.size(); ++i) {
                    int first_node_id = network.GetFirstId(i);
                    send_message(branches[i], std::to_string(first_node_id) + " ping");
                    std::string received_message = receive_message(branches[i]);
                    std::istringstream reply(received_message);
                    int node;
                    while (reply >> node) {
                        if (node == dest_id) {
                            yes = 1;
                        }
                    }
                }
                std::cout << "OK: " << yes << "\n";
            }
        } else if (comand == "exit") {
            for (size_t i = 0; i < branches.size(); ++i) {
                int first_node_id = network.GetFirstId(i);
                send_message(branches[i], std::to_string(first_node_id) + " remove");

                std::string reply = receive_message(branches[i]);
                if (reply != "OK") {
                    std::cout << reply << "\n";
                } else {
                    unbind(branches[i], first_node_id);
                }
            }
            exit(0);
        } else {
            std::cout << "Incorrect comand!\n";
        }
    }
}