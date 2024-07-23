#include "knight.h"
void display    (int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}
bool isPrime    (int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
        return false;
        }
    }
    return true;
}
string nameCheck(int HP){
    if(isPrime(HP)) return "Lancelot";
    else if(HP==999) return "Arthur";
    else return "Knight";
}
void openfile   (string &file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, string &line2 ,string &mushghostPatch,string &asclepiusPatch,string &merlinPatch){
    ifstream input;
    input.open(file_input);
    string line1;
    getline(input, line1,'\n'); // line 1 là 1 chuỗi kiểu string phải dùng string stream để tách ra 
    stringstream l1(line1);
    l1>>HP>>level>>remedy>>maidenkiss>>phoenixdown;
    rescue=-1;
    getline(input, line2, '\n');
    getline(input, mushghostPatch, ',' );
    getline(input, asclepiusPatch, ',' );
    getline(input, merlinPatch, ',' );
    input.close();
}
int battleResult(string name, int level, int levelO){
if(level > levelO || name == "Arthur" || name=="Lancelot") return 1;
else if(level < levelO) return -1;
else return 0;
}
int levelO      (int i){
    int b = i%10;
    if (i>6) {
        if (b>5) return b;
        else return 5;
    }
    else return b;
}
void eventResult(int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl){
    if(HP>maxHP) HP= maxHP;
    if(level>10) level=10;
    if(remedy>99) remedy=99;
    if(maidenkiss>99) maidenkiss=99;
    if(phoenixdown>99) phoenixdown=99;
    if(HP<=0){
        if(phoenixdown>0){
            phoenixdown--;
            HP=maxHP;tinyleft=0;frogleft=0;
        }
        else { rescue=0;}
    }
    if(tiny){
        if(remedy>0) {remedy-- ;tiny=false;tinyleft=0;HP*=5;if(HP>maxHP) HP= maxHP;}
        else if(tinyleft>0) tinyleft--;
        else if(tinyleft==0){tiny=false;tinyleft=0;if(HP>0)HP*=5;if(HP>maxHP) HP= maxHP;}
    }
    if(frog){
        if(maidenkiss>0) {maidenkiss-- ;frog=false;frogleft=0;level=oldlvl;}
        else if(frogleft>0) frogleft--;
        else if(frogleft==0){frog=false;frogleft=0;level=oldlvl;}
    }
}
void monster    (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl){
    int baseDamage[5];
    baseDamage[1]=10;  //Madbear
    baseDamage[2]=15;  //Bandit
    baseDamage[3]=45;  //LordLupin
    baseDamage[4]=75;  //Elf
    baseDamage[5]=95;  //Troll
    int monsterCode;
    stringstream ss(eCode);
    ss>>monsterCode;
    int result=battleResult(name, level, levelO(i));
    if(result == 1){
        level++; 
    }
    else if(result== -1){
       HP-= (baseDamage[monsterCode])*levelO(i);
    }
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue,
          maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
}
void shaman     (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl, int numofEvent){
    int result=battleResult(name, level, levelO(i));
    if(tiny||frog) result=0;
    if(result == 1){
        level+=2; 
    }
    else if(result== -1){
        if(remedy>0) remedy--;
        else if(i==numofEvent) HP*=1;
        else{tiny=true; tinyleft=3;
            if(HP>=5) HP/=5;
            else HP=1;
        }
       }
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue,
          maxHP,tiny,tinyleft,frog, frogleft,oldlvl);
 }
void vajsh      (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl){
    int result=battleResult(name, level, levelO(i));
    if(frog||tiny) result=0;
    if(result == 1){
        level+=2; 
    }
    else if(result== -1){
        if(maidenkiss>0) maidenkiss--;
        else{
        frog=true; frogleft=3;
        oldlvl=level;
        level=1;}
       }
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue,
          maxHP,tiny,tinyleft,frog, frogleft,oldlvl);
 }
void mushMario  (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl){
    int n1, s1=0;
    n1 = ((level + phoenixdown)%5 + 1)*3;
    for(int i=99; i>=101-n1*2; i-=2) s1+=i;
    HP += (s1%100)+1;
    while (!isPrime(HP)) HP+=1;
    eventResult (HP, level, remedy, maidenkiss, phoenixdown, rescue,   maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
 }
void mushFibo   (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl){
    int fb, fb1=1, fb2=1;
    if(HP==2) HP=1;
    else if(HP>2){
        while(fb1+fb2<HP){
            fb = fb1+fb2;
            fb1= fb2;
            fb2= fb;
        }
        HP=fb;
    }
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP, tiny, tinyleft, frog, frogleft, oldlvl);
 }
