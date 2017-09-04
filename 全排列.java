学会写DFS搜索树！！！！！！！第i层递归选择当前全排列的第 i 个元素
输入：[1, 1, 2, 3]
level one：1,		1(左侧兄弟已经访问过1，略去),	2,	   3
level two: 2,  3;								   1,3;	  1,2
level three:3;	2;								  3;  1; 2 ; 1

在第i层递归，左侧兄弟已经访问过元素[i]，则说明"第i个元素为nums[i]的所有全排列"都已经分析过，因此需要跳过nums[i]				
class Solution {
    /**
     * @param nums: A list of integers.
     * @return: A list of permutations.
     */
    private List<List<Integer>> res;
    public List<List<Integer>> permute(int[] nums) {
        // write your code here
        res = new ArrayList<List<Integer>>(); //本题在校验最终输出时，会对输出结果排序，所以不能使用LinkedList保存每项结果
        if (nums == null) {
            return res;
        }
        if (nums.length == 0) {
            res.add(new ArrayList<Integer>());
        	return res;
        }
        Arrays.sort(nums);
        boolean[] visit = new boolean[nums.length];
        List<Integer> path = new LinkedList<>();

        search(nums, path, visit);
        return res;
    }

    private void search(int[] nums, List<Integer> path, boolean[] visit) {
    	if (path.size() == nums.length) {
    		res.add(new ArrayList(path));
    	}
    	for (int start = 0; start < nums.length; start++) {
    		if (start > 0 && nums[start] == nums[start - 1]) {
    			continue;
    		}
    		if (visit[start]) { //避免dfs搜索出环
    			continue;
    		}
    		path.add(nums[start]);
    		visit[start] = true;
    		search(nums, path, visit);
    		path.remove(path.size() - 1);
    		visit[start] = false;
    	}
    }
}
