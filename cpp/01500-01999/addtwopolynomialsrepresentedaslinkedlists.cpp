
// 1634. Add Two Polynomials Represented as Linked Lists
// https://leetcode.com/problems/add-two-polynomials-represented-as-linked-lists/




/**
 * Definition for polynomial singly-linked list.
 * struct PolyNode {
 *     int coefficient, power;
 *     PolyNode *next;
 *     PolyNode(): coefficient(0), power(0), next(nullptr) {};
 *     PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
 *     PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
 * };
 */

class Solution {
public:
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {

        PolyNode* prev = nullptr;
        PolyNode* head = nullptr;
        int c_new;
        while( poly1 != nullptr || poly2 != nullptr ) {
            /*
            cout << "poly1 c ";
            if( poly1 != nullptr ) cout << poly1->coefficient << " p " << poly1->power;
            else cout << "null p null";
            cout << " poly2 c ";
            if( poly2 != nullptr ) cout << poly2->coefficient << " " << poly2->power;
            else cout << "null p null";
            cout << endl;
            */


            if( poly1 == nullptr && poly2 != nullptr ) {
                if( prev != nullptr )
                    prev->next = poly2;
                else
                    head = poly2;
                break;
            } else if( poly1 != nullptr && poly2 == nullptr ) {
                if( prev != nullptr )
                    prev->next = poly1;
                else
                    head = poly1;
                break;
           } else {
                // poly1 != nullptr && poly2 != nullptr

                if( poly1->power > poly2->power ) {
                    if( prev != nullptr )
                        prev->next = poly1;
                    else
                        head = poly1;
                    prev  = poly1;
                    poly1 = poly1->next;
                } else if( poly1->power < poly2->power ) {
                    if( prev != nullptr )
                        prev->next = poly2;
                    else
                        head = poly2;
                    prev  = poly2;
                    poly2 = poly2->next;
                } else {
                    // poly1->power == poly2->power
                    c_new = poly1->coefficient + poly2->coefficient;
                    if( c_new != 0 ) {
                        // we will repurpose poly1
                        poly1->coefficient = c_new;
                        if( prev != nullptr )
                            prev->next = poly1;
                        else
                            head = poly1;
                        prev  = poly1;
                    }
                    poly1 = poly1->next;
                    poly2 = poly2->next;
                }
                if( prev != nullptr )
                    prev->next = nullptr;
            }
        }


        return head;
    }
};
