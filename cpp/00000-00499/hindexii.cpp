
// 275. H-Index II
// https://leetcode.com/problems/h-index-ii/




class Solution {
private:
    int n;

    // binary search
    int search(vector<int>& citations, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        int h = n-mid; // number elements to the right including mid
        if( citations[mid]  >= h ) {
            // can we do better?
            int t = search(citations,s,mid-1);
            return t != -1 ? t : mid;
        } else {
            return search(citations,mid+1,e);
        }
    }

public:
    int hIndex(vector<int>& citations) {
        n = citations.size(); // 1 <= n <= 10^5

        if( citations.size() == 1 )
            if( citations[0] > 0 )
                return 1;
            else
                return 0;

        int t = search(citations,0,n-1);
        return t == -1 ? 0 : n-search(citations,0,n-1);
    }
};
