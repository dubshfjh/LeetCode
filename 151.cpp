c++使用一个stack的思想：顺序遍历将每个word存到栈中，再使用space依次连接stack中自顶向下的每个word
    使用下标i顺序遍历s：每次都将i移到first不为space/tab的字符，然后使用下标j从i开始右移到first space/tab字符，if(j > i)则将s.substr(i,j-i)加入栈中，最后 i右移到j处(即i右侧first space/tab字符)
"遇到的坑"：
    1. 当输入的s为""，" "，"  "...时，stack应该为空，所以此时的s为""，如果不加上判断条件s.length()>1就会导致崩溃！！！
    2. 当s长度为1时，s.substr(1)就是它自己(并不能裁剪为"")！！！此时的参数不再是起始下标，而是子串长度，但是当s长度为2时，s.substr(2)就能裁剪为""了...
class Solution {
public:
    void reverseWords(string &s) {
        stack<string> stk;
        int i,j;
        i = 0;
        while(i<s.length()){
            while((s[i]==' '|| s[i]=='\t') && i<s.length()){//i每次都右移到first不为space/tab的字符
                i++;
            }
            for(j=i;j<s.length();j++){//j每次都从i开始右移到first space/tab字符
                if(s[j]==' ' || s[j]=='\t'){
                    break;
                }
            }
            
            if(j>i){
                stk.push(s.substr(i,j-i));//当j==i时,s.substr(i,0)=""也会压入栈中导致到pop栈时s+= " "+""，导致本应该为""的结果变成了" "。
            }
          
            i = j;
        }
        s="";
        while(!stk.empty()){
            //cout<<stk.top()+",,,test"<<stk.size()<<endl;
            s += " "+stk.top();
            stk.pop();
        }
        if(s.length()>1){//当输入的s为""，" "，"  "...时，stack应该为空，所以此时的s为""，如果不加上判断条件s.length()>1就会导致崩溃！！！
            s=s.substr(1);          
        }
        //cout<<s<<",,,another"<<endl;
    }
};


C++放弃使用stack的思想：对于初始字符串"abc def"，首先对每个单独的word进行reverse得到"cba fed"，然后对整体的字符串进行reverse得到最终结果"def abc"
    同时，还必须得调整space的数目，每个word后面只能跟着1个空格，因此可以将原本s中的每个word备份到左侧("s中的空格数目>=正确格式的new s空格数目")，每左移一个word就把这个word reverse
    使用下标i遍历每个单独的word，使用下标left备份调整了后面紧随的空格数目之后的，每个word的first position(从而对每个单独的word进行reverse)。使用下标j记录previous word的最后一个字符的next postion，用来插入一个空格

class Solution {
public:
    void reverseWords(string &s) {
        int i,j,left,length;
        bool firstword = true;
        i = j = 0;
        length = s.length();
        while(true){
            while((s[i]==' ' || s[i]=='\t') && i<length){//i跳过所有的space/tab，从而遍历每个单独的word
                i++;
            }
            if(i == length){
                break;
            }
            if(!firstword){
                s[j++] = ' ';//j记录previous word的最后一个字符的next postion，当i遍历到第2个及以后的单词时，需要在previous word的后面补上one space
            }
            left = j;//left备份调整了后面紧随的空格数目之后的，每个word的first position

            while(s[i]!=' ' && s[i]!='\t' && i<length){//i必然在j的右侧，将从i开始的word左移到从j开始的position上
                s[j++] = s[i++];
            }
            reverse_word(s,left,j-1);//颠倒一个单独的word
            firstword = false;
        }
        s.resize(j);//删除s中last word+space之后的字符，即只留下{0,1...j-1}这前j个字符
        reverse_word(s,0,j-1);
        //cout<<s<<",,,another"<<endl;
    }
    //function to reverse any part of string from left to right (just one word or entire string)
    void reverse_word(string &s,int left,int right){
        char temp;
        while(left < right){
            temp = s[left];
            s[left++] = s[right];
            s[right--] = temp;
        }    
    }
};