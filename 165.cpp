"1.1" < "1.1.1"，"1.1" = "1.1.0.0.0.0.0..."，version1更大则返回1，version更小则返回-1,version==version2则返回0

将两个字符串按照'.'进行分割：使用i,j遍历，将version1,version2 每邻近'.'之间的子串转换成数字num1,num2：
    如果num1<num2则返回-1；如果num1>num2则返回1；如果num1==num2则将i,j移到当前'.'的下一个字符，分析下一对num1,num2直到有1个string遍历完毕
    如果遍历完1个字符串后还未返回，则接着往后分析较长string剩余的邻近'.'之间的数字number，如果剩余的number不全为0，
    则version1为较长串时return 1；version2为较长串时return -1。如果较长串剩余的number全为0，则return 0。

遇到的坑：
    1. struct 不需要再命一个别名；struct 的构造函数中，赋值语句以","分隔，而且位于空括号对{}之前；
        为避免每次声明对象就必须给构造函数显示传参，可以设计一个无参数的默认构造函数
    2. C++的map必须声明模板类的具体类型,例如map<string,string>,在替代class/struct存储变量这方面，不如Java的HashMap那么灵活(至少IBatis中HashMap的模板类是动态的)
    3. "1.1" == "1.1.0.0.0..."
    4. 在从字符串的"."之间获取number时，最后一个number的后方并没有"."，因此调用itoa()函数的条件为(s[i]=='.' || i==length-1)，
        而且再分析最后一个数字(即i==length-1)时，子串为s.substr(pos,i-pos+1)；但对前面的number(即s[i]=='.')，子串为s.subtr(pos,i-pos)
struct Pos_num{
    int pos;//存放当前数字的first char下标
    int number;
    Pos_num(): pos(-1),number(-1) {}
    Pos_num(int x,int y): pos(x),number(y) {}
};

class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i,j,len_1,len_2;
        Pos_num obj1,obj2;
        len_1 = version1.length();
        len_2 = version2.length();
        
        i = j = 0;
        while(i<len_1 && j<len_2){
            obj1 = getnumber(version1,i);
            obj2 = getnumber(version2,j);
            // cout<<obj1.number<<",,,"<<obj2.number<<endl;
            if(obj1.number > obj2.number){//version1版本更新
                return 1;
            }
            else if(obj1.number < obj2.number){
                return -1;
            }
            i = obj1.pos;
            j = obj2.pos;
        }
        //cout<<i<<",,,"<<j<<endl;
        while(i<len_1){
            obj1 = getnumber(version1,i);
            // cout<<"new"<<obj1.number<<endl;
            if(obj1.number != 0){
                return 1;
            }
            i = obj1.pos;
        }
        while(j<len_2){
            obj2 = getnumber(version2,j);
            if(obj2.number != 0){
                return -1;
            }
            j = obj2.pos;
        }
        return 0;
    }

    Pos_num getnumber(string s,int pos){
        Pos_num res;
        for(int i=pos;i<s.length();i++){
            if(s[i]=='.' || i==s.length()-1){
                string temp;
                if(s[i]=='.'){
                    temp = s.substr(pos,i-pos);
                }
                else{//s[i]不为'.'而且i为最后一个字符
                    temp = s.substr(pos,i-pos+1);
                }
                res = Pos_num(i+1,atoi(temp.c_str()));
                break;
            }
        }
        return res;
    }
};