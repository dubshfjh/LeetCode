分数都是有限/无限循环小数!!!!!
将长整数的除法转化为 1.在res头部记录整数段:（被除数/除数）， 余数初始化为（被除数%除数)  
    2.计算小数位， 余数r*=10，res在尾部记录 (r/除数) ，余数r 更新为 (r mod 除数)  3.循环执行第2步直到余数为 0/余数与之前某一轮的余数相等(即生成无限循环小数)
    "除法计算时，从第一个小数位开始，小数部分(a.000)每往后计算1位，都需要将当前的余数r更新为10*r后，再执行(/除数)的操作"

PS：无限循环小数的特点：从第i轮循的余数r=r_i开始，每次更新余数为10*r，再通过(r mod 除数)计算下一轮余数r_i+1，然后通过r_i+1计算出r_i+2，...
    经过1到多次循环到达第j轮循环时，余数r_j == r_i，则{r_i,r_i+1....r_j-1}这一段取值会从第j轮循环开始再取一次，因此{r_i,r_i+1...r_j-1}就是循环小数段
有限小数的特点，在第i轮循环中的余数r,更新为{10*r,r mod 除数}后，下一轮的余数为0！！例如1/4，余数r分别取值为 1,2,0

使用map记录step 2的每次循环时余数r，当在第i轮循环更新r为(10*r),再更新为下一轮余数(r mode 除数)时，如果在之后的第j轮循环的余数也是r时，
    说明第i轮到第j轮这一段循环中每次计算的{r*=10，res记录的(r/除数) }组合起来就是循环小数位

E.g. 计算14356/13 
1. 整数位为 14356/13 = 1104，余数r初始化为 14356 mod 13 = 4, res赋值为"1104"，由于r!=0，执行res+="."
2. "4"用于计算小数位中的1st位，map记录余数"4"对应的小数开始位(即res.size(),6)，r*=10 =40 ,计算 r/13=(40)/13 = 3，将"3"插入res的末尾，更新 r= rmod13 = 40%13 = 1,
3. "1"用于计算小数位中的2nd位，map记录余数"1"对应的小数开始位(即res.size(),7)，r*=10 =10, 计算 r/13=10/13 = 0，将"0"插入res的末尾，更新 r = rmod13 = 10
4. "10"用于计算小数位中的3rd位，map记录余数"10"对应的小数开始位(即res.size(),8)，r*=10 =100, 计算 r/13=100/13 = 7，将"7"插入res的末尾，更新 r = rmod13 = 9
5. "9"用于计算小数位中的4th位，map记录余数"9"对应的小数开始位(即res.size(),9)，r*=10 =90, 计算 r/13=90/13 = 6，将"6"插入res的末尾，更新 r = rmod13 = 12
6. "12"用于计算小数位中的5th位，map记录余数"12"对应的小数开始位(即res.size(),10)，r*=10 =120, 计算 r/13=120/13 = 9，将"9"插入res的末尾，更新 r = rmod13 = 3
7. "3"用于计算小数位中的6th位，map记录余数"3"对应的小数开始位(即res.size(),11)，r*=10 =30, 计算 r/13=30/13 = 2，将"2"插入res的末尾，更新 r = rmod13 = 4

8. 余数"4"在map中出现过，它对应的小数开始为为6，因此从第2步的上一个余数"4"，到第8步的当前余数"4"之间这一段的计算的(r/13)，就是循环小数位
    1104.(3076920)


class Solution {
public:
    string fractionToDecimal(long int numerator, long int denominator) {//由于除数，被除数取值INT_MIN时，abs(INT_MIN)，int_str(int)，(INT_MIN/-1),(INT_MIN/1)等操作都会overflow，所以必须设置remain,int_part都为long类型，而且int_str()函数的参数类型也必须为long
        string res;
        int i;
        long int remain,int_part;//int_part为结果的整数部分,remain为余数
        map<int,int> remain_decipos;//记录每个余数对应的小数开始位置
        bool pos_flag = true;

        if(denominator == 0){
            return "Error: the denominator is zero!!!";
        }

        if(numerator<0 ^ denominator<0){//除数，被除数不同时<0时为非正数(除了除数为0的情况)
            pos_flag = false;
        }
        if(!pos_flag && numerator!=0){//如果不排除除数为0的情况，则结果会是'-0'
            res += "-";
        }
        numerator = abs(numerator);
        cout<<numerator<<endl;
        denominator = abs(denominator);

        int_part = numerator/denominator;
        res += int_str(int_part);

        remain = numerator % denominator;
        if(remain == 0){//此时没有小数部分
            return res;
        }
        
        res += ".";//如果有小数部分，res补充个小数点字符
        for(;remain!=0;remain%=denominator){//如果结果为有限小数，则在某次循环中余数会更新为0；如果结果为无限循环小数，则第i次循环的余数r_i会与地j次循环的余数r_j取值相同
            if(remain_decipos.find(remain) != remain_decipos.end()){//需要为每个新余数记录 本层小数计算之前 的res.length()，在两个相同余数的i，j循环之间的计算结果{[i],[i+1]...[j-1]}就是循环部分
                int pos = remain_decipos[remain];
                res.insert(pos,1,'(');//在第pos个位置插入“1”个左括号
                res += ")";
                break;
            }
            remain_decipos[remain] = res.length();

            remain *= 10;
            res += int_str(remain/denominator);
        }
        return res;
    }


    string int_str(long int number){
        stringstream buffer;
        buffer<<number;
        return buffer.str();
    }

};