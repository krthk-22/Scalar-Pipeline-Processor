#include<bits/stdc++.h>
using namespace std;

 vector<string>inst;
 vector<int>data;
 vector<int>reg;
 vector<int>marked(256);
 int pc=0;
  int ni=0,ai=0,li=0,si=0,mi=0,ci=0,hi=0,ts=0,ds=0,cs=0,lii=0;
      float cy=0.0;
      int nc=0;
 string ir;
 int a,b;
   char op;
   int aluout;
   int lmd;


 void fetch(int k){
   pc=k;
   ir=inst[k]+inst[k+1];
   pc+=2; 
 }
 void decode(){
   op=ir[0];
   int x,y,z;
    if((ir[1]=='a')||(ir[1]=='b')||(ir[1]=='c')||(ir[1]=='d')||(ir[1]=='e')||(ir[1]=='f')){
        z=ir[1]-'a'+10;
      }
      else{
         z=ir[1]-'0';
      }
   if((ir[2]=='a')||(ir[2]=='b')||(ir[2]=='c')||(ir[2]=='d')||(ir[2]=='e')||(ir[2]=='f')){
        x=ir[2]-'a'+10;
      }
      else{
         x=ir[2]-'0';
      }
      if((ir[3]=='a')||(ir[3]=='b')||(ir[3]=='c')||(ir[3]=='d')||(ir[3]=='e')||(ir[3]=='f')){
        y=ir[3]-'a'+10;
      }
      else{
         y=ir[3]-'0';
      }


   if((ir[0]=='0')||(ir[0]=='1')||(ir[0]=='2')||(ir[0]=='4')||(ir[0]=='5')||(ir[0]=='6')){
     a=reg[x];
     b=reg[y];
   }
   else if((ir[0]=='8')||(ir[0]=='9')||(ir[0]=='b')||(ir[0]=='c')){
     a=reg[x];
     b=y;
   }
   else if(ir[0]=='3'){
      a=reg[z];
   }
   else if(ir[0]=='7'){
      a=reg[x];
   }
   else if(ir[0]=='a'){
      a=16*x+y;
   }
   else if(ir[0]=='d'){
      a=16*z+x;
      if(a/128==1){
          a=a-256;
      }
   }
   else if(ir[0]=='e'){
      a=reg[z];
      b=16*x+y;
      
   }  
 }

void execute(){
   if((op=='0')){
      ai++;
      aluout=(a+b)%256;
   }
   else if((op=='1')){
      ai++;
      aluout=(a-b)%256;
   }
   else if((op=='2')){
      ai++;
      aluout=(a*b)%256;
   }
   else if((op=='3')){
      ai++;
      aluout=(a+1)%256;
   }
   else if((op=='4')){
      li++;
      aluout=a&b;
   }
   else if((op=='5')){
      li++;
      aluout=a|b;
   }
   else if((op=='6')){
      li++;
      aluout=a^b;
   }
   else if((op=='7')){
      li++;
      int numBits = 8;
    int mask = (1 << numBits) - 1;
    int storedNumber = a&mask;
    aluout=~storedNumber;
   }
   else if((op=='8')){
      si++;
      aluout=(a<<b)%256;
   }
   else if((op=='9')){
      si++;
      aluout=(a>>b)%256;
   }
   else if((op=='a')){
      lii++;
      aluout=a;
   }
   else if((op=='b')){
      mi++;
      aluout=a+b;
   }
   else if((op=='c')){
      mi++;
      aluout=a+b;
   }
   else if((op=='d')){
      ci++;
      int prevpc=pc;
        pc=pc+2*a;
   }
   else if((op=='e')){
      ci++;
      if(a==0){
        int prevpc=pc;
         pc+=2*b;
      }
   }
   else{
      hi++;
   }
}
 void mem(int k){
    string iop=inst[k];
    if((iop[0]=='a')){
      lmd=aluout;
   }
   else if((iop[0]=='b')){
      lmd=data[aluout];
   }
    else if((iop[0]=='c')){
      int z;
      if((iop[1]=='a')||(iop[1]=='b')||(iop[1]=='c')||(iop[1]=='d')||(iop[1]=='e')||(iop[1]=='f')){
        z=iop[1]-'a'+10;
      }
      else{
         z=iop[1]-'0';
      }
      data[aluout]=reg[z];
   }
   else if((iop[0]>='0')&&(iop[0]<='9')){
      lmd=aluout;
   }
   
 }
 void writeback(int k){
   string iop=inst[k];
    int z;
      if((iop[1]=='a')||(iop[1]=='b')||(iop[1]=='c')||(iop[1]=='d')||(iop[1]=='e')||(iop[1]=='f')){
        z=iop[1]-'a'+10;
      }
      else{
         z=iop[1]-'0';
      }
   if(((iop[0]>='0')&&(iop[0]<='9'))||((iop[0]=='a')||(iop[0]=='b'))){
            reg[z]=lmd;
   }

 }

