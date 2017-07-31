class Solution {
    /**
     * @param A: An integer array.
     * @param B: An integer array.
     * @return: a double whose format is *.5 or *.0
     */
    public double findMedianSortedArrays(int[] A, int[] B) {
        // write your code here
        if (A.length == 0 && B.length == 0) {
            return 0;
        }
        int length = (A.length + B.length);
        double res = 0;
        if ((length & 1) == 0) { //长度为4，寻找第 2 个和 第 3 个元素
            int first = findKthLargest(A, 0, B, 0, length>>1);
//            int second = findKthLargest(A, 0, B, 0, 1 + length>>1);

            int second = findKthLargest(A, 0, B, 0, 1 + (length>>1));

//            int second = findKthLargest(A, 0, B, 0, 1 + (length>>1));
            res = first + second;
            res /= 2;
        } else {
            res = findKthLargest(A, 0, B, 0, 1 + length>>1);
        }
        return res;
    }
//    public double findMedianSortedArrays(int A[], int B[]) {
//        int len = A.length + B.length;
//        if (len % 2 == 1) {
//            return findKthLargest(A, 0, B, 0, len / 2 + 1);
//        }
//        return (
//                findKthLargest(A, 0, B, 0, len / 2) + findKthLargest(A, 0, B, 0, len / 2 + 1)
//        ) / 2.0;
//    }



    private int findKthLargest(int[] nums1, int start1, int[] nums2, int start2, int k) { //寻找{nums1 + nums2}升序中第 k 个元素, k从1开始计数
        if (start1 >= nums1.length) {
            return nums2[start2 + k - 1];
        }
        if (start2 >= nums2.length) {
            return nums1[start1 + k - 1];
        }
        if (k == 1) {
            return Math.min(nums1[start1], nums2[start2]);
        } else {
            int midLen = k>>1;
            int numsOneVal = (start1 + midLen - 1 < nums1.length) ? nums1[start1 + midLen - 1] : Integer.MAX_VALUE; //当nums1剩余长度<k/2时，e.g. nums1：{1}；nums2:{1,2...10000}，k = 1000，
            // 则应该在 {1} + {500....}中寻找第 k 个元素
            int numsTwoVal = (start2 + midLen - 1 < nums2.length) ? nums2[start2 + midLen - 1] : Integer.MAX_VALUE;
            if (numsOneVal < numsTwoVal) {
                return findKthLargest(nums1, start1 + midLen, nums2, start2, k - midLen);
            } else {
                return findKthLargest(nums1, start1, nums2, start2 + midLen, k - midLen);
            }
        }
    }

//    public static void main(String[] args) {
//        int[] nums1 = {1,2,3,4,5,6};
//        int[] nums2 = {2,3,4,5};
//        Solution obj = new Solution();
//        System.out.println(obj.findMedianSortedArrays(nums1, nums2));
//    }
}