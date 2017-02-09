Hash Table (直接保存string的缺陷：对每一个不同的10 letter子串都要保存在map中，内存爆炸！！！)
思想：记录从前往后每个10 letter子串的出现次数，当cur子串出现次数==2时，在res中记录当前子串
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        int length = s.length();
        vector<string> res;
        unordered_map<string,int> substr_num;
        for(int i=0;i<=length-10;i++){
            string temp = s.substr(i,10);
            if(substr_num.find(temp) == substr_num.end()){
                substr_num[temp] = 1;
            }
            else{
                if(substr_num[temp] == 1){
                    res.push_back(temp);
                }
                substr_num[temp]++;                
            }
        }
        return res;
    }
};


位运算(在map中保存 10 letter substr转化成的int)

The main idea is to store the (substring as int) in map to bypass the memory limits.

There are only four possible character A, C, G, and T, but I want to use 3 bits per letter instead of 2.

Why? It's easier to code.

A is 0x41, C is 0x43, G is 0x47, T is 0x54. Still don't see it? Let me write it in octal(八进制).

A is 0101, C is 0103, G is 0107, T is 0124. The last digit in octal are different for all four letters. That's all we need!

We can simply use s[i] & 7(111) to get the last digit which are just the last 3 bits, it's much easier than lookup table or switch or a bunch of if and else, right?

We don't really need to generate the substring from the int. While counting the number of occurrences, we can push the substring into result as soon as the count becomes 2, so there won't be any duplicates in the result.


核心思想：将A,C,G,T转化成int作为map的key，由于这四个字母转化成八进制数后的last digit都不一样，所以只需要存储字母4位八进制数
的1个last digit 对应的3位二进制数即可(通过s[i]&7获得)。算法：首先记录前10个字符的last digit的最后3字符对应的30位二进制数temp，并在map中记录temp出现的次数。
然后在通过temp&3FFFFFFF移除temp的最左侧3位数(即将最高3位置为0)，然后将next 新字符的最后3字符计算出后附在temp最后方，即temp<<3,temp|=(s[i++]&7)

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int,int> str_num;
        vector<string> res;
        int i,temp,length;//temp用来记录当前s[i]的 3*10 bit 数字位
        i = temp = 0;
        length = s.length();
        if(length <= 10){
            return res;
        }
        //由于A,C,G,T转化成 八进制数字后，它们的后3位并不同，所以考虑将10 letter子串的每个letter 转换成 八进制数字，然后取每个letter八进制数last digit对应的 3位二进制数即可
        while(i<=9){//获得first 10 letter substr的 3*10 bit 八进制数字
            temp = temp<<3;//temp：0->000->(1st char 的last digit:3 bits)000->(1st char 的last digit)(2nd char的last digit:3 bits)000->...
            temp |= (s[i++] & 7);//s[i] & 7(八进制的7对应二进制 000 000 000 111) 是为了获取s[i]的last digit对应的3位二进制数，
            //由于temp每次左移3位在末尾新增3个0，所以temp|=(3位二进制数)相当于在temp末尾附上s[i]last digit对应的3位二进制数，
        }

        while(true){
            /*
            if(str_num[temp = temp<<3 & 0x3FFFFFFF | s[i++]&7]++ == 1){
                res.push_back(s.substr(i-10,10));
            }
             */
            //以下代码可以直接简写成上方的形式(好好学学！)
            if(str_num[temp]++ == 1){
                res.push_back(s.substr(i-10,10));
            }
            
            if(i == length){
                break;   
            }
            temp = temp<<3;//temp每次左移3位,(10个char的last digit对应的3位二进制数 后面新增3个0)，即 (30 bits)000
            temp = temp & 0x3FFFFFFF;//0x开头的是十六进制常数，这句代码的作用是删除temp的首字母，即删除当前30位二进制数 的 first 3 bits
            //3 F FFFFFF = (11 1111...)，即30个1  temp = (30 bits)000 & 000(30个1) = 000(27 bits)000 = (27 bits)000
            temp |= (s[i++] & 7);//将代表此时s[i] last digit的3位二进制数附在temp末尾
        }
        return res;
    }
};