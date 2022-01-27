
// 718. Maximum Length of Repeated Subarray
// https://leetcode.com/problems/maximum-length-of-repeated-subarray/
// day 8 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3807/




class Solution {
private:
    unordered_map<int,vector<int>> ind(vector<int>* pNums, int n) {
        unordered_map<int,vector<int>> um;
        pair<unordered_map<int,vector<int>>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = um.insert({(*pNums)[i],{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }
        return um;
    }

    int mem[1000][1000];

    int rec(vector<int>* A, int na, int i, vector<int>* B, int nb, int j) {
        if( i >= na || j >= nb )
            return 0;

        if( mem[i][j] != -1 )
            return mem[i][j];

        int ret = 0;
        if( (*A)[i] == (*B)[j] )
            ret = 1 + rec(A,na,i+1,B,nb,j+1);

        return mem[i][j] = ret;
    }

public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {

        // we will use the shorter one as the driver
        int n1,n2;
        vector<int>* pNums1; // will point to shorter nums
        vector<int>* pNums2;
        if( nums1.size() < nums2.size() ) {
            pNums1 = &nums1; n1 = nums1.size();
            pNums2 = &nums2; n2 = nums2.size();
        } else {
            pNums1 = &nums2; n1 = nums2.size();
            pNums2 = &nums1; n2 = nums1.size();
        }

        // index positions of unique values in pNums2
        unordered_map<int,vector<int>> um = ind(pNums2,n2);


        //int mem[n1][n2];
        for(int i = 0; i < n1; ++i)
            for(int j = 0; j < n2; ++j)
                mem[i][j] = -1;

        int ans = 0;

        int j,k;
        unordered_map<int,vector<int>>::iterator e = um.end();
        unordered_map<int,vector<int>>::iterator f;
        for(int i = 0; i < n1; ++i) {
            // cout << "i " << i << endl;
            f = um.find((*pNums1)[i]);
            if( f != e ) {
               for(k = 0; k < f->second.size(); ++k) {
                   j = f->second[k];
                   // cout << "j " << j << endl;

                   ans = max(ans,rec(pNums1,n1,i,pNums2,n2,j));
                   if( ans == n1 )
                       break;
               }
            }
        }


        return ans;
    }
};
