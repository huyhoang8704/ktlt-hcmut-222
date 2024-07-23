#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}


// lần lược là 3 file của các sự kiện 13, 18, 19
string file_mush_ghost ,file_Asclepius_pack, file_merlin_pack;

int MAXHP; // giá trị lớn nhất HP
int LEVELOLD; // giá trị level trước khi hóa ếch
int hit_Mushroom, hit_Frog; // đếm số sự kiện biến thành ếch hoặc bị nấm
int figer; // nhân vật đang chơi là gì vua Arthur hay Lancelot hay hiệp sĩ bàn tròn
// kiểm tra xem đã gặp thần Asclepius hay phù thuỷ Merlin vì không được gặp lần 2 
bool meet_Asclepius = false, meet_Merlin = false;

bool checkPrime(int a){
    if(a <= 1) return false;
    for (int i = 2; i * i <= a; i++) 
        if (a % i == 0) return false;
    return true;
}

// event 1 -> 5;
// number là thứ tự sự kiện number = 1,2,3,4,5
void _su_kien_thu_1_2_3_4_5(int number,int i, int& HP, int& level){
    // vua Arthur and  Lancelot thắng full 
    if(figer == 1 || figer == -1){
        level ++;
        return;
    }

    // tính b và levelO như bkel :(((
    int b = i % 10;
    int levelO = i > 6 ? (b > 5 ? b : 5 ) : b;
    
    // baseDaemge nếu number = 1 -> baseDamege[1] = 10, number = 2 -> baseDamege[2] = 15 .......
    const int baseDamege[] = {0, 10, 15, 45, 75, 95};
    if(levelO < level ) level ++; // đánh thằng
    else if(levelO > level)  HP -= baseDamege[number] * levelO;   // đánh thua
}

void _su_kien_thu_6(int& level, int i, int& HP, int& remedy){
    // nếu bị hit nấm hay ếch thì bỏ qua sự kiện này
    if(hit_Mushroom || hit_Frog) return;
    // vua Arthur and  Lancelot thắng full 
    if(figer == 1 || figer == -1){
        level += 2;
        return;
    }

    // tính b và levelO như bkel :(((
    int b = i % 10;
    int levelO = i > 6 ? (b > 5 ? b : 5 ) : b;
    // đánh thằng
    if(levelO < level) level += 2;
    // đánh thua
    else if(levelO > level){
        // nếu có thuốc remedy thì được cứu không thì giảm HP đi /5 lần và cập nhật hit_mushroom = 4
        if(remedy > 0) remedy--;
        else{
            HP /= 5;
            if(HP == 0) HP = 1; // nếu HP = 0 khi chia 5 thì gán bằng 1  
            hit_Mushroom = 4;
        }
    }
}

void _su_kien_thu_7(int& level, int i, int& maidenkiss){
    // nếu bị hit nấm hay ếch thì bỏ qua sự kiện này
    if(hit_Mushroom || hit_Frog) return;
    // vua Arthur and  Lancelot thắng full 
    if(figer == 1 || figer == -1){
        level += 2;
        return;
    }

    // tính b và levelO như bkel :(((
    int b = i % 10;
    int levelO = i > 6 ? (b > 5 ? b : 5 ) : b;
    // đánh thằng
    if(levelO < level) level += 2;
    // đánh thua
    else if(levelO > level){
        if(maidenkiss > 0) maidenkiss--;
        else{ 
            LEVELOLD = level;  // lưu level lại để lúc sau hóa thành người
            level = 1;          // hóa ếch level = 1
            hit_Frog = 4;         // cap nhat hóa ếch
        }
    }
}

void _su_kien_thu_11(int& HP, int& level, int& phoenixdown){
    // trong file công thức tính n1 and HP
    int n1 = ((level +  phoenixdown) % 5 + 1 ) * 3, s1 = 0;
    s1 = n1 * (100 - n1); // này công thức cấp số cộng n0 = 99 , d = -2
    HP = HP + s1%100;

    HP += 1; // trường hợp xảy ra HP trên là số nguyên tố mà đề kêu tăng nên phải cộng cho 1 để tăng HP lên
    // checkPrime kiểm tra là số nguyên tố thì dừng lại tăng lên từng đương vị += 1
    while(!checkPrime(HP)) HP ++;
}

