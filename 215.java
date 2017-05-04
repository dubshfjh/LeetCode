public class Solution {
    
    int partition(int[] nums,int low,int high){
        int key = nums[high];
        int i = low;
        while(i < high){
            if(nums[i] <= key){
                swap(nums,low++,i++);
            }
            else{
                i++;    
            }
        }
        swap(nums,low,high);
        return low;
    }
    
   
    int partition(int[] nums,int low,int high){
        int key = nums[high];
        int left = low,right = high;
        while(left < right){
            while(left<right && nums[left] <= key){
                left++;
            }
            nums[right] = nums[left];

            while(right>left && nums[right] >= key){
                right--;
            }
            nums[left] = nums[right];
        }
        nums[left] = key;
        return left;
    }

    void swap(int[] nums,int i,int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public int helpFind(int[] nums,int k,int left,int right){
        int pivotIndex = partition(nums,left,right);
        if(nums.length - pivotIndex == k){
            return nums[pivotIndex];
        }
        else if(nums.length - pivotIndex < k){
            return helpFind(nums,k,left,pivotIndex-1);
        }
        else{
            return helpFind(nums,k,pivotIndex+1,right);
        }
    }

    public int findKthLargest(int[] nums, int k) {
        return helpFind(nums,k,0,nums.length-1);
    }
}

//大顶堆
public class Solution {
    
    public void heapAdjust(int[] nums,int eleIndex,int size){
        int left = (eleIndex<<1)+1;
        int right = (eleIndex<<1)+2;
        int maxIndex = eleIndex;
        if(left<size && nums[left] > nums[maxIndex]){
            maxIndex = left;
        }
        if(right<size && nums[right] > nums[maxIndex]){
            maxIndex = right;
        }

        if(maxIndex != eleIndex){
            swap(nums,maxIndex,eleIndex);
            // eleIndex = maxIndex;
            heapAdjust(nums,maxIndex,size);
        }
    }
    

    void swap(int[] nums,int i,int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public int findKthLargest(int[] nums, int k) {
        int size = nums.length;
        for(int i=size/2-1;i>=0;i--){
            heapAdjust(nums,i,size);
        }

        for(int i=1;i<k;i++){
            swap(nums,0,--size);
            heapAdjust(nums,0,size);
        }

        return nums[0];
    }
}