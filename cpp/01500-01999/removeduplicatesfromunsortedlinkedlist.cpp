
// 1836. Remove Duplicates From an Unsorted Linked List
// https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
private:
    // doubly linked list
    struct Node {
        ListNode* node;
        Node* prev;
        Node* next;
        Node(ListNode* nd) : node(nd), prev(nullptr), next(nullptr) {}
    };
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        if( head->next == nullptr ) return head;

        unordered_map<int,Node*> um;
        unordered_map<int,Node*>::iterator f;

        Node* node;
        Node* nHead;
        Node* nPrev = nullptr;
        Node* t;
        ListNode* ln = head;
        while( ln != nullptr ) {
            // cout << "ln->val " << ln->val << endl;
            f = um.find(ln->val);
            if( f == um.end() ) {
                t = new Node(ln);
                t->prev = nPrev;
                if( nPrev == nullptr ) {
                    nHead = t;
                } else {
                    nPrev->next = t;
                }
                nPrev = t;
                // cout << "inserting " << ln->val << endl;
                um.insert({ln->val,t});
            } else {
                if( f->second != nullptr ) {
                    // cout << "found, delete and skip " << endl;
                    // delete the node from the doubly linked list
                    // and skip this node
                    if( f->second->prev == nullptr ) {
                        // cout << "f->second->prev == nullptr" << endl;
                        nHead = f->second->next;
                    } else {
                        // cout << "f->second->prev != nullptr" << endl;
                        f->second->prev->next = f->second->next;
                    }
                    if( f->second->next != nullptr ) {
                        // cout << "f->second->next != nullptr" << endl;
                        f->second->next->prev = f->second->prev;
                    } else {
                        // cout << "f->second->next == nullptr" << endl;
                    }
                    if( f->second == nPrev ) {
                        // cout << "f->second != nPrev" << endl;
                        nPrev = f->second->prev;
                    }
                    delete f->second;
                    f->second = nullptr;
                } else {
                    // simply skip this node
                    // cout << "found and skip " << endl;
                }
            }
            // if( nHead == nullptr ) cout << "nHead == nullptr" << endl;
            // else cout << "nHead->node->val = " << nHead->node->val << endl;
            ln = ln->next;
        }

        if( nHead == nullptr ) return nullptr;
        node = nHead;
        ListNode* prev;
        while( node != nullptr ) {
            if( node == nHead ) head = node->node;
            else prev->next = node->node;
            node->node->next = nullptr;
            prev = node->node;
            t = node;
            node = node->next;
            delete t;
        }

        return head;
    }
};
