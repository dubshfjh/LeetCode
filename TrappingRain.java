public int trap(int[] height){
    if(height.length == 0){
        return 0;
    }
    int left,right,curLMaxH,curRMaxH,sum;
    left = sum = 0;
    right = height.length-1;
    curLMaxH = curRMaxH = 0;
    while(left < right){
        if(height[left] < height[right]){
            if(curLMaxH <= height[left]){
                curLMaxH = height[left];
            }
            else{
                sum += curLMaxH-height[left];
            }
            left++;
        }
        else{
            if(curRMaxH <= height[right]){
                curRMaxH = height[right];
            }
            else{
                sum += curRMaxH - height[right];
            }
            right--;
        }
    }
    return sum;
}

public static void main(String[] args){
    int[] nums = {2,0,1,0,3,0,4,0,6};
//        int target = 7;
    Main obj = new Main();
    System.out.println(obj.trap(nums));
    // for(int i:nums){
    //     System.out.print(i+" ");
    // }
    // System.out.println();
}