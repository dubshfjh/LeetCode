贪心法：使用 temp_sum= sum(gas[i]-cost[i]) 判断当前临时方案的有效性,一旦对于某个i导致temp_sum < 0，则说明从i到i+1这段路导致了入不敷出，于是贪心地暂定i+1为新出发点，并且将 temp_sum重置为0
同时使用另一个变量 total 记录 i= 0 to size-1 的整体 sum(gas[i]-cost[i])，如果整体油量>=整体消耗量，则一定会有可行解(即遍历临时解决方案得到temp_sum过程中最后的 i+1)
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {//gas[i]；存储了加油站i加的油量,cost[i]：存储了加油站i到加油站(i+1)%size的耗油量
        if(gas.size() == 0){
            return -1;
        }
        int temp_sum,total,index;//total = sum(gas[i]-cost[i]) i=0...size-1，如果整体加的油量 >= 整体耗的油量，就一定存在可行旅游方案
        //temp_sum利用贪心法原理，for i=0 to size-1: temp_sum = sum(gas[i]-cost[i])，一旦temp_sum < 0则说明从i到i+1这段路会导致入不敷出，于是贪心地暂定i+1为新的出发点,temp_sum重置为0
        index = -1;
        temp_sum = total = 0;
        for(int i=0;i<gas.size();i++){
            temp_sum += (gas[i]-cost[i]);
            total += (gas[i]-cost[i]);
            if(temp_sum < 0){
                index = i+1;
                temp_sum = 0;
            }
        }

        index = (total < 0)?-1:index;
        return index;
    }

    /*
    void quicksort(vector<int>& profit,vector<int>& index,int left,int right){
        if(left > right){
            return;
        }
        int low,high;
        low  = left;
        high = right;
        int key = profit[left];
        int index_left = index[left];
        while(low < high){
            while(profit[high] < key && low < high){
                high--;
            }
            profit[low] = profit[high];
            index[low] = index[high];
            cout<<low<<",,,"<<high<<endl;
            while(profit[low] > key && low < high){
                low++;
            }
            profit[high] = profit[low];
            index[high] = index[low];
        }
        profit[low] = key;//把key填到上一步的位置，因为不管low和high的大小，终归会执行a[high]=a[low]这一步，从而a[low]空了出来
        index[low] = index_left;
        cout<<",,,,"<<key<<endl;
        for(int i=0;i<profit.size();i++){
            // cout<<profit[i]<<"..."<<index[i]<<endl;;
        }
        quicksort(profit,index,left,low-1);
        quicksort(profit,index,low+1,right);
    }
    */
};