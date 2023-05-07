
// 2424. Longest Uploaded Prefix
// https://leetcode.com/problems/longest-uploaded-prefix/




class LUPrefix {
private:
    vector<int> bit; // binary indexed tree bit, 0 indexed
    int n;

    int sum(int r) {
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(int idx, int delta) {
        for(; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    int search(int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        if( sum(mid) == mid ) {
            // can we do better?
            int t = search(mid+1,e);
            return t != -1 ? t : mid;
        }

        return search(s,mid-1);
    }

public:
    LUPrefix(int n) {
        this->n = n+1;
        bit.assign(this->n,0);
    }

    void upload(int video) {
        add(video,1);
    }

    int longest() {
        // binary search
        // get the rightmost idx in bit
        // where sum(idx) == idx
        return search(0,n-1);
    }
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
