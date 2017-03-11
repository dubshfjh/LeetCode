|i-j|<=k, |nums[i]-nums[j]|<=t
利用bucket的概念，每个bucket大小设置为t+1。在分析元素nums[i]时，考虑nums[i]可能为负数
    设置bucket编号为 (nums[i]-INT_MIN)/(t+1)。满足要求的相邻元素为：
1.同一个bucket中的元素，就算该bucket中的t个元素都不相等，这些元素也必然与nums[i]距离小于t
2.最多也只能出现在相邻的左/右bucket中，而且nums[i]与邻居bucket中最新元素的距离<=t

"尚未理解透彻："由于每个元素i的桶编号是根据nums[i]/(t+1)来决定的，所以每个bucket中只需要保存最新处于该桶范围内的元素即可
于是，将nums[i]所处bucket中的元素新增/更新为nums[i]("只会执行新增操作，原因如下")

真实原因：当nums[i]在自己的bucket有元素 or 在左右bucket有距离<=t的元素，则已经找到了题意要求的邻居并return true了；
    map.put(bucket,remappedNum)这句"更新当前bucket内元素为nums[i]"的语句，只会在当前bucket为空&&左右无适合邻居时才执行
    因此，它的实际操作就是往空的bucket中插入nums[i]这仅有的元素

PS:由于nums中可能有负值元素，所以将 (nums[i]-INT_MIN)/(bucket_size)作为所属bucket编号

As a followup question, it naturally also requires maintaining a window of size k. When t == 0, it reduces to the previous question so we just reuse the solution.

Since there is now a constraint on the range of the values of the elements to be considered duplicates, it reminds us of doing a range check which is implemented in tree data structure and would take O(LogN) if a balanced tree structure is used, or doing a bucket check which is constant time. We shall just discuss the idea using bucket here.

Bucketing means we map a range of values to the a bucket. For example, if the bucket size is 3, we consider 0, 1, 2 all map to the same bucket. However, if t == 3, (0, 3) is a considered duplicates but does not map to the same bucket. This is fine since we are checking the buckets immediately before and after as well. So, as a rule of thumb, just make sure the size of the bucket is reasonable such that elements having the same bucket is immediately considered duplicates or duplicates must lie within adjacent buckets. So this actually gives us a range of possible bucket size, i.e. t and t + 1. We just choose it to be t and a bucket mapping to be num / t.

Another complication is that negative ints are allowed. A simple num / t just shrinks everything towards 0. Therefore, we can just reposition every element to start from Integer.MIN_VALUE.

Edits:

Actually, we can use t + 1 as the bucket size to get rid of the case when t == 0. It simplifies the code. The above code is therefore the updated version.
上述思想的java版
public class Solution {
    public boolean containsNearbyAlmostDuplicate(int[] nums, int k, int t) {
        if (k < 1 || t < 0) return false;
        Map<Long, Long> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            long remappedNum = (long) nums[i] - Integer.MIN_VALUE;
            long bucket = remappedNum / ((long) t + 1);
            if (map.containsKey(bucket)
                    || (map.containsKey(bucket - 1) && remappedNum - map.get(bucket - 1) <= t)
                        || (map.containsKey(bucket + 1) && map.get(bucket + 1) - remappedNum <= t))
                            return true;
            if (map.entrySet().size() >= k) {
                long lastBucket = ((long) nums[i - k] - Integer.MIN_VALUE) / ((long) t + 1);
                map.remove(lastBucket);
            }
            map.put(bucket, remappedNum);
        }
        return false;
    }
}

结合 推广到 |i-j|<=k, |nums[i]-nums[j]|<=t 的问题上，思想应该转换：设置一个set<long long> window有序地存储数组中所有元素
    对于每个元素[i]：保持window中只存放[i-k...i-1]这k个元素，当window.size()>k时，从set中erase nums[i-k-1]
    2.寻找它在set中的最小上界upper，检查是否满足(upper!=window.end() && *upper<=nums[i]+t)
    3.寻找它在set中的最大下界lower,当upper!=window.begin()时,lower=upper-1，检查是否满足(low!=window.end() && *lower>=nums[i]+t)
    4.在set中插入nums[i]

C++版，使用set排序式地存储元素，从左到右分析元素nums[i]，每次都尝试移除set[i-k-1]，并为每个nums[i]寻找 >=nums[i]的最小上界high，检测high与nums[i]的距离是否<=t；然后high--分析 <=nums[i]的最大下界，检测最大下界与nums[i]的距离是否<=t
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<long long> window;
        if(k == 0){
            return false;
        }
        for(int i=0;i<nums.size();i++){
            long long cur_val = nums[i];
            if(!window.empty()){
                if(window.size() > k){//保持窗口中只有与当前i距离在k以内的元素
                    window.erase(nums[i-k-1]);
                }
                //higher points to smallest element bigger or equal to val
                auto high_bound = window.lower_bound(cur_val);
                if(high_bound != window.end() && *high_bound<=cur_val+t){
                    return true;
                }

                if(high_bound != window.begin()){
                    auto low_bound = --high_bound;// low_bound points to biggest element smaller than val
                    if(low_bound!=window.end() && *low_bound>=cur_val-t){
                        return true;
                    }
                }
            }
            window.insert(cur_val);
        }
        return false;
    }
};