int main(){
    std::string folderPath = "input"; 
    std::string fileName = "ICache.txt"; 

    std::string filePath = folderPath + "/" + fileName;
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
               inst.push_back(line);
            }
            file.close();
    }

   fileName = "DCache.txt"; 

   filePath = folderPath + "/" + fileName;
        std::ifstream file1(filePath);
        if (file1.is_open()) {
            int line;
            while (file1>>hex>>line){
               data.push_back((line));
            }
            file1.close();
    }

       fileName = "RF.txt"; 
 filePath = folderPath + "/" + fileName;
        std::ifstream file2(filePath);
        if (file2.is_open()) {
            int line;
            while (file2>>hex>>line) {
               reg.push_back((line));
            }
            file2.close();
    }
     queue<int>q;
      queue<int>q1;
     int i=0;
     q.push(i);
     int prev1=-1;
      int prev2=-1;
      int fd=0;
      int fc=0;
      int hz;
      int tdhz=0;
      int tchz=0;
 while(!q.empty()){
    int k;
   while(!q.empty()){
       k=q.front();
        q.pop();
      if(marked[k]==0){
         fetch(k);
         ni++;
         marked[k]++;
        if((inst[k][0]=='0')||(inst[k][0]=='1')||(inst[k][0]=='2')||(inst[k][0]=='4')||(inst[k][0]=='5')||(inst[k][0]=='6')){
         if(prev1!=-1){
         if((inst[k+1][1]==inst[prev1][1])||(inst[k+1][0]==inst[prev1][1])){
            fd=1;
            hz=k;
         if(marked[prev1]==3){
            tdhz=1;
           }
          else if(marked[prev1]==2){
            tdhz=2;
           }
           else tdhz=0;
            ds+=tdhz;
         }
         else if(prev2!=-1){
            if((inst[k+1][1]==inst[prev2][1])||(inst[k+1][0]==inst[prev2][1])){
            fd=1;
            hz=k;
         if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
            ds+=tdhz;
         }
         }
         }
         else if((prev2!=-1)){
         if((inst[k+1][1]==inst[prev2][1])||(inst[k+1][0]==inst[prev2][1])){
            fd=1;
            hz=k;
         if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
            ds+=tdhz;
         }
         }
        }
        else if((inst[k][0]=='7')||(inst[k][0]=='8')||(inst[k][0]=='9')||(inst[k][0]=='b')){
          if(prev1!=-1){
           if((inst[k+1][0]==inst[prev1][1])){
            fd=1;
            hz=k;
         if(marked[prev1]==3){
            tdhz=1;
           }
          else if(marked[prev1]==2){
            tdhz=2;
           }
           else tdhz=0;
             ds+=tdhz;
         }
         else if(prev2!=-1){
        if((inst[k+1][0]==inst[prev2][1])){
            fd=1;
            hz=k;
         if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
             ds+=tdhz;
        }
         }
          }
          else if((prev2!=-1)){
          if((inst[k+1][0]==inst[prev2][1])){
            fd=1;
            hz=k;
         if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
             ds+=tdhz;
         }
          }
        }
         else if((inst[k][0]=='c')){
         if(prev1!=-1){
           if((inst[k][1]==inst[prev1][1])||(inst[k+1][0]==inst[prev1][1])){
            fd=1;
            hz=k;
         if(marked[prev1]==3){
            tdhz=1;
           }
          else if(marked[prev1]==2){
            tdhz=2;
           }
           else tdhz=0;
             ds+=tdhz;
         }
         else if(prev2!=-1){
            if((inst[k][1]==inst[prev2][1])||(inst[k+1][0]==inst[prev2][1])){
            fd=1;
            hz=k;
         if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
             ds+=tdhz;
         }
         }
         }
         else if((prev2!=-1)){
          if((inst[k][1]==inst[prev2][1])||(inst[k+1][0]==inst[prev2][1])){
            fd=1;
            hz=k;
         if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
             ds+=tdhz;
         }
         }
        }
         else if((inst[k][0]=='3')||(inst[k][0]=='e')){
             if(prev1!=-1){
             if((inst[k][1]==inst[prev1][1])){
            fd=1;
            hz=k;
           if(marked[prev1]==3){
            tdhz=1;
           }
          else if(marked[prev1]==2){
            tdhz=2;
           }
           else tdhz=0;
             ds+=tdhz;
         }
         else if(prev2!=-1){
            if((inst[k][1]==inst[prev2][1])){
            fd=1;
            hz=k;
           if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
             ds+=tdhz;
         }
         }
             }
      else if((prev2!=-1)){
         if((inst[k][1]==inst[prev2][1])){
            fd=1;
            hz=k;
         if(marked[prev2]==3){
            tdhz=1;
           }
           else tdhz=0;
             ds+=tdhz;
         }
      }
         }
         if((inst[k][0]=='e')||(inst[k][0]=='d')){
            fc=1;
            tchz=2;
            cs+=tchz;
         }
         if(fd==0){
         q1.push(k);
         }
      
      }
      else if(marked[k]==1){
        decode();
        marked[k]++;
         q1.push(k);
      }
       else if(marked[k]==2){
        execute();
        marked[k]++;
         q1.push(k);
      }
       else if(marked[k]==3){
        mem(k);
        marked[k]++;
         q1.push(k);
      }
       else if(marked[k]==4){
        writeback(k);
        marked[k]=0; 
      } 
   }
    nc++;
    q.swap(q1);
    if(inst[k][0]=='f'){
      continue;
    }
    else{
    if((fc==0)&&(fd==0)){
      if(((inst[i][0]>='0')&&(inst[i][0]<='9'))||((inst[i][0]=='a')||(inst[i][0]=='b'))){
    prev2=prev1;
    prev1=i;
    }
    else{
      prev2=prev1;
      prev1=-1;
    }
    i=pc;
   q.push(i);
    }
    else if((fc!=0)&&(fd==0)){
   if(tchz>0){
     tchz--;
   }
    else{
      if(((inst[i][0]>='0')&&(inst[i][0]<='9'))||((inst[i][0]=='a')||(inst[i][0]=='b'))){
    prev2=prev1;
    prev1=i;
    }
    else{
      prev2=prev1;
      prev1=-1;
    }
    i=pc;
         q.push(i);
         fc=0;
      }
    }
    else if((fc==0)&&(fd!=0)){
      if(tdhz>0){
         tdhz--;
      }
      else{
         q.push(hz);
         if(((inst[i][0]>='0')&&(inst[i][0]<='9'))||((inst[i][0]=='a')||(inst[i][0]=='b'))){
    prev2=prev1;
    prev1=i;
    }
    else{
      prev2=prev1;
      prev1=-1;
    }
         i=pc;
         q.push(i);
           fd=0;
      }
    }
    else{
       if(tdhz>0){
         tdhz--;
      }
      else if(tchz==2){
         q.push(hz);
         tchz=1;
      }
       else if(tchz==1){
         tchz--;
      }
      else{
         if(((inst[i][0]>='0')&&(inst[i][0]<='9'))||((inst[i][0]=='a')||(inst[i][0]=='b'))){
    prev2=prev1;
    prev1=i;
    }
    else{
      prev2=prev1;
      prev1=-1;
    }
    i=pc;
         q.push(i);
         fd=0;
         fc=0;
      }

    }
    }
 }
 cy=nc/(float)ni;
 ts=ds+cs;
 folderPath = "output";
  fileName = "Output.txt";
    
     filePath = folderPath +"/" + fileName;

   
    std::ofstream outfile(filePath);

    if (outfile.is_open()) {
       
        outfile << "Total number of instructions executed:"<<ni<<'\n';
        outfile << "Number of instructions in each class"<<'\n';
        outfile << "Arithmetic instructions              :"<<ai<<'\n';
        outfile << "Logical instructions                 :"<<li<<'\n';
        outfile << "Shift instructions                   :"<<si<<'\n';
        outfile << "Memory instructions                  :"<<mi<<'\n';
        outfile << "Load immediate instructions          :"<<lii<<'\n';
        outfile << "Control instructions                 :"<<ci<<'\n';
        outfile << "Halt instructions                    :"<<hi<<'\n';
        outfile << "Cycles Per instruction               :"<<cy<<'\n';
        outfile << "Total Number of stalls               :"<<ts<<'\n';
        outfile << "Data Stalls (RAW)                    :"<<ds<<'\n';
        outfile << "Control Stalls                       :"<<cs<<'\n';
         outfile.close();
     
    }
          
     fileName = "DCache.txt";
    
     filePath = folderPath +"/" + fileName;

   
    std::ofstream outfile1(filePath);

    if (outfile1.is_open()) {
       
       for(int i=0;i<data.size();i++){
         if(data[i]<0) outfile1<<hex<<(data[i]+256)%256<<'\n';
        else if(data[i]<=15) outfile1<<0<<hex<<(data[i]+256)%256<<'\n';
        else outfile1<<hex<<data[i]<<'\n';
          
       }
         outfile1.close();
    }
    return 0; 
}