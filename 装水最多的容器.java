对撞型Two pointers问题，当[start] 和 [end] 满足某种关系，则可以直接放弃其中 一侧 的分析
e.g. 本题中如果 [start] < [end])，可以直接断定 [start] 与 [end, end - 1...start+1] 不可能构成更优解，于是 直接分析 start + 1
public class Solution {
    /*
     * @param : a vector of integers
     * @return: an integer
     */
    public int maxArea(int[] heights) {
        // write your code here
        if (heights.length <= 1) {
        	return 0;
        }
        int area = 0;
        int start = 0;
        int end = heights.length - 1;
        while (start < end) {
        	int curArea = Math.min(heights[end], heights[start]) * (end - start);
        	area = Math.max(area, curArea);
        	if (heights[start] < heights[end]) {
        		start++;
        	} else {
        		end--;
        	}
        }
        return area;
    }
};