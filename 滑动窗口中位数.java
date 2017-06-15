Given an array of n integer, and a moving window(size k), move the window at each iteration from the start of the array, find the median of the element inside the window at each moving. 
(If there are even numbers in the array, return the N/2 th number after sorting the element in the window. )
public class Solution {
    /**
     * @param nums: A list of integers.
     * @return: The median of the element inside the window at each moving.
     */
    private int leftHeapSize;
    private int rightHeapSize;
    private Queue<Integer> lMaxHeap;
    private Queue<Integer> rMinHeap;
    private Queue<Integer> createHeap(int initSize, Comparator comparator) {
        if (comparator == null) {
            return new PriorityQueue<Integer>(initSize);
        } else {
            return new PriorityQueue<Integer>(initSize, comparator);
        }
    }
    public ArrayList<Integer> medianSlidingWindow(int[] nums, int k) {
        // write your code here
        ArrayList<Integer> res = new ArrayList<>();
        if (k <= 1){ //窗口size == 1，中位数为窗口中第1大的数字，此时不存在左侧堆,也不存在右侧堆
            for (int num : nums) {
                res.add(num);
            }
        } else if (k == 2) {//窗口size==2，中位数为窗口中第1大的数字，此时不存在左侧堆
            for (int i = 0; i < nums.length - 1; i++) {
                res.add(Math.min(nums[i], nums[i + 1]));
            }
        } else if (k >= nums.length) {
            Arrays.sort(nums);
            int oneMedian = (nums.length & 1) == 0 ? nums[(k>>1) - 1] : nums[k>>1];
            res.add(oneMedian);
        } else {
            Comparator revComparator =  new Comparator<Integer>(){
                public int compare(Integer o1, Integer o2) {
                    return o2 - o1;
                }
            };
            if ((k & 1) == 0) {//k为偶数时，第 k/2 大的数字为中位数
                leftHeapSize = (k>>1) - 1;
            } else {//k为奇数时，第 k+1/2 大的数字为中位数
                leftHeapSize = k>>1;
            }
            rightHeapSize = k - 1 - leftHeapSize;
            lMaxHeap = createHeap(leftHeapSize, revComparator); //中位数左侧为更小的数字，为它们建立大顶堆（左侧的max 为中位数替补）；
            //同理为右侧的更大数字建立小顶堆(右侧的min为中位数替补)
            rMinHeap = createHeap(rightHeapSize, null);
            res = getMedianList(nums, k);
        }
        return res;
    }
    private ArrayList<Integer> getMedianList(int[] nums, int k) {
        //初始化两个堆以及中位数
        ArrayList<Integer> res = new ArrayList<>();
        int median = nums[0];
        for (int i = 1; i < nums.length; i++) {
            if (i >= k) {//此时需要移动滑动窗口的左边界，即移除nums[i - k]
                res.add(median);
                if (nums[i - k] > median) {
                    rMinHeap.remove(nums[i - k]);
                } else if (nums[i - k] < median) {
                    lMaxHeap.remove(nums[i - k]);
                } else {//如果要移除的是中位数，则直接将左侧数字的最大值作为新中位数
                    median = lMaxHeap.poll();
                }
            }
            if (nums[i] > median) {
                rMinHeap.offer(nums[i]); //先将新的元素nums[i]插入右侧MaxHeap
                if (rMinHeap.size() > rightHeapSize) {//如果右侧数字过多，则将旧的median挤到左侧Heap,并将右侧Heap最小值作为新的median
                    lMaxHeap.offer(median);
                    median = rMinHeap.poll();
                }
            } else {
                lMaxHeap.offer(nums[i]);
                if (lMaxHeap.size() > leftHeapSize) {
                    rMinHeap.offer(median);
                    median = lMaxHeap.poll();
                }
            }
        }
        res.add(median);
        return res;
    }
    public static void main(String[] args) {
        int[] nums = {1,2,7,8,5};
        int k = 3;
        Solution obj = new Solution();
        List<Integer> res = obj.medianSlidingWindow(nums, k);
        for (int num : res) {
            System.out.println(num);
    }
}

