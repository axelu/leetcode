
// day 4 September 2020 challenge
// Partition Labels
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/554/week-1-september-1st-september-7th/3448/
// https://leetcode.com/problems/partition-labels/



class Solution {
public:
    vector<int> partitionLabels(string S) {
        // s.size() >= 1
        if( S.size() == 1 ) return {1};

        unordered_map<char,int> last;

        vector<int> r;

        char cc = S[0];
        auto cl = S.find_last_of(cc);
        last.insert({cc,cl});
        r.push_back(cl + 1);
        for(int pos = 0; pos < S.size(); ++pos) {
            char c = S[pos];
            if( c != cc ) {
                if( last.find(c) == last.end() )
                    // first time we encounter this char
                    last.insert({c,S.find_last_of(c)});
            } else {
                continue;
            }
/*
            cout << "pos     " << pos << endl;
            cout << "c       " << c << endl;
            cout << "c last  " << last.find(c)->second << endl;
            cout << "cc      " << cc << endl;
            cout << "cc last " << last.find(cc)->second << endl;
*/
            if( pos > last.find(cc)->second ) {
                cc = c;
                r.push_back(last.find(cc)->second - pos + 1);
            } else if ( last.find(c)->second > last.find(cc)->second ) {
                r.back() += last.find(c)->second - last.find(cc)->second;
                cc = c;
            }
        }

        return r;
    }
};
