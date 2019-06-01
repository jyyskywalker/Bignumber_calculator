#ifndef _BIGINTEGER_CLASS_HPP
#define _BIGINTEGER_CLASS_HPP
#include <iostream>
#include <string>
#include <vector>
// BIGNUMBER_CALCULATOR.version_1
// 乘法用的是小学算法，除法用的是每次减去开头是1的同位的数
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::istream;

class BigInteger
{
    public:
        Bignumber(string num='', int signal=1){}
        Bignumber(string a){
            if(a[0]=='-'){
                signal = -1;
                num = a.substr(1, a.size()-1);
            }
            else 
                signal = 1;
                num = a;
        }
        friend ostream& operator<<(ostream& out, BigInteger a);
        friend istream& operator>>(istream& in, BigInteger &a);
        BigInteger operator+(const BigInteger &a);
        BigInteger operator-(const BigInteger &a);
        BigInteger operator*(const BigInteger &a);
        BigInteger operator/(const BigInteger &a);
        BigInteger& operator=(const BigInteger &a){
            if(this != &a){
                signal = a.signal;
                num = a.num;
            }
            return *this;
        };

        ~BigInteger() {};
    private:
        string num;
        int signal;
};

BigInteger BigInteger::operator+(const BigInteger &a){    
    BigInteger result,                              // 接着将运算对象的num复制到两个新的string对象里面，使用reverse算法将数字调转
    string temp1 = a.num;                           // 
    string temp2 = this->num;
    string temp_result='';
    int flag=0;
    std::reverse(begin(temp1), end(temp1));
    std::reverse(begin(temp2), end(temp2));
    BigInteger result;
    if(this->signal==-1&&a.signal==1){                     // 首先要判断输入进来的大整数是不是同符号的，如果同符号，则使用-运算符
        this->signal=1;
        return a-*this;
    }
    else if(this->signal==1&&a.signal==-1){
        a.signal=1;
        return *this-a;
    }
    
    int i=0;
    for ( i=0; i<temp1.size()&&i<temp2.size; ++i){   // 这一部分用于进位
        char ch = (temp1[i]+temp2[i]-'0')%10+'0'+flag;
        temp_result.push_back(ch);
        if((temp1[i]+temp2[i])/10==1)
            flag = 1;
        else
            flag=0;
    }
    if(temp1.size()=temp2.size()){
        if(flag=1)
            temp2[i]=1;
    }
    else if(temp1.size()<temp2.size()){
        for(i; i<temp2.size(); ++i){
            temp_result.push_back(temp2[i]+flag);
            flag=0;
        }
    }
    else (temp1.size()>temp2.size()){
        for(i;i<temp1.size; ++i){
            temp_result.push_back(temp1[i]+flag);
            flag = 0;
        }
    }
    std::reverse(begin(temp_result), end(temp_result))
    result.num = temp_result;
    result.signal=a.signal=1?1:-1;
    return result;
}


