
// 1756. Design Most Recently Used Queue
// https://leetcode.com/problems/design-most-recently-used-queue/



class MRUQueue {
private:
    vector<int> v;
    int N;
public:
    MRUQueue(int n) {
        v = vector<int>(n);
        int i;
        generate(v.begin(),v.end(),[i = 1]() mutable { return i++; });
        N = n;
    }

    int fetch(int k) {
        if( k == N ) return v.back();
        vector<int>::iterator it = v.begin();
        for(int i = 1; i < k; ++i) ++it;
        int ans = *it;
        v.erase(it);
        v.push_back(ans);
        return ans;
    }
};

/**
 * Your MRUQueue object will be instantiated and called as such:
 * MRUQueue* obj = new MRUQueue(n);
 * int param_1 = obj->fetch(k);
 */
