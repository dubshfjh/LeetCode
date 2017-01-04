2
set 2 1
set 1 1
set 2 3
set 4 1 
get 1
get 2

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
题意理解错误1：一个元素固定占1个空间单位，而不是占value个空间单位，set函数需要重新写一份。
题意理解错误2：最近最少访问元素是 最近没被 get/set 的元素，而不单是最近被 set 的元素

class LRUCache{
public:
    map<int,int> m;//key to value
    vector<int> key_visited;//key_visited.begin()存储最少使用的元素
    int surplus_cap;//剩余容量
    LRUCache(int capacity) {
        surplus_cap = capacity;
    }
    
    int get(int key) {
        if(m.find(key) == m.end()){
            return -1;
        }
        else{
            return m[key];
        }
    }
    /*
    void set(int key, int value) {
        //首先判断key是否是已经出现的元素，因为key为新/旧元素时所需空间不一样
        if(m.find(key) == m.end()){//新元素需要value个存储单位
            cout<<"lalal";
            if(surplus_cap >= value){//空间足够
                surplus_cap -= value;
            }
            else{//需要依次排除掉least recently used元素
                while(surplus_cap < value && key_visited.size()>0){
                    surplus_cap += m[key_visited[0]];
                    map<int,int>::iterator it = m.find(key_visited[0]);
                    m.erase(it);
                    key_visited.erase(key_visited.begin());                    
                }
                surplus_cap -= value; 
            }
            m[key] = value;
            //将新元素直接插入到vector末尾
            key_visited.push_back(key);
        }
        else{//旧元素只需要(value-m[key]个元素)
            int need_space = value - m[key];
            if(surplus_cap >= need_space){
                surplus_cap -= need_space;
            }
            else{
                while(surplus_cap < need_space && key_visited.size()>0){
                    surplus_cap += m[key_visited[0]];
                    map<int,int>::iterator it = m.find(key_visited[0]);
                    m.erase(it);
                    key_visited.erase(key_visited.begin());
                }
                surplus_cap -= need_space;
            }
            m[key] = value;
            //将旧元素从现在的位置移到vector的末尾
            vector<int>::iterator old = find(key_visited.begin(),key_visited.end(),key);
            key_visited.erase(old);
            key_visited.push_back(key);
        }
    }
    */
};

int main(){
    int n,key,val;
    char op[3];
    while(true){
        cin>>n;
        if(n<0){
            break;
        }
        LRUCache obj = LRUCache(n);
        while(true){
            cin>>op;
            if(strcmp(op,"set")==0){
                cin>>key>>val;
                cout<<key<<val<<endl;
                obj.set(key,val);
            }
            else if(strcmp(op,"set")==0){
                cin>>key;
                cout<<obj.get(key)<<endl;;
            }
            else{
                break;
            }
        }
    }    
    return 0;
}

通过了测试用例，但是"超时"了
使用一个map存放key和value的对应关系
使用一个vector存储访问元素的记录，vector尾部存放最近访问的元素，vector头部为最近最少访问的元素
改进思路：使用链表存储元素的访问记录

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
class LRUCache{
public:
    map<int,int> m;//key to value
    vector<int> key_visited;//key_visited.begin()存储最少使用的元素,key_visited每次将最新访问的元素push_back
    int surplus_cap;//剩余容量
    LRUCache(int capacity) {
        surplus_cap = capacity;
    }
    
    int get(int key) {
        if(m.find(key) == m.end()){
            return -1;
        }
        else{
            //将key代表的元素移动到 key_visited 的末尾
            vector<int>::iterator it_key = find(key_visited.begin(),key_visited.end(),key);
            key_visited.erase(it_key);
            key_visited.push_back(key);
            return m[key];
        }
    }
    
    void set(int key, int value) {
        //首先要区分key是否为旧元素，如果为旧元素则消耗 0 个空间单位，如果为新元素则消耗 1 个空间单位
        if(m.find(key) == m.end()){//新元素需要1个单位
            if(surplus_cap >= 1){//空间仍然够用
                surplus_cap -= 1;
            }
            else{//需要移除最近最少使用的元素，即 key_visited 的第0个元素
                map<int,int>::iterator it = m.find(key_visited[0]);
                m.erase(it);
                key_visited.erase(key_visited.begin());
                // surplus_cap += 1;
                // surplus_cap -= 1;
            }
            key_visited.push_back(key);
            m[key] = value;
        }
        else{//旧元素不需要新的空间，它主需要将key代表的元素移动到 key_visited 的末尾
            m[key] = value;
            vector<int>::iterator it_key = find(key_visited.begin(),key_visited.end(),key);
            key_visited.erase(it_key);
            key_visited.push_back(key);
        }
//      for(int i=0;i<key_visited.size();i++){
//          cout<<key_visited[i]<<",,,"<<m[key_visited[i]]<<endl;
//      }
    }
    
};


