#pragma once

#include <iostream>
#include "functions.hpp"

typedef enum { BLACK, RED } NodeColor;

template<class T1, class T2>
class Node {
private:
    T1 Key;
    T2 Value;
    Node* Left;
    Node* Right;
    Node* Parent;
    NodeColor Color; // Color: Black or Red
public:
    Node(): Key(nullptr), Value(0), Left(nullptr), Right(nullptr), Parent(nullptr), Color(RED) {}

    void GetKey(T1 key) {
        
        Key = new char [257];
        int i = 0;
        while (i != 256 && key[i] != '\0') {
            if ('A' <= key[i] && key[i] <= 'Z') {
                Key[i] = key[i] - 'A' + 'a';
            }
            else {
                Key[i] = key[i];
            }
            i++;            
        }
        Key[i] = '\0';
        while (i != 257) {
            Key[i] = 0;
            i++;
        }
        
    }
    
    T1 FindKey() {
        return Key;
    }
    void GetValue(T2 value) {
        Value = value;
    }
    T2 FindValue() {
        return Value;
    }
    void GetLeft(Node* node) {
        Left = node;
    }
    Node* FindLeft() {
        return Left;
    }
    void GetRight(Node* node) {
        Right = node;
    }
    Node* FindRight() {
        return Right;
    }
    void GetParent(Node* parent) {
        Parent = parent;
    }
    Node* FindParent() {
        return Parent;
    }
    void GetColor(NodeColor color) {
        Color = color;
    }
    NodeColor FindColor() {
        return Color;
    }
    ~Node() {
        delete [] Key;
    }
};

template<class T1, class T2>
class Tree {
private:
    Node<T1,T2>* Root;
    Node<T1,T2>* TNull;
public:
    Tree() {
        TNull = new Node<T1,T2>;
        TNull->GetColor(BLACK);
        Root = TNull;
        TNull->GetLeft(Root);
        TNull->GetRight(Root);
        Root->GetParent(TNull);
    }

    Node<T1,T2>* FindRoot() {
        return Root;
    }

    Node<T1,T2>* FindTNull() {
        return TNull;
    }

    void GetKey(T1 key) {
        Root->GetKey(key);
    }

    void GetValue(T2 value) {
        Root->GetValue(value);
    }
    
    void AllTreeDelete() {
        Node<T1,T2> *current_root = Root;
        Node<T1,T2> *deleting_ptr = nullptr;
        while (current_root != TNull) {
            if (current_root->FindLeft() != TNull) {
                current_root = current_root->FindLeft();
            }
            else if (current_root->FindRight() != TNull) {
                current_root = current_root->FindRight();
            }
            else {
                deleting_ptr = current_root;
                if (current_root->FindParent()->FindLeft() == current_root) {
                    current_root->FindParent()->GetLeft(TNull);
                }
                else {
                    current_root->FindParent()->GetRight(TNull);
                }
                current_root = current_root->FindParent();
                delete deleting_ptr;
            }
        }
        delete TNull;
    } 
    
    Node<T1,T2>* Search(T1 key) {
        Node<T1,T2> *x = Root;
        while (x != TNull && Equal_strings(key, x->FindKey()) != 0) { // 
            if (Equal_strings(key, x->FindKey()) == -1) {
                x = x->FindLeft();
            }
            else {
                x = x->FindRight();
            }
        }
        if (x == TNull) {
            return nullptr;
        }
        return x;
    }
    
    void LeftRotation(Node<T1,T2>* x) {
        Node<T1,T2> *y = x->FindRight();  // у is instally the right node of x
        x->GetRight(y->FindLeft());  // Turning the left node of y into the right node of x
        if (y->FindLeft() != TNull) {
            y->FindLeft()->GetParent(x);
        }
        y->GetParent(x->FindParent()); // The parent of y became the parent of x
        if (x->FindParent() == TNull) {
            Root = y;
        }
        else if (x == x->FindParent()->FindLeft()) {
            x->FindParent()->GetLeft(y);
        }
        else {
            x->FindParent()->GetRight(y);
        }
        y->GetLeft(x); // x becomes the left child of y
        x->GetParent(y);
    }