void _su_kien_thu_12(int& HP){
    // 2 số đầu của fibnacion
    int f1 = 1, f2 = 1;
    // tăng f2 đến khi nào lớn hơn hoặc bằng HP thì lúc này f1 sẽ luôn bé hơn HP -> HP = f1;
    while( HP > f2){
        int t = f2;
        f2 += f1;
        f1 = t;
    }
    HP = f1;
}

// tìm min max vị trí cuối cùng này chắc dễ rồi tìm min max mà
int _su_kien_thu_13_1(int arr[], int n){
    int maxi = 0 , mini = 0;
    for(int i = 1; i < n; i++){
       if(arr[i] >= arr[maxi]) maxi = i;
       if(arr[i] <= arr[mini]) mini = i;
    } 
    return maxi + mini;
}

int _su_kien_thu_13_2(int arr[], int n){ 
    int i = 1; // biến chạy i = 1;

    while(i < n && arr[i-1] < arr[i]) i ++; // lên núi nào :((  VD = 1 2 3 -1 thì leo lên 1 2 3 tới -1 thì lúc while sẽ dừng
    int index = i;  // lưu lại đỉnh núi
    while(i < n && arr[i-1] > arr[i]) i ++; // xuống núi nào :((  VD = 3 2 1 4 thì leo lên 1 2 3 tới 4 thì lúc while sẽ dừng
    // nếu chạy hết ngọn núi thì i == n lúc này mảng có dạng núi lên và xuống
    // VD 1 2 3 -2 -1 while đầu chạy tới index = 3 thì dừng tương ứng -2 while 2 dẽ dừng khi i == n -> điểm núi index - 1
    if(i == n) return arr[index - 1] + index - 1; 
    // không dạng núi
    return -5;      
}

// tìm min max vị trí đầu này chắc dễ rồi cũng tìm min max mà
int _su_kien_thu_13_3(int arr[], int n){
    int maxi2 = 0 , mini2 = 0;
    for(int i = 0; i < n; i++){
        maxi2 = arr[i] > arr[maxi2] ? i : maxi2;
        mini2 = arr[i] < arr[mini2] ? i : mini2;
    }    
    return maxi2 + mini2;   
}

int _su_kien_thu_13_4(int arr[], int n){
    // TH nếu có 2 phần tử n == 2 thì nào bé hơn thì sẽ là max2 tương ứng min 
    if(n == 2 && arr[1] < arr[0]) return arr[1] + 1; // arr[0] lớn hơn 
    else if(n == 2 && arr[0] < arr[1]) return arr[0]; // arr[1] lớn hơn 
    // TH đủ 3 số và 3 số phải khác nhau nếu bằng nhau thì ko tìm được max2
    else if(n >= 3 && !(arr[0] == arr[1] && arr[0] == arr[2])){
        int max1 = max(arr[0], max(arr[1], arr[2])); // tìm max trong 3 số;
        int min1 = min(arr[0], min(arr[1], arr[2])); // tìm min trong 3 số;
        int sum = arr[0] + arr[1] + arr[2];
        int max2 = sum - min1 - max1; // số giữa min và max thì là max2 rồi
        if(max2 == max1) max2 = min1; // nếu max1 = max2 thì số max2 = min1
        if(max2 == arr[0]) return arr[0];
        else if(max2 == arr[1]) return arr[1] + 1;
        else if(max2 == arr[2]) return arr[2] + 2;
    } 
    return -12;
}

