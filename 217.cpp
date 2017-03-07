class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        map<int,int> visited;
        for(int i=0;i<nums.size();i++){
            if(visited[nums[i]]){
                return  true;
            }
            visited[nums[i]] = 1;
        }
        return false;
    }
};


C++ set集合容器：实现了红黑树的平衡二叉检索树的数据结构，插入元素时，它会自动调整二叉树的排列，把元素放到适当的位置，以保证每个子树根节点键值大于左子树所有节点的键值，小于右子树所有节点的键值；另外，还得保证根节点左子树的高度与右子树高度相等。
平衡二叉检索树使用中序遍历算法，检索效率高于vector、deque和list等容器，另外使用中序遍历可将键值按照从小到大遍历出来。
构造set集合主要目的是为了快速检索，不可直接去修改键值。

常用操作：
1.元素插入：insert()
2.中序遍历：类似vector遍历（用迭代器）
3.反向遍历：利用反向迭代器reverse_iterator。
  例：
    set<int> s;
    ......
    set<int>::reverse_iterator rit;
    for(rit=s.rbegin();rit!=s.rend();rit++)
4.元素删除：与插入一样，可以高效的删除，并自动调整使红黑树平衡。
            set<int> s;
            s.erase(2);        //删除键值为2的元素
            s.clear();
5.元素检索：find()，若找到，返回该键值迭代器的位置，否则，返回最后一个元素后面一个位置。
            set<int> s;
            set<int>::iterator it;
            it=s.find(5);    //查找键值为5的元素
            if(it!=s.end())    //找到
                cout<<*it<<endl;
            else            //未找到
                cout<<"未找到";
6.自定义比较函数
    (1)元素不是结构体：
        例：
        //自定义结构体myComp的构造函数符号"()",重载“（）”操作符
        struct myComp//
        {
            bool operator()(const your_type &a,const your_type &b)
            {
                return a.data-b.data>0;
            }
            
        };
        set<int,myComp>s;
        ......
        set<int,myComp>::iterator it;
    (2)如果元素是结构体，可以直接将比较函数写在结构体内。
        例：
        struct Info
        {
            string name;
            float score;
            //重载“<”操作符，自定义排序规则
            bool operator < (const Info &a) const
            {
                //按score从大到小排列
                return a.score<score;
            }
        };
        set<Info> s;
        ......
        set<Info>::iterator it;


利用set容器的"红黑树(即平衡二叉排序树)"上每个节点的key值唯一特性，将vector转换为set后检查：是否有取值重复(即节点key值重复)的元素被删除了
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return nums.size() > set<int>(nums.begin(), nums.end()).size();
    }
};