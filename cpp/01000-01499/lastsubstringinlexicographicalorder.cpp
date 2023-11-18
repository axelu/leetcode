
// https://leetcode.com/problems/last-substring-in-lexicographical-order/
// 1163. Last Substring in Lexicographical Order




class Solution {
public:
    string lastSubstring(string& s) {
        int n = s.size();

        // find all positions of the greatest char in s
        // those positions are the candidates for the
        // start of the last substring in lexicographical order
        int mx_chr = -1;
        vector<int> positions;
        for(int i = 0; i < n; ++i) {
            if( s[i]-'a' > mx_chr ) {
                mx_chr = s[i]-'a';
                positions.clear();
                positions.push_back(i);
            } else if( s[i]-'a' == mx_chr ) {
                positions.push_back(i);
            }
        }

        int p_sz = positions.size();
        if( p_sz == n )
            return s;
        if( p_sz == 1 )
            return s.substr(positions[0]);


        int pos_i = p_sz - 2;
        int pos_j = p_sz - 1;
        while( true ) {

            // start comparing strings starting at i+1 and j+1
            int i = positions[pos_i] + 1;
            int j = positions[pos_j] + 1;
            while( true ) {
                if( j == n ) {
                    // the larger substring starts at positions[pos_i]
                    pos_j = pos_i;
                    pos_i = pos_j - 1;
                    break;

                } else if( i == positions[pos_j] ) {
                    // the larger substring starts at positions[pos_i]
                    pos_j = pos_i;
                    pos_i = pos_j - 1;
                    break;

                } else if( s[i] > s[j] ) {
                    // the larger substring starts at i
                    pos_j = pos_i;
                    pos_i = pos_j - 1;
                    break;

                } else if( s[i] < s[j] ) {
                    // the larger substring start at j
                    --pos_i;

                    break;
                }
                ++i;
                ++j;
            }

            // exit
            if( pos_j == 0 )
                break;
            if( pos_i < 0 )
                break;
        }

        return s.substr(positions[pos_j]);
    }
};
