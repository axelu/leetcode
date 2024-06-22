
// 3074. Apple Redistribution into Boxes
// https://leetcode.com/problems/apple-redistribution-into-boxes/



class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        // it is guaranteed that it's possible to redistribute packs of apples into boxes
        int total_apples = accumulate(apple.begin(),apple.end(),0);

        sort(capacity.begin(),capacity.end(),greater<>());
        int m = capacity.size();
        int i = 0;
        int running_capacity = 0;
        for(; i < m; ++i) {
            running_capacity += capacity[i];
            if( running_capacity >= total_apples )
                break;
        }

        return i+1;
    }
};
