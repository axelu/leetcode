
// 1597. Build Binary Expression Tree From Infix Expression
// https://leetcode.com/problems/build-binary-expression-tree-from-infix-expression/



/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    string infix2postfix(string infix) {
        string postfix = "";

        stack<char> stck;
        for(char c : infix) {
            if( isdigit(c) ) {
                 postfix += c;

            } else if( c == '(' ) {
                 stck.push(c);

            } else if( c == ')' ) {
                while( stck.top() != '(' ) {
                    postfix += stck.top();
                    stck.pop();
                }
                stck.pop(); // pop opening parenthesis

            } else {
                // char c is an operation: +, -, *, /
                // as long as the current operation has lower or equal precedence
                // compared to what is on top of our stck, we can clear our stack
                // (     -> lowest precedence
                // +, -  -> medium precedence
                // *, /  -> highest precedence
                int c_prec = (c == '*' || c == '/') ? 2 : 1;
                int t_prec;
                while( !stck.empty() ) {
                    if( stck.top() == '*' || stck.top() == '/' )
                        t_prec = 2;
                    else if( stck.top() == '-' || stck.top() == '+' )
                        t_prec = 1;
                    else
                        t_prec = 0;

                    if( c_prec <= t_prec ) {
                        postfix += stck.top();
                        stck.pop();
                    } else {
                        break;
                    }
                }
                stck.push(c); // push the operation to the stack
            }
        }

        while( !stck.empty() ) {
            postfix += stck.top();
            stck.pop();
        }
        return postfix;
    }

    Node* postfix2exptree(string postfix) {
        stack<Node*> stck;

        for(char c: postfix) {
            if( isdigit(c) ) {
                stck.push(new Node(c));

            } else {
                Node* right = stck.top();
                stck.pop();
                Node* left = stck.top();
                stck.pop();

                Node* operation = new Node(c,left,right);
                stck.push(operation);
            }
        }

        return stck.top(); // root of exp tree
    }

public:
    Node* expTree(string s) {
        if( s.size() == 1 )
            return new Node(s[0]);

        // string s is a valid infix expression
        // s consists of digits (operands, operands are one digit) and
        // the characters '+', '-', '*', and '/' (operations) and
        // opening and closing parenthesis

        string postfix = infix2postfix(s); // infix expression to postfix expression
        return postfix2exptree(postfix);   // postfix expression to expression tree
    }
};
