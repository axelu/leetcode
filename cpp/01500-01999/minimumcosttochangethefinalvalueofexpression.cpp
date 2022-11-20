
// 1896. Minimum Cost to Change the Final Value of Expression
// https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/






class Solution {
private:
    string infix2postfix(string& infix) {
        string postfix = "";

        stack<char> stck;
        for(char c : infix) {
            if( isdigit(c) ) { // 1 or 0
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
                // char c is an operation:
                //     & (bitwise AND operator), | (bitwise OR operator)
                // & and | have equal precedence
                // as the current operation can only have equal precedence
                // compared to what is on top of our stck, we can clear our stack
                while( !stck.empty() && stck.top() != '(' ) {
                    postfix += stck.top();
                    stck.pop();
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

    struct Node{
        int id;
        char val;
        Node* left;
        Node* right;
        Node(int id, char c) : id(id), val(c), left(nullptr), right(nullptr) {}
        Node(int id, char c, Node * l, Node * r) : id(id), val(c), left(l), right(r) {}
    };

    int evaluate(Node* node) {
        if( node->val == '0' )
            return 0;
        else if( node->val == '1' )
            return 1;

        int l = evaluate(node->left);
        int r = evaluate(node->right);

        if( node->val == '|' )
            return l | r;
        else // node->val == '&'
            return l & r;
    }

    int mem[100000][2];

    int rec(Node* node, int desired_result) {
        // cout << "rec node->val " << node->val << " desired_result " << desired_result << endl;
        // returns the minimum number of changes to
        // achieve the desired result compared to the original result

        if( node->val == '0' )
            return desired_result == 0 ? 0 : 1;
        else if( node->val == '1' )
            return desired_result == 1 ? 0 : 1;

        if( mem[node->id][desired_result] != -1 )
            return mem[node->id][desired_result];

        // | operation
        //     desired result 1, keep OR operation:
        //         l = 1, r = 0 OR l = 0, r = 1 OR l = 1, r = 1
        //     desired result 1, change OR operation to AND operation:
        //         l = 1, r = 1
        //     desired result 0, keep OR operation:
        //         l = 0, r = 0
        //     desired result 0, change OR operation to AND operation:
        //         l = 0, r = 0 OR l = 0, r = 1 OR l = 1, r = 0

        // & operation
        //     desired result 1, keep AND operation:
        //         l = 1, r = 1
        //     desired result 1, change AND operation to OR operation:
        //         l = 1, r = 0 OR l = 0, r = 1 OR l = 1, r = 1
        //     desired result 0, keep AND operation:
        //         l = 0, r = 0 OR l = 0, r = 1 OR l = 1, r = 0
        //     desired result 0, change AND operation to OR operation:
        //         l = 0, r = 0

        int l0 = rec(node->left,0);
        int l1 = rec(node->left,1);
        int r0 = rec(node->right,0);
        int r1 = rec(node->right,1);

        int ret = INT_MAX;

        if( node->val == '|' ) {
            if( desired_result == 1 )
                ret = min({l1+r0,l0+r1,l1+r1});
            else
                ret = min({l0+r0,1+l1+r0,1+l0+r1});

        } else { // node->val == '&'
            if( desired_result == 1 )
                ret = min({l1+r1,1+l1+r0,1+l0+r1});
            else
                ret = min({l0+r0,l1+r0,l0+r1});;
        }

        return mem[node->id][desired_result] = ret;
    }

public:
    int minOperationsToFlip(string& expression) {
        string postfix = infix2postfix(expression);
        // cout << postfix << endl;

        // build an expression tree
        stack<Node*> stck;
        Node* node;
        int id = 0;
        for(int i = 0; i < postfix.size(); ++i) {
            if( postfix[i] == '|' || postfix[i] == '&' ) {
                Node* r = stck.top();
                stck.pop();
                Node* l = stck.top();
                stck.pop();
                node = new Node(id++,postfix[i],l,r);
            } else {
                node = new Node(id++,postfix[i]);
            }
            stck.push(node);
        }

        // evalute the current expression(tree)
        int org = evaluate(node);
        // cout << "org " << org << endl;

        memset(mem,-1,sizeof mem);
        return rec(node,!org);
    }
};
