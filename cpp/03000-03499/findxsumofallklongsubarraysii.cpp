
// 3321. Find X-Sum of All K-Long Subarrays II
// https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/






class Solution {
private:
    struct ListNode{
        long long val;
        long long freq;
        int list; // 0 no list, 1 left list, 2 right list
        ListNode* prev;
        ListNode* next;
        ListNode(int val) : val(val), freq(1), list(0), prev(nullptr), next(nullptr) {};
    };

    ListNode* tail_left;
    ListNode* head_left;
    ListNode* tail_right;
    ListNode* head_right;

    long long sum_right;
    int length_right;

    unordered_map<int,ListNode*> byVal;
    map<int,set<int>> byFreq;

    void remove_node_from_list(ListNode* listNode) {
        // the list node maybe the front of the node list OR
        // the list node maybe the back of the node list OR
        // the list node maybe somewhere in the middle of the node list OR
        // the list node maybe the front AND the back of the node list
        // in the last case, we will delete the list node AND the frequency node

        ListNode* prev = listNode->prev;
        ListNode* next = listNode->next;
        if( prev == nullptr && next != nullptr ) {
            // our node is the tail
            next->prev = nullptr;
            if( listNode->list == 1 )
                tail_left = next;
            else
                tail_right = next;
        } else if( prev != nullptr && next == nullptr ) {
            // our node is the head
            prev->next = nullptr;
            if( listNode->list == 1 )
                head_left = prev;
            else
                head_right = prev;
        } else if( prev != nullptr && next != nullptr ) {
            // node is somewhere in the middle
            prev->next = next;
            next->prev = prev;
        } else {
            // prev == nullptr && next == nullptr
            // our node is head and tail
            if( listNode->list == 1 ) {
                tail_left = nullptr;
                head_left = nullptr;
            } else {
                tail_right = nullptr;
                head_right = nullptr;
            }
        }

        // housekeeping
        if( listNode->list == 2 ) {
            sum_right -= listNode->freq * listNode->val;
            --length_right;
        }
        listNode->list = 0;
        listNode->prev = nullptr;
        listNode->next = nullptr;
    }

    void insert_node_to_list(ListNode* prev, ListNode* listNode, ListNode* next) {
        // prev == nullptr && next == nullptr : we are starting a list, look at listNode->list to determine which list

        if( prev == nullptr && next == nullptr ) {
            if( listNode->list == 1 ) {
                tail_left = listNode;
                head_left = listNode;
            } else {
                tail_right = listNode;
                head_right = listNode;
            }
        } else if( prev == nullptr ) {
            // our node becomes the new tail
            next->prev = listNode;
            listNode->next = next;
            if( listNode->list == 1 )
                tail_left = listNode;
            else
                tail_right = listNode;
        } else if( next == nullptr ) {
            // our node becomes the new head
            prev->next = listNode;
            listNode->prev = prev;
            if( listNode->list == 1 )
                head_left = listNode;
            else
                head_right = listNode;
        } else {
            // somewhere in the middle
            prev->next = listNode;
            listNode->prev = prev;
            next->prev = listNode;
            listNode->next = next;
        }

        // housekeeping
        if( listNode->list == 2 ) {
            ++length_right;
            sum_right += listNode->freq * listNode->val;
        }

        return;
    }

