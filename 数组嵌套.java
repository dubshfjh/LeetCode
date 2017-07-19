public class Solution {
	private int[] cache;
    public int arrayNesting(int[] nums) {
        if (nums.length == 0) {
        	return 0;
        }
        // 由于 maxNestLen[i] = 1 + maxNestLen[nums[i]]，这个变化状态不连续，所以不适合用dp
        //改用记忆化搜索
        // int[] maxNestLen = new int[nums.length];
        // Arrays.fill(maxNestLen, 1);
        cache = new int[nums.length];
        boolean[] visit = new boolean[nums.length];
        Arrays.fill(cache, 0);
        int maxLen = 1;
        
        for (int i = 0; i < nums.length; i++) {
            // Arrays.fill(visit, false);
	        maxLen = Math.max(maxLen, helpSearch(nums, i, visit));
        }
        return maxLen;
    }

    private int helpSearch(int[] nums, int i, boolean[] visit) {
        // System.out.println(i);
    	if (cache[i] > 0) { //记忆化搜索返回
    		return cache[i];
    	} else if (i < 0 || i > nums.length) { //访问到越界元素
    		return 0;
    	} else if (visit[i]) { //避免再次对此次搜索path上已访问的节点 环式递归
    		return 0;
    	}
        visit[i] = true;
    	int neighborLen = helpSearch(nums, nums[i], visit);
        visit[i] = false;
        
    	cache[i] = 1 + neighborLen;
        return cache[i];
    }
}