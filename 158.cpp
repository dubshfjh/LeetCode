'''
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.
'''
思路
因为要调用多次，这里又多了一些corner case：

第一次调用时，如果read4读出的多余字符我们要先将其暂存起来，这样第二次调用时先读取这些暂存的字符
第二次调用时，如果连暂存字符都没读完，那么这些暂存字符还得留给第三次调用时使用

所以，难点就在于怎么处理这个暂存字符。因为用数组和指针控制对第二种情况比较麻烦，且这些字符满足先进先出，所以我们可以用一个队列暂存这些字符。这样，只要队列不为空，就先读取队列。
"由于自己的C++代码没有测试，后附他人的java代码，而且我理解错误了：
赋予空指针temp给read4()函数，函数执行完毕后temp会指向真实字符的head，所以下面的代码并没有让buf指向读取到字符串的head"

Wrong Answer，第2个需求今后再补上(使用指针保持字符串的Head有点麻烦)
class Solution{
    queue<char> exist_ch;//存储上一次read函数中最后一次read4读取出的多余字符
    int read(char *buf, int n) {
        int read4_chnum;
        int ch_read = 0;//记录本轮已读取(不包括存储在队列中的)的字符数
        char *temp;
        if(!exist_ch.empty()){//先读取队列中的元素
            int temp = min(n,exist_ch.size());//temp表示min(队列中存在元素，需要读取元素)
            n -= temp;
            ch_read += temp;//在上一轮往队列中插入元素时，已经将buf右移到这些元素之后了，所以在读取队列元素时不需要再右移buf
            while(temp>0){
                exist_ch.pop();
                temp--;
            }
        }
        if(n == 0){
            return ch_read;
        }

        while(n > 0){
            read4_chnum =  read4(buf);//将原本为空的指针buf传给read4函数，函数执行完后buf指向真实字符串(长度为1-4)的head,read4(buf)返回min(4,buf剩余字符数)
            if(read4_chnum > n){//此时read4从buf中读取的字符数 > 还需要读取的字符数n
                buf += n;//buf先右移n个单位，然后在将read4读出的多余字符存储进入队列的过程中，将buf总共右移"read4已经读取出来的字符数目"个单位
                ch_read += n;//read函数此次只读取了n个字符
                n -= n; 
                for(int i=n;i<read4_chnum;i++){//将read4函数读取的多余字符
                    exist_ch.push(*buf);
                    buf++;
                }
                return ch_read;
            }
            else{//此时read4读取的字符数 <= 还需要读取的字符数，不需要往队列中push元素
                buf += read4_chnum;
                ch_read += read4_chnum;
                n -= read4_chnum;
            }
        }
        return ch_read;
    }
};



public class Solution extends Reader4 {
    Queue<Character> remain = new LinkedList<Character>();

    public int read4(char[] buf,int n){
        int ch_read = 0;
        // 队列不为空时，将队列之前暂存的字符读取回buf中
        while(ch_read<n && !remain.isEmpty()){
            buf[ch_read] = remain.poll();
            ch_read++;
        }

        for(;ch_read<n;ch_read+=4){
            char[] temp = new char[4];//构建空的字符数组
            int read4_chnum = read4(temp);//执行完read4函数后，获得保存了字符的字符数组
            // 如果读到字符多于我们需要的字符，需要暂存这些多余字符,arraycopy(src, srcPos, dest, destPos, length)
            if(read4_chnum > n - ch_read){//将temp的全部字符读取到
                System.arraycopy(temp,0,buf,ch_read,n - ch_read);
                //把多余的字符存在队列中
                for(int j= n - ch_read;j<read4_chnum;j++){
                    remain.offer(temp[j]);
                }
            }
            else{// 如果读到的字符少于我们需要的字符，直接拷贝
                System.arraycopy(temp,0,buf,ch_read,read4_chnum);
            }

            //如果读不满4个，说明数据已经读完，返回min(总所需长度,目前已经读到的长度)
            if(read4_chnum < 4){
                return Math.min(ch_read+read4_chnum, n);
            }
        }
        // 如果到这里，说明每次的read4函数都读取了4个字符，直接返回n
        return n;
    }
};