初始化 res = nums[0];
使用pos_dp[i]记录{0...i}这一段中(不一定以0开头，但一定以i结尾)contiguous subarray的最大值，试图得到"max正数"乘积
    ps:没必要用数组，使用 imax 这个变量记录即可，在分析每个i后，更新 res = max(res,imax);
使用neg_dp[i][i]记录{0...i}这一段中（不一定以0开头，但一定以i结尾）contiguous subarray的最小值，试图得到"min负数"乘积
    ps:没必要用数组，使用 imin 这个变量记录即可
'''
太过混乱，需要使用技巧
分析pos_dp[i]
    如果pos_dp[i-1]以i-1结尾,
        则对于pos_dp[i]有3种策略：1.采用以i-1结尾的连续子数组(pos_dp[i-1]) plus [i]构成乘积  2.放弃i-1之前的子序列，从[i]重新开始构成子数组 3.放弃i
        即pos_dp[i] = max(pos_dp[i-1]*[i],[i],pos_dp[i])
    如果pos_dp[i-1]不以i结尾，则有放弃[0...i-1]/放弃[i]两种策略，pos_dp[i] = max(self,[i],pos_dp[i-1])

    如果neg_dp[i-1]以i-1结尾，则 最小负数neg_dp[i-1]*[i]也有可能产生最大乘积
        即pos_dp[i] = max(self,neg_dp[i-1]*[i])
    
分析neg_dp[i]
'''
PS: 
技巧如下：如果[i]<0，则(到[i-1]为止的最大乘积imax * [i]) 必然< (到[i-1]为止的最小乘积imin *[i])，也就是说只有imin*[i]才可能产生到[i]为止的最大值/(上一轮的i_max*nums[i])才可能产生本轮的i_min。所以交换二者来重定义i_max和i_min：swap(imax,imin)
          由于本轮过后的imax和imin必须以[i]为结尾的，所以不用考虑放弃[i]的情况，只需要分析[i]自己/[...i-1,i]这一段即可，更新 imax = max([i],imax*[i])
          同理，更新 imin = min([i], imin*[i])。在分析完元素[i]后更新 res = max(res,imax)。
PS：为什么在定义了i_max -> 以元素[i]为结尾后max乘积后 , res = max{0_max,1_max,2_max....}？
    分析完[i]后更新的res >= 之前所有轮的imax，而最大乘积必然是要以nums中的 1 个元素作为结尾的


class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int size = nums.size();
        if(size == 0){
            return INT_MIN;
        }
        
        //在分析元素nums[i]并更新res后,res存放到nums[i]为止的max连续乘积
        //i_max/i_min存放了'以元素nums[i]为结尾的contiguous子数组'的max/min乘积
        int i_max,i_min,res;
        i_max = i_min = res = nums[0];
        
        for(int i=1;i<size;i++){
            if(nums[i] < 0){// (最大数i_max*负数) 必然<= (最小数i_min*负数)，所以只有(上一轮的i_min*nums[i])才可能产生本轮的i_max，同理(上一轮的i_max*nums[i])才可能产生本轮的i_min
                swap(i_max,i_min);//因此通过交换二者重定义i_max和i_min
            }
            
            //因为i_max,i_min都以i为结尾元素，所以i_max/i_min = {nums[i] itself,上一轮i_max/i_min * nums[i]}
            i_max = max(nums[i], i_max*nums[i]);
            i_min = min(nums[i], i_min*nums[i]);
            
            //分析完每个nums[i]产生的i_max是全局最大值的一个候选者
            res = max(res,i_max);
        }
        return res;
    }
};