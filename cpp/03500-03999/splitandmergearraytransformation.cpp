
// 3690. Split and Merge Array Transformation
// https://leetcode.com/problems/split-and-merge-array-transformation/



class Solution {
private:
    string vectorint2string(vector<int>& nums) {
        string s = "";
        // 0 <= nums[i] <= 5
        // 2 <= nums.size() <= 6
        for(int i = 0; i < nums.size(); ++i)
            s.push_back(nums[i]+'0');
        return s;
    }

public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        // 2 <= n == nums1.length == nums2.length <= 6
        // -1e5 <= nums1[i], nums2[i] <= 1e5
        // nums2 is a permutation of nums1

        if( nums1 == nums2 )
            return 0;

        int n = nums1.size();

        // we have at most 6 distinct values, so lets 'compress'
        set<int> st;     // uniques
        for(int x: nums1)
            st.insert(x);
        map<int,int> mp; // key: value in nums; value: index
        int idx = 0;
        for(int x: st) {
            mp.insert({x,idx});
            ++idx;
        }
        for(int i = 0; i < n; ++i)
            nums1[i] = mp[nums1[i]];
        for(int i = 0; i < n; ++i)
            nums2[i] = mp[nums2[i]];

        string s1 = vectorint2string(nums1); // cout << "s1 " << s1 << endl;
        string s2 = vectorint2string(nums2); // cout << "s2 " << s2 << endl;

        queue<string> q;
        q.push(s1);
        bool seen[543211];memset(seen,false,sizeof seen);
        seen[stoi(s1)] = true;
        int steps = 1;
        while( !q.empty() ) {
            // process all in queue

            queue<string> q_new;
            while( !q.empty() ) {
                string s = q.front();
                q.pop();

                // cout << "s " << s << endl;

                // 'permute'
                for(int l = 1; l < n; ++l) {
                    string m = "";
                    int i = 0; // left index
                    for(int j = 0; j < n; ++j) {
                        m.push_back(s[j]);
                        // cout  << "  l " << l << " i " << i << " j " << j << " m " << m << endl;
                        if( j-i+1 == l ) {
                            // s = l + m + r
                            string l = "";
                            if( i > 0 )
                                l = s.substr(0,i);
                            string r = "";
                            if( j < n-1 )
                                r = s.substr(j+1);
                            string s_new;
                            for(int k = 0; k < l.size() + r.size(); ++k) {
                                if( k == i )
                                    continue;
                                s_new = l + r;
                                s_new.insert(k, m);
                                // cout << "  s_new " << s_new << endl;
                                if( s_new == s2 )
                                    return steps;
                                if( !seen[stoi(s_new)] ) {
                                    seen[stoi(s_new)] = true;
                                    q_new.push(s_new);
                                }
                            }
                            if( j < n-1 ) {
                                // append
                                s_new = l + r + m;
                                // cout << "  s_new " << s_new << endl;
                                if( s_new == s2 )
                                    return steps;
                                if( !seen[stoi(s_new)] ) {
                                    seen[stoi(s_new)] = true;
                                    q_new.push(s_new);
                                }
                            }
                            m.erase(m.begin());
                            ++i;
                        }
                    }
                }
            }
            swap(q, q_new);
            ++steps;
        }

        return -1;
    }
};
