#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define NEG_ACC 100
#define POS_ACC 100
#define DIGIT(longnum, i) ( (longnum).data[(i)+NEG_ACC] )
void LNsubLN(struct LongNum &ln, struct LongNum subtractment);
void LNmulLN(struct LongNum &ln, struct LongNum multiplier);
void LNaddLN(struct LongNum &ln, struct LongNum addment);
int LNabscmp(const struct LongNum &a, const struct LongNum &b);
int LNcmp(const struct LongNum &a, const struct LongNum &b);
void LNoutput(struct LongNum ln);




int main()
{
    return 0;
}

struct LongNum{
    LongNum(){
    flush();
    }
    void flush(){
        int i;
        for(i=0;i<NEG_ACC+POS_ACC;i++)
            data[i]=0;
        sign = 1;
    }
    
    char inline digit(int i) const {return data[i+NEG_ACC];}
    char data[NEG_ACC+POS_ACC];
    signed char sign;
};




struct LongNum LNinput()
{
    char s[NEG_ACC+POS_ACC+10];
    int i,j,k;
    struct LongNum res;
    cin >> s;
    
    if(s[0]=='-'){
        res.sign = -1;
        i=1;
    }else{
        res.sign = 1;
        i=0;
    }
    

    j = POS_ACC-1;
    for(;i<strlen(s) && s[i]!='.';i++){
        DIGIT(res, j--) = s[i]-'0';
    }
    j++;
    for(k=j;k<POS_ACC;k++)
        DIGIT(res, k-j) = DIGIT(res,k);
        for(k=POS_ACC;k-j<POS_ACC;k++)
            DIGIT(res, k-j) = 0;
            if(s[i]=='.'){
                j=-1;
                for(i++;i<strlen(s);i++)
                    DIGIT(res, j--) = s[i]-'0';
                    }
    return res;
}



void LNoutput(struct LongNum ln)
{
    if(ln.sign == -1)cout << '-';

    int i, j, flag=0;
    for(i=POS_ACC-1;i>=0;i--)
        if( flag || ln.digit(i)!=0 ){
            flag = 1;
            cout << (char)(ln.digit(i)+'0');
        }
    if(!flag)cout << '0';
    j = 0;
    for(i=-NEG_ACC;i<0;i++)
        if(ln.digit(i)!=0){
            j = i;
            break;
        }
    if(j != 0){
        cout << '.';
        for(i=-1; i>=j; i--)
            cout << (char)(ln.digit(i)+'0');
    }
}


struct LongNum toLN(int n)
{
    struct LongNum res;
    if(n<0){
        res.sign = -1;
        n = -n;
    } else res.sign = 1;
        int i=0,p10=1;

        while((p10*10)/10==p10){
            p10*=10;
            i++;
        }
    for(;i>=0;i--){
        DIGIT(res, i) = n/p10;
        n %= p10;
        p10 /= 10;
    }
    return res;
}


int LNabscmp(const struct LongNum &a, const struct LongNum &b)
{
    int i;
    for(i=POS_ACC-1; i>=-NEG_ACC; i--){
        if(a.digit(i)==b.digit(i))continue;
        if(a.digit(i)>b.digit(i))return 1;
        if(a.digit(i)<b.digit(i))return -1;
    }
    return 0;
}


int LNcmp(const struct LongNum &a, const struct LongNum &b)
{
    if(a.sign == 1 && b.sign == -1)return 1;
    if(a.sign == -1 && b.sign == 1)return -1;
    if(a.sign == 1 && b.sign == 1)return LNabscmp(a,b);
    if(a.sign == -1 && b.sign == -1)return -LNabscmp(a,b);
    return 0;
}




