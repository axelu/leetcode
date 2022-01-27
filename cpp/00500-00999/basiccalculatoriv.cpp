
// 770. Basic Calculator IV
// https://leetcode.com/problems/basic-calculator-iv/


class Poly {
public:
    map<vector<string>,int> terms;

    Poly(){};

    Poly(string& s) {
        // s contains either a variable or a non-negative integer
        if( isdigit(s[0]) ) terms.insert({{},stoi(s)});
        else terms.insert({{s},1});
    }

    void add(Poly& p) {
        map<vector<string>,int>::iterator search;
        for(pair<vector<string>,int> pterm : p.terms) {
            search = terms.find(pterm.first);
            if( search != end(terms) ) search->second += pterm.second;
            else terms.insert({pterm.first,pterm.second});
        }
    }

    void sub(Poly& p) {
        map<vector<string>,int>::iterator search;
        for(pair<vector<string>,int> pterm : p.terms) {
            search = terms.find(pterm.first);
            if( search != end(terms) ) search->second -= pterm.second;
            else terms.insert({pterm.first,-pterm.second});
        }
    }

    void mul(Poly& p) {
        map<vector<string>,int> tmpTerms = move(terms);
        terms.clear();

        vector<string> key;
        map<vector<string>,int>::iterator terms_search;
        for(pair<vector<string>,int> tmpTerm : tmpTerms)
            for(pair<vector<string>,int> pterm : p.terms) {
                key = {};
                for(string s : tmpTerm.first) key.push_back(s);
                for(string s : pterm.first) key.push_back(s);
                sort(begin(key),end(key));
                terms_search = terms.find(key);
                if( terms_search != end(terms) ) terms_search->second += (tmpTerm.second * pterm.second);
                else terms.insert({key,tmpTerm.second * pterm.second});
            }
    }

    Poly eval(unordered_map<string,int>& evalmap) {
        map<vector<string>,int> tmpTerms = move(terms);
        terms.clear();

        unordered_map<string,int>::iterator em_ite = end(evalmap);
        unordered_map<string,int>::iterator em_search;
        vector<string> key;
        int ce;
        map<vector<string>,int>::iterator terms_search;
        for(pair<vector<string>,int> tmpTerm : tmpTerms) {
            ce = tmpTerm.second;
            key = {};
            for(string s : tmpTerm.first) {
                em_search = evalmap.find(s);
                if( em_search != em_ite ) ce *= em_search->second;
                else key.push_back(s);
            }
            terms_search = terms.find(key);
            if( terms_search != end(terms) ) terms_search->second += ce;
            else terms.insert({key,ce});
        }

        return *this;
    }

    vector<string> toList() {
        vector<vector<string>> keys;
        for(pair<vector<string>,int> term : terms)
            keys.push_back(term.first);

        sort(begin(keys),end(keys),[](vector<string> a, vector<string> b) {
            size_t na = a.size();
            size_t nb = b.size();
            if( na > nb ) {
                return true;
            } else if( na == nb ) {
                string x,y;
                for(int i = 0; i < na; ++i) {
                    x = a[i];
                    y = b[i];
                    if( x != y ) return x < y;
                }
            }
            return false;
        });

        vector<string> ans;
        string r;
        int ce;
        for(vector<string> key : keys) {
            ce = terms.find(key)->second;
            if( ce == 0 ) continue;
            r = to_string(ce);
            for(string s : key) r += "*" + s;
            ans.push_back(r);
        }

        return ans;
    }
};

class Solution {
private:
    size_t n;
    int gpos;
    unordered_map<string,int> evalmap;

    Poly make(string& s) {
        return Poly(s);
    }

    Poly combine(Poly& left, Poly& right, char operation) {
        if( operation == '+' ) {
            left.add(right);
        } else if( operation == '-' ) {
            left.sub(right);
        } else {
            // operation == '*'
            left.mul(right);
        }
        return left;
    }

    Poly parse(string& expr, int pos = 0) {
        deque<char> os; // operations
        deque<Poly> ps; // operands aka Poly's

        string t = "";
        char c,op;
        Poly left,right;

        int i;
        for(i = pos; i < n; ++i) {
            c = expr[i];
            if( c == ')' ) {
                gpos = i;
                break;
            } else if ( c == '(') {
                right = parse(expr,i+1);
                t = "";
                i = gpos;
            } else if( isalnum(c) ) {
                t += c;
            } else if ( !isblank(c) ) {
                if( t != "" ) {
                    // t contains either a variable or a non-negative integer
                    right = make(t);
                }
                if( os.empty() || os.back() == '+' || os.back() == '-' ) {
                    // push operand
                    ps.push_back(right);
                } else {
                    // os.top() == "*"
                    // get operation
                    op = '*';
                    os.pop_back();
                    // get left operand
                    left = ps.back();
                    ps.pop_back();
                    // execute operation and push operand
                    ps.push_back(combine(left,right,op));
                }
                // push operation
                os.push_back(c);
                t = "";
            }
        }

        // finish up
        if( t != "" ) {
            // t contains either a variable or a non-negative integer
            right = make(t);
        }
        if( ps.empty() ) {
            return right;
        } else if( os.back() == '+' || os.back() == '-' ) {
            // push operand
            ps.push_back(right);
        } else {
            // os.top() == "*"
            // get operation
            op = '*';
            os.pop_back();
            // get left operand
            left = ps.back();
            ps.pop_back();
            // execute operation and push operand
            ps.push_back(combine(left,right,op));
        }

        // stack of operands contains at least one Poly
        left = ps.front();
        ps.pop_front();
        // if more than one, we pop alternating an operation and an operand
        while( !ps.empty() ) {
            op = os.front();
            os.pop_front();
            right = ps.front();
            ps.pop_front();
            left = combine(left,right,op);
        }

        return left;
    }

public:
    vector<string> basicCalculatorIV(string expr, vector<string>& evalvars, vector<int>& evalints) {
        n = expr.size();

        for(int i = 0; i < evalvars.size(); ++i)
            evalmap.insert({evalvars[i],evalints[i]});

        return parse(expr).eval(evalmap).toList();
    }
};
