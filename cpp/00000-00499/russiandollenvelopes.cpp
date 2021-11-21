
// 354. Russian Doll Envelopes
// https://leetcode.com/problems/russian-doll-envelopes/
// day 30 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/592/week-5-march-29th-march-31st/3690/

// inspired by https://medium.com/swlh/problems-with-advanced-ds-binary-search-and-the-russian-doll-5b64cb5ee67b


class Solution {
private:
    // binary search
    int search(int arr[], int s, int e, int k) {
        int pos = -1;
        while(s <= e) {
            int mid = (s + e) / 2;

            if( arr[mid] < k ) {
                pos = mid;
                s = mid+1;
            } else {
                e = mid-1;
            }
        }

        return pos;
    }
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if( n <= 1 ) return n;

        // envelopes[i] = [wi, hi] represents the width and the height of an envelope
        // sort on width
        sort(envelopes.begin(),envelopes.end(),[](vector<int>& a, vector<int>& b){
            if( a[0] != b[0] )
                return a[0] < b[0];
            else
                return a[1] > b[1];
        });

        int f[n]; memset(f,0,sizeof f);
        int num_envs[n+1];
        for(int i = 0; i <= n; ++i) num_envs[i] = INT_MAX;


        int min_m,max_m,j;
        for(int i = 0; i < n; ++i) {
            if( i == 0 ) {
                f[i] = 1;
                num_envs[1] = envelopes[0][1];
                min_m = 1;
                max_m = 1;
            } else {
                j = search(num_envs,min_m,max_m,envelopes[i][1]);
                if( j == -1) {
                    num_envs[1] = min(num_envs[1],envelopes[i][1]);
                    f[i] = 1;
                } else {
                    num_envs[j+1] = min(num_envs[j+1],envelopes[i][1]);
                    f[i] = j+1;
                    min_m = min(min_m,j+1);
                    max_m = max(max_m,j+1);
                }
            }
        }

        return *max_element(f,f+n);
    }
};
