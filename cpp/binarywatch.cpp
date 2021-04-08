
// Binary Watch
// https://leetcode.com/problems/binary-watch/


class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        if( num == 0 ) return {"0:00"};
        if( num >= 9 ) return {};
        
        // binary 1111111111 = decimal 1023
        
        vector<string> r;
        
        for(int i = 0; i <= 1023; ++i) {
            bitset bs = bitset<10>(i);
            if( bs.count() == num ) {
                string b = bs.to_string();
                int h = bitset<4>(b.substr(6)).to_ulong();
                int m = bitset<6>(b.substr(0,6)).to_ulong();
                if( h <= 11 && m <= 59 )
                    r.push_back( to_string(h) + ":" + (( m <= 9 ) ? "0" + to_string(m) : to_string(m)) );
            }
        }

/*
        sort(r.begin(),r.end(),[](string a, string b){
            if( a.size() < b.size () ) {
                return true;
            } else if ( a.size() > b.size() ) {
                return false;
            } else {
                // same size
                return a < b;
            }
        });
*/
        
        return r; 
    }
};
