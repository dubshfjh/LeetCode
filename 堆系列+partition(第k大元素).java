大trick！！！由于pivot最终是需要与1个">[pivot]的数字"作交换的，所以提前使用[high]对pivot进行备份
使用2个指针：i负责遍历数组(low为初值)，j负责维护不满足要求(此处要求为>pivot)的队列头部(low为初值)

Partition在算法导论上的写法(首先选择 pivotIndex，然后通过swap(nums[pivotIndex], nums[high]))来备份nums[pivotIndex]
1. 当i遇到不满足要求(>pivot)的元素，直接continue分析next
2. 当i遇到满足要求(<=pivot)的元素，则swap(nums[i], nums[j])，j++
3. 当i遍历完所有元素后，j为">pivot"的队列"头部"元素，将它与 pivot 互换位置，使得pivot分割左右2个队列
class Solution {
    /*
     * @param k : description of k
     * @param nums : array of nums
     * @return: description of return
     */
    private Random random = new Random();

    public int kthLargestElement(int k, int[] nums) {
        // write your code here
        if (k == 0) {
            return 0;
        }
        return calKthMax(nums, k, nums.length);
    }
    
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
    
    private int calKthMax(int[] nums, int k, int n) {
        if (k <= 0 || k > n) {
            return Integer.MIN_VALUE;
        }
        int index = n - k; //升序序列中第 n - k + 1个数字，它在升序后的序列中下标为 n - k
        return partition(nums, index, 0, n - 1);
    }

    private int partition(int[] nums, int k, int low, int high) {
        if (low > high) {
            return Integer.MIN_VALUE;
        }
        int pivotIndex = low + random.nextInt(high - low);
        swap(nums, pivotIndex, high);
        int i = low;
        int j = low; //i负责遍历数组, j负责维护不满足要求的队列头部
        //大trick！！！由于pivot最终是需要与1个">[pivot]的数字"作交换的，所以提前使用[high]对pivot进行备份
//        for (i = low + 1; i <= high; i++) {
        for (; i < high; i++) { //high为pivot的备份
            if (nums[i] <= nums[high]) {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
                j++;
            }
        }
        //此时j为">pivot"的队列"头部"元素，将它与 pivot 互换位置，使得pivot分割左右2个队列
        swap(nums, j, high);
        if (j == k) {
            return nums[j];
        } else if (j < k) {
            return partition(nums, k, j + 1, high);
        } else {
            return partition(nums, k, low, j - 1);
        }
    }

    // public static void main(String[] args) {
    //     int[] nums = {9,3,2,4,8};
    //     int k = 3;
    //     Solution obj = new Solution();
    //     System.out.println(obj.kthLargestElement(k, nums));
    // }
};

class Solution {
    /*
     * @param k : description of k
     * @param nums : array of nums
     * @return: description of return
     */
    public int kthLargestElement(int k, int[] nums) {
        // write your code here
        if (k == 0) {
            return 0;
        }
        return maxHeapSort(k, nums);
    }

    private int maxHeapSort(int k, int[] nums) {
        buildHeap(nums);
        int size = nums.length;
        for (int i = 1; i < k; i++) {
            swap(nums, 0, size - 1);
            size--; //由于堆顶元素已经被置换到尾部，所以此时数组size必须更新为size-1，否则会导致数组尾部的元素再次被取出作为Heap顶部
            maxHeapAdjust(nums, 0, size);
            //size--;
        }
        return nums[0];
    }

    private void buildHeap(int[] nums) {
        int length = nums.length;
        for (int i = length>>1; i >= 0; i--) {
            maxHeapAdjust(nums, i, length);
        }
    }

    private void maxHeapAdjust(int[] A, int index, int size) {
        int lChild = index * 2 + 1;
        int rChild = lChild + 1;
        while (lChild < size && rChild < size) {
            if (A[lChild] <= A[index] && A[rChild] <= A[index]) {
                break;
            }
            int maxChild = (A[lChild] > A[rChild]) ? lChild : rChild;
            swap(A, index, maxChild);
            index = maxChild;

            lChild = 2 * index + 1;
            rChild = lChild + 1;
        }
        if (rChild < size && A[rChild] > A[index]) {
            swap(A, index, rChild);
        }
        if (lChild < size && A[lChild] > A[index]) {
            swap(A, index, lChild);
        }
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    // public static void main(String[] args) {
    //     int[] nums = {9,3,2,4,8};
    //     int k = 3;
    //     Solution obj = new Solution();
    //     System.out.println(obj.kthLargestElement(k, nums));
    // }
};

