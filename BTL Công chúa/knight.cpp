#include "knight.h"
using namespace std;

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}
int levelO(int i){                //tinh levelO
    double b=i%10;
    int levelquai;
    return levelquai=i>6?(b>5?b:5):b;
}
int min(int &HP, int &maxHP){
    if (maxHP>=HP*5) {return HP*5;}
    else return maxHP;
}
int minn(int a){             // min voi remedy maidenkiss phoenixdown
    if (a<99) return a;
    else return 99;
}
int minHP(int &HP, int &maxHP){  // min HP
    if (HP<maxHP) return HP;
    else return maxHP;
}
int min_level(int &level){
    if (level <10) return level;
    else return 10;
}
bool isPrime(int n) {            // check HP la so nguyen to 
    if (n < 2)                 
        return false;
    for (int i = 2; i <= (n/2); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
int findPrimeNum(int n) {
    // Nhập vào số nguyên n và trả về số nguyên tố > n và gần n nhất
    int i = n + 1;
    while (!isPrime(i)) {
        i++;
    }
    return i;
}
int s1(int n) {
    int tong = 0;
    for (int i = 99; i >= 11 && n >= 1; i -= 2) {
        tong += i;
        n--;
    }
    return tong;
}
int fibonacci_closest(int x) {       // tra ve so fibonacci gan nhat
  int a = 0, b = 1, c = 1;
  while (c <= x) {
    a = b;
    b = c;
    c = a + b;
  }
  return (x - b < c - x) ? b : c;
}
bool checkArthur(int &HP){           // check HP=999 la arthur
    if (HP==999){
        return true;
    }
    else 
    {
        return false;
    }
}
bool check13(int num){             // check sk13
    int n=1;
    while (num/n !=0){
        n*=10;
        if (num/n == 13) return true;
    }
    return false;
}
// nam 1
void mushGhost1(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr[],int n2,int maxHP){
    int max=arr[0], min=arr[0], maxi=0, mini=0;
    for( int i=1; i<n2; i++){
        if(arr[i]>max){
         max= arr[i];}
        if(arr[i]<min){
         min= arr[i];}
    }
    for( int i=1; i<n2; i++){
        if(arr[i]==max){
         maxi=i;}
        if(arr[i]==min){
         mini=i;}
    }
    HP-=(maxi+mini); HP=minHP(HP,maxHP);
    if (HP<0 && phoenixdown >=1){ HP=maxHP; phoenixdown--;}

}
// nam 2
void mushGhost2(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr[],int n2,int maxHP){
    bool mountain=true;
    int mtx, mti;
    if(n2==1){mountain= true;
    mtx= arr[0];
    mti=0;
    }
    else if(n2==2){
        if(arr[0]==arr[1]) 
        mountain=false;
        else 
        mountain= true;
    }
    else {
        bool globalmax=false;
        for(int i=1; i<n2-1; i++) {
            if(arr[i]>arr[i-1] && arr[i] > arr[i+1]){
                globalmax= true; 
                mtx= arr[i]; 
                mti=i;
            }
            if(arr[i] < arr[i-1] && arr[i] < arr[i+1]
            || arr[i]==arr[i-1]||arr[i]==arr[i+1]) {mountain= false; break;}
            if((i==n2-2 )&& (!globalmax)) {
                if(arr[0]>arr[n2-1]) { mtx= arr[0]; mti=0;}
                else { mtx= arr[n2-1]; mti=n2-1;}
            }
        }
    }
    if(mountain) HP-= (mtx + mti);
    else HP+=5;
     HP=minHP(HP,maxHP);
    if (HP<0 && phoenixdown >=1){ HP=maxHP; phoenixdown=phoenixdown-1;}
}
//nam3
void mushGhost3(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr3[],int n2,int maxHP){
    int max=arr3[n2-1], min=arr3[n2-1], maxi=n2-1, mini=n2-1;
    for( int i=n2-2; i>=0; i--){
        if(arr3[i]>max){ 
            max= arr3[i];
            }
        if(arr3[i]<min){ min=arr3[i];}
    }
    for( int i=n2-2; i>=0; i--){
        if(arr3[i]==max)
        maxi=i;
        if(arr3[i]==min) 
        mini=i;
    }
    HP-=(maxi+mini); HP=minHP(HP,maxHP);
    if (HP<0 && phoenixdown >=1){ HP=maxHP; phoenixdown--;}
}
//nam 4
void mushGhost4(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr4[],int n2,int maxHP){
    int k=3;
    if(n2<3) k=n2;
    int max=arr4[k-1], maxi=k-1;
    int max2=max, max2i=maxi;
    for( int i=k-2; i>=0; i--){
        if(arr4[i]>max) {max2= max; 
        max= arr4[i];}
    }
    for( int i=k-2; i>=0; i--){
        if(arr4[i]==max2) 
        max2i=i;
    }
    if(max==max2) HP+=12 ;
    else HP-=(max2+max2i);
    HP=minHP(HP,maxHP);
    if (HP<0 && phoenixdown >=1){ HP=maxHP; phoenixdown--;}
}
void mushGhost(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,string mushGhostpatch,int maxHP){
    int max_HP=maxHP;
    ifstream patch;
    patch.open(mushGhostpatch);
    string line1,line2;
    int n2;
    getline(patch,line1,'\n'); stringstream l1(line1); l1>>n2;
    string abc[100];
    int arr[100],arr3[100];
    for (int i=0;i<n2;i++){
        getline(patch,abc[i],','); stringstream ss(abc[i]);
        ss>>arr[i];
    }
    for (int i=0;i<n2;i++){
        arr3[i]=arr[i];
        if (arr3[i]<0) arr3[i]=-arr3[i];
        arr3[i]=(17*(arr3[i])+9)%257;
    }
    patch.close();
    for (int k=2;k<eventcode.length();k++){
        if (eventcode[k]=='1')
        mushGhost1(HP, level, remedy, maidenkiss,phoenixdown,rescue,eventcode ,arr,n2,max_HP);
 
        else if (eventcode[k]=='2') 
        mushGhost2(HP, level, remedy, maidenkiss,phoenixdown,rescue, eventcode,arr,n2,max_HP);
        else if (eventcode[k]=='3')
        mushGhost3(HP, level, remedy, maidenkiss,phoenixdown,rescue, eventcode ,arr3,n2,max_HP);
        
        else if (eventcode[k]=='4')
        mushGhost4(HP, level, remedy, maidenkiss,phoenixdown,rescue, eventcode,arr3,n2,max_HP);
        if (rescue==0) break;}

}
bool checkmerlin(string line){
    bool m=false,e=false,r=false,l=false,i=false,n=false;
    for (int k=0;k<line.length();k++){
        if (line[k]=='m'|| line[k]=='M') 
        m=true;
        if (line[k]=='e'|| line[k]=='E') 
        e=true;
        if (line[k]=='r'|| line[k]=='R') 
        r=true;
        if (line[k]=='l'|| line[k]=='L') 
        l=true;
        if (line[k]=='i'|| line[k]=='I') 
        i=true;
        if (line[k]=='n'|| line[k]=='N') 
        n=true;
    }
    if (m==true && e==true && r==true && l==true && i==true && n==true) return true;
    else return false;
}
// merlin
void sk18(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string merlinpatch,int maxHP){
    ifstream patch; patch.open(merlinpatch);
    string line1;
    getline(patch,line1); stringstream l1(line1);
    int n9;
    l1>>n9;
    for (int i=0;i<n9;i++){
        string line;
        getline(patch,line,'\n');
        if (checkmerlin(line)){
            if ((line.find("merlin")<line.length())|| (line.find("Merlin")<line.length())) HP+=3;
            else HP+=2;
        }
    }
    HP=minHP(HP,maxHP);
    patch.close();
}
// asclepius
void sk19(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string asclepiusPatch,int maxHP){
ifstream patch; patch.open(asclepiusPatch);
int r1,c1;
string line1,line2;
getline(patch,line1); stringstream l1(line1);
l1>>r1;
getline(patch,line2); stringstream l2(line2);
l2>>c1;
int pack[100][100];
for (int i=0;i<r1;i++){
    string row;
    getline(patch,row,'\n'); stringstream ss(row);
    for (int j=0;j<c1;j++) ss>>pack[i][j];
}
patch.close();
for ( int i=0;i<r1;i++){
    int pick=3;
    for (int j=0;j<c1;j++){
        if (pick>0){
            if (pack[i][j]==16){ pick--;remedy++;}
            else if (pack[i][j]==17){pick--;maidenkiss++;}
            else if (pack[i][j]==18) {pick--;phoenixdown++;}
        }
    }
}
}
// mo file
void openfile(string &file_input,int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string &line2,string &file_mush_ghost,string &file_asclepius_pack,string &file_merlin_pack)
 {
    ifstream input; 
    input.open(file_input);
    string line1;
    getline (input,line1,'\n'); 
    stringstream l1(line1);
    l1>>HP>>level>>remedy>>maidenkiss>>phoenixdown;    // dong 1
    rescue=-1;
    getline(input,line2,'\n');
    getline(input,file_mush_ghost,',');
    getline(input,file_asclepius_pack,',');
    getline(input,file_merlin_pack,',');
    input.close();
 }
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    string line2,mushghost,asclepius,merlin;
    openfile (file_input,HP,level,remedy,maidenkiss,phoenixdown,rescue,line2,mushghost,asclepius,merlin);
    float baseDamage;
    int check19=0;
    int damage,tinyevent=1,frogevent=1,old_level,old_HP,endtiny=0,endfrog=0,maxHP=HP,count=1;
    stringstream l2(line2);
    int event[1000];
    while (l2 >>event[count]){                         // dong 2
        count ++;
    }
    count--;     // co 3 sk thi count=3
    for (int i=1;i<=count;i++){
        if (event[i]==0){                                   // sukien0
        rescue =1;
        display( HP,level,  remedy,  maidenkiss,  phoenixdown,  rescue);
        break;
        }
        if (event[i]==1){                                  //sukien1
            baseDamage=1;
            if (isPrime(old_HP)==true){             // lancelot
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (checkArthur(old_HP)==true){           // arthur
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (level>levelO(i))
            {
               level = level +1;
               level=min_level(level); 
            }
            else if (level == levelO(i))
            {
                level=level*1;   
            }
            else if(level <levelO(i))
            {
                damage=baseDamage * levelO(i)*10;
                HP=HP-damage;
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5; minHP(HP,maxHP);        // checksk6
            if (i==endfrog) level=old_level;     // checksk7
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }
        if (event[i]==2){                                  //sukien2
            baseDamage=1.5;
            if (isPrime(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (level>levelO(i))
            {
               level = level +1;
               level=min_level(level); 
            }
            else if (level == levelO(i))
            {
                level=level*1;   
            }
            else if(level <levelO(i))
            {
                damage=baseDamage * levelO(i)*10;
                HP=HP-damage;
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;minHP(HP,maxHP);
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }
        if (event[i]==3){                                  //sukien3
            baseDamage=4.5;
            if (isPrime(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (level>levelO(i))
            {
               level = level +1;
               level=min_level(level); 
            }
            else if (level == levelO(i))
            {
                level=level*1;   
            }
            else if(level <levelO(i))
            {
                damage=baseDamage * levelO(i)*10;
                HP=HP-damage;
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5; minHP(HP,maxHP);
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }          
        if (event[i]==4){                                  //sukien4
            baseDamage=7.5;
            if (isPrime(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (level>levelO(i))
            {
               level = level +1;
               level=min_level(level); 
            }
            else if (level == levelO(i))
            {
                level=level*1;   
            }
            else if(level <levelO(i))
            {
                damage=baseDamage * levelO(i)*10;
                HP=HP-damage;
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;minHP(HP,maxHP);
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }            
        if (event[i]==5){                                  //sukien5
            baseDamage=9.5;
            if (isPrime(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (level>levelO(i))
            {
               level = level +1;
               level=min_level(level); 
            }
            else if (level == levelO(i))
            {
                level=level*1;   
            }
            else if(level <levelO(i))
            {
                damage=baseDamage * levelO(i)*10;
                HP=HP-damage;
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;minHP(HP,maxHP);
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }   
        if (event[i]==6){                                  //sukien6
            if (isPrime(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (i<endfrog || i < endtiny){
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);break; }
                else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                continue;
            }
             old_HP=HP;
            if(level>levelO(i)){               
                level+=2;
                level=min_level(level);
            }
            else if (level == levelO(i)){
                level *=1;
            }
            else {
                endtiny=i+3;
                if (HP>=5){
                    HP=HP/5;
                }
                else 
                    HP=1;
                if (remedy >= 1) {
                    HP=HP*5; minHP(HP,maxHP);
                    remedy--;
                }
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
        }
        if (event[i]==7){                                  //sukien7
            if (isPrime(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            if (i<endtiny || i < endfrog){
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);break;}
                else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                continue;
            }
             old_level=level;
            if (level >levelO(i)){
                level+=2;
                level=min_level(level);
            }
            else if (level==levelO(i)){
                level*=1;
            }
            else {
                level=1;
                if (maidenkiss >=1){
                    level=old_level;
                    maidenkiss--;
                }
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
        }
        if (event[i]==11){
            int n1=((level+ phoenixdown)%5+1)*3;
            HP += s1(n1) % 100;
            HP=findPrimeNum(HP);
            HP = minHP(HP, maxHP);
             if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5; minHP(HP,maxHP);
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }   
        if (event[i]==12){
            if (HP==1){
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                continue;
            }
            if (HP>1){
                HP=fibonacci_closest(HP);
            }
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }   
        if (check13(event[i])==true){                    // su kien 13
            string eCode = to_string(event[i]);
            mushGhost(HP, level, remedy, maidenkiss,phoenixdown,rescue,eCode,mushghost,maxHP);
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        if (event[i]==18){
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            sk18(HP, level, remedy, maidenkiss,phoenixdown,rescue,merlin,maxHP);
            HP=minHP(HP,maxHP);
             if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        if (event[i]==19){
            if (check19 >=1){
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                continue;
            }
            else check19 +=1;
            if (checkArthur(old_HP)==true){
                level+=1;
                if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                else { rescue=-1; display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
                continue;
            }
            sk19(HP, level, remedy, maidenkiss,phoenixdown,rescue,asclepius,maxHP);
            remedy=minn(remedy);
            maidenkiss=minn(maidenkiss);
            phoenixdown=minn(phoenixdown);
            HP=minHP(HP,maxHP);
            if (i<endtiny || i < endfrog){
                if (i<endtiny && remedy>=1){
                    remedy--;
                    HP=HP*5; HP=minHP(HP,maxHP);
                }
                else if (i<endfrog && maidenkiss>=1){
                    maidenkiss--;
                    level=old_level;
                }
            }

            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        if (event[i]==15){      // su kien 15
             remedy= minn(remedy +1);
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }   
        if (event[i]==16){       // su kien 16
             maidenkiss= minn(maidenkiss +1);
             if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }   
        if (event[i]==17){          // su kien 17
             phoenixdown = minn(phoenixdown +1);
            if (HP<0 && phoenixdown >=1){
                HP=maxHP;
                phoenixdown--;
            }
            else if (HP<0 && phoenixdown==0){
                rescue=0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            else if (HP > 0) {
                rescue = -1;    
            }
            if (i==endtiny) HP*=5;
            if (i==endfrog) level=old_level;
            if (i==count && rescue==-1) {rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
            else display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            
        }   
        if (event[i]==99){         // su kien 99 gap Bowser
            if (HP==999  || (isPrime(old_HP)==true && level>=8) || level==10){
                level=10;}
            else { 
                rescue=0;
                display( HP,  level,  remedy,  maidenkiss,  phoenixdown,  rescue);
                break;
            }
        }  
    }// ngoac ham for

}

