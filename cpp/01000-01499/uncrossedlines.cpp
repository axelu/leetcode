
// 1035. Uncrossed Lines
// https://leetcode.com/problems/uncrossed-lines/




class Solution {
private:
    int n1,n2;

    // binary search equal or greater aka lower bound
    int search(vector<int>& arr, int s, int e, int x) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( arr[mid] >= x ) {
            // can we do better?
            int t = search(arr,s,mid-1,x);
            return t != -1 ? t : mid;
        } else {
            return search(arr,mid+1,e,x);
        }
    }


    int rec(vector<int>& nums1, map<int,vector<int>>& m, int u, int v, int mem[]) {
        // cout << "rec u " << u << " v " << v << endl;
        if( u == n1 || v == n2 )
            return 0;

        int memIdx = u*n2+v;
        if( mem[memIdx] != -1 )
            return mem[memIdx];

        // we have a choice
        // skip connecting nums1[u] to anything in nums2
        // OR
        // connect nums1[u] with the 1st available nums2[j] where nums1[u] == nums2[j]
        //     and v <= j < n2

        // skip
        // cout << "  skip    u " << u << " v " << v << " " << u+1 << " " << v << endl;
        int a = rec(nums1,m,u+1,v,mem);

        // connect
        // cout << "  connect u " << u << " v " << v << endl;
        int b = 0;
        auto f = m.find(nums1[u]);
        if( f != m.end() ) {
            int v_new = search(f->second,0,f->second.size()-1,v);
            if( v_new != -1 ) {
                // cout << "  connect u " << u << " v " << v << " " << u+1 << " " << f->second[v_new]+1 << endl;
                b = 1 + rec(nums1,m,u+1,f->second[v_new]+1,mem);
            }
        }

        return mem[memIdx] = max(a,b);
    }

public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        n1 = nums1.size();
        n2 = nums2.size();

        map<int,vector<int>> m;
        pair<map<int,vector<int>>::iterator,bool> p;
        for(int i = 0; i < n2; ++i) {
            p = m.insert({nums2[i],{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }



        int mem[n1*n2];memset(mem,-1,sizeof mem);
        return rec(nums1,m,0,0,mem);

    }
};
