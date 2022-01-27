
// 736. Parse Lisp Expression
// https://leetcode.com/problems/parse-lisp-expression/



class Solution {
    int getValue(string key, vector<unordered_map<string,int>>& stck) {
        int ret = -10;
        for(int i = stck.size()-1; i >= 0; --i) {
            auto f = stck[i].find(key);
            if( f != stck[i].end() ) {
                ret = f->second;
                break;
            }
        }
        return ret;
    }

    int rec(string& expression, int n, int& pos, vector<unordered_map<string,int>>& stck) {
        // cout << "rec pos " << pos << " stck.size " << stck.size() << endl;

        if( expression[pos] == 'l' ) {          // let
            // cout << "  let" << endl;

            // the value of the last token is what we will return
            // advance to 1st token
            pos += 4;
            // build a map of key values
            // keys and values alternate, but last token is what we return
            unordered_map<string,int> um;
            stck.push_back(um);
            int f = 0; // key 0 val 1
            string key = "";
            while(true) {
                if( f == 0 ) { // key
                    int v;
                    if( expression[pos] == '-' || isdigit(expression[pos]) ) {
                        string t = "";
                        while( expression[pos] != ' ' && expression[pos] != ')' ) {
                            t += expression[pos];
                            ++pos;
                        }
                        v = stoi(t);
                    } else if( expression[pos] == '(' ) {
                        ++pos;
                        v = rec(expression,n,pos,stck);
                    } else {
                        while( expression[pos] != ' ' && expression[pos] != ')' ) {
                            key += expression[pos];
                            ++pos;
                        }
                    }
                    if( expression[pos] == ' ' ) {
                        ++pos;
                        f = 1;  // expect a value next
                    } else {    // has to be a ')'
                        ++pos;
                        int t;
                        if( !key.empty() )
                            v = getValue(key,stck);
                        stck.pop_back();
                        return v;
                    }
                } else { // value
                    int v;
                    if( expression[pos] != '-' && !isdigit(expression[pos]) && expression[pos] != '(' ) {
                        string t = "";
                        while( expression[pos] != ' ' && expression[pos] != ')') {
                            t += expression[pos];
                            ++pos;
                        }
                        v = getValue(t,stck);
                    } else if( expression[pos] == '-' || isdigit(expression[pos]) ) {
                        string t = "";
                        while( expression[pos] != ' ' && expression[pos] != ')' ) {
                            t += expression[pos];
                            ++pos;
                        }
                        v = stoi(t);
                    } else {
                        ++pos;
                        v = rec(expression,n,pos,stck);
                    }
                    stck.back()[key] = v;
                    if( expression[pos] == ')' ) {
                        ++pos;
                        stck.pop_back();
                        return v;
                    } else { // has to be a ' '
                        ++pos;
                        key = "";
                        f = 0;  // expect key next
                    }
                }

            }
        } else {   // add or mult
            // add a b OR mult a b
            // advance and remember op
            int op; // add 0, mult = 1
            if( expression[pos] == 'a' ) {
                // cout << "  add" << endl;
                pos += 4; op = 0;
            } else {
                // cout << "  mult" << endl;
                pos += 5; op = 1;
            }
            // a
            int a;
            if( expression[pos] == '-' || isdigit(expression[pos]) ) {
                string t = "";
                while( expression[pos] != ' ' ) {
                    t += expression[pos];
                    ++pos;
                }
                ++pos;
                a = stoi(t);
            } else if( expression[pos] == '(' ) {
                ++pos;
                a = rec(expression,n,pos,stck);
                ++pos;
            } else {
                string t = "";
                while( expression[pos] != ' ' ) {
                    t += expression[pos];
                    ++pos;
                }
                ++pos;
                a = getValue(t,stck);
            }
            // b
            int b;
            if( expression[pos] == '-' || isdigit(expression[pos]) ) {
                string t = "";
                while( expression[pos] != ')' ) {
                    t += expression[pos];
                    ++pos;
                }
                ++pos;
                b = stoi(t);
            } else if( expression[pos] == '(' ) {
                ++pos;
                b = rec(expression,n,pos,stck);
                ++pos;
            } else {
                string t = "";
                while( expression[pos] != ')' ) {
                    t += expression[pos];
                    ++pos;
                }
                ++pos;
                b = getValue(t,stck);
            }
            // eval
            int r = op == 0 ? a+b : a*b;
            // cout << "  eval op " << op << " a " << a << " b " << b << " r " << r << " pos " << pos << endl;
            return r;
        }
    }

public:
    int evaluate(string& expression) {
        if( expression[0] == '-' || isdigit(expression[0]) )
            return stoi(expression);

        int n = expression.size(); // cout << "n " << n << endl;
        vector<unordered_map<string,int>> stck;
        int pos = 1; // expression starts with '('
        int ans = rec(expression,n,pos,stck);

        // cout << "pos " << pos << endl;
        // cout << "stck.size " << stck.size() << endl;

        return ans;
    }
};
