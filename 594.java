求解最长和谐子序列
由于是求解子序列，所以挑选的元素不需要相邻，对于元素nums[i]而言，如果 nums[i] + 1 || nums[i] - 1存在，
    则必然可以挑选得到一个包含这2个元素的子序列，所以 包含 nums[i] 的最长子序列length = max { nums[i]个数 + (nums[i]+1)个数,
    nums[i]个数 + (nums[i]-1)个数 }，在遍历 nums[i]的过程中，只需要分析一侧的邻居即可//we don't need to check both +1 and -1
    e.g. 对于每个元素[i]，只需要分析右邻居[i]+1是否存在即可；如果还分析左邻居，则分析到 [j]==[i]+1时，[j]的左邻居就是[i]，重复进行了分析
坑：Integer_MAX + 1 == Integer_MIN，所以应该使用 long变量计算 右邻居 的值

public class Solution {
    public int findLHS(int[] nums) {
        int res = 0;
        Map<Long, Integer> countNum = new HashMap<Long, Integer>();
        for (long num:nums) {
            countNum.put(num, countNum.getOrDefault(num, 0) + 1); //jdk1.8 提供的新方法
        }
        
        for (long num:countNum.keySet()){
            long rightNeighbor = num + 1;
            if (countNum.containsKey(rightNeighbor)) {
                res = Math.max(res, countNum.get(num) + countNum.get(rightNeighbor));
            }
        }
        return res;
    }
}


“滑动窗口” 求解最长和谐子串
/*
public class Solution {
     public int findLHS(int[] nums) {
        if (nums.length == 0) {
            return 0;
        }
        Map<Integer,Integer> location = new HashMap<Integer,Integer>();//location 存放每个值的最新出现位置
        int min,max,res,left,right;
        min = max = nums[0];
        location.put(min,0);
        left = right = 0;
        res = 1;
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] > max + 1 || nums[i] < min - 1) {//必须放弃整个滑动窗口
                res = Math.max(res, right - left + 1);
                left = right = i;
                location.remove(min);
                location.remove(max);
                min = max = nums[i];

            }
            else if (nums[i] == min || nums[i] == max) {
                right++;
            }
            else {//1.min==max，则直接将nums[i]作为缺失的窗口边界 2.min!=max 必须右移滑动窗口的左边界，使得包含nums[i]时仍然和谐：1. [i]==min-1，则必须消除max  2.[i]==max+1，则必须消除min
                res = Math.max(res, right - left + 1);
                if (min == max) {
                    right++;
                    min = Math.min(min, nums[i]);
                    max = Math.max(min, nums[i]);
                }
                else{
                    if (nums[i] == min - 1){
                        left = location.get(max) + 1;
                        location.remove(max);
                        max = min;
                        min = nums[i];
                    }
                    else{
                        left = location.get(min) + 1;
                        location.remove(min);
                        min = max;
                        max = nums[i];
                    }
                }
            }
            location.put(nums[i], i);
        }
        return res;
    }

    public static void main(String[] args) {
        int[] nums = {1,3,2,2,5,2,3,7};
        Main obj = new Main();
        System.out.println(obj.findLHS(nums));
    }
}
*/