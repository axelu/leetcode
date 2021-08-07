#include <vector>
#include <array>
#include <iostream>
#include <queue>


using namespace std;


// Dijkstra's algorithm
int shortestPath(int n, vector<array<int,2>> G[], int s, int d) {

    // min heap
    priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

    // distances
    int A[n+1];
    for(int i = 0; i < n+1; ++i) A[i] = 1000000;

    // push our source vertex into priority queue
    pq.push({0,s});
    // set distance to our source vertex itself to 0
    A[s] = 0;

    int u,v,weight;
    while(!pq.empty()) {

        u = pq.top()[1];
        pq.pop();

        vector<array<int,2>>::iterator it;
        for(it = G[u].begin(); it != G[u].end(); ++it) {
            v = (*it)[0];
            weight = (*it)[1];

            //  If there is shorter path to v through u.
            if( A[v] > A[u] + weight ) {
                // Updating distance of v
                A[v] = A[u] + weight;
                pq.push({A[v], v});
            }
        }
    }

    return A[d];
}


int main() {

    // question: can we use Dijkstra for [Single-Source] Longest Path calculation?


    vector<array<int,2>> G1[6];
    G1[0] = {{1,20},{5,25}};
    G1[1] = {{2,10},{3,20}};
    G1[2] = {{3,100}};
    G1[3] = {{4,30}};
    G1[5] = {{4,70}};

    // shortest path from 0 -> 4
    int d1 = shortestPath(6,G1,0,4);
    cout << "shortest path from 0 -> 4 " << d1 << endl;


    // G2 all edges negated
    // running Dijkstra now will find the longest path
    vector<array<int,2>> G2[6];
    G2[0] = {{1,-20},{5,-25}};
    G2[1] = {{2,-10},{3,-20}};
    G2[2] = {{3,-100}};
    G2[3] = {{4,-30}};
    G2[5] = {{4,-70}};

    int d2 = shortestPath(6,G2,0,4);
    cout << "longest path from 0 -> 4  " << -d2 << endl;
    // I believe the accepted answer in this post is wrong
    // https://cs.stackexchange.com/questions/74406/dijkstra-s-in-a-graph-with-negation-of-edges


    // another example from above post
    vector<array<int,2>> G3[3];
    G3[0] = {{1,2},{2,1}};
    G3[2] = {{1,2}};

    // shortest path from 0 -> 1
    int d3 = shortestPath(3,G3,0,1);
    cout << "shortest path from 0 -> 1 " << d3 << endl;

    // G2 all edges negated
    // running Dijkstra now will find the longest path
    vector<array<int,2>> G4[3];
    G4[0] = {{1,-2},{2,-1}};
    G4[2] = {{1,-2}};

    int d4 = shortestPath(3,G4,0,1);
    cout << "longest path from 0 -> 1  " << -d4 << endl;


    return 0;
}
