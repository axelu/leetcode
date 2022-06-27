
// 1687. Delivering Boxes from Storage to Ports
// https://leetcode.com/problems/delivering-boxes-from-storage-to-ports/


class Solution {
private:
    
    int rec(vector<vector<int>>& boxes, int i, int maxBoxes, int maxWeight, int mem[]) {
        if( i == boxes.size() )
            return 0;
        
        if( mem[i] != -1 )
            return mem[i];

        // we have a choice
        // starting with box i
        // take as many boxes as we can OR
        // waste some capacity of the ship by taken some boxes on the next
        // trip if it saves us trips
        
        // we start from storage and need to get back to storage
        int trips = 0; 
        int curr_port = -1;
        int weight = 0;
        int k = i;
        int t_idx;   // 1st index where we saw the last port
        int t_trips; // trips up to the idx t_idx including return to storage
        for(; k < boxes.size() && k < i + maxBoxes; ++k) {

            weight += boxes[k][1];
            if( weight > maxWeight )
                break;

            // assuming we loaded the box initially, if we are
            // at its destination port, we would just unload it,
            // otherwise we have one trip from where we are
            // to current box's destination port
            if( curr_port != boxes[k][0] ) {
                ++trips;
                curr_port = boxes[k][0];
                t_idx = k;
                t_trips = trips;
            }

        }
        --k; // we didn't take the kth box
        
        // we return to storage: trips + 1
        int a = trips + 1 + rec(boxes,k+1,maxBoxes,maxWeight,mem);

        // if we loaded one or more boxes and the last consequtive boxes
        // are destined for the same port, we could start a new trip with the
        // 1st box that goes to the last port to save trips
        int b = INT_MAX;
        if( k - i >= 1 && t_idx > i )
            b = t_trips + rec(boxes,t_idx,maxBoxes,maxWeight,mem);
        
        return mem[i] = min(a,b);
    }
    
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        
        int mem[boxes.size()];memset(mem,-1,sizeof mem);
        return rec(boxes,0,maxBoxes,maxWeight,mem);
    }
};
