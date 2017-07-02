k Sum 问题:由于本题的k=4尚未较小值，所以仍然采用"2 Sum"问题中的"对撞性指针"思想，首先对整体的nums排序
然后固定左侧的 k-2 个pivot(本题为2个轴i,j)，最后的两个pivot【start和end】 初始化为 j+1 和 nums.length-1，令newtarget = target - sum([i],[j])
1. 如果 [start] + [end] == newtarget，为避免重复解则start++，end--
2. 如果 [start] + [end] < newtarget，则start 与 {start+1...end-1}的组合必然 < newtarget，因此当前的start不会产生可行解，start++
3. 如果 [start] + [end] > newtarget，则{start+1...end-1} 与 end 的组合必然 > newtarget，因此当前的end不会产生可行解, end--
ps：为避免重复解，对于左侧的 k-1 个pivot(本题为 i,j,start)，对于同一个取值只分析一次：即 if(pivot > 初值 && [pivot]==[pivot-1])，则 continue

当 k Sum 问题中的 k 取值较大时，则考虑使用 0-1 背包问题，令 n = nums.length，问题转化为 从前n件物品中挑选k件物品，恰好填充容量为target的背包
初步思路：将k和target视作背包2个维度的容量，设计数组 boolean[n][k][target]。具体思路得去 九章算法强化班视频 回顾
public class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        int i,j,start,end;
        List<List<Integer>> res = new ArrayList<List<Integer>>();
        int length = nums.length;
        if(length < 4){
            return res;
        }
        Arrays.sort(nums);
        for(i=0;i<length-3;i++){
            if(i>0 && nums[i]==nums[i-1]){
                continue;
            }
            for(j=i+1;j<length-2;j++){
                if(j>i+1 && nums[j]==nums[j-1]){
                    continue;
                }
                start = j+1;
                end = length-1;
                int newtarget = target - (nums[i]+nums[j]);
                while(start < end){
                    if(start > j+1 && nums[start]==nums[start-1]){
                        start++;
                        continue;
                    }
                    if(nums[start]+nums[end] == newtarget){
                        List<Integer> temp = new ArrayList<Integer>();
                        temp.add(nums[i]);
                        temp.add(nums[j]);
                        temp.add(nums[start]);
                        temp.add(nums[end]);
                        res.add(temp);

                        start++;
                        end--;
                    }
                    else if(nums[start]+nums[end] < newtarget){
                        start++;
                    }
                    else{
                        end--;
                    }
                }
            }
        }
        return res;
    }
}