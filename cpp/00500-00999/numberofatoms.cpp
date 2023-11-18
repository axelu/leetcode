
// 726. Number of Atoms
// https://leetcode.com/problems/number-of-atoms/




class Solution {
private:
    string get_element(string& formula, int& i) {
        // i will be at a position in formula that is an uppercase letter
        string ret = "";
        ret += formula[i++];
        while( i < formula.size() && islower(formula[i]) )
            ret += formula[i++];
        return ret;
    }

    int get_count(string& formula, int& i) {
        if( i == formula.size() || !isdigit(formula[i]) )
            return 1;

        int ret = formula[i++]-'0';
        while( i < formula.size() && isdigit(formula[i]) )
            ret = ret * 10 + (formula[i++]-'0');
        return ret;
    }

    map<string,int> rec(string& formula, int& i) {
        map<string,int> ret;

        while( i < formula.size() ) {

            if( isupper(formula[i]) ) {
                string element = get_element(formula,i);
                int count = get_count(formula,i);
                auto p = ret.insert({element,count});
                if( !p.second )
                    p.first->second += count;
            } else if( formula[i] == '(' ) {
                map<string,int> t = rec(formula,++i);
                // when we return here, formula[i] must be a ')'
                ++i;
                int factor = get_count(formula,i);
                for(auto& tp: t) {
                    tp.second *= factor;
                    auto p = ret.insert({tp.first,tp.second});
                    if( !p.second )
                        p.first->second += tp.second;
                }

            } else if( formula[i] == ')' ) {
                return ret;
            }
        }

        return ret;
    }

public:
    string countOfAtoms(string formula) {

        int i = 0;
        map<string,int> res = rec(formula,i);

        string ans = "";
        for(auto& p: res) {
            ans = ans + p.first;
            if( p.second > 1 )
                ans = ans + to_string(p.second);
        }

        return ans;
    }
};
