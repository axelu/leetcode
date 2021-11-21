
// 1689. Partitioning Into Minimum Number Of Deci-Binary Numbers
// https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/



class Solution {
public:
    int minPartitions(string n) {
        int mx = 0;
        for(int i = 0; i < n.size(); ++i) {
            mx = max(mx,n[i]-'0');
            if( mx == 9 ) break;
        }
        return mx;
    }
};
