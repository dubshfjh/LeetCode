对撞型双指针问题：矮柱子负责蓄水(只影响当前位置,e.g 矮柱子[left]只能在当前位置蓄水)，
高柱子负责向邻居提供水位高度(高柱子[right] 可以向 [left...right - 1]提供更高的水位)；

因此对于left, right双指针，只需要移动其中的矮柱子即可(其中的高柱子还可以承担向另一侧提供水位的作用，)，
双向移动left,right直到两个指针碰撞到同一个位置

分析为什么移动较短的柱子(即为啥只有高柱子才能承担向"另一侧"提供水位的作用)，本题中不是求最优解，只需保证解的正确性
假定 [left] < [right]，那么我们应该将 left 右移，因为此时 右柱子提供的水位更高，
	如果左右指针此时对撞，则由于水位只需要考虑左右两侧的"短板"，所以更高的右侧水位可以被忽略
	1. 如果[left + 1] < [left]，则[left + 1]负责蓄水，蓄水量直接为 [left] - [left + 1]
    2. 如果[left + 1] >= [right]，则[left + 1]负责提供高水位，更新左侧的最高水位，然后它将与 [right]比较一下谁的水位更高，
    	二者中的矮柱子由于只能影响自己这个位置，没有再分析的意义了，直接向中间移动

// 因此"双指针碰撞的preStep"就决定移动哪边柱子
// 假定 [left] < [right]，那么我们将 left 右移到 left + 1，此时两个指针即将对撞！left, left + 1, right
// 1. 如果 [left + 1] < [left]，那么新的柱子是蓄水方，此时 左侧提供[left]水位，
// 	右侧提供 [right]水位，由于 [left] < [right]，所以该柱子蓄水量为 Min([left], [right]) - [left + 1]，即 [left] - [left + 1] 
public class Solution {
    /*
     * @param heights: a list of integers
     * @return: a integer
     */
    public int trapRainWater(int[] heights) {
        // write your code here
        if (heights.length <= 1) {
        	return 0;
        }
        int left = 0;
        int right = heights.length - 1;
        int leftMaxHeight = 0;
        int rightMaxHeight = 0;
        int rainArea = 0;
        while (left < right) {
        	if (leftMaxHeight > 0) {
        		if (heights[left] < leftMaxHeight) {
        			rainArea += (leftMaxHeight - heights[left]);
        		} 
        	}
        	leftMaxHeight = Math.max(leftMaxHeight, heights[left]);

        	if (rightMaxHeight > 0) {
        		if (heights[right] < rightMaxHeight) {
        			rainArea += (rightMaxHeight - heights[right]);
        		}
        	}
        	rightMaxHeight = Math.max(rightMaxHeight, heights[right]);

        	if (heights[left] < heights[right]) {
        		left++;
        	} else {
        		right--;
        	}
        }
        return rainArea;
    }
};