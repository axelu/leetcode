
// 3508. Implement Router
// https://leetcode.com/problems/implement-router/

class Router {
private:
    int memoryLimit;
    queue<vector<int>> q;

    // source->destination->timestamp
    unordered_map<int,unordered_map<int,set<int>>> rt;

    unordered_map<int,vector<int>> destinations;

    vector<int> remove_oldest_packet() {
        int source = q.front()[0];
        int destination = q.front()[1];
        int timestamp = q.front()[2];
        q.pop();
        
        // maintain router
        auto it_src = rt.find(source);
        auto it_dest = it_src->second.find(destination);
        it_dest->second.erase(timestamp);
        if( it_dest->second.empty() )
            it_src->second.erase(it_dest);
        if( it_src->second.empty() )
            rt.erase(it_src);

        // maintain destinations
        auto it_dests = destinations.find(destination);
        auto it_timestamps = find(it_dests->second.begin(), it_dests->second.end(), timestamp);
        it_dests->second.erase(it_timestamps);
        if( it_dests->second.empty() )
            destinations.erase(it_dests);

        return {source, destination, timestamp};
    }

public:
    Router(int memoryLimit) {
        this->memoryLimit = memoryLimit;
        
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        // is is guaranteed that 
        // addPacket be called in increasing order of timestamp

        // attempt to add new packet to router
        // if duplicate based on source, destination and timestamp
        // return false
        bool is_duplicate = false;

        set<int> timestamps{timestamp};
        unordered_map<int,set<int>> dests{{destination,timestamps}};
        auto p_src = rt.insert({source,dests});
        if(  !p_src.second ) {
            auto p_dest = p_src.first->second.insert({destination,{timestamp}});
            if( !p_dest.second ) {
                auto p_timestamp = p_dest.first->second.insert(timestamp);
                if( !p_timestamp.second )
                    is_duplicate = true;
            }
        }
        if( is_duplicate )
            return false;

        // if queue at capacity, the remove oldest packet
        if( q.size() == memoryLimit )
            remove_oldest_packet();

        // add new packet to queue
        q.push({source, destination, timestamp});
        
        // add timestamp to destinations
        auto p_dests = destinations.insert({destination,{timestamp}});
        if( !p_dests.second ) {
            auto it_timestamps = upper_bound(p_dests.first->second.begin(), p_dests.first->second.end(), timestamp);
            if( it_timestamps == p_dests.first->second.end() )
                p_dests.first->second.push_back(timestamp);
            else
                p_dests.first->second.insert(it_timestamps, timestamp);
        }

        return true;
    }
    
    vector<int> forwardPacket() {
        // if queue is empty, return empty array
        if( q.empty() )
            return {};

        return remove_oldest_packet();
    }
    
    int getCount(int destination, int startTime, int endTime) {
        auto it_dests = destinations.find(destination);
        if( it_dests == destinations.end() )
            return 0;

        int n = it_dests->second.size();

        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        int target = startTime;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= it_dests->second[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && it_dests->second[s] < target )
            ++s;

        int start_idx = s;
        if( s == n || it_dests->second[s] > endTime )
            return 0;


        // binary search upper bound while loop
        // upper bound -> greater than target
        s = 0;
        e = n; // n = nums.size()
        // int mid;
        target = endTime;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= it_dests->second[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && it_dests->second[s] <= target )
            ++s;

        int end_idx = s;

        int cnt = end_idx - start_idx;
        
        return cnt;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */

// passes 742/746 test cases, then TLE as of 4/7/2025
// what is slow is distance calc in multiset
// in passing solution replaced with binary search on a vector that we keep sorted

class Router {
private:
    int memoryLimit;
    queue<vector<int>> q;

    // source->destination->timestamp
    unordered_map<int,unordered_map<int,set<int>>> rt;

    unordered_map<int,multiset<int>> destinations;

    vector<int> remove_oldest_packet() {
        int source = q.front()[0];
        int destination = q.front()[1];
        int timestamp = q.front()[2];
        q.pop();

        // maintain router
        auto it_src = rt.find(source);
        auto it_dest = it_src->second.find(destination);
        it_dest->second.erase(timestamp);
        if( it_dest->second.empty() )
            it_src->second.erase(it_dest);
        if( it_src->second.empty() )
            rt.erase(it_src);

        // maintain destinations
        auto it_dests = destinations.find(destination);
        auto it_timestamps = it_dests->second.find(timestamp);
        it_dests->second.erase(it_timestamps);
        if( it_dests->second.empty() )
            destinations.erase(it_dests);

        return {source, destination, timestamp};
    }

public:
    Router(int memoryLimit) {
        this->memoryLimit = memoryLimit;

    }

    bool addPacket(int source, int destination, int timestamp) {
        // is is guaranteed that
        // addPacket be called in increasing order of timestamp

        // attempt to add new packet to router
        // if duplicate based on source, destination and timestamp
        // return false
        bool is_duplicate = false;

        set<int> timestamps{timestamp};
        unordered_map<int,set<int>> dests{{destination,timestamps}};
        auto p_src = rt.insert({source,dests});
        if(  !p_src.second ) {
            auto p_dest = p_src.first->second.insert({destination,{timestamp}});
            if( !p_dest.second ) {
                auto p_timestamp = p_dest.first->second.insert(timestamp);
                if( !p_timestamp.second )
                    is_duplicate = true;
            }
        }
        if( is_duplicate )
            return false;

        // if queue at capacity, the remove oldest packet
        if( q.size() == memoryLimit )
            remove_oldest_packet();

        // add new packet to queue
        q.push({source, destination, timestamp});
        // add timestamp to destinations
        auto p_dests = destinations.insert({destination,{timestamp}});
        if( !p_dests.second )
            p_dests.first->second.insert(timestamp);

        return true;
    }

    vector<int> forwardPacket() {
        // if queue is empty, return empty array
        if( q.empty() )
            return {};

        return remove_oldest_packet();
    }

    int getCount(int destination, int startTime, int endTime) {
        auto it_dests = destinations.find(destination);
        if( it_dests == destinations.end() )
            return 0;

        auto it_start = it_dests->second.lower_bound(startTime);
        if( it_start == it_dests->second.end() || *it_start > endTime )
            return 0;

        auto it_end = it_dests->second.upper_bound(endTime);
        int cnt = distance(it_start, it_end);

        return cnt;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */
