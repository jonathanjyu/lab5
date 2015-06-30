#include <iostream>
#include "HugeInt.h"
using namespace std;

ostream & operator<< (ostream & out, const HugeInt & BigNumber)
{
  if(BigNumber.sign=='-'){
    out << BigNumber.sign;
  }

  for(int i=0; i<BigNumber.size; i++){
    out << BigNumber.number[i];
  }
  return out;
}

istream & operator>> (istream & in, HugeInt & BigNumber)
{
  BigNumber.size=0;
  delete [] BigNumber.number;
  string InputNumber;
  in >> InputNumber;
  if (InputNumber.at(0)!='-'){
    BigNumber.size=InputNumber.size();
    BigNumber.number=new int[BigNumber.size];
    BigNumber.sign='\0';
    for(int i=0; i<BigNumber.size; i++){
      BigNumber.number[i]=InputNumber.at(i)-48;
    }
  }
  else {
    BigNumber.size=InputNumber.size()-1;
    BigNumber.number=new int[BigNumber.size];
    BigNumber.sign='-';
    for(int i=0; i<BigNumber.size; i++){
      BigNumber.number[i]=InputNumber.at(i+1)-48;
    }
  }
  return in;
}

HugeInt::HugeInt(string InputNumber)
{
  if(InputNumber.at(0)!='-'){
    size=InputNumber.size();
    number=new int[size];
    sign='\0';
    for(int i=0; i<size; i++){
      number[i]=InputNumber.at(i)-48;
    }
  }
  else {
    size=InputNumber.size()-1;
    number=new int[size];
    sign='-';
    for(int i=0; i<size; i++){
      number[i]=InputNumber.at(i+1)-48;
    }
  }
}

HugeInt::HugeInt(int SmallNumber) // default integer constructor
{
  int getNumSize=SmallNumber;
  if(SmallNumber>=0){
    sign='\0';
  }
  else{
    sign='-';
  }
  size=0;
  while(1){
    size++;
    if(getNumSize/10 == 0){
      break;
    }
    getNumSize/=10;
  }
  number = new int[size];
  int tens=1;
  for(int i=1;i<size;i++){
    tens*=10;
  }
  for(int i=0;i<size;i++){
    number[i]=SmallNumber/tens;
    SmallNumber%=tens;
    tens/=10;
  }
}

HugeInt::HugeInt(HugeInt & CopyHugeInt)
{
  if(sign=='\0'||sign=='-'){
    delete [] number;
  }
  size=CopyHugeInt.size;
  number=new int[size];
  sign=CopyHugeInt.sign;
  for(int i=0; i<size; i++){
    number[i]=CopyHugeInt.number[i];
  }
}

HugeInt HugeInt::operator+ (HugeInt & BigNumber)
{
  HugeInt output;
  int size_tmp=((size>=BigNumber.size)?(size):(BigNumber.size));
  output.size=size_tmp;
  output.number=new int[output.size+1];
  for(int i=0; i<output.size; i++){
    if((size-1-i>=0)&&(BigNumber.size-1-i>=0)){
      output.number[output.size-1-i]=number[size-1-i]+BigNumber.number[BigNumber.size-1-i];
      output.number[output.size-2-i]+=output.number[output.size-1-i]/10;
      output.number[output.size-1-i]=output.number[output.size-1-i]%10;
    }
    else if(size>=BigNumber.size){
      output.number[output.size-1-i]=number[size-1-i];
      output.number[output.size-2-i]+=output.number[output.size-1-i]/10;
      output.number[output.size-1-i]=output.number[output.size-1-i]%10;
    }
    else {
      output.number[output.size-1-i]=BigNumber.number[BigNumber.size-1-i];
      output.number[output.size-2-i]+=output.number[output.size-1-i]/10;
      output.number[output.size-1-i]=output.number[output.size-1-i]%10;
    }
  }
  return output;
}

void HugeInt::operator= (const HugeInt & BigNumber)
{
  delete [] number;
  size=BigNumber.size;
  number=new int[size];
  for(int i=0;i<size;i++){
    number[i]=BigNumber.number[i];
  }
  return;
}

HugeInt HugeInt::operator- (HugeInt BigNumber)
{
  HugeInt output;
  int copyThis[size];
  int result[size];

  for(int i=0; i<size; i++){
    copyThis[i]=number[i];
  }

  if(size==BigNumber.size){
    int mode=1;
    for(int i=0;i<size;i++){
      if(copyThis[i]<BigNumber.number[i]){
        mode=2;
        break;
      }
    }
    cout<<mode<<endl;
    switch(mode){
      case 1: // A-B>=0
        for(int i=size-1;i>=0;i--){
          if(copyThis[i]<BigNumber.number[i]){
            copyThis[i]+=10;
            copyThis[i-1]--;
          }
          result[i]=copyThis[i]-BigNumber.number[i];
        }
        for(int i=0;i<size;i++){ // find size
          if(result[i]!=0){
            output.size=size-i;
            output.sign='\0';
            output.number=new int[output.size];
            for(int j=0;j<output.size;j++){
              output.number[j]=result[i+j];

            }
            break;
          }
        }
        break;
      case 2: // A-B<0
        for(int i=size-1;i>=0;i--){
          if(BigNumber.number[i]<copyThis[i]){
            BigNumber.number[i]+=10;
            BigNumber.number[i-1]--;
          }
          result[i]=BigNumber.number[i]-copyThis[i];
        }
        for(int i=0;i<size;i++){ // find size
          if(result[i]!=0){
            output.size=size-i;
            output.number=new int[output.size];
            output.sign='-';
            for(int j=0;j<output.size;j++){
              output.number[j]=result[i+j];
            }
            break;
          }
        }
        break;
    }
    return output;
  }
  else if(size>BigNumber.size){ // A-B>0
    int i,j; // counter
    for(i=size-1,j=BigNumber.size-1;i>=0,j>=0;i--,j--){
      if(copyThis[i]<BigNumber.number[i]){
        copyThis[i]+=10;
        copyThis[i-1]--;
      }
      result[i]=copyThis[i]-BigNumber.number[i];
    }
    for(j=i;j>=0;j--){
      if(copyThis[i]<0){
        copyThis[i]+=10;
        copyThis[i-1]--;
      }
      result[i]=copyThis[i];
}
    for(i=0;i<size;i++){ // find size
      if(result[i]!=0){
        output.size=size-i;
        output.sign='\0';
        output.number=new int[output.size];
        for(int j=0;j<output.size;j++){
          output.number[j]=result[i+j];
        }
        break;
      }
    }
    return output;
  }
  else{ // A-B<0
    int i,j; // counter
    for(i=BigNumber.size-1,j=size;i>=0,j>=0;i--,j--){
      if(BigNumber.number[i]<copyThis[i]){
        BigNumber.number[i]+=10;
        BigNumber.number[i-1]--;
      }
      result[i]=BigNumber.number[i]-copyThis[i];
    }
    for(j=i;j>=0;j--){
      if(BigNumber.number[i]<0){
        BigNumber.number[i]+=10;
        BigNumber.number[i-1]--;
      }
      result[i]=BigNumber.number[i];
    }
    for(int i=0;i<size;i++){ // find size
      if(result[i]!=0){
        output.size=size-i;
        output.number=new int[output.size];
        output.sign='-';
        for(int j=0;j<output.size;j++){
          output.number[j]=result[i+j];
        }
        break;
      }
    }
    return output;
  }

}

