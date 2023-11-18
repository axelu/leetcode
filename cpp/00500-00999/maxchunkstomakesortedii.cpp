
// 768. Max Chunks To Make Sorted II
// https://leetcode.com/problems/max-chunks-to-make-sorted-ii/





class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size();

        vector<int> arrsorted(arr);
        sort(arrsorted.begin(),arrsorted.end());
        // debug
        // for(int i = 0; i < n; ++i)
        //     cout << i << ":" << arrsorted[i] << " ";
        // cout << endl;

        unordered_map<int,pair<int,int>> cnt; // val, {cnt arrsorted, cnt arr}

        int ans = 0;
        int diff = 0;
        for(int i = 0; i < n; ++i) {
            auto psorted = cnt.insert({arrsorted[i],{1,0}});
            if( psorted.second ) {
                ++diff; // we discovered a new distinct number
            } else {
                ++psorted.first->second.first;
            }

            auto p = cnt.insert({arr[i],{0,1}});
            if( p.second ) {
                ++diff; // we discovered a new distinct number
            } else {
                ++p.first->second.second;
            }

            if( psorted.first->second.first == psorted.first->second.second ) {
                --diff;
                cnt.erase(psorted.first);
            }
            if( arrsorted[i] != arr[i] ) {
                if( p.first->second.first == p.first->second.second ) {
                    --diff;
                    cnt.erase(p.first);
                }
            }

            // cout << "i " << i << " diff " << diff << endl;

            if( diff == 0 ) {
                ++ans;
                cnt.clear();
            }

        }

        return ans;
    }
};
