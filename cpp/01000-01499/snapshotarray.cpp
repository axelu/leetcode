
// 1146. Snapshot Array
// https://leetcode.com/problems/snapshot-array/





class SnapshotArray {
private:
    int n,id;
    int * v;
    vector<array<int,2>> * snap_v;
    unordered_map<int,int> changes;

    // binary search largest element less or equal
    int search(int s, int e, int index, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( snap_v[index][mid][0] == target ) {
            return mid;
        } else if( snap_v[index][mid][0] > target ) {
            return search(s,mid-1,index,target);
        } else {
            // can we do better?
            int ans = search(mid+1,e,index,target);
            return ans != -1 ? ans : mid;
        }
    }

public:
    SnapshotArray(int length) {
        n = length;
        v = new int[n];
        for(int i = 0; i < n; ++i)
            v[i] = 0;

        id = 0;
        snap_v = new vector<array<int,2>>[n];
    }

    void set(int index, int val) {
        changes[index] = val;
    }

    int snap() {
        for(auto it = begin(changes); it != end(changes); ++it)
            snap_v[it->first].push_back({id,it->second});
        changes.clear();
        return id++;
    }

    int get(int index, int snap_id) {
        int t = search(0,snap_v[index].size()-1,index,snap_id);
        return t == -1 ? 0 : snap_v[index][t][1];
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */
