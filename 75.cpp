class Solution {
public:
    void sortColors(vector<int>& nums) {
    	int i,low,high;//low存储当前i左侧第一个不为red的元素；high存储当前i右侧最后一个不为blue的元素；i只需要遍历到high为止(因为high之后全部为Blue)
    	i=low=0;
    	high=nums.size()-1;
    	if(low==high){
    		return;
    	}
    	
    	while(i<=high){//Attention!!!必须是i<=high，因为high的初值[size-1]仍然可能需要左移（即[size-1]=="red"的情况！！！）
    	    //否则在遇到case:[W,R]时，low=0,high=1,而i直接右移到了high的初值1后，就放弃了对high的移动，实乃大谬！
    		if(nums[i]==1){//对于white直接忽略即可
    			i++;
    		}
    		else if(nums[i]==0){//对于Red，需要与当前的low交换位置
    			while(low<i && nums[low]==0){
    				low++;
    			}
    			//cout<<"low: "<<low<<",,,"<<i<<endl;
    			if(low==i){
    				i++;
    			}
    			else{
    				swap(nums[low],nums[i]);
    			}
    		}
    		else{//对于Blue，需要与当前的high交换位置
    			while(high>i && nums[high]==2){
    				high--;
    			}
    			//cout<<"high"<<high<<",,,"<<i<<endl;
    			if(high==i){
    				i++;
    			}
    			else{
    				swap(nums[high],nums[i]);
    			}
    		}
    	}
    }
};