    void maintain(int val, int x, int op) {
        // cout << "maintain val " << val << " op " << op << endl;
        // op == 1 add, op == 0 remove

        ListNode* listNode;
        auto fval = byVal.find(val);
        if( fval == byVal.end() ) {
            // cout << "creating new node" << endl;
            listNode = new ListNode(val);
            byVal.insert({val,listNode});
            byFreq[1].insert(val);
        } else {
            listNode = fval->second;
            // our node is either part of the left list or the right list
            remove_node_from_list(listNode);
            // the frequency of our node increases or decreases by one
            byFreq[listNode->freq].erase(val);
            if( byFreq[listNode->freq].empty() )
                byFreq.erase(listNode->freq);
            if( op )
                ++listNode->freq;
            else
                --listNode->freq;
            if( listNode->freq )
                byFreq[listNode->freq].insert(val);
            else
                byVal.erase(val);
        }

        if( op || listNode->freq ) {

            // we need to determine where our [new] node with value val and frequency goes:
            // left list or right list
            int freq = listNode->freq;
            auto f = byFreq[freq].find(val);

            // node left of us
            // byFreq, then in the value's list, the prior value
            //    if we are the 1st value, then last value of prior frequency if any
            //    if none, then we are the tail of the left list
            int prevval = -1;
            if( f == byFreq[freq].begin() ) {
                auto it_byFreq = byFreq.find(freq);
                if( it_byFreq != byFreq.begin() ) {
                    it_byFreq = prev(it_byFreq);
                    prevval = *(it_byFreq->second.rbegin());
                }
            } else {
                prevval = *prev(f);
            }
            ListNode* prev = nullptr;
            // cout << "prevval " << prevval << endl;
            if( prevval != -1 )
                prev = byVal[prevval];

            // node to right of us
            // byFreq, then in the value's list, the next value
            //     if we are the last value, then the 1st value of the next frequency if any
            //     if non, then we are the head of the right list
            int nextval = -1;
            if( next(f) == byFreq[freq].end() ) {
                auto it_byFreq = byFreq.find(freq);
                if( next(it_byFreq) != byFreq.end() ) {
                    it_byFreq = next(it_byFreq);
                    nextval = *(it_byFreq->second.begin());
                }
            } else {
                nextval = *next(f);
            }
            ListNode* next = nullptr;
            // cout << "nextval " << nextval << endl;
            if( nextval != -1 )
                next = byVal[nextval];

            // special case
            // left of us is nothing and right of us is nothing
            //    we are just starting out, so add to right list
            // left of us is left_head and right of us is right_tail OR
            // left of us is nothing and right of us is right_tail
            //    if length_right < x then add to right list as tail, otherwise to left list as head

            if( prev == nullptr && next == nullptr ) {
                listNode->list = 2;
            } else if( prev == nullptr && next == tail_right ) {
                if( length_right < x ) {
                    listNode->list = 2;
                } else {
                    listNode->list = 1;
                    next = nullptr;
                }
            } else if( prev == head_left && next == tail_right ) {
                if( length_right < x ) {
                    listNode->list = 2;
                    prev = nullptr;
                } else {
                    listNode->list = 1;
                    next = nullptr;
                }
            } else {
                listNode->list = prev != nullptr ? prev->list : next->list;
            }
            insert_node_to_list(prev,listNode,next);

            // we need to balance our lists
            // the right list can only be of length x
            if( length_right > x ) {
                // move right tail node to left head node
                // should only ever be 1 move from right to left
                listNode = tail_right;
                remove_node_from_list(listNode);
                listNode->list = 1;
                insert_node_to_list(head_left, listNode, nullptr);

            } else if(length_right < x && head_left != nullptr ) {
                // move left head node to right tail node
                // should only ever be 1 move from left to right
                listNode = head_left;
                remove_node_from_list(listNode);
                listNode->list = 2;
                insert_node_to_list(nullptr, listNode, tail_right);
            }
        }

        return;
    }

    // debug
    void printList(ListNode* listNode) {
        ListNode* ln = listNode;
        while( listNode != nullptr ) {
            cout << listNode->freq << ":" << listNode->val << " ";
            listNode = listNode->next;
        }
        cout << endl;
    }

public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size(); // 1 <= n <= 50

        // we need to track frequency of a given element in all k-length subarray
        // and sum the top x frequent elements of a given subarray
        // if there is a tie on frequency, the bigger element is considered more frequent

        // we will maintain to doubly-linked list of nodes
        //      left              right
        // ----------------- -----------------
        // tail ... ... head tail ... ... head
        // the right list represents our top x elements and their frequency in the current subarray ordered
        // the left list represents the remaining elements and their frequency in the current subarray ordered


        vector<long long> ans(n-k+1);

        tail_left = nullptr;
        head_left = nullptr;
        tail_right = nullptr;
        head_right = nullptr;

        sum_right = 0LL;
        length_right = 0;

        // sliding window
        int i = 0;
        for(int j = 0; j < n; ++j) {
            /*
            cout << "i " << i << " j " << j << endl;
            cout << "before" << endl;
            cout << "left list  ";printList(tail_left);
            cout << "right list ";printList(tail_right);
            */
            maintain(nums[j], x, 1); // add
            /*
            cout << "after add" << endl;
            cout << "left list  ";printList(tail_left);
            cout << "right list ";printList(tail_right);
            */
            if( j-i+1 == k ) {
                ans[i] = sum_right;
                maintain(nums[i], x, 0); // remove
                ++i;
            }
        }

        return ans;
    }
};
