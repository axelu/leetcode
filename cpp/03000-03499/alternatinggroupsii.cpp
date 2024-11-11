
// 3208. Alternating Groups II
// https://leetcode.com/problems/alternating-groups-ii/


class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        // an alternating group cannot cross consecutive tiles of the the same color
        
        // 012345678901234
        // 0123456789                   colors.size() = 10
        // 012345                       k = 6
        //  012345
        //   ...
        //          012345
        
        for(int i = 0; i < k-1; ++i)
            colors.push_back(colors[i]);
        
        int n = colors.size();
        
        // start at first index for colors[index] != colors[index+1]
        int i = 0;
        while( i < n-1 && colors[i] == colors[i+1] )
            ++i;
        if( i == n-1 )
            return 0;
        
        int ans = 0;
        
        for(int j = i+1; j < n; ++j) {
            if( j == n-1 || colors[j] == colors[j+1] ) {        
                // we have a window from i to j of alternating colors
                // cout << "i " << i << " j " << j << endl;
                
                int t = (j - i + 1) - k + 1;
                if( t > 0 )
                    ans += t;
                
                // advance
                i = j+1;
                while( i < n-1 && colors[i] == colors[i+1] )
                    ++i;
                j = i; // loop advances j
            }
        }
        
        return ans;
    }
};
