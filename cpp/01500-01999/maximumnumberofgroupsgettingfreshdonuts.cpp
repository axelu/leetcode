
// 1815. Maximum Number of Groups Getting Fresh Donuts
// https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/


class Solution {
private:
    unordered_map<long long,int> mem;
    long long hash_done;
    
    long long hash(vector<int>& v, int batchSize) {
        // 1 <= groups.length <= 30
        // so there could be 30 groups with the same remainder
        // theoritical max 2.91683E+17, which is less than MAX_LLONG
        long long h = 0;
        for(int i = 1; i < batchSize; ++i)
            h = h * 31 + v[i];

        return h;
    }
    
    // int rec(int cnt[], int batchSize, int rem) {
    int rec(vector<int>& cnt, int batchSize, int rem) {
        long long h = hash(cnt,batchSize);

        // no more group left, we cannot make another group happy
        if( h == hash_done )
           return 0;
        
        h = h * 31 + rem; // account for the previous remainder in our hash
        auto f = mem.find(h);
        if( f != mem.end() )
           return f->second;
        
        int a = 0;
        for(int i = 1; i < batchSize; ++i) {
            if( cnt[i] > 0 ) {
                --cnt[i];        
                
                // the group we are combining this group with will be happy, 
                // if the combined remainder becomes 0
                // example
                // batchsize = 4
                // size of previouse group 1 -> previous remainder 3
                // if we combine the group of size 1 with a group of size 3
                // the next group can be happy
                
                int rem_new = (rem + i) % batchSize;
                int b = rec(cnt,batchSize,rem_new);
                a = max(a,(rem == 0 ) + b);
                
                // backtrack                
                ++cnt[i];
            }
        }
        
        mem.insert({h,a});
        return a;
    }
    
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        // 1 <= batchSize <= 9
        // 1 <= groups.length <= 30
        
        if( batchSize == 1 ) // at batchsize == 1 all groups will be happy
            return groups.size();
        
        // all groups with a size that is a multiple of batchsize will be happy
        // more formally: groups with size_of_group % batchsize == 0 will be happy
        // lets group the groups by the size of the remainder
        // 0 <= remainder < batchsize
        vector<int> cnt(batchSize,0);
        // before we count the groups with a given remainder, 
        // lets precompute the hash when all groups rem > 0 are served
        hash_done = hash(cnt,batchSize);
        
        for(int size_of_group : groups )
            ++cnt[size_of_group % batchSize];
        
        return cnt[0] + rec(cnt,batchSize,0);
    }
};
