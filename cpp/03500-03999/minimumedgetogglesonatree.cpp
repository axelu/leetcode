
// 3812. Minimum Edge Toggles on a Tree
// https://leetcode.com/problems/minimum-edge-toggles-on-a-tree/


class Solution {
private:
    void printvector(vector<int>& v) {
        for(int x: v)
            cout << x << " ";
    }

    /*
    pair<int,vector<int>> rec(unordered_map<int, pair<vector<int>,vector<int>>>::iterator end, 
            unordered_map<int, pair<vector<int>,vector<int>>>::iterator it, 
            int picks, int length, bool needed_parity) 
    {
        // needed parity 0 even, 1 odd
        if( it == end )
            return picks % 2 == needed_parity ? make_pair(length,vector<int>()) : make_pair(-1,vector<int>());

        // TODO cache anwser key:(it and picks parity) 

        // we have a choice
        //     pick first (not flipped) OR
        //     pick second (flipped)
        auto a = rec(end, next(it), picks,     length + it->second.first.size(),  needed_parity);
        auto b = rec(end, next(it), picks + 1, length + it->second.second.size(), needed_parity);

        int ret_length;
        vector<int> ret_picks;

        if( a.first == -1 && b.first == -1 ) {
            ret_length = -1;

        } else if( a.first == -1 ) {
            ret_length = length + it->second.second.size();
            ret_picks = b.second;
            ret_picks.push_back(it->first); // our current edge index
        
        } else if( b.first == -1 ) {
            ret_length = length + it->second.first.size();
            ret_picks = a.second;

        } else {
            if( a < b ) {
                ret_length = length + it->second.first.size();
                ret_picks = a.second;
            } else {
                ret_length = length + it->second.second.size();
                ret_picks = b.second;
                ret_picks.push_back(it->first); // our current edge index
            }
        }

        return {ret_length, ret_picks};
    }

    vector<int> solve(unordered_map<int, pair<vector<int>,vector<int>>>& um, bool needed_parity) {
        // parity 0 even, 1 odd
        // we have to pick pair.first parity number of times while minimizing length
        auto end = um.end();
        auto it  = um.begin();
        auto ret = rec(end, it, 0, 0, needed_parity);
        if( ret.first == -1 )
            return {-1};
        return ret.second;
    }

    unordered_map<int,vector<int>> mem_best_flipped;

    vector<int> rec(vector<vector<pair<int,int>>>& t, int u, int src, bool flipped, string& start, string& target) {
        // cout << "rec u " << u << " src " << src << " flipped " << flipped << endl;
        // it is guaranteed that we will be called 1st with not flipped, then with flipped
        // if called with flipped we can throw cached answer away to keep memory reasonable
        if( flipped ) {
            auto ret = mem_best_flipped[u];
            mem_best_flipped.erase(u);

            // debug
            // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
            // cout << "res "; printvector(ret); cout << endl;

            return ret;
        }

        // ret.back() will include length of answer, if not possible, then -1, as 0 would be a valid answer
        // if a child gives us not flipped -1 AND flipped -1, then there is no solution
        // if a child give us not flipped -1 OR flipped -1, then for that child is only one solution

        // flipped false
        //     start[u] == target[u] => even flips
        //     start[u] != target[u] => odd flips 
        // flipped true
        //     start[u] == target[u] => odd flips
        //     start[u] != target[u] => even flips 

        // so the challenge becames to pick the best answer from our children
        // with an odd number or even number of flips

        // let us key by edge_idx

        int nbr_children = 0;
        vector<int> predetermined;
        int must_flip = 0;
        unordered_map<int, pair<vector<int>,vector<int>>> tmp; // key: edge_idx, value: {ansnotflipped,ansflipped}
        for(auto& p: t[u]) {
            int v = p.first;
            if( v == src )
                continue;
            int edge_idx = p.second;

            ++nbr_children;

            vector<int> a = rec(t, v, u, false, start, target); // not flipped
            vector<int> b = rec(t, v, u, true, start, target);  // flipped

            if( a.back() == -1 && b.back() == -1 ) {
                return {-1};
            } else if( a.back() == -1 ) {
                // flipping this edge is the only possible path
                ++must_flip;
                predetermined.push_back(edge_idx);
                b.pop_back();
                predetermined.insert(predetermined.end(), b.begin(), b.end());
            } else if( b.back() == -1 ) {
                // not flipping this edge is the only possible path
                a.pop_back();
                predetermined.insert(predetermined.end(), a.begin(), a.end());
            } else {
                // with this edge we have the option to not flip or to flip
                a.pop_back();
                b.pop_back();
                tmp[edge_idx] = {a,b};
            }
        }
        if( nbr_children == 0 ) {
            // if( flipped )
            //     return start[u] != target[u] ? vector<int>{0} : vector<int>{-1};
            // else
            //     return start[u] == target[u] ? vector<int>{0} : vector<int>{-1};

            // if we are here, we are called with not flipped
            // let us store flipped answer
            vector<int> ret_flipped(1);
            ret_flipped[0] = start[u] != target[u] ? 0 : -1;
            mem_best_flipped[u] = ret_flipped;

            vector<int> ret_not_flipped(1);
            ret_not_flipped[0] = start[u] == target[u] ? 0 : -1;

            // debug
            // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
            // cout << "res "; printvector(ret_not_flipped); cout << endl;

            return ret_not_flipped;
        }

        // at this point we know how many edges already must be flipped !!!
        // need already adjusted (basically XOR)
        // ---------------------
        // even even    even
        // even odd     odd
        // odd  even    odd
        // odd  odd     even

        // !flipped
        //     start[u] == target[u] => even flips
        //     start[u] != target[u] => odd flips
        bool needed_parity_not_flipped = start[u] == target[u] ? 0 : 1;
        // adjust for already must be flipped
        if( (needed_parity_not_flipped == 0 && must_flip % 2 == 1) ||
            (needed_parity_not_flipped == 1 && must_flip % 2 == 1) )
            needed_parity_not_flipped = !needed_parity_not_flipped; // toggle
        // flipped
        //     start[u] == target[u] => odd flips
        //     start[u] != target[u] => even flips 
        bool needed_parity_flipped = start[u] == target[u] ? 1 : 0;
        // adjust for must be flipped
        if( (needed_parity_flipped == 0 && must_flip % 2 == 1) ||
            (needed_parity_flipped == 1 && must_flip % 2 == 1) )
            needed_parity_flipped = !needed_parity_flipped; // toggle
        

        // debug
        // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
        // cout << "must_flip " << must_flip << " ";
        // cout << "needed_parity_not_flipped " << needed_parity_not_flipped << " ";
        // cout << "needed_parity_flipped " << needed_parity_flipped  << endl;


        // calc best answer incoming not flipped
        auto best_not_flipped = solve(tmp, needed_parity_not_flipped);
        if( best_not_flipped.empty() || best_not_flipped.back() != -1 ) {
            best_not_flipped.insert(best_not_flipped.end(), predetermined.begin(), predetermined.end());
            best_not_flipped.push_back(best_not_flipped.size());
        }

        // calc best answer incoming flipped
        vector<int> best_flipped;
        if( needed_parity_flipped == needed_parity_not_flipped ) {
            best_flipped = best_not_flipped;
        } else {
            best_flipped = solve(tmp, needed_parity_flipped);
            if( best_flipped.empty() || best_flipped.back() != -1 ) {
                best_flipped.insert(best_flipped.end(), predetermined.begin(), predetermined.end());
                best_flipped.push_back(best_flipped.size());
            }
        }

        // if we are here, we are called with not flipped
        // let us store flipped answer
        mem_best_flipped[u] = best_flipped;

        // debug
        // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
        // cout << "res "; printvector(best_not_flipped); cout << endl;

        return best_not_flipped;
    }
    */
    // top down
    ///////////////////////////////////////////////////////////////////////////
    // bottom up
    /*
    pair<int,vector<int>*> rec(unordered_map<int, pair<vector<int>*,vector<int>*>>::iterator end, 
            unordered_map<int, pair<vector<int>*,vector<int>*>>::iterator it, 
            int picks, int length, bool needed_parity) 
    {
        // needed parity 0 even, 1 odd
        if( it == end ) {
            vector<int> * ptr_ret = new vector<int>(); 
            if( picks % 2 == needed_parity ) {
                return make_pair(length,ptr_ret); 
            } else {
                return make_pair(-1,ptr_ret); // TODO we could return nullptr
            }
        }

        // TODO cache anwser key:(it and picks parity) 

        // we have a choice
        //     pick first (not flipped) OR
        //     pick second (flipped)
        auto a = rec(end, next(it), picks,     length + it->second.first->size(),  needed_parity);
        auto b = rec(end, next(it), picks + 1, length + it->second.second->size(), needed_parity);

        int ret_length;
        vector<int> * ret_picks;

        if( a.first == -1 && b.first == -1 ) {
            ret_length = -1;
            ret_picks = new vector<int>();
            delete a.second; a.second = nullptr;
            delete b.second; b.second = nullptr;

        } else if( a.first == -1 ) {
            ret_length = length + it->second.second->size();
            ret_picks = b.second;
            ret_picks->push_back(it->first); // our current edge index
            delete a.second; a.second = nullptr;
        
        } else if( b.first == -1 ) {
            ret_length = length + it->second.first->size();
            ret_picks = a.second;
            delete b.second; b.second = nullptr;

        } else {
            if( a < b ) {
                ret_length = length + it->second.first->size();
                ret_picks = a.second;
                delete b.second; b.second = nullptr;
            } else {
                ret_length = length + it->second.second->size();
                ret_picks = b.second;
                ret_picks->push_back(it->first); // our current edge index
                delete a.second; a.second = nullptr;
            }
        }

        return {ret_length, ret_picks};
    }

    vector<int>* solve(unordered_map<int, pair<vector<int>*,vector<int>*>>& um, bool needed_parity) {
        if( um.size() != 0 )
            cout << "solve " << um.size() << endl;
        // parity 0 even, 1 odd
        // we have to pick pair.first parity number of times while minimizing length
        auto end = um.end();
        auto it  = um.begin();
        auto ret = rec(end, it, 0, 0, needed_parity);
        if( ret.first == -1 ) {
            vector<int>* ret = new vector<int>();
            ret->push_back(-1);
            return ret;
        }
        return ret.second;
    }

    vector<int> post_order;
    vector<int> parent;
    vector<bool> is_leaf;
    vector<pair<vector<int>*,vector<int>*>> tmpres;

    void dfs(vector<vector<pair<int,int>>>& t, int u, int src) {
        parent[u] = src;
        for(auto& p: t[u]) {
            int v = p.first;
            if( v != src ) {
                is_leaf[u] = false;
                dfs(t, v, u);
            }
        }
        post_order.push_back(u);
        return;
    }

    void rec(vector<vector<pair<int,int>>>& t, int u, string& start, string& target) {
        // cout << "rec u " << u << endl;
        // it is guaranteed that our children have answers

        vector<int> * ptr_ret_not_flipped = new vector<int>();
        vector<int> * ptr_ret_flipped = new vector<int>();

        if( is_leaf[u] ) {
            // if( !flipped )
            //     return start[u] == target[u] ? vector<int>{0} : vector<int>{-1};
            // else
            //     return start[u] != target[u] ? vector<int>{0} : vector<int>{-1};

            if( start[u] != target[u] ) 
                ptr_ret_not_flipped->push_back(-1);
            tmpres[u].first = ptr_ret_not_flipped;

            if( start[u] == target[u] )
                ptr_ret_flipped->push_back(-1);
            tmpres[u].second = ptr_ret_flipped;

        } else {
            vector<int> predetermined;
            int must_flip = 0;
            unordered_map<int, pair<vector<int>*,vector<int>*>> tmp; // key: edge_idx, value: {ansnotflipped,ansflipped}
            bool broke = false;
            vector<int> tobecleaned;
            for(auto& p: t[u]) {
                int v = p.first;
                bool clean = true;
                if( v != parent[u] ) {
                    // cout << "rec u " << u << " child v " << v << endl;
                    if( !broke ) {
                        int edge_idx = p.second;
                        vector<int>* a = tmpres[v].first;  // not flipped
                        vector<int>* b = tmpres[v].second; // flipped

                        if( a->empty() == false && a->back() == -1 && b->empty() == false && b->back() == -1 ) {
                            ptr_ret_not_flipped->push_back(-1);
                            tmpres[u].first = ptr_ret_not_flipped;
                            ptr_ret_flipped->push_back(-1);
                            tmpres[u].second = ptr_ret_flipped;
                            broke = true;
                        } else if( a->empty() == false && a->back() == -1 ) {
                            // flipping this edge is the only possible path
                            ++must_flip;
                            predetermined.push_back(edge_idx);
                            //if( b->empty() == false ) {
                            //    b->pop_back();
                            //    predetermined.insert(predetermined.end(), b->begin(), b->end());
                            //}
                            predetermined.insert(predetermined.end(), b->begin(), b->end());
                        } else if( b->empty() == false && b->back() == -1 ) {
                            // not flipping this edge is the only possible path
                            //if( a->empty() == false ) {
                            //    a->pop_back();
                            //    predetermined.insert(predetermined.end(), a->begin(), a->end());
                            //}
                            predetermined.insert(predetermined.end(), a->begin(), a->end());
                        } else {
                            // with this edge we have the option to not flip or to flip
                            // if( a->empty() == false ) a->pop_back();
                            // if( b->empty() == false ) b->pop_back();
                            tmp[edge_idx] = {a,b};
                            clean = false;
                            tobecleaned.push_back(v);
                        }
                    }
                    // cleanup
                    if( clean ) {
                        delete tmpres[v].first;
                        tmpres[v].first = nullptr;
                        if( tmpres[v].second != nullptr ) {
                            delete tmpres[v].second;
                            tmpres[v].second = nullptr;
                        }
                    }
                }
            } // end processing every child
            if( broke ) {
                for(int v: tobecleaned) {
                    delete tmpres[v].first;
                    tmpres[v].first = nullptr;
                    if( tmpres[v].second != nullptr ) {
                        delete tmpres[v].second;
                        tmpres[v].second = nullptr;
                    }
                }
                return;
            }

            // at this point we know how many edges already must be flipped !!!
            // need already adjusted (basically XOR)
            // ---------------------
            // even even    even
            // even odd     odd
            // odd  even    odd
            // odd  odd     even

            // !flipped
            //     start[u] == target[u] => even flips
            //     start[u] != target[u] => odd flips
            bool needed_parity_not_flipped = start[u] == target[u] ? 0 : 1;
            // adjust for already must be flipped
            if( (needed_parity_not_flipped == 0 && must_flip % 2 == 1) ||
                (needed_parity_not_flipped == 1 && must_flip % 2 == 1) )
                needed_parity_not_flipped = !needed_parity_not_flipped; // toggle
            // flipped
            //     start[u] == target[u] => odd flips
            //     start[u] != target[u] => even flips 
            bool needed_parity_flipped = start[u] == target[u] ? 1 : 0;
            // adjust for must be flipped
            if( (needed_parity_flipped == 0 && must_flip % 2 == 1) ||
                (needed_parity_flipped == 1 && must_flip % 2 == 1) )
                needed_parity_flipped = !needed_parity_flipped; // toggle

            // debug
            // cout << "rec u " << u << " ";
            // cout << "must_flip " << must_flip << " ";
            // cout << "needed_parity_not_flipped " << needed_parity_not_flipped << " ";
            // cout << "needed_parity_flipped " << needed_parity_flipped  << endl;

            // calc best answer incoming not flipped
            vector<int> * ptr_best_not_flipped = solve(tmp, needed_parity_not_flipped);
            if( ptr_best_not_flipped->empty() || ptr_best_not_flipped->back() != -1 ) {
                ptr_best_not_flipped->insert(ptr_best_not_flipped->end(), predetermined.begin(), predetermined.end());
                // ptr_best_not_flipped->push_back(ptr_best_not_flipped->size());
            }
            // calc best answer incoming flipped
            vector<int> * ptr_best_flipped;
            if( needed_parity_flipped == needed_parity_not_flipped ) {
                ptr_best_flipped = ptr_best_not_flipped;
            } else {
                ptr_best_flipped = solve(tmp, needed_parity_flipped);
                if( ptr_best_flipped->empty() || ptr_best_flipped->back() != -1 ) {
                    ptr_best_flipped->insert(ptr_best_flipped->end(), predetermined.begin(), predetermined.end());
                    // ptr_best_flipped->push_back(ptr_best_flipped->size());
                }
            }

            tmpres[u].first = ptr_best_not_flipped;
            tmpres[u].second = ptr_best_flipped;

            for(int v: tobecleaned) {
                delete tmpres[v].first;
                tmpres[v].first = nullptr;
                if( tmpres[v].second != nullptr ) {
                    delete tmpres[v].second;
                    tmpres[v].second = nullptr;
                }
            }

            return;
        }
    }
    */
    ///////////////////////////////////////////////////////////////////////////

