
// 981. Time Based Key-Value Store
// https://leetcode.com/problems/time-based-key-value-store/




class TimeMap {
private:
    unordered_map<string,vector<pair<int,string>>> um;

    // binary search
    // largest element less or equal element
    string search(vector<pair<int,string>>& v, int s, int e, int target) {
        if( s > e ) return "";

        int mid = s + ((e - s)/2);
        if( v[mid].first == target ) {
            return v[mid].second;
        } else if( v[mid].first > target ) {
            return search(v,s,mid-1,target);
        } else {
            // can we do better?
            string ans = search(v,mid+1,e,target);
            return !ans.empty() ? ans : v[mid].second;
        }
    }

public:
    /** Initialize your data structure here. */
    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        // timestamps for all TimeMap.set operations are strictly increasing
        pair<unordered_map<string,vector<pair<int,string>>>::iterator,bool> p;
        p = um.insert({key,{{timestamp,value}}});
        if( !p.second )
            p.first->second.push_back({timestamp,value});
    }

    string get(string key, int timestamp) {
        unordered_map<string,vector<pair<int,string>>>::iterator f;
        f = um.find(key);
        if( f != um.end() ) {
            return search(f->second,0,f->second.size()-1,timestamp);
        }
        return "";
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
