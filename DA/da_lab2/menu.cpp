#include <iostream>
#include <fstream>
#include "RBTree.hpp"
#include "work_with_files.hpp"
#include "menu.hpp"


int Menu() {
    Tree<char *, unsigned long long> *tree = new Tree<char *, unsigned long long>;
    char line [257];
    unsigned long long value;
    while(std::cin >> line) {
        if (line[0] == '+') {
            std::cin >> line;
            std::cin >> value;
            Node<char *, unsigned long long> *node = new Node<char *, unsigned long long>;
            node->GetKey(line);
            node->GetValue(value);
            node->GetParent(tree->FindTNull());
            if (tree->Insert(node) == 0) {
                std::cout << "OK\n";
            }
            else {
                delete node;
                std::cout << "Exist\n";
            }
            node = nullptr;
        }
        else if (line[0] == '-') {
            std::cin >> line;
            Str_copy(line, line);
            Node<char*, unsigned long long> *deliting_node = tree->Search(line);
            if (deliting_node != nullptr) {
                tree->Delete(deliting_node);
                std::cout << "OK\n";
                deliting_node = nullptr;
            }
            else {
                std::cout << "NoSuchWord\n";
            }
        }
        else if (line[0] == '!') {
            std::cin >> line;
            if (line[0] == 'S') {
                std::cin >> line; // Path 
                std::ofstream File;
                File.exceptions(std::ofstream::badbit | std::ofstream::failbit);

                try {
                    File.open(line, std::ios_base::binary);
                    if (!File.is_open()) {
                        throw "File with this name does not exist\n";
                    }
                    if (tree->FindRoot() == nullptr) {
                        File.close();
                        throw "OK\n";
                    }
                    else {
                        Tree_save(File, tree, tree->FindRoot());
                        File.close();
                        std::cout << "OK\n";
                    } 
                }
                catch (const std::exception &exeption) {
                    std::cout << "ERROR: "  << exeption.what() << "\n";
                }
            }
            if (line[0] == 'L') {
                std::cin >> line;
                std::ifstream File;
                File.exceptions(std::ifstream::badbit);
                try {
                    File.open(line, std::ios_base::binary);
                    if (!File.is_open()) {
                        throw "File with this name does not exist\n";
                    }
                    else if (File.peek() == EOF) {
                        delete tree;
                        tree = new Tree<char *, unsigned long long>;
                        std::cout << "OK\n";
                    }
                    else {
                        Tree<char *, unsigned long long> *new_tree;
                        new_tree = new Tree<char *, unsigned long long>;
                        Load_tree(&File, new_tree);
                        File.close();
                        delete tree;
                        tree = new_tree;
                        std::cout << "OK\n";
                    }
                }
                catch (const char* error) {
                    std::cout << "ERROR: " << error;
                }
                catch (const std::exception &exeption) {
                    std::cout << "ERROR: " << exeption.what() << "\n";
                }
            }
        }
        else {
            Str_copy(line, line);
            Node<char*, unsigned long long> *searching_node = tree->Search(line);
            if (searching_node != nullptr) {
                std::cout << "OK: " << searching_node->FindValue() << "\n";
            }
            else {
                std::cout << "NoSuchWord\n";
            }
        }
    }
    delete tree;
    return 0;
}