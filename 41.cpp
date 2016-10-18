#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

算法思想：使得nums[i]存放i+1这个值，首先扫描一次nums，对nums[i]和nums[nums[i]-1]进行swap。然后第二次扫描nums，找到first !=i+1的元素nums[index]，
index+1就是最终结果

为什么不需要考虑nums[i]>i+1的情况呢？示例：[1,2,2,4]->[1,2,4,2]->[1,2,4,2]; [1,2,5,3,4]->[1,2,4,5,3]->[1,2,3,4,5]
如果[i+1,i+2,...]出现了i+1这个值(nums[i]>i+1)，则i+1处必然会通过swap得到该值；如果后方都没有i+1这个值，则i就是第一个(nums[i]!=i+1)的下标
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int i,index;
        for(i=0;i<nums.size();i++){
        	if(nums[i]>=1 && nums[i]<=nums.size()){
        		//如果交换的数据nums[index]还是大于等于1且<i+1，则放在合适的位置,保证二者数据不相等来避免死循环
        		//
        		//nums[i]==nums[nums[i]-1]意味着：当前的nums[i]应该放置到nums[i]-1这个位置上，但是该位置已经放了正确的数，此时不应该继续置换，否则死循环
        		//例子：[1,2,4,2]->[1,2,2,4]，此时nums[i]<i+1(i=2,nums[i]=2)，此时的2本来应该放到nums[1]上，但是nums[1]已经有正确解了，所以直接i++
        		
        		while(nums[i]>=1 && nums[i]<i+1 && nums[i]!=nums[nums[i]-1]){//如果某次的nums[i]>i+1，则nums[i]的真实Index必然在i右侧，所以在多次i++之后分析该index时
        			index=nums[i]-1;							//就可以把nums[i]交换到正确的index上了
        			swap(nums[i],nums[index]);
        		}

        	}
        }

        for(i=0;i<nums.size();i++){
        	if(nums[i]!=i+1){
        		return i+1;
        	}
        }

		return nums.size()+1;                
    }
};