void mushGhost1 (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl, int array[], int n2){
    int max=array[0], min=array[0], maxi=0, mini=0;
    for( int i=1; i<n2; i++){
        if(array[i]>max) max= array[i];
        if(array[i]<min) min= array[i];
    }
    for( int i=1; i<n2; i++){
        if(array[i]==max) maxi=i;
        if(array[i]==min) mini=i;
    }
    HP-=(maxi+mini);
    if(tiny) tinyleft++;
    if(frog) frogleft++;
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP, tiny, tinyleft, frog, frogleft, oldlvl);
 }
void mushGhost2 (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl, int array[], int n2){
    bool mountain=true;
    int mtx, mti;
    if(n2==1) {mountain= true; mtx= array[0]; mti=0;}
    else if(n2==2){
        if(array[0]==array[1]) mountain=false;
        else mountain= true;
    }
    else {
        bool globalmax=false;
        for(int i=1; i<n2-1; i++) {
            if(array[i]>array[i-1] && array[i] > array[i+1]){
                globalmax= true; mtx= array[i]; mti=i;
            }
            if(array[i] < array[i-1] && array[i] < array[i+1]
            || array[i]==array[i-1]||array[i]==array[i+1]) {mountain= false; break;}
            if((i==n2-2 )&& (!globalmax)) {
                if(array[0]>array[n2-1]) { mtx= array[0]; mti=0;}
                else { mtx= array[n2-1]; mti=n2-1;}
            }
        }
    }
    if(mountain) HP-= (mtx + mti);
    else HP+=5;
    if(tiny) tinyleft++;
    if(frog) frogleft++;
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP, tiny, tinyleft, frog, frogleft, oldlvl);
}
void mushGhost3 (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl, int array3[], int n2){
    int max=array3[n2-1], min=array3[n2-1], maxi=n2-1, mini=n2-1;
    for( int i=n2-2; i>=0; i--){
        if(array3[i]>max) max= array3[i];
        if(array3[i]<min) min= array3[i];
    }
    for( int i=n2-2; i>=0; i--){
        if(array3[i]==max) maxi=i;
        if(array3[i]==min) mini=i;
    }
    HP-=(maxi+mini);
    if(tiny) tinyleft++;
    if(frog) frogleft++;
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP, tiny, tinyleft, frog, frogleft, oldlvl);
 }
void mushGhost4 (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl, int array4[], int n2){
    int max=array4[2], min=array4[2], max2, max2i;
    if(n2==1) HP+=12;
    else if(n2==2){
        if(array4[0]>array4[1]){max2=array4[1];max2i=1;}
        else if(array4[0]<array4[1]){max2=array4[0];max2i=0;}
        else {max2=-5;max2i=-7;}
        HP-=max2+max2i;
    }
    else if(n2>2){
        for( int i=2; i>=0; i--){
            if(array4[i]>=max) max=array4[i];
            if(array4[i]<=min) min=array4[i];
        }
        if(min<max){
            for( int i=2; i>=0; i--){
            if(array4[i]<max && array4[i]>min) {
                max2=array4[i];max2i=i;
                break;
            }
            else if(array4[i]==min) {
                max2=array4[i];max2i=i;
                }
            }
        HP-=(max2+max2i);
        }
        else HP+=12;
    }
    
    if(tiny) tinyleft++;
    if(frog) frogleft++;
    eventResult(HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP, tiny, tinyleft, frog, frogleft, oldlvl);
 }
