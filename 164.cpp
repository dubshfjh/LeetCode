桶排序，不管数据是否均匀分布，其时间复杂度和空间复杂度都是O(n)，参见算法导论112-113
首先设定相同大小的n个桶[本题设定size个桶，每个桶的容量：bucketsize = 1 + max-min/(size-1)]，将每个nums[i]放到所属的第nums[i]/bucketsize个桶中，再执行插入排序
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <limits.h>
using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int size,bucketsize;
        size = nums.size();
        if(size < 2){
            return 0;
        }
        //题意中只说了所有数都是非负数，但所有的数字都可能取同一个值，所以设定size个桶共同存储最多(max-min+1)个元素，当桶大小(max-min+1)/(size-1) 不为整数时，指定bucketsize += 1，e.g bucketsize=3.36时应制定它为4！！！而且(INT_MAX-0+1) = INT_MIN < 0，所以不妨设每个桶大小为(max-min)/(size-1)，此时size个桶也足够存储所有元素了
        int max_ele,min_ele;
        max_ele = INT_MIN;
        min_ele = INT_MAX;
        for(int i=0;i<size;i++){
            min_ele = min(nums[i],min_ele);
            max_ele = max(nums[i],max_ele);
        }
        
        bucketsize = 1+(max_ele - min_ele)/(size-1);//每个桶的大小都相同,设定共有size个桶，nums[i]被分配到第0个..第size-1个桶中的一个
        cout<<bucketsize<<",,,"<<min_ele<<",,,"<<max_ele<<",,,"<<size<<endl;
        list<int> temp;
        list<int>::iterator it;
        vector<list<int>> buckets(size,temp);
        
        for(int i=0;i<size;i++){//size个元素插入size个桶
            int bucket_id = (nums[i] - min_ele)/bucketsize;
            // cout<<bucket_id<<",,,";
            if(buckets.size()==0){
                buckets[bucket_id].push_back(nums[i]);
            }
            else{
                it = buckets[bucket_id].begin();
                while(it!=buckets[bucket_id].end() && (*it)<nums[i]){
                    it++;
                }
                
               buckets[bucket_id].insert(it,nums[i]);
            }
        }
        int gap,pre;
        gap = pre = INT_MIN;
        for(int i=0;i<size;i++){//从前往后遍历size个桶，依次计算排好序的元素间gap
            if(buckets[i].size()==0){
                continue;
            }
            it = buckets[i].begin();
            // cout<<pre<<",,,"<<*it<<endl;
            if(pre == INT_MIN){
                pre = *it;
                it++;
            }
            while(it != buckets[i].end()){
                gap = max(gap,*(it)-pre);
                pre = *it;
                it++;
            }
        }
        return gap;
    }
};


int main(){
    int a[]={0,1,3,50,51,54,58,75,89,99};
    vector<int> num(a,a+10);
    Solution sol=Solution();
    int res = sol.maximumGap(num);
    cout<<res<<endl;
    return 0;
}
