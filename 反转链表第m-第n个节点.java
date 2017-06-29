/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
旧版头插法，问题1：由于忘记将mNode指向“头插链表”的下一个节点，
问题2：使用nPost维护nNode的下一个节点时，把它的位置放错了。"没有做到BugFree"
问题3：旧版有缺陷，每次头插一个节点都需要修改preM.next，不够优雅
public class Solution {
    public ListNode reverseBetween(ListNode head, int m, int n) {
        if(head==null || head.next==null || m>=n){
            return head;
        }
        ListNode pre = new ListNode(0);
        pre.next = head;
        head = pre;
        for(int i=1;i<m;++i){
            head = head.next;
        }
        ListNode mPre = head;
        ListNode mNode = mPre.next;
        ListNode nNode = mNode.next;
        ListNode nPost = nNode;
        // ListNode nPost = nNode.next;
        for(int i=m;i<n;++i){
            nPost = nNode.next;
            nNode.next = mPre.next;
            mPre.next = nNode;
            nNode = nPost;
            //nPost = nPost.next; //由于nPost为被翻转节点的next节点，如果写在此处，当n取值为链表长度，在反转完最后一个节点后： nPost = null.next，空指针异常

        }
        mNode.next = nPost;//之前居然忘记要把“头插链表”的尾节点mNode处理，必须让它指向第n+1个节点，否则就成循环链表了
        return pre.next;
    }
}


新版头插法：mPre维护第 m-1 个节点，mNode维护“头插链表”部分的尾节点，nNode维护“头插链表”的 头节点(即始终保持 nNode = mPre.next)，nNode不停地被更新为 头插的节点nPost
在对 所有 nPost 节点执行头插操作以后，需要执行2步操作：
1.将“头插链表” 的尾节点 mNode指向第 n+1 个节点，避免 mNode 仍然指向 它在 reverse后链表的前一个节点
2. 由于优雅头插没有对mPre.next进行更新， 此时的 mPre仍然指向 mNode，所以更新 mPre 指向“头插链表”的头节点 nNode

public class Solution {
    public ListNode reverseBetween(ListNode head, int m, int n) {
        if(head==null || head.next==null || m>=n){
            return head;
        }
        ListNode pre = new ListNode(0);
        pre.next = head;
        head = pre;
        for(int i=1;i<m;++i){
            head = head.next;
        }
        ListNode mPre = head;
        ListNode mNode = mPre.next;

        ListNode nNode = mNode;
        ListNode nPost = nNode.next;

        for(int i=m;i<n;i++){
            ListNode temp = nPost.next;
            nPost.next = nNode;
            nNode = nPost;
            nPost = temp;
        }

        mNode.next = nPost;
        mPre.next = nNode;
        return pre.next;
    }
}