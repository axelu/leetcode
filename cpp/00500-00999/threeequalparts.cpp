
// 927. Three Equal Parts
// https://leetcode.com/problems/three-equal-parts/
// day 17 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3817/





class Solution {
private:
    bool cmp(vector<int>& arr, int s1, int e1, int s2, int e2, int s3, int e3) {
        // cout << "cmp                          ";
        // cout << "s1 " << s1 << " e1 " << e1 << " s2 " << s2 << " e2 " << e2 << " s3 " << s3 << " e3 " << e3 << endl;
        // advance to 1st one
        for(; s1 < e1; ++s1)
            if( arr[s1] == 1 )
                break;
        for(; s2 < e2; ++s2)
            if( arr[s2] == 1 )
                break;
        for(; s3 < e3; ++s3)
            if( arr[s3] == 1 )
                break;

        // cout << "cmp after advance to 1st one ";
        // cout << "s1 " << s1 << " e1 " << e1 << " s2 " << s2 << " e2 " << e2 << " s3 " << s3 << " e3 " << e3 << endl;

        
        for(; s3 <= e3; ++s3) {
            if( arr[s1] != arr[s2] || arr[s1] != arr[s3] )
                return false;
            ++s1;
            ++s2;
        }
        
        return true;    
    }
    
    
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        // each part arr[0]...arr[i],arr[i+1]...arr[j-1],arr[j]...arr[j-1] needs same number of 1s
        // hence number of 1s has to be divisible by 3
        // trailing 0s are determined by the 1st one from the right
        
        int i;
        
        int n = arr.size(); // 3 <= arr.length <= 30000
        
        int ones = 0;
        int lst1 = -1; // index of last 1
        for(i = 0; i < n; ++i)
            if( arr[i] == 1 ) {
                ++ones;
                lst1 = i;
            }
        
        // if there are no ones, we can devide it anywhere
        if( ones == 0 )
            return {0,2};
        
        if( ones % 3 != 0 )
            return {-1,-1};
        
        // number of ones we need in each part
        int part = ones/3;
        
        // number of trailing zeros
        int tr0s = n-(lst1+1);

        int ans_i = -1, ans_j = -1;

        
        // part 1
        int t = 0;
        for(i = 0; i < n; ++i) {
            if( arr[i] == 1 )
                ++t;
            if( t == part )
                break;
        }
        t = 0;
        while( t < tr0s ) {
            ++i;
            ++t;
            if( arr[i] == 1 )
                return {-1,-1};
        }
        ans_i = i;
        
        // part 2
        t = 0;
        ++i;
        for(; i < n; ++i) {
            if( arr[i] == 1 )
                ++t;
            if( t == part )
                break;
        }
        t = 0;
        while( t < tr0s ) {
            ++i;
            ++t;
            if( arr[i] == 1 )
                return {-1,-1};
        }
        ans_j = i+1;

        
        if( cmp(arr,0,ans_i,ans_i+1,ans_j-1,ans_j,n-1) )
            return {ans_i,ans_j};
        else
            return {-1,-1};
    }
};
