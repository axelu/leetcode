
// 2444. Count Subarrays With Fixed Bounds
// https://leetcode.com/problems/count-subarrays-with-fixed-bounds/




class Solution {
private:
    long long solve(vector<int>& nums, int minK, int maxK, int s, int e) {
        // a subarray [s,e] exists that has at least one minK, one maxK

        // edge case
        if( minK == maxK ) {
            long long n = e - s + 1;
            return n * (n+1)/2;
        }

        long long ret = 0;

        // find every immediate pair minK,maxK
        vector<pair<int,int>> v; // minK idx, maxK idx
        for(int i = s; i <= e; ++i) {
            if( nums[i] == minK ) {
                if( v.empty() ) {
                    v.push_back({i,-1});
                } else {
                    // last pair incomplete
                    //    last pair has no minimum yet => add our min
                    //    last pair has minimum => replace with our min
                    // last pair is complete
                    //    last pair max is closer => new pair our min, last pair max
                    //    last pair min is closer => new pair our min, -1

                    if( v.back().first == -1 && v.back().second != -1 ) {
                        v.back().first = i;
                    } else if( v.back().first != -1 && v.back().second == -1 ) {
                        v.back().first = i;
                    } else {
                        if( v.back().second > v.back().first ) {
                            v.push_back({i,v.back().second});
                        } else {
                            v.push_back({i,-1});
                        }
                    }
                }
            } else if( nums[i] == maxK ) {
                if( v.empty() ) {
                    v.push_back({-1,i});
                } else {

                    // last pair incomplete
                    //    last pair has no maximum yet => add our max
                    //    last pair has maximum => replace with our max
                    // last pair is complete
                    //    last pair min is closer => new pair last pair min, our max
                    //    last pair max is closer => new pair our -1, our max

                    if( v.back().first != -1 && v.back().second == -1 ) {
                        v.back().second = i;
                    } else if( v.back().first == -1 && v.back().second != -1 ) {
                        v.back().second = i;
                    } else {
                        if( v.back().first > v.back().second ) {
                            v.push_back({v.back().first,i});
                        } else {
                            v.push_back({-1,i});
                        }
                    }
                }
            }
        }
        if( v.back().first == -1 || v.back().second == -1 )
            v.pop_back();

        /*
        for(int i = 0; i < v.size(); ++i) {
            cout << v[i].first << ":" << v[i].second << " ";
        }
        cout << endl;
        */


        // determine number of subarrays that pivot around our min,max pairs
        // without doublecounting

        int pre_min, pre_max;
        for(int i = 0; i < v.size(); ++i) {
            long long l = v[i].first < v[i].second ? v[i].first : v[i].second;
            long long r = v[i].first > v[i].second ? v[i].first : v[i].second;
            if( i == 0 ) {
                ret += (l - s + 1) * (e - r + 1);

            } else {
                // as we are processing from left to right,
                // we can expand to the right and will not double count
                // but to the left, we have to determine when to stop

                // if current left is maxK, then go to prior min + 1
                // if current left is minK, then go to prior max + 1

                if( nums[l] == maxK ) {
                    ret += (l - (v[i-1].first + 1) + 1) * (e - r + 1);
                } else {
                    ret += (l - (v[i-1].second + 1) + 1) * (e - r + 1);
                }
            }
        }

        return ret;
    }

public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int n = nums.size();

        long long ans = 0;

        // determine subarray that has only values between minK and maxK inclusive
        // meaning it has minK and maxK but no elements < minK and no element > maxK

        bool has_min_k = false;
        bool has_max_k = false;
        int i = 0;
        for(int j = 0; j < n; ++j) {
            if( nums[j] == minK )
                has_min_k = true;
            if( nums[j] == maxK )
                has_max_k = true;

            if( nums[j] < minK || nums[j] > maxK ) {
                if( has_min_k && has_max_k ) {
                    // cout << "found subarray " << i << " " << j-1 << endl;
                    ans += solve(nums,minK,maxK,i,j-1);
                }
                has_min_k = false;
                has_max_k = false;
                i = j+1;
            }
        }
        // finish up
        if( has_min_k && has_max_k ) {
            // cout << "found subarray " << i << " " << n-1 << endl;
            ans += solve(nums,minK,maxK,i,n-1);
        }

        return ans;
    }
};
