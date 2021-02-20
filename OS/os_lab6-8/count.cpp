#include <iostream>
#include <unistd.h>
#include <sstream>
#include <set>

#include "zmq_functions.h"

#include "topology.h"

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        std::cout << "Wrong arguments Not enough parameters!\n";
        exit(1);
    }
    int current_id = std::atoi(argv[1]);
    int child_id = -1;
    if (argc == 3) {
        child_id = std::atoi(argv[2]);
    }

    zmq::context_t context;
    zmq::socket_t parent_socket(context, ZMQ_REP);
    connect(parent_socket, current_id);

    zmq::socket_t child_socket(context, ZMQ_REQ);

    std::string message;

    auto start_clock = std::chrono::high_resolution_clock::now();
    auto stop_clock = std::chrono::high_resolution_clock::now();
    auto time_clock = 0;
    bool flag_clock = false;

    while (1) {
        message = receive_message(parent_socket);

        std::istringstream request(message);
        int dest_id;

        request >> dest_id;

        std::string comand;
        request >> comand;

        if (dest_id == current_id) {
            if (comand == "pid") {
                send_message(parent_socket, "OK: " + std::to_string(getpid()));
            } else if (comand == "create") {
                int new_child_id;
                request >> new_child_id;
                if (child_id != -1) {
                    unbind(child_socket, child_id);
                }
                bind(child_socket, new_child_id);
                pid_t pid = fork();
                if (pid < 0) {
                    perror("Can't create new process!\n");
                    exit(1);
                }
                if (pid == 0) {
                    execl("./count", "./count", std::to_string(new_child_id).c_str(), std::to_string(child_id).c_str(), NULL);
                    perror("Can't create new process!\n");
                    exit(1);
                }
                send_message(child_socket, std::to_string(new_child_id) + "pid");
                child_id = new_child_id;
                send_message(parent_socket, receive_message(child_socket));
            } else if (comand == "remove") {
                if (child_id != -1) {
                    send_message(child_socket, std::to_string(child_id) + " remove");
                    std::string msg = receive_message(child_socket);
                    if (msg == "OK") {
                        send_message(parent_socket, "OK");
                    }
                    unbind(child_socket, child_id);
                    disconnect(parent_socket, current_id);
                    break;
                }
                send_message(parent_socket, "OK");
                disconnect(parent_socket, current_id);
                break;
            } else if (comand == "ping") {
                std::string reply;
                if (child_id != -1) {
                    send_message(child_socket, std::to_string(child_id) + " ping");
                    std::string msg = receive_message(child_socket);
                    reply += " " + msg;
                }
                send_message(parent_socket, std::to_string(current_id) + reply);
            } else if (comand == "exec") {
                std::string subcomand;
                request >> subcomand;
                std::string msg = "OK: " + std::to_string(current_id);
                if (subcomand == "start") {
                    start_clock = std::chrono::high_resolution_clock::now();
                    flag_clock = true;
                } else if (subcomand == "stop") {
                    if (flag_clock) {
                        stop_clock = std::chrono::high_resolution_clock::now();
                        time_clock += std::chrono::duration_cast<std::chrono::milliseconds>(stop_clock - start_clock).count();
                        flag_clock = false;
                    }
                } else if (subcomand == "time") {
                    if (flag_clock == true) {
                        stop_clock = std::chrono::high_resolution_clock::now();
                        time_clock += std::chrono::duration_cast<std::chrono::milliseconds>(stop_clock - start_clock).count();
                        start_clock = stop_clock;
                    }
                    //stop_clock = std::chrono::high_resolution_clock::now();
                    //time_clock += std::chrono::duration_cast<std::chrono::milliseconds>(stop_clock - start_clock).count();
                    msg += ": " + std::to_string(time_clock);
                }
                send_message(parent_socket, msg);
            } 
        } else if (child_id != -1) {
            send_message(child_socket, message);
            send_message(parent_socket, receive_message(child_socket));
            if (child_id == dest_id && comand == "remove") {
                child_id = -1;
            }
        } else {
            send_message(parent_socket, "Error: node is unavailable!\n");
        }
    }
}