void _su_kien_thu_13(string s, int& HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int& resuce){

    // nhập file
    ifstream input(file_mush_ghost); 
    int n2;
    input >> n2;    // nhập hàng 1 với n2 là số lượng hàng tiếp theo

    int arr[101] = {0};
    for(int i = 0; i < n2; i++){
        // nhập mảng loại nấm vì các số cách nhau dấu ',' nên getline tới dấu ',' -> lưu vào mảng arr
        string temp;
        getline(input, temp, ',');
        arr[i] = stoi(temp);
    }
    // nấm loại 1 = maxi + mini
    int mush1 = _su_kien_thu_13_1(arr,n2);
    // nấm loại 2 = mtx + mti
    int mush2 = _su_kien_thu_13_2(arr,n2);

    // thay đổi arr để sử lí 2 nấm còn lại 
    for(int i = 0; i < n2; i++){
        arr[i] = (17*abs(arr[i])+9)%257;
        //cout << arr[i] << " ";

    }

    // nấm loại 3 = maxi2 + mini2
    int mush3 = _su_kien_thu_13_3(arr,n2);
    // nấm loại 4 = max2_3x + max2_3i
    int mush4 = _su_kien_thu_13_4(arr,n2);
    // chuỗi nấm vd 131423 ta cần lấy 1423 thì i chạy từ 2 -> lenght
    for(int i = 2; i < s.length(); i++){
        char c = s[i];
        if(c == '1') HP -= mush1; // nấm 1
        else if(c == '2') HP -= mush2; // nấm 2
        else if(c == '3') HP -= mush3; // nấm 3
        else if(c == '4') HP -= mush4; // nấm 4
        // CẬP NHẬT HP
        if(HP > MAXHP) HP = MAXHP;
        if(HP <= 0){
            // nếu có thuốc phượng hoàng hồi sinh thì sẽ sống mà HP về lại Maxhp các hiệu ứng nấm ếch biến mất
            if(phoenixdown > 0){
                phoenixdown --;
                HP =  MAXHP;
                // hiệu ứng nấm và ếch biến mất 
                if( hit_Frog != 0)  level =  LEVELOLD; //
                hit_Mushroom =  hit_Frog = 0;                
            }
            else return; // không có thuốc thì chết thôi :)))
        } 
    }
}



void _su_kien_thu_18(int& HP){
    // nhập file file_merlin_pack đã sử lí trong hàm file input
    ifstream input(file_merlin_pack); 
    // bien string lưu tạm 
    string temp;
    // nhập n9
    getline(input, temp);
    int n9 = stoi(temp);

    // nhập các dòng còn lại 
    for(int i = 0; i < n9; i++){
        // nhập chuỗi từng dòng và xử lí
        getline(input, temp);
        // nếu có chuỗi merlin and Merlin thì HP += 3 hàm find nếu tìm ko thấy thì string::npos
        // temp.find("Merlin") != string::npos tìm thấy -> true không thấy -> false
        if(temp.find("Merlin") != string::npos || temp.find("merlin") != string::npos) HP += 3;
        else{
            // tìm có tồn tại các chữ m e r l i n in hoa và thường trong chuỗi hay không 
            bool check = (temp.find('M') != string::npos || temp.find('m') != string::npos)
                    && (temp.find('E') != string::npos || temp.find('e') != string::npos)
                    && (temp.find('R') != string::npos || temp.find('r') != string::npos)
                    && (temp.find('L') != string::npos || temp.find('l') != string::npos)
                    && (temp.find('I') != string::npos || temp.find('i') != string::npos)
                    && (temp.find('N') != string::npos || temp.find('n') != string::npos);
            // nếu tồn tại thì HP += 2
            if(check == true) HP += 2;
            // bool arr[256] = {false};
            // for(char c : temp) arr[c]  = true;
            // if((arr['M'] || arr['m']) && (arr['E'] || arr['e']) && (arr['R'] || arr['r'])
            // && (arr['L'] || arr['l']) && (arr['I'] || arr['i']) && (arr['C'] || arr['c'])) HP += 2;
        }
    }
}