BigInteger BigInteger::operator-(const BigInteger& a){
    BigInteger result;
    string temp1=this->num;
    string temp2=a.num;
    string temp_result='';
    int sig=1;
    std::reverse(begin(temp1), end(temp1));
    std::reverse(begin(temp2), end(temp2));
    int flag1 = 0;

    if(this->signal==1&&a.signal==-1){          // 这里先处理符号的问题，转化为加法
        a.signal=1;
        return *this+a;
    }
    if(this->signal==-1&&a.signal==1){
        a.signal=-1;
        return *this+a;
    }
                                                // 开始通过大小来计算最后的结果
    if(this->num.size()=a.num.size()){          // 第一种情况
        for (int j=a.size()-1;j>=0;--j){
            if(temp1[j]<temp2[j]){
                string s=temp2;
                temp2=temp1;
                temp1=s;
                sig=-1;
                break;
            }
            else
                break;
        }
        
        for(int i=0; i<a.num.size(); ++i){
            if((temp1[i]-flag1)<temp2[i]){
                temp_result.push_back(temp1[i]-flag1+10-temp2[i]);  // 这里应该要有对最后的数的判断
                flag1=1;
            }
            else
            {
                temp_result.push_back(temp1[i]-flag1-temp[i]);
                flag1=0;
            }    
        }
    }//第二种情况，第一个数的长度大于第二个数的长度
    else if(this->num.size()>a.num.size()){
        sig=this->signal;
        int i=0;
        for(i=0; i<a.num.size(); ++i){
            if((temp1[i]-flag1)<temp2[i]){
                temp_result.push_back(temp1[i]-flag1+10-temp2[i]);
                flag1=1;
            }
            else
            {
                temp_result.push_back(temp1[i]-flag1-temp[i]);
                flag1=0;
            }  
        }
        for(i; i<this->num.size();++i){
            if(temp1[i]-flag1<0){
                temp_result.push_back(temp1[i]+10-flag1);
                flag1=1;
            }
            else{
                temp_result.push_back(temp1[i]-flag1);
                flag1=0;
            }   
        }
    }//第三种情况，第一个数的长度小于第二个数的长度
    else{
        sig=-1*this->signal;
        int i=0        
        for(i=0; i<this->num.size(); ++i){
            if(temp2[i]-flag1<temp1[i]){
                temp_result.push_back(temp2[i]+10-flag1-temp1[i]);
                flag1=1;
            }
            else{
                temp_result.push_back(temp2[i]-flag1-temp1[i]);
                flag1=0;
            }
        }
        for(i; i<a.num.size(); ++i){
            if(temp2[i]-flag1<0){
                temp_result.push_back(temp2[i]+10-flag1);
                flag1=1;
            }
            else{
                temp_result.push_back(temp2[i]-flag1);
                flag1=0
            }
        }
    }
    std::reverse(begin(temp_result), end(temp_result));
    result.signal=sig;
    result.num=temp_result;
    return result;
}

BigInteger BigInteger::operator*(const BigInteger& a){
    BigInteger temp;
    temp.signal=1;
    temp.num='';
    BigInteger result;
    result.signal=1;
    result.num='0';
    result.signal=this->signal*a.signal;
    string temp1=this->num;
    string temp2=a.num;
    std::reverse(begin(temp1), end(temp1));
    std::reverse(begin(temp2), end(temp2));
    
    for (i=0; i<temp1.size(); i++){
        int flag=0;
        for(int j=0; j<i; j++){
            temp.num.push_back('0');
        }
        for (int j=0; j<temp2.size(); j++){
            char ch=((temp1[j]-'0')*(temp2[j]-'0')+flag)%10+'0';
            flag=(temp1[j]-'0')*(temp2[j]-'0')/10;
            temp.num.push_back(ch);
        }
        result=result+temp;
        temp.num='';
    }
    result.signal=sig;
    std::reverse(begin(result.num), end(result.num));
    return result;
}



BigInteger BigInteger::operator/(const BigInteger& a){
    BigInteger temp1.num = this->num;
    temp1.signal = 1;
    BigInteger temp2.num = a.num;
    temp2.signal = 1;
    BigInteger result;
    result.signal=1;
    result.num='0';

    while((temp1-temp2).signal!=-1){
        int t = temp1.num.size()-temp2.num.size;
        BigInteger temp;
        temp.signal = 1;
        temp.num ='1';
        for(int i=0; i<t; i++){
            temp.num.push_back('0');
        }
        result = result+temp;
        temp=temp*temp2;
        temp1=temp1-temp;
    }
    result.signal=temp1.signal*temp2.signal;
    return result;
}

friend ostream& operator<<(ostream& out, BigInteger a){
    if(a.signal==-1){
        out << '-' << a.num << endl;
    }
    else
    {
        out << a.num << endl;
    }
    return out;
}

friend istream& operator>>(istream& in, BigInteger &a){
    string s;
    in >> s;
    if(s[0]=='-'){
        a.signal=-1;
        a.num=s.substr(1,s.size()-1);
    }
    else if(s[0]=='+'){
        a.signal=1;
        a.num=s.substr(1,s.size()-1);
    }
    else{
        a.signal=1;
        a.num=s.substr(1,s.size()-1);
    }
    return in;
}

#endif