    void RightRotation(Node<T1,T2>* x) {
        Node<T1,T2> *y = x->FindLeft(); // y is instally the left node of x
        x->GetLeft(y->FindRight()); // Turning the right node of y into the left node of x
        if (y->FindRight() != TNull) {
            y->FindRight()->GetParent(x);
        }
        y->GetParent(x->FindParent()); // The parent of y became the patent of x
        if (x->FindParent() == TNull) {
            Root = y;
        }
        else if (x == x->FindParent()->FindLeft()) {
            x->FindParent()->GetLeft(y);
        }
        else {
            x->FindParent()->GetRight(y);
        }
        y->GetRight(x); // x becomes the right child of y
        x->GetParent(y);
    }
    
    void Fixup(Node<T1,T2>* x) {
        while (x->FindParent()->FindColor() == RED) {
            if (x->FindParent() == x->FindParent()->FindParent()->FindLeft()) {
                Node<T1,T2> *y;
                y = x->FindParent()->FindParent()->FindRight();
                if (y->FindColor() == RED) {
                    x->FindParent()->GetColor(BLACK);
                    y->GetColor(BLACK);
                    x->FindParent()->FindParent()->GetColor(RED);
                    x = x->FindParent()->FindParent();
                }
                else {
                    if (x == x->FindParent()->FindRight()) {
                        x = x->FindParent();
                        LeftRotation(x);
                    }
                    x->FindParent()->GetColor(BLACK);
                    x->FindParent()->FindParent()->GetColor(RED);
                    RightRotation(x->FindParent()->FindParent());
                }
            }
            else {
                Node<T1,T2> *y;
                y = x->FindParent()->FindParent()->FindLeft();
                if (y->FindColor() == RED) {
                    x->FindParent()->GetColor(BLACK);
                    y->GetColor(BLACK);
                    x->FindParent()->FindParent()->GetColor(RED);
                    x = x->FindParent()->FindParent();
                }
                else {
                    if (x == x->FindParent()->FindLeft()) {
                        x = x->FindParent();
                        RightRotation(x);
                    }
                    x->FindParent()->GetColor(BLACK);
                    x->FindParent()->FindParent()->GetColor(RED);
                    LeftRotation(x->FindParent()->FindParent());
                }
            }
        }
        Root->GetColor(BLACK); 
    }

    bool Insert(Node<T1, T2>* insertable_root) {
        Node<T1, T2> *parent_root = TNull;
        Node<T1,T2> *current_root = Root;
        while (current_root != TNull) {
            parent_root = current_root;
            int strings_comparison = Equal_strings(insertable_root->FindKey(), current_root->FindKey());
            if (strings_comparison != 0) { 
                if (strings_comparison == -1) {
                    current_root = current_root->FindLeft();
                }
                else {
                    current_root = current_root->FindRight();
                }
            }
            else {
                return 1;
            }
        }
        insertable_root->GetParent(parent_root);
        if (parent_root == TNull) {
            Root = insertable_root;
        }
        else if (Equal_strings(insertable_root->FindKey(), parent_root->FindKey()) == -1) {
            parent_root->GetLeft(insertable_root);
        }
        else {
            parent_root->GetRight(insertable_root);
        }
        insertable_root->GetLeft(TNull);
        insertable_root->GetRight(TNull);
        insertable_root->GetColor(RED);
        Fixup(insertable_root);
        return 0;
    }

    Node<T1,T2> *TreeMinimum(Node<T1,T2> *x) {
        while (x->FindLeft() != TNull) {
            x = x->FindLeft();
        }
        return x;
    }

    void Transplant(Node<T1,T2> *u, Node<T1,T2> *v) {
        if (u->FindParent() == TNull) {
            Root = v;
        }
        else if (u == u->FindParent()->FindLeft()) {
            u->FindParent()->GetLeft(v);
        }
        else {
            u->FindParent()->GetRight(v);
        }
        v->GetParent(u->FindParent());
    }

