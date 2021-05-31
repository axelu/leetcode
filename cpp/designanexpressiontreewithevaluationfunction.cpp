
// 1628. Design an Expression Tree With Evaluate Function
// https://leetcode.com/problems/design-an-expression-tree-with-evaluate-function/




/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {
public:
    virtual ~Node () {};
    virtual int evaluate() const = 0;
protected:
    // define your fields here
    string val;
    Node* left;
    Node* right;
};

class ImplNode : public Node {
public:
    ImplNode(string s) {
        val = s;
        left = nullptr;
        right = nullptr;
    }

    ImplNode(string s, Node* l, Node* r) {
        val = s;
        left = l;
        right = r;
    }

    int evaluate() const override {
        if( val == "+" || val == "-" || val == "*" || val == "/" ) {
            int l = left->evaluate();
            int r = right->evaluate();
            if( val == "+") return l+r;
            if( val == "-") return l-r;
            if( val == "*") return l*r;
            if( val == "/") return l/r;
        }
        return stoi(val);
    }
};

/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input
 * and returns the expression tree represnting it as a Node.
 */

class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix) {

        stack<Node*> stck;
        Node* node;
        for(int i = 0; i < postfix.size(); ++i) {
            if( postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" || postfix[i] == "/" ) {
                Node* r = stck.top();
                stck.pop();
                Node* l = stck.top();
                stck.pop();
                node = new ImplNode(postfix[i],l,r);
            } else {
                node = new ImplNode(postfix[i]);
            }
            stck.push(node);
        }
        return node;
    }
};


/**
 * Your TreeBuilder object will be instantiated and called as such:
 * TreeBuilder* obj = new TreeBuilder();
 * Node* expTree = obj->buildTree(postfix);
 * int ans = expTree->evaluate();
 */
