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
分治法：
1. 递归终止条件：start > end，则返回null；start == end，则返回 lists.get(start)
2. Divide：首先获取左半部分(lists[start..mid])的排序链表头 lHalfHead，然后获取右半部分(lists[mid+1...right])的排序链表头 rHalfHead
3. Conquer：将 lHalfHead 和 rHalfHead mergeTwoLinks

public class Solution {
    /**
     * @param lists: a list of ListNode
     * @return: The head of one sorted list.
     */
    public ListNode mergeKLists(List<ListNode> lists) {  
        // write your code here
        if (lists.size() == 0) {
        	return null;
        }
        return helpMerge(lists, 0, lists.size() - 1);
    }

    private ListNode helpMerge(List<ListNode> lists, int start, int end) {
    	if (start > end) {
    		return null;
    	} else if (start == end) {
    		return lists.get(start);
    	} else {
    		int midIndex = start + ((end - start)>>1);
    		ListNode lHalfHead = helpMerge(lists, start, midIndex);
    		ListNode rHalfHead = helpMerge(lists, midIndex + 1, end);
    		return mergeTwoLinks(lHalfHead, rHalfHead);
    	}
    }

    private ListNode mergeTwoLinks(ListNode left, ListNode right) {
    	ListNode dummy = new ListNode(0);
    	ListNode curNode = dummy;
    	while (left != null && right != null) {
    		if (left.val < right.val) {
    			curNode.next = left;
    			left = left.next;
    		} else {
    			curNode.next = right;
    			right = right.next;
    		}
    		curNode = curNode.next;
    	}
    	if (left != null) {
    		curNode.next = left;
    	}
    	if (right != null) {
    		curNode.next = right;
    	}
    	return dummy.next;
    }
}