void _su_kien_thu_19(int& maidenkiss, int & remedy, int&phoenixdown){

    // nhập file 2 giá trị r1 và c1 tại dòng 1 của file file_Asclepius_pack
    // r1 là số hàng 
    // c1 thuốc trong 1 hàng
    ifstream input(file_Asclepius_pack); 
    int r1, c1;
    input >> r1 >> c1;

    // check từng từ trong 1 hàng for ngoài là hàng for trong là cột hay thuốc
    for(int i = 0; i < r1; i++){
        int count = 0;  // đếm số lượng cập nhật lại = 0
        for(int j = 0; j < c1; j++){
            int number; // nhâp giá trị thuốc 
            input >> number;    

            if(count == 3) continue;    // đã đủ thuốc 1 hàm
            // nếu giá trị của thuốc nằm trong giá trị 16, 17 , 18 tương ứng thuốc remedy maidenkiss phoenixdown thì count tăng lên
            // nếu count == 3 thì việc tìm kiếm thuốc sẽ dừng lại chờ tới hàng say
            if(number >= 16 && number <= 18){
                count ++; // tăng số lượng thuốc
                if(number == 16)  remedy ++;
                else if(number == 17 )  maidenkiss ++;
                else if(number == 18 )  phoenixdown ++;
            }
        }
    }    
}

