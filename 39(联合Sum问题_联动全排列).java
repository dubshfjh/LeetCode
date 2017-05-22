候选者中的每个元素可以选择1-任意次，但不能有重复解，近似47题去重复的全排列Version2 中：每层从[0...,n-1]选择1个数字作为path的第i个元素，但是兄弟节点不能取值相同，而且子节点不能取比父节点小的元素。e.g. [1,2] 选择后 不能再选 [2,1]

与全排列思想的区别：

1.无重复元素的全排列中每个节点都可以取当前递归路径中祖先节点下标之外的全部元素 1,2,3;2,1,3，每个取值都会在每个下标出现； 如果有重复元素，则在本次递归的路径中也会出现 下标不同 but 取值相同的情况 E.g. 1,1,2;2,1,1
    
    Subsets & 联合Sum中，[1,2,3] 和 [2,1,3]属于重复元素，因此 递归路径中 当前节点的Value 必须 >= 祖先节点的Value，可以通过 (数组升序排序 & 子节点 startIndex >=祖先节点startIndex)控制
    
    联合Sum中：子节点不能取比父节点小的元素，只能取 >= 父节点的元素，于是 控制子节点的起始元素位置为本层选择元素的下标 i (not i + 1 because we can reuse same elements , 也不是startIndex+1！！！)    
    兄弟节点(即path中当前位置元素的另一种选择)不能取值为[i]

2.全排列的终止条件为 path.size()==n; combinationSum的终止条件为： Sum(path) >= target

public class Solution {
    List<List<Integer>> res;
    
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        res = new ArrayList<List<Integer>>();
        if(candidates.length == 0){
            return res;
        }
        Arrays.sort(candidates);
        List<Integer> path = new ArrayList<Integer>();
        helpCombination(candidates,target,path,0);
        return res;
    }

    void helpCombination(int[] candidates, int remain, List<Integer> path, int startIndex){
        if(remain <= 0){
            if(remain == 0){
                res.add(new ArrayList<>(path));
            }
            return;
        }
        for(int i=startIndex;i<candidates.length;i++){//E.g.输入的每个[i]互不相等， 本层选了[i]之后，子元素可以选择 >=[i]的元素；兄弟节点(即path中当前位置元素的另一种选择)不能取值为[i]
            /*由于本题中 candidates[] 不存在相等元素，本层的兄弟节点 不需要跳过之前已选择的元素
            if(i>startIndex && nums[i]==nums[i-1]){
                continue;
            }
            */
            path.add(candidates[i]);
            helpCombination(candidates,remain-candidates[i],path,i);// not i + 1 because we can reuse same elements
            path.remove(path.size()-1);
        }
    }
}


    /* Wrong Answer：会在选择了[1,2] 后 再出现选择[2,1]的情况
    void helpCombination(int[] candidates, int target, List<Integer> path, int sum){
        if(sum >= target){
            if(sum == target){
                res.add(new ArrayList<>(path));
            }
            return;
        }
        for(int i=0;i<candidates.length;i++){
            if(i>0 && nums[i]==nums[i-1]){
                continue;
            }
            
            path.add(nums[i]);
            helpCombination(candidates,target,path,sum+nums[i]);
            path.remove()
        }
    }
    */