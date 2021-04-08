
// 352. Data Stream as Disjoint Intervals
// https://leetcode.com/problems/data-stream-as-disjoint-intervals/

/*
    Thought off ideal implementation
    - Red-Black BST based Interval Tree that supports insertion and deletion
    - short of that:
        - create an undirected graph using vector<pair<int,vector<int>>>
        - here comes a new number val, add val for fast lookup to an unordered_set<int>
          if val already in set -> ignore the number
          if not, try with val-1 unless val == 0
            if result, add val to graph with an outgoing edge to val-1, update node val-1 with an outgoing edge to val
            if not, try with val+1 unless val == INT_MAX
            if result, add val to graph with an outgoing edge to val+1, update node val+1 with an outgoing edge to val
            if not, add val to graph with no outging edge
        - produce intervals using dfs to find connected components like
            https://cp-algorithms.com/graph/search-for-connected-components.html
            start a component with just the val of that node, then invoke dfs and update
               'component' if greater or higher value found
        - follow up: how to deal with lots of merges and a large number stream?
             when we add a node to a component, we delete the intermediate node immediately
             now our search if a new number is already covered becomes tricky -> answer: Interval Tree
    - another approach:
        use a map<int,int> with key the endpoint and value the start point, use lower_bound to find and extend
            maybe supplement with a map with map<int,int> with key the start point and value the endpoint
            TODO in below implementation: maintain output vector when we make changes
*/
class SummaryRanges {
private:
    map<int,int> endpoints;
public:
    /** Initialize your data structure here. */
    SummaryRanges() {

    }

    void addNum(int val) {
        map<int,int>::iterator it1,it2;

        it1 = endpoints.lower_bound(val);

        /*
        cout << val << " ";
        if( it1 != endpoints.end() ) cout << it1->first << " " << it1->second;
        else cout << "not found";
        cout << endl;
        */

        if( it1 == endpoints.end() ) {
            // try val-1
            it2 = it1;
            if( val != 0 ) it2 = endpoints.lower_bound(val-1);
            // it may find the same, but if not ...
            if( it2 != it1 ) {
                int t = it2->second;
                endpoints.erase(it2);
                endpoints.insert({val,t});
            } else {
                endpoints.insert({val,val});
            }

        } else if( it1->first != val ) {
            // it1 pointing to a value greater than val

            bool add = true;

            // check start
            if( it1->second <= val) {
                // ignore
                add = false;
            } else if( val != INT_MAX && val + 1 == it1->second ) {
                // we can extend the start point to val
                it1->second = val;
                add = false;
            }

            // try val-1
            it2 = it1;
            if( val != 0 ) it2 = endpoints.lower_bound(val-1);
            // it may find the same, but if not ...
            if( it2 != it1 ) {
                if( it1->second == val ) {
                    // merge
                    it1->second = it2->second;
                    endpoints.erase(it2);
                } else {
                    int t = it2->second;
                    endpoints.erase(it2);
                    endpoints.insert({val,t});
                    add = false;
                }
            }

            if( add ) endpoints.insert({val,val});
        }
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> r(endpoints.size());

        int i = 0;
        for(pair<int,int> p : endpoints) {
            r[i] = {p.second,p.first};
            ++i;
        }

        return r;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