void mushGhost  (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl, string mushGhostpatch){
    ifstream mgpatch;
    mgpatch.open(mushGhostpatch);
    string line1, line2;
    int n2;
    getline(mgpatch, line1, '\n');
    stringstream l1(line1);
    l1>>n2;
    int *array = new int [n2];
    int *array3 = new int [n2];
    for(int i=0; i< n2; i++) {
        string line;
        getline(mgpatch, line, ',');
        stringstream ss(line);
        ss>>array[i];
    }
    for( int i=0; i<n2; i++){
        array3[i]=array[i];
        if(array3[i]<0) array3[i]=-array3[i];
        array3[i]=(17*(array3[i]) + 9) % 257;
    }
    mgpatch.close();
    for(int k=2; k<eCode.length(); k++) {
        if(eCode[k]=='1') mushGhost1(HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, array, n2);
        else if(eCode[k]=='2') mushGhost2(HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, array, n2);
        else if(eCode[k]=='3') mushGhost3(HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, array3, n2);
        else if (eCode[k]=='4') mushGhost4(HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, array3, n2);
        if(rescue==0) break;
    }
    delete[] array;
    delete[] array3;
    eventResult (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
}
void asclepius  (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl, string asclepiusPatch){
    ifstream aspatch;
    aspatch.open(asclepiusPatch);
    int r1, c1;
    string line1, line2;
    getline(aspatch, line1);
    stringstream l1(line1);
    l1>>r1; //
    getline(aspatch, line2);
    stringstream l2(line2);
    l2>>c1;
    int** pack = new int*[r1];
    for (int i = 0; i < r1; i++) pack[i] = new int[c1];

    for (int i = 0; i < r1; i++) {
        string row;
        getline(aspatch, row, '\n');
        stringstream ss(row);
        for (int j = 0; j < c1; j++) ss>>pack[i][j];
    }
    aspatch.close();
    for(int i=0; i<r1; i++){
        int pick=3;
        for(int j=0; j<c1; j++){
            if(pick>0){
                if(pack[i][j]==16) {pick--;remedy++;}
                else if(pack[i][j]==17) {pick--;maidenkiss++;}
                else if(pack[i][j]==18) {pick--;phoenixdown++;}
            }
        }
    }
    for(int i = 0; i<r1; i++) delete[] pack[i];
    delete[] pack;
    eventResult (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
}
void bowser     (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl){
    if((name=="Arthur")||( name=="Lancelot" && level>=8)|| (name=="Knight" &&level==10)) level=10;
    else rescue =0;
    eventResult (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
}
bool checkMerlin(string line){
    bool m=false, e=false, r=false, l=false, i=false, n=false;
    for(int k=0; k < line.length(); k++){
        if(line[k]=='m'||line[k]=='M') m=true;
        if(line[k]=='e'||line[k]=='E') e=true;
        if(line[k]=='r'||line[k]=='R') r=true;
        if(line[k]=='l'||line[k]=='L') l=true;
        if(line[k]=='i'||line[k]=='I') i=true;
        if(line[k]=='n'||line[k]=='N') n=true;
    }
    if(m==true && e==true && r==true && l==true && i==true && n==true) return true;
    else return false;
}
void merlin     (int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int i, string eCode, string name, int maxHP, bool &tiny,int &tinyleft, bool &frog, int& frogleft, int& oldlvl,string merlinPatch){
    ifstream mlpatch;
    mlpatch.open(merlinPatch);
    string line1;
    getline(mlpatch,line1);
    stringstream l1(line1);
    int n9;
    l1>>n9;
    for(int i=0; i<n9; i++){
        string line;
        getline(mlpatch, line, '\n');
        if(checkMerlin(line)){
            if((line.find("merlin")<line.length())|| (line.find("Merlin")<line.length())) HP+=3;
            else HP+=2;
        }
    }
    mlpatch.close();
    eventResult (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
}
//
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    string line2;
    string mushghostPatch,asclepiusPatch, merlinPatch;
    openfile(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue, line2, mushghostPatch, asclepiusPatch, merlinPatch);
    string name=nameCheck(HP);
    int const maxHP = HP;
    bool tiny=false, frog=false;
    int tinyleft=0, frogleft=0;int oldlvl;
    int i=0,  numofEvent=0;
    string eCode,  eCount;
    stringstream cou(line2);
    stringstream l2(line2);
    while(cou>>eCount) numofEvent++;
    bool ascMeet=false, merMeet=false;
    while (l2>>eCode){
        i++;
        if (eCode=="0") rescue =1;
        else if(eCode=="1" || eCode=="2"|| eCode=="3"|| eCode=="4"|| eCode=="5") monster(HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
        else if(eCode=="6") shaman      (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, numofEvent);
        else if(eCode=="7") vajsh       (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
        else if(eCode=="11") mushMario  (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
        else if(eCode=="12") mushFibo   (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
        else if(eCode[0]=='1'&&eCode[1]=='3') mushGhost (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, mushghostPatch);
        else if(eCode=="15"){remedy++;eventResult       (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);}
        else if(eCode=="16"){maidenkiss++;eventResult   (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);}
        else if(eCode=="17"){phoenixdown++;eventResult  (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);}
        else if(eCode=="19"){
            if(ascMeet) eventResult     (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
            else{ascMeet=true;asclepius (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, asclepiusPatch);}
        }
        else if(eCode=="99") bowser     (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
        else if(eCode=="18") {
            if(merMeet) eventResult     (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
            else {merMeet=true;merlin   (HP, level, remedy, maidenkiss, phoenixdown, rescue, i, eCode,name, maxHP,tiny,tinyleft,frog, frogleft, oldlvl, merlinPatch);}
        }
        
        if( i== numofEvent && rescue==-1) {
            rescue=1;frogleft=0;tinyleft=0;
            eventResult (HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP,tiny,tinyleft,frog, frogleft, oldlvl);
        }
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        if( rescue ==0 || rescue==1) break;
    }
}