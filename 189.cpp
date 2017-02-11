1. rotate k个字符：将后 k 个字符([size-k]...[size-1]) rotate 到前 size-k 个字符([0]...[k-1])的位置之前
   为了一定程度地加速，当 k > size/2时，可以选择将前 size-k 个字符rotate到 后 k 个字符之后
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        k = k % size;
        if(k <= 0){
            return;
        }
        int i,j;
        j = 0;
        if(k <= size/2){//将后 k 个字符([size-k]...[size-1]) rotate 到前 size-k 个字符([0]...[k-1])的位置之前
            vector<int> temp(nums.begin()+size-k, nums.end());
            nums.erase(nums.begin()+size-k,nums.end());
            nums.insert(nums.begin(),temp.begin(),temp.end());            
        }
        else{//将前 size-k 个字符rotate到 后 k 个字符之后
            vector<int> temp(nums.begin(),nums.begin()+size-k);
            nums.insert(nums.end(),temp.begin(),temp.end());
            nums.erase(nums.begin(),nums.begin()+size-k);
        }
    }
};


//2. 使用迭代器遍历(GG啦!!!)

Runtime Error: attempt to increment a singular iterator.
出错原因：在使用iterator遍历vector时，该vector的size发生了变化
"
    it++;/it--;
    vector.push_back();/vector.insert();
"
/*
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        k = k % size;
        if(k <= 0){
            return;
        }
        int j = 0;
        if(k <= size/2){
            vector<int>::iterator it = nums.end();
            while(j < k){
                it--;
                cout<<*it<<endl;
                "导致出错"nums.insert(nums.begin(),*it);
                j++;
            }
            nums.erase(nums.end()-k,nums.end());
        }
        else{
            vector<int>::iterator it = nums.begin();
            while(j < size-k){
                int temp = *it;
                "导致出错"nums.push_back(temp);
                cout<<temp<<endl;
                it++;
                j++;
            }
            nums.erase(nums.begin(),nums.begin()+j);
        }
    }
};
*/
*

2. 参考186  Reverse Words in a String的解法
1) reverse前size-k个元素
2) reverse后k个元素
3) reverse所有元素

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int size = nums.size();
        k %= size;
        if(k <= 0){
            return;
        }
        reverse(nums.begin(),nums.begin()+size-k);//reverse(i,j)：颠倒[i,j)
        reverse(nums.begin()+size-k,nums.end());
        reverse(nums.begin(),nums.end());
    }
};


3. Make an extra copy and then rotate.
Rotate the elements.后k个元素[size-k...size-1]左移到[0...k-1]，前size-k个元素[0...size-k-1]移动到[k...size-1]，
所以Rotate前的[i] 对应 Rotate后的[(i+k)%size]

class Solution 
{
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if ((n == 0) || (k <= 0)){
            return;
        }
        
        // Make a copy of nums
        vector<int> numsCopy(n);
        for (int i = 0; i < n; i++){
            numsCopy[i] = nums[i];
        }
        
        for (int i = 0; i < n; i++){
            nums[(i + k)%n] = numsCopy[i];
        }
    }
};


4. 首先 Swap the last k elements with the first k elements. The last k elements will be in the correct positions
然后， but we need to rotate the remaining (n - k) elements to the right by k steps.

class Solution 
{
public:
    void rotate(int nums[],int n,int k) {
        for(;k = k%size;){
            for(int i=0;i<k;i++){
                swap(nums[i], nums[size-k+i]);//Index i (0 <= i < n - k) becomes n - k - i.
            }

            n -= k;//前k个元素已经到了正确位置
            nums += k;//nums指针移到第k+1个元素，下一次循环rotate本轮remaining n-k elements后k个元素(即与前k个元素互换位置)
        }
    }
};