    vector<int> post_order;
    vector<int> parent;
    vector<int> edge; // edge_idx of edge parent to u, said differently: edge_idx of edge leading to u if tree rooted in 0
    vector<bool> is_leaf;

    void dfs(vector<vector<pair<int,int>>>& t, int u, int src_node, int src_edge) {
        parent[u] = src_node;
        edge[u] = src_edge;
        for(auto& p: t[u]) {
            int v = p.first;
            int e = p.second;
            if( v != src_node ) {
                is_leaf[u] = false;
                dfs(t, v, u, e);
            }
        }
        post_order.push_back(u);
        return;
    }

    vector<bool> edge_to_be_flipped;

    void rec(vector<vector<pair<int,int>>>& t, int u, string& start, string& target) {
        // cout << "rec u " << u << endl;
        // it is guaranteed that our children have answers, meaning 
        // it is guaranteed that the edges leading to our children have answers
        // sets edge_to_be_flipped[u] to true if the edge leading to u has to be flipped

       if( is_leaf[u] ) {
            if( start[u] != target[u] ) 
                edge_to_be_flipped[edge[u]] = true;

        } else {
            int must_flip = 0;
            for(auto& p: t[u]) {
                int v = p.first;
                if( v != parent[u] ) {
                    int e = p.second;
                    if( edge_to_be_flipped[e] ) ++must_flip;
                }
            }

            if( must_flip % 2 ) {
                // u will be flipped based on children needs
                if( start[u] == target[u] )
                    edge_to_be_flipped[edge[u]] = true;
            } else {
                // u will not be flipped based on children needs
                if( start[u] != target[u] )
                    edge_to_be_flipped[edge[u]] = true;
            }
        }
        return;
    }

public:
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {
        
        // undirected tree with n nodes numbered from 0 to n-1
        // t[u] = {{v0,edge_idx of edge u-v0}, ...}
        vector<vector<pair<int,int>>> t(n); 
        for(int i = 0; i < n-1; ++i) {
            // i is the edge index
            int u = edges[i][0];
            int v = edges[i][1];
            t[u].push_back({v,i});
            t[v].push_back({u,i});
        }
        
        /*
        // top down
        // arbitrarily rooting tree in node 0
        auto ans = rec(t, 0, -1, false, start, target);
        if( ans.back() == -1 )
            return ans;

        ans.pop_back();
        sort(ans.begin(), ans.end());
        return ans;
        */

        /*
        // buttom up
        // arbitrarily rooting tree in node 0
        // post order traversal 
        parent.resize(n);
        is_leaf.assign(n,true);
        dfs(t, 0, -1);

        // now we can create answer by processing nodes in post_order order
        // when we come to a node we know its children (if any) have an answer already
        // and we clean up as we go along
        tmpres.resize(n);
        for(int u: post_order) {
            // cout << "u " << u << endl;
            rec(t, u, start, target);

            
            // cout << "u " << u << " ";
            // cout << "not flipped ";
            // for(int i = 0; i < tmpres[u].first->size(); ++i) {
            //     cout << tmpres[u].first->at(i) << " ";
            // }
            // cout << endl;
            // cout << "u " << u << " ";
            // cout << "flipped ";
            // for(int i = 0; i < tmpres[u].second->size(); ++i) {
            //     cout << tmpres[u].second->at(i) << " ";
            // }
            // cout << endl;
            
            // early exit
            if( tmpres[u].first->empty()  == false && tmpres[u].first->back()  == -1 &&
                tmpres[u].second->empty() == false && tmpres[u].second->back() == -1 ) {

                for(int i = 0; i < n; ++i) {
                    if( tmpres[i].first != nullptr ) {
                        delete tmpres[i].first; tmpres[i].first = nullptr;
                    }
                    if( tmpres[i].second != nullptr ) {
                        delete tmpres[i].second; tmpres[i].second = nullptr;
                    }
                }
                return {-1};
            }
        }

        vector<int> ret = *tmpres[0].first;
        sort(ret.begin(), ret.end());
        delete tmpres[0].first; tmpres[0].first = nullptr;
        delete tmpres[0].second; tmpres[0].second = nullptr;
        return ret;
        */


        // assumption via observation:
        // an edge either has to be flipped or it doesn't
        // there is no case in which a node will have a solution
        // for the incoming edge to be flipped or not flipped
        // hence the only thing we need to determine is if there
        // is a solution and for that solution, which edges need to be flipped

        // arbitrarily rooting tree in node 0
        // post order traversal 
        parent.resize(n);
        edge.resize(n);
        is_leaf.assign(n,true);
        // we are telling the edge with idx n-1 leads to node 0
        dfs(t, 0, -1, n-1);


        // now we can create answer by processing nodes in post_order order
        // when we come to a node we know its children (if any) have an answer already
        // meaning we know if the edge leading to a child has to be flipped or not
        edge_to_be_flipped.assign(n,false);
        for(int u: post_order) {
            // cout << "u " << u << endl;
            rec(t, u, start, target);

        }
        if( edge_to_be_flipped[n-1] )
            return {-1};

        vector<int> ans;
        for(int i = 0; i < n-1; ++i)
            if( edge_to_be_flipped[i] )
                ans.push_back(i);

        return ans;
    }
};





