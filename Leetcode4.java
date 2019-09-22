public class Leetcode4 {
    private Solution solution;
    public Leetcode4() {
        solution = new Solution();
    }

    class Solution {
        public double findMedianSortedArrays(int[] nums1, int[] nums2) {
            if (null == nums1 || 0 == nums1.length) {
                return findMedianInOneArray(nums2);
            }
            if (null == nums2 || 0 == nums2.length) {
                return findMedianInOneArray(nums1);
            }
            int totalLen = nums1.length + nums2.length;
            if (totalLen % 2 == 0) {
                return 0.5 * (getKthElement(nums1, 0, nums2, 0, totalLen / 2) +
                        getKthElement(nums1, 0, nums2, 0, totalLen / 2 + 1));
            } else {
                return 1.0 * getKthElement(nums1, 0, nums2, 0, totalLen / 2 + 1);
            }
        }

        private double findMedianInOneArray(int[] nums) {
            int length = nums.length;
            if (length % 2 == 0) {
                return 0.5 * (nums[length / 2 - 1] + nums[length / 2]);
            }
            return 1.0 * nums[length / 2];
        }

        /**
         * 从nums1[start1...]，nums2[start2...]中，寻找全局第k小的元素（k=1,2...n-1）
         * 核心：假设nums1，nums2各贡献了 k/2 个元素，则比较 nums1[start1 + k/2]，nums2[start2 + k/2]
         * 一、假设二者各自都还能贡献 k/2 个元素
         * 1. nums1[start1 + k/2 - 1] 较小，说明nums1需要贡献的元素数 > k/2个，因此“全局第k小的元素”，必然不在 nums1[start1...start1 + k/2 - 1]中
         *    可以直接尝试在 nums1[start1 + k/2...]，nums2[start2...]中寻找 全局第 k/2 小的元素
         * 2. nums1[start1 + k/2 - 1] 较大，说明nums2需要贡献的元素数 > k/2个，直接尝试在 nums1[start1...]，nums2[start2 + k/2...]中寻找 k/2 个元素
         * 3. 二者相等，则任意选择nums1，nums2 贡献k/2个元素
         *
         * 二、如果有1个数组，已经不能再贡献 k/2 个元素
         * 则“较长的另1个数组”，贡献的元素数必然 > k/2，因此尝试在 较短数组[start]，较长数组[start + k/2]中寻找 k/2 个元素
         * @param nums1
         * @param start1
         * @param nums2
         * @param start2
         * @param k
         * @return
         */
        public int getKthElement(int[] nums1, int start1, int[] nums2, int start2, int k) {
            if (start1 >= nums1.length) {
                return nums2[start2 + k - 1];
            }
            if (start2 >= nums2.length) {
                return nums1[start1 + k - 1];
            }
            int tryElementNum = k / 2, nums1MidValue = Integer.MIN_VALUE, nums2MidValue = Integer.MIN_VALUE;
            if (tryElementNum == 0) {
                return Math.min(nums1[start1], nums2[start2]);
            }
            if (start1 + tryElementNum - 1 < nums1.length) {
                nums1MidValue = nums1[start1 + tryElementNum - 1];
            }
            if (start2 + tryElementNum - 1 < nums2.length)  {
                nums2MidValue = nums2[start2 + tryElementNum - 1];
            }
            if (nums1MidValue == Integer.MIN_VALUE || nums2MidValue == Integer.MIN_VALUE) {
                // 此时只有1个数组的贡献元素数 > k/2 ，让它直接贡献 k/2 个元素
                return nums1MidValue == Integer.MIN_VALUE
                        ? getKthElement(nums1, start1, nums2, start2 + tryElementNum, k - tryElementNum)
                        : getKthElement(nums1, start1 + tryElementNum, nums2, start2, k - tryElementNum);
            }
            if (nums1MidValue < nums2MidValue) {
                // 此时nums1贡献的元素数将 > k/2
                return getKthElement(nums1, start1 + tryElementNum, nums2, start2, k - tryElementNum);
            } else {
                // 此时nums2贡献的元素数将 > k/2
                return getKthElement(nums1, start1, nums2, start2 + tryElementNum, k - tryElementNum);
            }
        }
    }

    public static void main(String[] args) {
        int[] nums1 = {};
        int[] nums2 = {1};
        Leetcode4 leetcode4 = new Leetcode4();
        System.out.println(leetcode4.solution.findMedianSortedArrays(nums1, nums2));
    }
}
