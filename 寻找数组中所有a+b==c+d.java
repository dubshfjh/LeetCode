这个题目与 Four Sum 问题没有任何共同之处，哪怕数组元素无重复！！！！！原因和test case见下方
Four Sum中 为了避免 1. 一个元素使用多次 or 2. 数组中存在处于不同位置的相同元素，还是得老老实实
for(i=0...n-1){
    for(j=i+1...n-1){
        start = j+1;
        end = n-1;
        while(start < end){

        }
    }
}

曾经天真地用它来尝试 Four Sum 问题
[1,0,-1,-2,2]
target: 0
Answer is：[[1,0,1,-2],[1,0,0,-1],[0,-2,0,2],[1,2,-1,-2],[1,-1,-2,2]]

[1,0,1,-2]原因：{[0],[1]} 组合 {[0],[3]}， 但是 [0]+[1] == [0]+[3]
[1,0,0,-1]原因：{[0],[1]} 组合 {[1],[2]}，但是 [0]+[1] == [1]+[2] 
'''误区在于 a+b == c+d 从来没要求是4个元素啊, 只要{a,b}是两个不同元素；{c,d}是两个不同元素；以及不出现{[0],[1]}=={[1],[0]} 即可
这3点通过 for(i=0...n-1)
            for(j=i+1...n-1)
使得 j>i 避免了 分析完 {0,1} 后 又分析 {1,0}的情况，因为只存在 {0,1/2/...n-1} 和 {1,2/3/.../n-1} 这类组合
'''


如果数组中无重复元素 求解 a+b == c+d ，将任意 [i]+[j] 作为key,（i,j）作为value
则对于每一对 (i,j)，
1. 如果 !(HashMap.containsKey(target-([i]+[j])))，则向HashMap中添加 [i]+[j] 映射 {i,j}
2. 如果 HashMap 已包含 target-([i]+[j])，则该元素的 value 与 当前 {i,j} 构成 四元组


class Pair{
    int i,j;
    public Pair(int i,int j){
        this.i = i;
        this.j = j;
    }
}
public class Solution {
    public List<List<Integer>> findABCD(int[] nums) {
        Map<Integer,Pair> record = new HashMap<Integer,Pair>();
        List<List<Integer>> res = new ArrayList<List<Integer>>();
        for(int i=0;i<nums.length-1;i++){
            for(int j=i+1;j<nums.length;j++){
                int comple = nums[i]+nums[j];
                if(!record.containsKey(comple)){
                    record.put(nums[i]+nums[j],new Pair(nums[i],nums[j]));
                }
                else{
                    Pair complePair = record.get(comple);
                    List<Integer> temp = new ArrayList<Integer>();
                    temp.add(complePair.i);
                    temp.add(complePair.j);
                    temp.add(nums[i]);
                    temp.add(nums[j]);
                }
            }
        }
        return res;
    }
}
