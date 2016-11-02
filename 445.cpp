由于Map是类似红黑树的“非线性”存储，而sort方法只能对“线性存储”的容器进行排序。
所以首先将Map<char,int>转存到vector<pair<char,int>>中，然后可以自定义比较函数compare(const pair<char,int>a,..b)，见代码
或者可以自定义一个函数对象
// struct CmpByValue {  
//   bool operator()(const PAIR& lhs, const PAIR& rhs) {//按照value升序排列  
//     return lhs.second < rhs.second;  
//   }  
// }; 
对Map按照Key 和 Value排序的方法参考了日志：http://blog.csdn.net/acidgl8757/article/details/17416439


class Solution {
public:
    typedef pair<char,int> My_Pair;
    static bool compare(const My_Pair& left, const My_Pair& right){//自己定义一个按照value降序排列的compare
        return left.second > right.second;
    }

    string frequencySort(string s) {
        map<char,int> ch_num;
        string res="";
        for(int i=0;i<s.length();i++){
            if(ch_num.count(s[i])==0){
                ch_num.insert(pair<char,int>(s[i],1));
            }
            else{
                // cout<<s[i]<<"..."<<ch_num[s[i]]<<endl;
                ch_num[s[i]]++;
            }
        }
        
        vector<My_Pair> ch_num_vec(ch_num.begin(),ch_num.end());
        sort(ch_num_vec.begin(),ch_num_vec.end(),compare);

        for(int i=0;i<ch_num_vec.size();i++){
            char ch = ch_num_vec[i].first;   
            for(int j=0;j<ch_num_vec[i].second;j++){
                res += ch;
            }
        }
        return res;
    }
};
    // 整体记录了字符出现次数再排序，会超时，必须缩减hash表的规模才行
    // void quicksort(int a[],int left,int right){
    //     if(left>right){
    //         return;
    //     }
    //     int low,high,key;
    //     low = left;
    //     high = right;
    //     key = a[left];

    //     while(low < high){
    //         // cout<<low<<",,,";
    //         while(a[high]>key && low<high){
    //             high--;
    //         }
    //         a[low] = a[high];
    //         index[low] = index[high];

    //         while(a[low]<key && low<high){
    //             low++;
    //         }
    //         a[high] = a[low];
    //         index[high] = index[low];
    //     }
    //     a[low] = key;
    //     index[low] = left;

    //     quicksort(a,left,low-1);
    //     quicksort(a,low+1,right);
    // }
// };