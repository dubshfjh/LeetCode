'''
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called one time.
'''
int read(char *buf, int n) {
    int res = 0;
    while(n > 0){//n表示本轮还需要读取的字符数
        int ch_num = min(read4(buf),n);//将原本为空的指针传给read4,当read4函数执行完毕后buf指向真实字符串(长度为1-4)的head, read4(buf)表示min(4,buf剩余的字符数)，在本轮真正需要(能够)读取的字符数：min(read4(buf),n)
        res += ch_num;//res增加本轮read4()读取的字符数
        buf += ch_num;
        if(ch_num < 4){//本轮read4()读取的字符数目<4时，下一轮就不需要读字符了
            break;
        }
        n-=4;
    }
    return res;
}