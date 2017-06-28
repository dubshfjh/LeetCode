采用归并的思想，每一层递归地对list[left...right]部分排序，如果left == right，则直接返回唯一的链表；否则中分这段链表子数组,mid=(left+right)>>1
分别递归的对左侧的list[left...mid]，以及右侧的list[mid+1...right]排序，并记录左半排序链表头LHead，以及右半排序链表头RHead，
然后将两段排序链表Merge起来，将整体的链表头作为本层递归结果返回 
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        ListNode head = null;
        if(lists==null || lists.length==0){
            return head;
        }
        head = mergeHelper(lists,0,lists.length-1);
        return head;
    }

    public ListNode mergeHelper(ListNode[] lists,int left,int right){
        if(left==right){
            return lists[left];
        }
        int mid = (left+right)>>1;
        ListNode leftHead = mergeHelper(lists,left,mid);
        ListNode rightHead = mergeHelper(lists,mid+1,right);
        return merge(leftHead,rightHead);
    }

    public ListNode merge(ListNode lHead, ListNode rHead){
        ListNode preHead = new ListNode(0);
        ListNode node = preHead;
        while(lHead!=null && rHead!=null){
            if(lHead.val < rHead.val){
                node.next = lHead;
                lHead = lHead.next;
            }
            else{
                node.next = rHead;
                rHead = rHead.next;
            }
            node = node.next;
        }
        //你居然又忘记把两个链表中尚未合并的那个整体merge起来！！！！
        if(lHead!=null){
            node.next = lHead;
        }
        if(rHead!=null){
            node.next = rHead;
        }
        return preHead.next;
    }
}