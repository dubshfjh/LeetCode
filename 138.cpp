/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
与133题"复制无向图"套用几乎同一模板
关键思想：使用一个Map记录原始node和复制node的对应关系(用于判断原始node是否已经创建了复制node)。
    因此一旦创建了复制node，就必须在分析复制node的next和random之前，就在map中记录原始node已经有了复制node(否则会多次创建同一个节点，例如node->random指向本身时)
从head开始递归创建其复制节点，如果本层的head为NULL则递归结束；否则创建head的复制节点temp，并在map中记录map[head]=temp；
然后判断head的next和random是否已经创建过，如果Map中找不到head->next/head->random对应的复制node，则递归创建(head->next)/(head->random)；
如果map中已有记录，则直接将temp的next和random指向map[head->next/head->random]。最后返回temp
class Solution {
public:
    unordered_map<RandomListNode*, RandomListNode*> created;

    RandomListNode *copyRandomList(RandomListNode *head){
        if(head == NULL){
            return head;
        }
        RandomListNode *temp = new RandomListNode(head->label);
        created[head] = temp;
        if(created.find(head->next) != created.end()){
            temp->next = created[head->next];
        }
        else{
            temp->next = copyRandomList(head->next);
        }

        if(created.find(head->random) != created.end()){
            temp->random = created[head->random];
        }
        else{
            temp->random = copyRandomList(head->random);
        }
        return temp;
    }
};