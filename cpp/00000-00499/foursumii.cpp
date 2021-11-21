
// 454. 4Sum II
// https://leetcode.com/problems/4sum-ii/
// day 17 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/571/week-3-december-15th-december-21st/3569/




class Solution {
private:
    unordered_map<int,int> vtom(vector<int>& v) {
        unordered_map<int,int> um;
        for(int i : v) {
            auto p = um.insert({i,1});
            if( !p.second ) ++p.first->second;
        }
        return um;
    }

    unordered_map<int,int> mtom(unordered_map<int,int> A, unordered_map<int,int> B) {
        unordered_map<int,int> um;
        for(auto ita = A.begin(); ita != A.end(); ++ita) {
            for(auto itb = B.begin(); itb != B.end(); ++itb) {
                int f = ita->second * itb->second;
                auto p = um.insert({ita->first + itb->first,f});
                if( !p.second ) p.first->second += f;
            }
        }
        return um;
    }

public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        // constraints: A, B, C, D have same length of N where 0 ≤ N ≤ 500

        unordered_map<int,int> umab = mtom(vtom(A),vtom(B));
        unordered_map<int,int> umcd = mtom(vtom(C),vtom(D));

        int ans = 0;
        for(auto it = umab.begin(); it != umab.end(); ++it) {
            auto f = umcd.find(-it->first);
            if( f != umcd.end() )
                ans += f->second * it->second;
        }

        return ans;
    }
};