// passes 516/537 test cases as of 1/31/2026
// then MLE


class Solution {
private:
    void printvector(vector<int>& v) {
        for(int x: v)
            cout << x << " ";
    }

    pair<int,vector<int>> rec(unordered_map<int, pair<vector<int>,vector<int>>>::iterator end,
            unordered_map<int, pair<vector<int>,vector<int>>>::iterator it,
            int picks, int length, bool needed_parity)
    {
        // needed parity 0 even, 1 odd
        if( it == end )
            return picks % 2 == needed_parity ? make_pair(length,vector<int>()) : make_pair(-1,vector<int>());

        // TODO cache anwser key:(it and picks parity)

        // we have a choice
        //     pick first (not flipped) OR
        //     pick second (flipped)
        auto a = rec(end, next(it), picks,     length + it->second.first.size(),  needed_parity);
        auto b = rec(end, next(it), picks + 1, length + it->second.second.size(), needed_parity);

        int ret_length;
        vector<int> ret_picks;

        if( a.first == -1 && b.first == -1 ) {
            ret_length = -1;

        } else if( a.first == -1 ) {
            ret_length = length + it->second.second.size();
            ret_picks = b.second;
            ret_picks.push_back(it->first); // our current edge index

        } else if( b.first == -1 ) {
            ret_length = length + it->second.first.size();
            ret_picks = a.second;

        } else {
            if( a < b ) {
                ret_length = length + it->second.first.size();
                ret_picks = a.second;
            } else {
                ret_length = length + it->second.second.size();
                ret_picks = b.second;
                ret_picks.push_back(it->first); // our current edge index
            }
        }

        return {ret_length, ret_picks};
    }

