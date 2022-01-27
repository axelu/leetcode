
// 2080. Range Frequency Queries
// https://leetcode.com/problems/range-frequency-queries/




class RangeFreqQuery {
private:
    unordered_map<int,vector<int>> um; // value,index

    // binary search equal or greater aka lower bound
    int searchL(vector<int>& arr, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( arr[mid] == target ) {
            return mid;
        } else if( arr[mid] > target) {
            // can we do better?
            int t = searchL(arr,s,mid-1,target);
            return t != -1 ? t : mid;
        } else {
            // arr[mid] < target
            return searchL(arr,mid+1,e,target);
        }
    }

    // binary search less or equal
    int searchR(vector<int>& arr, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( arr[mid] == target ) {
            return mid;
        } else if( arr[mid] < target) {
            // can we do better?
            int t = searchR(arr,mid+1,e,target);
            return t != -1 ? t : mid;
        } else {
            // arr[mid] > target
            return searchR(arr,s,mid-1,target);
        }
    }

public:
    RangeFreqQuery(vector<int>& arr) {
        for(int i = 0; i < arr.size(); ++i) {
            auto p = um.insert({arr[i],{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }
    }

    int query(int left, int right, int value) {
        auto f = um.find(value);
        if( f == um.end() )
            return 0;

        int s = searchL(f->second,0,f->second.size()-1,left);
        if( s == -1 || f->second[s] > right )
            return 0;

        int e = searchR(f->second,0,f->second.size()-1,right);
        if( e == -1 || f->second[e] < left )
            return 0;

        return e-s+1;
    }
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
