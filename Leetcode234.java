public class Leetcode234 {
    public class ListNode {
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
        }
    }
    /**
     * Definition for singly-linked list.
     * public class ListNode {
     *     int val;
     *     ListNode next;
     *     ListNode(int x) { val = x; }
     * }
     * 1. 将前半部分列表 与 reverse(后半部分列表) 顺序比较，如果相等则为回文列表
     * 2. 利用快慢指针找到mid节点，通过从preDummyHead开始遍历，
     *    可以保证节点数为偶数n时，slow节点最终处于第n/2 - 1个节点；节点数为奇数n时，slow节点最终处于第 n/2 个节点，方便对后半列表以“头插法”reverse
     */
    class Solution {
        public boolean isPalindrome(ListNode head) {
            if (null == head || null == head.next) {
                return true;
            }
            ListNode preNode1 = new ListNode(-1);
            preNode1.next = head;
            ListNode slow = preNode1, fast = preNode1;
            while (fast != null && fast.next != null) {
                slow = slow.next;
                fast = fast.next.next;
            }
            ListNode preNode2 = new ListNode(-1);
            preNode2.next = slow.next;
            // 断开前半列表 与 后半列表
            slow.next = null;
            reverseList(preNode2, preNode2.next);
            while (preNode1 != null && preNode2 != null) {
                // System.out.println(preNode1.val + ", " + preNode2.val);
                if (preNode1.val != preNode2.val) {
                    return false;
                }
                preNode1 = preNode1.next;
                preNode2 = preNode2.next;
            }
            return true;
        }

        private void reverseList(ListNode preNode, ListNode head) {
            // 需要从第2个节点开始头插，如果从head开始会导致head.next指向自身
            if (null == head) {
                return;
            }
            ListNode temp = null, reverseNode = head.next;
            while (reverseNode != null) {
                temp = reverseNode.next;
                reverseNode.next = preNode.next;
                preNode.next = reverseNode;
                reverseNode = temp;
            }
            // 头插法结束后，head.next仍然指向之前的第2个节点，而它实际上是尾节点了，所以让它的next指向空
            head.next = null;
        }
    }
}
