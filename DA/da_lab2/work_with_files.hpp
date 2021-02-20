#pragma once

#include <iostream>
#include <fstream>
#include "RBTree.hpp"

template <class T1, class T2>
void Load_tree(std::ifstream *File, Tree<T1,T2> *tree) {
    while (!File->eof()) {
        char key [257];
        unsigned long long value;
        File->read(reinterpret_cast<char*>(key), 257*sizeof(char));
        File->read(reinterpret_cast<char*>(&value), sizeof(unsigned long long));
        Node<T1,T2> *node = new Node<T1,T2>;
        node->GetKey(key);
        node->GetValue(value);
        if (tree->Insert(node) != 0) {
            delete node;
        }
    }
}

template <class T1, class T2>
void Tree_save(std::ostream &File, Tree<T1,T2> *tree, Node<T1,T2> *node) {
    if (node != tree->FindTNull()) {
        Tree_save(File, tree, node->FindLeft());
        char key [257];
        unsigned long long value = 0;
        Str_copy(node->FindKey(), key);
        value = node->FindValue();
        File.write((const char *)key, sizeof(char)*257);
        File.write((const char *)&value, sizeof(unsigned long long));
        Tree_save(File, tree, node->FindRight());
    }
}