string file(string file_input , int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown){
    // nhập file input
    ifstream input(file_input);
    // hàng 1 2 và 3 
    string row1, row2, row3;
    getline(input, row1);   // nhập hàng 1 vào row1
    getline(input, row2);   // nhập hàng 2 vào row3
    getline(input, row3);   // nhập hàng 3 vào row2
            

    // xử lí row 1 đưa row1 vào string stream lúc này string stream như 1 file có lưu trữ chuỗi row1
    // row1 gồm HP, level, remedy, maidenkiss, phoenixdown
    stringstream ss1(row1);
    ss1 >>  HP >>  level >>  remedy >>  maidenkiss >>  phoenixdown;   // nhập giống cin cin cin cin >>  
    
    // cập nhật MAXHP
    MAXHP = HP;
    // nếu MAXHP == 99 -> vua Arthur gán figer = 1
    // nếu MAXHP là số nguyên tố -> hiệp sĩ Lancelot gán figer = -1
    // nếu không phải 2 TH trên thì sẽ là hiệp sĩ bàn tròn gán figer = 0
    if(MAXHP == 999) figer = 1;
    else if(checkPrime(MAXHP)) figer = -1;
    else figer = 0;

    // như phần row1 nhưng row3 cách nhau bởi dấu ',' nên dùng getline để lấy từng chuỗi
    stringstream ss3(row3);
    getline(ss3, file_mush_ghost, ',');
    getline(ss3, file_Asclepius_pack, ',');
    getline(ss3, file_merlin_pack);

    // trả về row2 để chạy thứ tự sự kiện
    return row2;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    // đang diễn ra nên kq là -1
    rescue = -1;


    // lúc ban đầu hit_Frog và hit_Mushroom  = 0 vì nhân vật chưa bị trúng chiêu
    hit_Frog = hit_Mushroom = 0;
    meet_Asclepius = meet_Merlin = false;


    // event là row2 sự kiện xử lí trong hàm file
    string event = file(file_input, HP, level, remedy, maidenkiss, phoenixdown);

    stringstream ss(event);
    ss >> event;

    for(int i = 1; true; i++){
        // mã sự kiện
        int number_event = event[0] - '0';      // lấy số đầu tiên mã sự kiện VD 15 ->  event[0] - '0' = '1' - '0' = 1
        // nếu event chỉ có lenght 1 hay có phần '\r' ở cuối này do phần mền bkel thì number ko cần thay đổi
        // nếu ko phải thì phải cập VD 14 -> number_event = (event[0] - '0')*10 + event[i] - '0' = 14
        if( event[1] != '\0' && event[1] != '\r') number_event = number_event * 10 + event[1] - '0';

        if(number_event == 0) rescue = 1; // win win win
        // gặp quái từ 1 -> 5
        else if( number_event>=1 && number_event <= 5) _su_kien_thu_1_2_3_4_5(number_event , i , HP, level);
        // gặp quái 6
        else if(number_event == 6)  _su_kien_thu_6(level, i , HP, remedy);
        // gặp quái 7
        else if(number_event == 7) _su_kien_thu_7(level, i, maidenkiss);
        // sự kiện 11
        else if(number_event == 11) _su_kien_thu_11(HP, level, phoenixdown);
        // sự kiện 12
        else if(number_event == 12) _su_kien_thu_12(HP);
        // sự kiện 13
        else if(number_event == 13)  _su_kien_thu_13(event, HP, level, remedy, maidenkiss, phoenixdown, rescue);
        // sự kiện 15 -> remedy tăng lên 1
        else if(number_event == 15) remedy ++;
        // sự kiện 16 -> maidenkiss tăng lên 1
        else if(number_event == 16) maidenkiss ++;
        // sự kiện 17 -> phoenixdown tăng lên 1
        else if(number_event == 17) phoenixdown ++;
        // sự kiện 18
        else if(number_event == 18 && !meet_Merlin){
            _su_kien_thu_18(HP);
            meet_Merlin = true; // đã găp phù thủy Merlin
        }
        // sự kiện 19
        else if(number_event == 19 && !meet_Asclepius){
            _su_kien_thu_19(maidenkiss, remedy, phoenixdown);
            meet_Asclepius = true;// đã găp thần Asclepius
        }
        // sự kiện 99
        else if(number_event == 99){
            // vua Arthur and  Lancelot nếu level >= 8 thì thằng level tăng lên 10
            if(figer == 1 || figer == -1 && level >= 8) level = 10;
            // hiệp sĩ bàn tròn phải level == 10 mới thắng
            else if(level == 10) level = 10;
            else rescue = 0; // thua rồi :(((
        }

        // kiểm tra HP có <= 0 hay không
        if(HP <= 0){
            // nếu có thuốc phượng hoàng hồi sinh thì sẽ sống mà HP về lại Maxhp các hiệu ứng tí haon ếch biến mất
            if(phoenixdown > 0){
                phoenixdown --;
                HP =  MAXHP;
                // hiệu ứng nấm và ếch biến mất 
                if( hit_Frog != 0)  level =  LEVELOLD; //
                hit_Mushroom =  hit_Frog = 0;                
            }
            else rescue = 0; // không có thuốc thì chết thôi :)))
        }
        // xem thử thắng hay thua nếu == -1 thì đang diễn ra nếu thua hoặc thắng thì nghỉ chơi
        if(rescue == 0 || rescue == 1) break;

        // xem thử bị hit nấm hay ếch hay không
        // bị hit nấm
        if(hit_Mushroom > 0){
            // nếu có thuốc thì giải thôi
            if(remedy > 0){
                remedy --;  
                hit_Mushroom = 0;    
                HP *= 5;    
            }
            else{
                hit_Mushroom --; // trừ đi từng sự kiện đến 0 thì hết hiện ứng nấm
                if(hit_Mushroom == 0) HP *= 5;
            }
        }
        // bị hit ếch
        else if( hit_Frog > 0){
            // nếu có thuốc thì giải thôi
            if( maidenkiss > 0){
                maidenkiss --;  
                hit_Frog = 0;    
                level =  LEVELOLD;          
            }
            else{
                hit_Frog --; // trừ đi từng sự kiện đến 0 thì hết hiện ứng nấm
                if(hit_Frog == 0) level = LEVELOLD;
            }
        }  

        // cập nhật lại các giá trị nếu vượt quá MAX
        if(HP > MAXHP) HP = MAXHP;
        if(level > 10) level = 10;
        if(remedy > 99) remedy = 99;
        if(maidenkiss > 99) maidenkiss = 99;
        if(phoenixdown > 99) phoenixdown = 99;

        // nhập sự kiện tiếp theo nếu hết thì ss >> event trả về false kết thúc nếu còn thì tiếp tục
        if(ss >> event) display( HP,  level,  remedy,  maidenkiss,  phoenixdown, -1); 
        // hết rồi thắng thôi
        else{
            rescue = 1;
            break;
        }
    }
    display( HP,  level,  remedy,  maidenkiss,  phoenixdown, rescue); 
}