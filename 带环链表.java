快慢指针：龟兔赛跑问题，快慢指针如果能够相遇，则说明链表存在环
踩到的坑：在使用快慢指针时，为减少移动次数而初始化 fast = head.next，因此当链表长度<=1时，必须直接返回结果，
	否则会导致fast初始化为null，然后因为调用null.next而导致runtime error
/**
 * Definition for ListNode.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int val) {
 *         this.val = val;
 *         this.next = null;
 *     }
 * }
 */ 
public class Solution {
    /**
     * @param head: The first node of linked list.
     * @return: True if it has a cycle, or false
     */
    public boolean hasCycle(ListNode head) {  
        // write your code here
        if (head == null || head.next == null) {
            return false;
        }
        ListNode fast = head.next;
        ListNode slow = head;
        while (fast != null && fast.next != null) {
        	if (slow == fast) {
        		return true;
        	}
        	slow = slow.next;
        	fast = fast.next.next;
        }
        return false;
    }
}

