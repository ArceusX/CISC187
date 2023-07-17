#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

/* Each node contains either
 *      1. question as data and y/n responses as child nodes
 *      2. object name as data and 2 null child pointers
 */
struct Node {
    std::string data;
    Node* ifYes;
    Node* ifNo;
    
    Node(std::string data, Node* yes = nullptr, Node* no = nullptr): 
        data(data), ifYes(yes), ifNo(no) {}
    
    // in was passed file, reads it, stores data into node
    static void read(std::istream& in, Node*& node);
    
    // out was passed file, writes data in tree into file
    static void write(std::ostream& out, const Node* node,
        std::string whitespace = "");
    
    friend std::istream& operator>>(std::istream&, Node*&);
    friend std::ostream& operator<<(std::ostream&, const Node*);
    
    ~Node();
};

inline std::ostream& operator<<(std::ostream& out, const Node* node) {
    Node::write(out, node);
    return out;
}

inline std::istream& operator>>(std::istream& in, Node*& node) {
    Node::read(in, node);
    return in;
}

#endif