    void DeleteFixup(Node<T1,T2> *x) {
        while ((x != Root) && (x->FindColor() == BLACK)) {
            if (x == x->FindParent()->FindLeft()) {
                Node<T1,T2> *y = x->FindParent()->FindRight();
                if (y->FindColor() == RED) {
                    y->GetColor(BLACK);
                    x->FindParent()->GetColor(RED);
                    LeftRotation(x->FindParent());
                    if (x->FindParent() == Root) {
                        Root = x->FindParent()->FindParent();
                    }
                    y = x->FindParent()->FindRight();
                }
                if ((y->FindLeft()->FindColor() == BLACK) && (y->FindRight()->FindColor() == BLACK)) {
                    y->GetColor(RED);
                    x = x->FindParent();
                }
                else {
                    if (y->FindRight()->FindColor() == BLACK) {
                        y->FindLeft()->GetColor(BLACK); 
                        y->GetColor(RED);
                        RightRotation(y);
                        if (y == Root) {
                            Root = y->FindParent();
                        }
                        y = x->FindParent()->FindRight();
                    }
                    y->GetColor(x->FindParent()->FindColor());
                    x->FindParent()->GetColor(BLACK);
                    y->FindRight()->GetColor(BLACK);
                    LeftRotation(x->FindParent());
                    if (x->FindParent() == Root) {
                        Root = x->FindParent()->FindParent();
                    }
                    x = Root;
                }
            }
            else {
                Node<T1,T2> *y = x->FindParent()->FindLeft();
                if (y->FindColor() == RED) {
                    y->GetColor(BLACK);
                    x->FindParent()->GetColor(RED);
                    RightRotation(x->FindParent());
                    if (x->FindParent() == Root) {
                        Root = x->FindParent()->FindParent();
                    }
                    y = x->FindParent()->FindLeft();
                }
                if ((y->FindRight()->FindColor() == BLACK) && (y->FindLeft()->FindColor() == BLACK)) {
                    y->GetColor(RED);
                    x = x->FindParent();
                }
                else {
                    if (y->FindLeft()->FindColor() == BLACK) {
                        y->FindRight()->GetColor(BLACK);
                        y->GetColor(RED);
                        LeftRotation(y);
                        if (Root == y) {
                            Root = y->FindParent();
                        }
                        y = x->FindParent()->FindLeft();
                    }
                    y->GetColor(x->FindParent()->FindColor());
                    x->FindParent()->GetColor(BLACK);
                    y->FindLeft()->GetColor(BLACK);
                    RightRotation(x->FindParent());
                    if (x->FindParent() == Root) {
                        Root = x->FindParent()->FindParent();
                    }
                    x = Root;
                }
            }
        }
        x->GetColor(BLACK);
    }

    void Delete(Node<T1,T2>* z) {
        Node<T1,T2> *y = z;
        Node<T1,T2> *x;
        NodeColor y_original_color = y->FindColor();
        if (z->FindLeft() == TNull) {
            x = z->FindRight();
            Transplant(z, z->FindRight());
            if (z == Root) {
                Root = x;
            }
        }
        else if (z->FindRight() == TNull) {
            x = z->FindLeft();
            Transplant(z, z->FindLeft());
            if (z == Root) {
                Root = x;
            }
        }
        else {
            y = TreeMinimum(z->FindRight());
            y_original_color = y->FindColor();
            x = y->FindRight();
            if (y->FindParent() == z) {
                x->GetParent(y);
            }
            else {
                Transplant(y, y->FindRight());
                y->GetRight(z->FindRight());
                y->FindRight()->GetParent(y);
            }
            Transplant(z, y);
            y->GetLeft(z->FindLeft());
            y->FindLeft()->GetParent(y);
            y->GetColor(z->FindColor());
        }
        if (y_original_color == BLACK) {
            DeleteFixup(x);
        }
        delete z;
    }

    ~Tree() {
        AllTreeDelete();
    }
};