
// 1426. Counting Elements
// https://leetcode.com/problems/counting-elements/



class Solution {
public:
    int countElements(vector<int>& arr) {
        int n = arr.size();
        unordered_set<int> us;
        for(int i = 0; i < n; ++i)
            us.insert(arr[i]);
        int ans = 0;
        unordered_set<int>::iterator e = us.end();
        for(int i = 0; i < n; ++i)
            if( us.find(arr[i]+1) != e ) ++ans;
        return ans;
    }
};