int main(){
    int n,key,val;
    char op[3];
    while(true){
        cin>>n;
        if(n<0){
            break;
        }
        LRUCache obj = LRUCache(n);
        while(true){
            cin>>op;
            if(strcmp(op,"set")==0){
                cin>>key>>val;
                obj.set(key,val);
            }
            else if(strcmp(op,"get")==0){
                cin>>key;
                obj.get(key);
                // cout<<obj.get(key)<<endl;
            }
            else{
                break;
            }
        }
    }
    return 0;
}


"Hash table + List"
Use the new C++11 unordered_map and a list. The good thing about lists is that iterators are never invalidated by modifiers (unless erasing the element itself). 
This way, we can store the iterator to the corresponding LRU queue in the values of the hash map.(即用map存储key与pair<value,list中iterator>的对应关系)
Since using erase on a list with an iterator takes constant time, all operations of the LRU cache run in constant time.

定义List<int>存放key；定义pair<int,List<int>::iterator>存放 value和List的iterator；定义map记录key 和 pair<value,iterator>
1. 定义修改位置函数： 将每次set/get的元素使用 erase+push_front 插入list对象的头部，因此最少最近访问的元素就是list的尾部元素back
2. 定义get函数：对于map中找不到的元素返回-1；对于能找到的元素 先改变位置，再返回 map[key].first
3. 定义set函数：如果key为已存在元素，则首先修改元素位置，然后更新 map[key] = pair(value,List<int>.begin())
                如果key为新元素，if(map.size() == 容量)，则额外需要移除最近最少访问元素：即首先从 map中移除(key == List<int>.back())的项，然后 List<int>.pop_back()，
                                 然后对于(size<容量 or size==容量)的新元素，都需要在 List<int>和map中新增记录，即 List<int>.push_front(key) ，以及在map中新增 pair(value,List<int>.begin())
#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <string.h>
using namespace std;
class LRUCache{
public:
    // My_Map cache;
    // My_List key_visited;//unordered_map.erase(iterator), erase(it_begin(),it.end()),erase(key)
    // int _capacity;
    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int get(int key) {
        My_Map::iterator it = cache.find(key);
        if(it == cache.end()){
            return -1;
        }
        else{
            //将key代表的元素移动到 key_visited 的末尾
            change_pos(it);
            return it->second.first;//it->second为My_pair对象，My_pair.first为value
        }
    }
    
    void set(int key, int value) {
        //首先要区分key是否为旧元素，如果为旧元素则消耗 0 个空间单位，如果为新元素则消耗 1 个空间单位
        My_Map::iterator it = cache.find(key);        
        if(it == cache.end()){//新元素需要1个单位
            if(cache.size() == _capacity){//空间不够用,需要移除最近最少使用的元素，即 key_visited 的back
                int key_del = key_visited.back();
                cache.erase(key_del);
                key_visited.pop_back();
            }
            key_visited.push_front(key);//不管新增元素时，空间是否够用，都需要新增kry元素
        }
        else{//旧元素不需要新的空间，它主需要将key代表的元素移动到 key_visited 的末尾
            change_pos(it);
        }
        //不管元素为新/旧，都需要在map中记录/更新 key->pair(value,iterator)
        cache[key] = {value,key_visited.begin()};
//      for(int i=0;i<key_visited.size();i++){
//          cout<<key_visited[i]<<",,,"<<m[key_visited[i]]<<endl;
//      }
    }

private:
    typedef list<int> My_List;//存放key
    typedef pair<int,My_List::iterator> My_Pair;//存放value和key对应的iterator
    typedef unordered_map<int,My_Pair> My_Map;//存放key->pair<value,iterator>
    
    My_Map cache;
    My_List key_visited;//unordered_map.erase(iterator), erase(it_begin(),it.end()),erase(key)
    int _capacity;
    
    void change_pos(My_Map::iterator it){
        int key = it->first;
        My_List::iterator it_key = it->second.second;
        key_visited.erase(it_key);

        key_visited.push_front(key);
        it->second.second = key_visited.begin();
    }  
};