    vector<int> solve(unordered_map<int, pair<vector<int>,vector<int>>>& um, bool needed_parity) {
        // parity 0 even, 1 odd
        // we have to pick pair.first parity number of times while minimizing length
        auto end = um.end();
        auto it  = um.begin();
        auto ret = rec(end, it, 0, 0, needed_parity);
        if( ret.first == -1 )
            return {-1};
        return ret.second;
    }

    unordered_map<int,vector<int>> mem_best_flipped;

    vector<int> rec(vector<vector<pair<int,int>>>& t, int u, int src, bool flipped, string& start, string& target) {
        // cout << "rec u " << u << " src " << src << " flipped " << flipped << endl;
        // it is guaranteed that we will be called 1st with not flipped, then with flipped
        // if called with flipped we can throw cached answer away to keep memory reasonable
        if( flipped ) {
            auto ret = mem_best_flipped[u];
            mem_best_flipped.erase(u);

            // debug
            // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
            // cout << "res "; printvector(ret); cout << endl;

            return ret;
        }

        // ret.back() will include length of answer, if not possible, then -1, as 0 would be a valid answer
        // if a child gives us not flipped -1 AND flipped -1, then there is no solution
        // if a child give us not flipped -1 OR flipped -1, then for that child is only one solution

        // flipped false
        //     start[u] == target[u] => even flips
        //     start[u] != target[u] => odd flips
        // flipped true
        //     start[u] == target[u] => odd flips
        //     start[u] != target[u] => even flips

        // so the challenge becames to pick the best answer from our children
        // with an odd number or even number of flips

        // let us key by edge_idx

        int nbr_children = 0;
        vector<int> predetermined;
        int must_flip = 0;
        unordered_map<int, pair<vector<int>,vector<int>>> tmp; // key: edge_idx, value: {ansnotflipped,ansflipped}
        for(auto& p: t[u]) {
            int v = p.first;
            if( v == src )
                continue;
            int edge_idx = p.second;

            ++nbr_children;

            vector<int> a = rec(t, v, u, false, start, target); // not flipped
            vector<int> b = rec(t, v, u, true, start, target);  // flipped

            if( a.back() == -1 && b.back() == -1 ) {
                return {-1};
            } else if( a.back() == -1 ) {
                // flipping this edge is the only possible path
                ++must_flip;
                predetermined.push_back(edge_idx);
                b.pop_back();
                predetermined.insert(predetermined.end(), b.begin(), b.end());
            } else if( b.back() == -1 ) {
                // not flipping this edge is the only possible path
                a.pop_back();
                predetermined.insert(predetermined.end(), a.begin(), a.end());
            } else {
                // with this edge we have the option to not flip or to flip
                a.pop_back();
                b.pop_back();
                tmp[edge_idx] = {a,b};
            }
        }
        if( nbr_children == 0 ) {
            // if( flipped )
            //     return start[u] != target[u] ? vector<int>{0} : vector<int>{-1};
            // else
            //     return start[u] == target[u] ? vector<int>{0} : vector<int>{-1};

            // if we are here, we are called with not flipped
            // let us store flipped answer
            vector<int> ret_flipped(1);
            ret_flipped[0] = start[u] != target[u] ? 0 : -1;
            mem_best_flipped[u] = ret_flipped;

            vector<int> ret_not_flipped(1);
            ret_not_flipped[0] = start[u] == target[u] ? 0 : -1;

            // debug
            // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
            // cout << "res "; printvector(ret_not_flipped); cout << endl;

            return ret_not_flipped;
        }

        // at this point we know how many edges already must be flipped !!!
        // need already adjusted (basically XOR)
        // ---------------------
        // even even    even
        // even odd     odd
        // odd  even    odd
        // odd  odd     even

        // !flipped
        //     start[u] == target[u] => even flips
        //     start[u] != target[u] => odd flips
        bool needed_parity_not_flipped = start[u] == target[u] ? 0 : 1;
        // adjust for already must be flipped
        if( (needed_parity_not_flipped == 0 && must_flip % 2 == 1) ||
            (needed_parity_not_flipped == 1 && must_flip % 2 == 1) )
            needed_parity_not_flipped = !needed_parity_not_flipped; // toggle
        // flipped
        //     start[u] == target[u] => odd flips
        //     start[u] != target[u] => even flips
        bool needed_parity_flipped = start[u] == target[u] ? 1 : 0;
        // adjust for must be flipped
        if( (needed_parity_flipped == 0 && must_flip % 2 == 1) ||
            (needed_parity_flipped == 1 && must_flip % 2 == 1) )
            needed_parity_flipped = !needed_parity_flipped; // toggle


        // debug
        // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
        // cout << "must_flip " << must_flip << " ";
        // cout << "needed_parity_not_flipped " << needed_parity_not_flipped << " ";
        // cout << "needed_parity_flipped " << needed_parity_flipped  << endl;


        // calc best answer incoming not flipped
        auto best_not_flipped = solve(tmp, needed_parity_not_flipped);
        if( best_not_flipped.empty() || best_not_flipped.back() != -1 ) {
            best_not_flipped.insert(best_not_flipped.end(), predetermined.begin(), predetermined.end());
            best_not_flipped.push_back(best_not_flipped.size());
        }

        // calc best answer incoming flipped
        vector<int> best_flipped;
        if( needed_parity_flipped == needed_parity_not_flipped ) {
            best_flipped = best_not_flipped;
        } else {
            best_flipped = solve(tmp, needed_parity_flipped);
            if( best_flipped.empty() || best_flipped.back() != -1 ) {
                best_flipped.insert(best_flipped.end(), predetermined.begin(), predetermined.end());
                best_flipped.push_back(best_flipped.size());
            }
        }

        // if we are here, we are called with not flipped
        // let us store flipped answer
        mem_best_flipped[u] = best_flipped;

        // debug
        // cout << "rec u " << u << " src " << src << " flipped " << flipped << " ";
        // cout << "res "; printvector(best_not_flipped); cout << endl;

        return best_not_flipped;
    }

public:
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {
        return {};
        // undirected tree with n nodes numbered from 0 to n-1
        // t[u] = {{v0,edge_idx of edge u-v0}, ...}
        vector<vector<pair<int,int>>> t(n);
        for(int i = 0; i < n-1; ++i) {
            // i is the edge index
            int u = edges[i][0];
            int v = edges[i][1];
            t[u].push_back({v,i});
            t[v].push_back({u,i});
        }

        // arbitrarily rooting tree in node 0
        auto ans = rec(t, 0, -1, false, start, target);
        if( ans.back() == -1 )
            return ans;

        ans.pop_back();
        sort(ans.begin(), ans.end());
        return ans;
    }
};
