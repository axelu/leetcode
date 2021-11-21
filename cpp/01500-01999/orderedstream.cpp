
// 1656. Design an Ordered Stream
// https://leetcode.com/problems/design-an-ordered-stream/


class OrderedStream {
private:
    vector<string> v;
    vector<bool> b;
    int N,idx;
public:
    OrderedStream(int n) {
        v = vector<string>(n+1);
        b = vector<bool>(n+1,false);
        N = n;
        idx = 1;
    }

    vector<string> insert(int id, string value) {
        v[id] = value;
        b[id] = true;
        if(id != idx) return {};

        vector<string> r;
        int i = id;
        for(; i <= N; ++i) {
            if(!b[i]) break;
            r.push_back(v[i]);
        }
        idx = i;
        return r;
    }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(id,value);
 */
