
// 1840. Maximum Building Height
// https://leetcode.com/problems/maximum-building-height/


class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        int restric_sz = restrictions.size();
        if( restric_sz == 0 )
            return n-1;
        
        restrictions.push_back({1,0}); // height of the first building must be 0
        ++restric_sz;
        sort(restrictions.begin(),restrictions.end());
        if( restrictions.back()[0] < n ) {
            restrictions.push_back({n,1000000000});
            ++restric_sz;
        }
        
        // pass 1
        for(int i = 1; i < restric_sz; ++i) {
            int curr_idx = restrictions[i][0];
            int curr_mxh = restrictions[i][1];            
            int prev_idx = restrictions[i-1][0];
            int prev_mxh = restrictions[i-1][1];
            if( curr_mxh > prev_mxh ) {
                // do we need to adjust curr_mxh down?
                int distance    = curr_idx - prev_idx;
                int height_diff = curr_mxh - prev_mxh;

                if( height_diff > distance )
                    restrictions[i][1] = prev_mxh + distance;
            } 
        }
        
        int ans = 0;
        
        // pass 2
        for(int i = restric_sz-1; i > 0; --i) {
            int curr_idx = restrictions[i][0];
            int curr_mxh = restrictions[i][1];            
            int prev_idx = restrictions[i-1][0];
            int prev_mxh = restrictions[i-1][1];
            int distance = curr_idx - prev_idx;
            int abs_height_diff = abs(curr_mxh - prev_mxh);
            
            if( curr_mxh < prev_mxh ) {
                // do we need to adjust prev_mxh down?                
                if( abs_height_diff > distance ) {
                    // adjust prev_mxh down
                    restrictions[i-1][1] = prev_mxh = curr_mxh + distance;
                }
            }
            
            int t = distance - abs_height_diff;
            ans = max(ans, max(curr_mxh,prev_mxh) + t/2);
        }
        
        return ans;
    }
};




// passes 49/50 test cases, then TLE as of 11/7/2023


class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        int restric_sz = restrictions.size();
        if( restric_sz == 0 )
            return n-1;

        restrictions.push_back({1,0}); // height of the first building must be 0
        ++restric_sz;
        sort(restrictions.begin(),restrictions.end());
        if( restrictions.back()[0] < n ) {
            restrictions.push_back({n,1000000000});
            ++restric_sz;
        }

        // we will go through restrictions from left to right
        // we will look to our left and determine if:
        //    the current idx's restriction need to be adjusted down OR
        //    the prior idx's restriction need to be adjusted down
        //        (if the latter, we need to go backwards)
        for(int i = 1; i < restric_sz; ++i) {
            int curr_idx = restrictions[i][0];
            int curr_mxh = restrictions[i][1];
            int prev_idx = restrictions[i-1][0];
            int prev_mxh = restrictions[i-1][1];

            // curr_mxh == prev_mxh -> nothing to do

            if( curr_mxh < prev_mxh ) {
                // do we need to adjust prev_mxh down?
                int distance    = curr_idx - prev_idx;
                int height_diff = prev_mxh - curr_mxh;

                if( height_diff > distance ) {
                    // adjust prev_mxh down
                    restrictions[i-1][1] = curr_mxh + distance;
                    // we need to go backwards
                    for(int j = i-1; j-1 >= 0; --j) {
                        int cidx = restrictions[j][0];
                        int cmxh = restrictions[j][1];
                        int pidx = restrictions[j-1][0];
                        int pmxh = restrictions[j-1][1];
                        if( pmxh > cmxh ) {
                            int tmp_distance    = cidx - pidx;
                            int tmp_height_diff = pmxh - cmxh;
                            if( tmp_height_diff > tmp_distance )
                                restrictions[j-1][1] = cmxh + tmp_distance;
                            else
                                break;
                        } else {
                            break;
                        }
                    }
                }

            } else if( curr_mxh > prev_mxh ) {
                // do we need to adjust curr_mxh down?
                int distance    = curr_idx - prev_idx;
                int height_diff = curr_mxh - prev_mxh;

                if( height_diff > distance )
                    restrictions[i][1] = prev_mxh + distance;
            }
        }

        int ans = 0;

        // we know at restrictions we will be the current values
        // question becomes how far above that can go in between
        for(int i = 1; i < restric_sz; ++i) {
            int curr_idx = restrictions[i][0];
            int curr_mxh = restrictions[i][1];
            int prev_idx = restrictions[i-1][0];
            int prev_mxh = restrictions[i-1][1];
            int distance = curr_idx - prev_idx;
            int abs_height_diff = abs(curr_mxh - prev_mxh);

            int t = distance - abs_height_diff;
            ans = max(ans, max(curr_mxh,prev_mxh) + t/2);
        }

        return ans;
    }
};
