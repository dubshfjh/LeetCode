#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

思路完全错误了，只考虑了相邻元素left<right时才可能互换，输入为[1,3,2]时输出应该为[2,1,3]！！

但是下面的算法流程为:i=0时,[i]<[i+1],index=0; i=1时,[i]>[i+1],index保持不变，因此交换[0]和[1]得到[3,1,2]
正确流程应该从最后一个元素开始，找到与它最近而且小于它的元素，记录下标right_index(即最靠后的可换数),min_val(nums[size-1])
然后分析倒数第二个元素，找到与它最近而且小于它的元素，如果该元素下标==right_index，则比较其value与min_val的更小值并且更新

PS:如果[size-2]<[size-1]，则第一次的right_index=size-2，right_index必然不可能再更新；如果[size-2]>=[size-1]，则从[size-2]开始找到的第一个更小元素下标index
必然<=从[size-1]]开始得到的right_index。如果index<right_index，则index代表的数在right_index的更高位，互换index与[size-2]必然不会得到紧邻数。
因此只需要考虑right_index=index时，将right_index位的数置换成min(min_val,val)即可
/*
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i,size,index,temp;//index记录最后一个left<right的，left值
        size=nums.size();
        if(size<=1){
        	return;
        }
        index=-1;
        for(i=0;i<size-1;i++){
        	if(nums[i]<nums[i+1]){
        		index=i;
        	}
        }
        if(index<0){//没有更大的数字排列方式，数组颠倒得到最小数后return(任意的left>right，因此nums[0]...nums[size-1]依次递减)
        	for(i=0;i<size/2;i++){
        		temp=nums[i];
        		nums[i]=nums[size-1-i];
        		nums[size-1-i]=temp;
        	}
        	return;
        }
        temp=nums[index];
        nums[index]=nums[index+1];
        nums[index+1]=temp;
		
		for(i=0;i<nums.size();i++){
    		cout<<nums[i]<<endl;
		}
		
        return;
    }
};
*/
正确流程应该从最后一个元素开始，找到与它最近而且小于它的元素，记录下标right_index(即最靠后的可换数),min_val(nums[size-1])
然后分析倒数第二个元素，找到与它最近而且小于它的元素，如果该元素下标==right_index，则比较其value与min_val的更小值并且更新，最后将
将right_index位的数置换成min_val，但并非交换right_index和high_index就能得到结果！！！！
举例说明：input为[1,3,2]时,right_index=0,high_index=2,如果直接交换则会得到[2,3,1]，但是正确结果为[2,1,3]

因此正确结果为将nums[high_index]换到right_index后，对{nums[right_index]....nums[size-1]}这些元素从小到大排序，依次插入到{right_index+1...size}坐标上
如果输入为[1,4,3,5,2],则right_index=0,high_index=4,对{1,4,3,5}排序后进行插入，得到正确结果{2,1,3,4,5}

PS:由于在最终得到的right_index和high_index之间的元素，必然>=nums[high_index]，所以这些元素对应的最接近更小数的index有可能>=right_index
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i,j,high,size,temp,right_index,min_val,high_index;//right_index为最靠后的可以被置换的元素下标
        size=nums.size();
        if(size<=1){
        	return;
        }
        right_index=-1;
        min_val=INT_MAX;
        for(high=size-1;high>=1;high--){//nums[high]为试图换到前面(最靠近而且更小的数字)的数
        	temp=high-1;
        	while(nums[temp]>=nums[high]&&temp>=0){
        		temp--;
        	}
        	if(temp>=0){//temp为前一个<nums[high]的数字
        		if(temp>right_index){//如果当前的temp<right_index，则temp再更高位，置换该位为nums[high]产生的数   必然>置换right_index为min_val产生的数
        			right_index=temp;
        			min_val=nums[high];
        			high_index=high;
        		}
        		if(temp==right_index){
        			if(nums[high]<min_val){
        				min_val=nums[high];
        				high_index=high;
        			}
        		}
        	}//如果right_index==temp，则此时的nums[high]
        }
        if(right_index>=0){
        	temp=nums[right_index];
	        nums[right_index]=nums[high_index];
	        nums[high_index]=temp;//将原本的nums[right_index]插入到high_index
	        
	        for(i=right_index+1;i<size;i++){//对原本的{nums[right_index]....nums[size-1]}这些元素从小到大排序
	        	for(j=size-1;j>i;j--){//冒泡排序，每次通过交换，把当前的最小数左移到当前的i位置,然后i++
	        		if(nums[j]<nums[j-1]){
	        			temp=nums[j];
	        			nums[j]=nums[j-1];
	        			nums[j-1]=temp;
	        		}
	        	}
	        }
        }//如果right_index<0，则说明所有的元素都找不到最接近的可交换数，即对于任意的index，nums[0]>=nums[1]>=...>=nums[index]，则应该将它倒置为最小数
		else{
			for(i=0;i<size/2;i++){
				temp=nums[i];
				nums[i]=nums[size-1-i];
				nums[size-1-i]=temp;
			}
		}
		/*
        for(i=0;i<nums.size();i++){
        	cout<<nums[i];
        }
		*/
		return;
    }
};
int main(){
    int a[]={3,2,1};
    vector<int> nums(a,a+3);
    
    Solution sol=Solution();
    sol.nextPermutation(nums);
    return 0;
}
