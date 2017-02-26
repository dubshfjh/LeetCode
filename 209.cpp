将数组左右边界left和right初始化为0，循环执行直到right==size(为保证最后一个元素被分析，必须使用do-while循环)：
1.不管right是否<size，先右移一次，再循环右移right直到 right==size 或者 [left...right-1]的sum>=s
2.left左移直到 [left+1...right-1]的sum<s，更新minlen = (right-1)-left+1 = right-left，回到步骤1
class Solution {
public:
    int res = INT_MAX;
    int minSubArrayLen(int s, vector<int>& nums) {
        int left,right,sum,minlen,size;
        left = right = sum = 0;
        minlen = INT_MAX;
        size = nums.size();
        while(right < size){//如果[0...right]的sum>=s，为每个[right]找到最短subarray的左边界，使得[left...right]的sum>=s，然后将
            // while(right < size && sum < s){被注释掉的while循环 + 被注释的最后一行并不能替代do while，因为这些代码在处理最后一个元素(right==size-1)时，sum+=nums[right++]执行后，right==size跳出了while循环，于是最后元素的最短左边界并未分析！！！
            //     sum += nums[right++];
            // }
            do sum += nums[right++];//不管是否满足while都会执行1次do，不断右移right，直到跳出循环时{left...right-1}的sum>=s
            while (right < size && sum < s);
            
            while(left<right && sum-nums[left]>=s){//left不断右移，直到排除掉[left]将导致sum<s,当跳出循环时，{left...right-1}的sum是针对当前right的最短合理subarray
                sum -= nums[left++];
            }
            if(sum >= s){//为靠后的元素(比如最后元素last)分析sum时,{left...last}的sum可能<s
                minlen = min(minlen,right-left);
            }
            // cout<<left<<",,,"<<right<<",,,"<<sum<<endl;

            //sum += nums[right++];

        }
        return (minlen==INT_MAX)?0:minlen;
    }
};