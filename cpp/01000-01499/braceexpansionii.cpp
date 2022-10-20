
// 1096. Brace Expansion II
// https://leetcode.com/problems/brace-expansion-ii/




// see 1597. Build Binary Expression Tree From Infix Expression
// https://leetcode.com/problems/build-binary-expression-tree-from-infix-expression/

class Solution {
private:
    string infix2postfix(string infix) {
        string postfix = "";

        int n = infix.size();

        stack<char> stck;
        for(int i = 0; i < n; ++i) {
            char c = infix[i];

            if( islower(c) ) {
                // we need to look one back to determine operation
                // if prior char is a lowercase letter or a '}'
                // then our operation is 'concatenate'
                // if it is ',' we already accounted for it
                if( i > 0 ) {
                    char pre = infix[i-1];
                    if( islower(pre) || pre == '}' ) {
                        while( !stck.empty() && stck.top() == '+' ) {
                            postfix += stck.top();
                            stck.pop();
                        }
                        stck.push('+');
                    }
                }
                postfix += c;

            } else if( c == '{' ) {
                // we need to look one back to determine operation
                if( i > 0 ) {
                    char pre = infix[i-1];
                    if( islower(pre) || pre == '}' ) {
                        while( !stck.empty() && stck.top() == '+' ) {
                            postfix += stck.top();
                            stck.pop();
                        }
                        stck.push('+');
                    }
                }
                stck.push(c);

            } else if( c == '}' ) {
                while( stck.top() != '{' ) {
                    postfix += stck.top();
                    stck.pop();
                }
                stck.pop(); // pop opening parenthesis

            } else {
                // char c is an operation aka ','
                // as long as the current operation has lower or equal precedence
                // compared to what is on top of our stck, we can clear our stack
                // {     -> lowest precedence
                // ,     -> medium precedence
                // +     -> highest precedence
                int c_prec = 1;
                int t_prec;
                while( !stck.empty() ) {
                    if( stck.top() == '+' )
                        t_prec = 2;
                    else if( stck.top() == ',' )
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

    set<string> postfix2set(string postfix) {
        stack<set<string>> stck;

        for(char c: postfix) {
            if( islower(c) ) {
                stck.push({string(1,c)});
            } else {
                auto b = stck.top();
                stck.pop();
                auto a = stck.top();
                stck.pop();

                set<string> r;

                if( c == '+' ) // concatenate
                    for(auto& sa : a)
                        for(auto& sb : b)
                            r.insert(sa+sb);
                else {
                    for(auto& sb : b)
                        a.insert(sb);
                    r = a;
                }

                stck.push(r);
            }
        }

        return stck.top();
    }
public:
    vector<string> braceExpansionII(string expression) {
        string postfix = infix2postfix(expression);
        // cout << postfix << endl;
        set<string> st = postfix2set(postfix);

        return vector(st.begin(),st.end());
    }
};