void LNaddLN(struct LongNum &ln, struct LongNum addment)
{
    int i,p;
    if(ln.sign == addment.sign){
        p=0;
        for(i=-NEG_ACC;i<POS_ACC;i++){
            p += ln.digit(i) + addment.digit(i);
            DIGIT(ln, i) = p%10;
            p/=10;
        }
    }else{

        if(ln.sign == -1){
            struct LongNum dummy = ln;
            ln = addment;
            addment = dummy;
        }
        int cmp = LNabscmp(ln,addment);
        if(cmp == 0)

            ln.flush();
        else if(cmp > 0){
            addment.sign = 1;
            LNsubLN(ln, addment);
        }else{
            addment.sign = 1;
            LNsubLN(addment, ln);
            ln = addment;
            ln.sign = -1;
        }
    }
}


void LNsubLN(struct LongNum &ln, struct LongNum subtractment)
{
    if(subtractment.sign == -1){
        subtractment.sign = 1;
        LNaddLN(ln, subtractment);
        return;
    }
    
    if(ln.sign == -1){
        ln.sign = 1;
        LNaddLN(ln, subtractment);
        ln.sign = -ln.sign;
        return;
    }
    
    int cmp = LNabscmp(ln, subtractment);
    if(cmp == 0){
        ln.flush();
        return;
    }
    

    if(cmp < 0){
        struct LongNum dummy = ln;
        ln = subtractment;
        subtractment = dummy;
        LNsubLN(ln, subtractment);
        ln.sign = -ln.sign;
        return;
    }
    
    int i, p=0;
    for(i=-NEG_ACC; i<POS_ACC; i++){
        p = ln.digit(i)-subtractment.digit(i)-p;
        DIGIT(ln, i) = (p+10)%10;
        if(p<0)p=1;else p=0;
    }
}


void LNmulLN(struct LongNum &ln, struct LongNum multiplier)
{
    ln.sign *= multiplier.sign;
    int i, j, k, p;
    struct LongNum res;
    
    for(i=-NEG_ACC; i<POS_ACC; i++){
        
        j=-NEG_ACC-i-1;
        if(j<-NEG_ACC)j=-NEG_ACC;
        for(; i+j<POS_ACC && j<POS_ACC; j++){
            p = ln.digit(i) * multiplier.digit(j);
            k = i+j;
            while(p>0 && k<POS_ACC){
                if(k>= -NEG_ACC && k<POS_ACC)
                    DIGIT(res, k) += p%10;
                p /= 10;
                if(DIGIT(res,k) >= 10){
                    p += DIGIT(res,k)/10;
                    DIGIT(res,k) %= 10;
                }
                k++;
            }
        }
    }
    res.sign = ln.sign;
    ln = res;
}


void LNshlLN(struct LongNum &ln, int displacement)
{
    int i;
    struct LongNum res;
    for(i=-NEG_ACC; i<POS_ACC; i++)
        if(
           i-displacement >= -NEG_ACC &&
           i-displacement < POS_ACC
           )
            DIGIT(res, i) = ln.digit(i-displacement);
    ln = res;
}

void LNdivLN(
             struct LongNum &ln, struct LongNum divider)
{
    struct LongNum res, zero;
    res.flush(); zero.flush();
    int res_sign = ln.sign * divider.sign;
    ln.sign = divider.sign = 1;
    int p_ln, p_divider;
    if(LNcmp(ln, zero) == 0) return;
    if(LNcmp(divider, zero) == 0){
        ln.flush();
        return;
    }
    int i, j;
    for(i=POS_ACC-1;i>=-NEG_ACC;i--)
        if(ln.digit(i) != 0){
            p_ln = i;
            break;
        }
    for(i=POS_ACC-1;i>=-NEG_ACC;i--)
        if(divider.digit(i) != 0){
            p_divider = i;
            break;
        }

    i = p_ln - p_divider;
    if(i>POS_ACC) i = POS_ACC-1-p_divider;
    LNshlLN(divider, i);
    struct LongNum tempnum;
    for(;i>-NEG_ACC;i--){
        tempnum.flush();

        j=0;
        do{
            LNaddLN(tempnum, divider);
            j++;
        }while(LNabscmp(tempnum, ln) <= 0);
        LNsubLN(tempnum, divider);
        j--;

        LNsubLN(ln, tempnum);
        DIGIT(res, i) = j;
        
        LNshlLN(divider, -1);
    }
    res.sign = res_sign;
    ln = res;
}



