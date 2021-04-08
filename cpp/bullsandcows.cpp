
// day 10 September 2020 challenge
// Bulls and Cows
// https://leetcode.com/problems/bulls-and-cows/



class Solution {
public:
    string getHint(string secret, string guess) {

        unordered_map<char,unordered_set<int>> s = _process(secret);
        unordered_map<char,unordered_set<int>> g = _process(guess);

        int a = 0;
        int b = 0;
        for(auto civ : s) {
            auto f = g.find(civ.first);
            if( f != g.end() ) {
                int at = 0;
                for(auto pos : civ.second) {
                    if( f->second.find(pos) != f->second.end() )
                        ++at;
                }
                a += at;
                b += min(civ.second.size() - at, f->second.size() - at);
            }
        }

        return to_string(a) + "A" + to_string(b) + "B";
    }
private:
    unordered_map<char,unordered_set<int>> _process(string& str) {
        unordered_map<char,unordered_set<int>> m;
        for(int i = 0; i < str.size(); ++i) {
            auto p = m.insert({str[i],{i}});
            if ( !p.second )
                p.first->second.insert(i);
        }
        return m;
    }
};
