时间复杂度要求O(n^2)，因此类比 twoSumClosest 中对撞型指针的解法，首先固定住数字[i]，然后通过对撞指针寻找[j], [k]
1. 对numbers升序排列，依次将 numbers[0...n - 3] 作为固定的数字 [i], 将 target - [i] 作为 [j] + [k] 需要靠近的目标
2. b, c 采用对撞型双指针，分别从 [i + 1] 和 [n - 1]开始对撞
3.1 如果 [j] + [k] > target - [i], 则说明 {j + 1...k - 1} 与 {k} 的组合与新目标距离 > 0，
	而且距离必然会逐渐增加，因此可以舍弃对 [k] 的分析，k--
3.2 如果 [j] + [k] < target - [i]，则说明 {j} 与 {j + 1...k - 1} 的组合与新目标距离也会逐渐增加，
	因此舍弃对 [j] 的分析, j++
3.3 [j] + [k] == target，距离为最小值 0

//不再为了逻辑分明，而单独分离出 twoSumClosest 这个方法
public class Solution {
    /**
     * @param numbers: Give an array numbers of n integer
     * @param target : An integer
     * @return : return the sum of the three integers, the sum closest target.
     */
    public int threeSumClosest(int[] numbers, int target) {
        // write your code here
        if (numbers == null || numbers.length < 3) {
            return Integer.MIN_VALUE;
        }
        Arrays.sort(numbers);
        int finalSum = -1;
        int minDistance = Integer.MAX_VALUE;

        for (int i = 0; i < numbers.length - 2; i++) {
            int twoTarget = target - numbers[i];
            int start = i + 1;
            int end = numbers.length - 1;
            while (start < end) {
                int threeSum = numbers[start] + numbers[end] + numbers[i];
                if (Math.abs(threeSum - target) < minDistance) {
                    minDistance = Math.abs(threeSum - target);
                    finalSum = threeSum;
                }

                if (numbers[start] + numbers[end] < twoTarget) {
                    start++;
                } else if (numbers[start] + numbers[end] > twoTarget) {
                    end--;
                } else {
                    return target;
                }
            }
        }
        return finalSum;
    }

    public static void main(String[] args) {
        int[] nums = {2,7,11,15};
        int target = 3;
        Solution obj = new Solution();
        System.out.println(obj.threeSumClosest(nums, target));
    }
}

//该版本分离了twoSumClosest的算法逻辑，导致判断"TwoTarget+nums[i] 与 target" 以及 "TwoTarget与newTarget" 距离时的代码冗余度极高
public class Solution {
    /**
     * @param numbers: Give an array numbers of n integer
     * @param target : An integer
     * @return : return the sum of the three integers, the sum closest target.
     */
    public int threeSumClosest(int[] numbers, int target) {
        // write your code here
        if (numbers == null || numbers.length < 3) {
            return Integer.MIN_VALUE;
        }

        int finalSum = Integer.MAX_VALUE;
        int minDistance = Integer.MAX_VALUE;
        Arrays.sort(numbers);
        for (int i = 0; i < numbers.length - 2; i++) {
            if (i > 0 && numbers[i] == numbers[i - 1]) {
                continue;
            }
            int twoSumTarget = target - numbers[i];
            int tempTwoSum = getTwoSumClosest(numbers, i + 1, twoSumTarget);
            int tempDis = Math.abs(tempTwoSum + numbers[i] - target);
            if (tempDis < minDistance) {
                finalSum = tempTwoSum + numbers[i];
                minDistance = tempDis;
            }
        }
        return finalSum;
    }

    private int getTwoSumClosest(int[] numbers, int start, int target) {
        int end = numbers.length - 1;
        int finalSum = Integer.MAX_VALUE;
        int minDistance = Integer.MAX_VALUE;
        while (start < end) {
            int tempSum = numbers[start] + numbers[end];
            int tempDis = Math.abs(target - tempSum);
            if (tempDis < minDistance) {
                minDistance = tempDis;
                finalSum = tempSum;
            }
            if (numbers[start] + numbers[end] < target) {
                start++;
            } else if (numbers[start] + numbers[end] > target) {
                end--;
            } else {
                return target;
            }
        }
        return finalSum;
    }

    public static void main(String[] args) {
        int[] nums = {2,7,11,15};
        int target = 3;
        Solution obj = new Solution();
        System.out.println(obj.threeSumClosest(nums, target));
    }
}