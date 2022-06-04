
// 911. Online Election
// https://leetcode.com/problems/online-election/



class TopVotedCandidate {
private:
    int n;
    vector<int> leader;
    vector<int>* _times;

public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        n = persons.size(); // times.length == persons.length

        // doubly-linked list
        struct ListNode {
            int id;
            int votes;
            ListNode *prev;
            ListNode *next;
            ListNode(int x) : id(x), votes(0), prev(nullptr), next(nullptr) {}
        };

        ListNode* candidate[n];
        ListNode* node;
        ListNode* prev = nullptr;
        for(int i = 0; i < n; ++i) {
            node = new ListNode(i);
            candidate[i] = node;
            node->prev = prev;
            if( prev != nullptr )
                prev->next = node;
            prev = node;
        }

        leader.resize(n);
        ListNode* head = candidate[0];
        for(int i = 0; i < n; ++i) {
            // cast the vote at times[i]
            node = candidate[persons[i]];
            ++node->votes;

            if( node->prev != nullptr ) { // reorder
                ListNode* t = node;
                while( t->prev != nullptr && t->prev->votes <= node->votes) {
                    t = t->prev;
                }
                if( t != node ) {
                    // remove our node from the its current position and
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                    // insert our node before t
                    node->prev = t->prev;
                    if( t->prev != nullptr ) {
                        t->prev->next = node;
                    } else {
                        // t was the head and our node becomes the new head
                        head = node;
                    }
                    node->next = t;
                    t->prev = node;
                }
            }
            // populate leader board
            leader[i] = head->id;
        }

        _times = &times;
    }

    int q(int t) {
        // find the index
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( (*_times)[mid] >= t )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && (*_times)[s] > t) || s == n )
            --s;

        // t >= times[0], hence not needed
        // if( s == -1 )
        //    return 0;

        return leader[s];
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */
