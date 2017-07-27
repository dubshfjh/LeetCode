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