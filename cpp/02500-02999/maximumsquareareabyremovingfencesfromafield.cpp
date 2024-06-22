
// 2975. Maximum Square Area by Removing Fences From a Field
// https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        // 1 <= hFences.length, vFences.length <= 600
        
        // idea
        //      either from hFences or vFences construct all possible differences
        //      which should worst case by l * (l-1)/2 -> l = 600 -> 179700
        //      sort those by size desc
        //      create a map of the fence positions from the other fences (either hFences or vFences)
        //      then go on that list 1 by 1 and see if we have the largest difference also
        
        
        hFences.push_back(1);
        hFences.push_back(m);
        int hFences_sz = hFences.size();
        unordered_set<int> hDiffs;
        for(int i = 0; i < hFences_sz-1; ++i) {
            int s = hFences[i];
            for(int j = i+1; j < hFences_sz; ++j)
                hDiffs.insert(abs(hFences[j] - s));
        }
        
        int ans = -1;
        
        vFences.push_back(1);
        vFences.push_back(n);
        sort(vFences.begin(),vFences.end());
        for(int i = 0; i < vFences.size()-1; ++i) {
            int s = vFences[i];
            int j = vFences.size()-1;
            while( j > i && vFences[j] - s > ans ) {
                if( hDiffs.find(vFences[j] - s) != hDiffs.end() )
                    ans = vFences[j] - s;
                --j;
            }
        }
        if( ans == -1 )
            return -1;
        
        return ((long)ans * (long)ans) % 1000000007L;
    }
};
