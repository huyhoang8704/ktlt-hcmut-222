#include "knight2.h"

class BaseKnight;
class NormalKnight;
class DragonKnight;
class LancelotKnight;
class PaladinKnight;
class BaseItem;
class Antidote;
class PhoenixdownI;
class PhoenixdownII;
class PhoenixdownIII;
class PhoenixdownIV;
class Events;
class BaseBag;
class BagPaladin;
class BagLancelot;
class BagNormalKnight;
class BagDragon;
class BaseOpponent;
class MadBear;
class Bandit;
class LordLupin;
class Elf;
class Troll;
class Tornbery;
class QueenOfCards;
class NinaDeRings;
class OmegaWeapon;
class VuonSauRieng;
class Hades;

bool isPrime(int num) {
  // Trường hợp đặc biệt
  if (num <= 1) {return false;}
  // Kiểm tra từ 2 đến căn bậc hai của số đó
  for (int i = 2; i <= sqrt(num); i++) {
    if (num % i == 0) {return false;}
  }
  return true;
}
int levelO(int i, int eventid){ return (i+eventid)%10 +1;}
bool BaseOpponent::WinHades=false;
bool BaseOpponent::WinOmegaWeapon=false;
/* * * BEGIN implementation of class BaseBag * * */

BaseBag::BaseBag(BaseKnight *knight){
    this->knight_=knight;
    this->maxsize=0;
    this->pHead=nullptr;
    this->size=0;
}
bool BaseBag::insertFirst(BaseItem * item){
    if (size>=maxsize) return false;
    node *p= new node();
    p->data=item;
    p->pNext=pHead;
    pHead=p;
    size ++;
    return true;
}
void BaseBag::XoaItem(){
    if (size<=0) return;
    size--;
    node *p=new node();
    p=pHead;
    pHead=pHead->pNext;
    delete p;       // xóa phần tử đầu tiên ra khỏi bộ nhớ
}
void BaseBag::Xoa3Item(){
    XoaItem();
    XoaItem();
    XoaItem();
}
BaseItem * BaseBag::get(ItemType itemType){
    if(size <= 0) return nullptr;
    node *p=pHead;
    while(p && p->data->Type() != itemType) p = p->pNext;
    // nếu tìm thấy vật phẩm thì đổi vị trí và return về nó 
    if(p){
        swap(pHead->data, p->data);
        return pHead->data;
    }
    return nullptr;
}
BaseItem *BaseBag::checkPhoenixdown(){
    if (size==0) return nullptr;
    node *p=pHead;
    while (p && !p->data->canUse(knight_)) p=p->pNext;
    if (p){
        swap(pHead->data,p->data);
        return pHead->data;
    }
    return nullptr;
}
bool BaseBag::useItem(ItemType itemType){
    BaseItem* p = nullptr;
    if(itemType == Antidoteitem)                p = get(Antidoteitem);
    else p=checkPhoenixdown();


    if(p == nullptr) return false;    // không có vật phẩm
    // nếu có vật phẩm thì sài
    this->pHead->data->use(knight_);  // sử dụng vật phẩm xong rồi xóa
    XoaItem();
    return true;
}
string BaseBag::toString()const{
    if (size==0) return "Bag[count=0;]";
    string ket_qua = "Bag[count=" + to_string(size)+";";
    node *p=pHead;
    while (p){
        ket_qua +=p->data->toString()+",";
        p=p->pNext;
    }
    ket_qua[ket_qua.length()-1]=']';
    return ket_qua;
}
BaseBag::~BaseBag(){ while(size>0)  XoaItem();}



// kế thừa constructor của lớp cha 
BagPaladin::BagPaladin(BaseKnight *knight_):BaseBag(knight_){
    this ->maxsize=-1;
}
BagLancelot::BagLancelot(BaseKnight *knight_):BaseBag(knight_){
    this ->maxsize=16;
}
BagNormalKnight::BagNormalKnight(BaseKnight *knight_):BaseBag(knight_){
    this ->maxsize=19;
}
BagDragon::BagDragon(BaseKnight *knight_):BaseBag(knight_){
    this ->maxsize=14;
}
bool BagDragon::insertFirst(BaseItem *item){
    if (size >=maxsize || item->Type()==Antidoteitem) return false;
    node *p= new node();
    p->data=item;
    p->pNext=pHead;
    pHead=p;
    size ++;
    return true;
}

/* * * END implementation of class BaseBag * * */
// CLASS EVENTS
Events::Events(const string &file){
    ifstream inputt(file);
    // line 1
    inputt >> e;
    event = new int [e];
    for(int i = 0; i < e; i++) inputt >> event[i];
}
int Events::count() const{    // đếm số sự kiện
    return e;
}
int Events::get(int k)const{  // lấy ra sự kiện th
    return event[k];
}
Events::~Events(){
    delete[] event;
}   // hủy 

// END EVENTS



/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight::BaseKnight(){}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight *knight_;
    
    switch (maxhp) {
    case 888:
        knight_ = new LancelotKnight();
        knight_->bag = new BagLancelot(knight_);
        break;
    case 345: case 354: case 435: case 453: case 534: case 543:
        knight_ = new DragonKnight();
        knight_->bag = new BagDragon(knight_);
        break;
    default:
        if (isPrime(maxhp)) {
            knight_ = new PaladinKnight();
            knight_->bag = new BagPaladin(knight_);
        } else {
            knight_ = new NormalKnight();
            knight_->bag = new BagNormalKnight(knight_);
        }
        break;
}
    knight_ ->id=id;
    knight_ ->maxhp=knight_->hp=maxhp;
    knight_ ->level=level;
    knight_ ->gil=gil;
    // thêm phoenixdown và antidote vào túi đồ
    for (int i=1;i<=phoenixdownI;i++){
        BaseItem *VatPham =new PhoenixdownI();
        if (!knight_->bag->insertFirst(VatPham)) delete VatPham;
    }
    for (int i=1;i<=antidote;i++){
        BaseItem *VatPham =new Antidote();
        if (!knight_->bag->insertFirst(VatPham)) delete VatPham;
    }
    return knight_;
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
int BaseKnight::gethp(){ return hp;}
void BaseKnight::sethp(int hp){
    if (hp >maxhp) this->hp=maxhp;
    else this->hp=hp;
}
int BaseKnight::getlevel(){return level;}
void BaseKnight::setlevel(int level){
    if (level>10) this->level=10;
    else this->level=level;
}
int BaseKnight::getmaxhp(){return this->maxhp;}
int BaseKnight::getgil(){ return this->gil;}
void BaseKnight::setgil(int gil){
    if (gil>999){
        this->Gil_thua=gil-999;
        this->gil=999;
    }
    else this->gil=gil;
}
int BaseKnight::getGil_thua(){
    int thua;
    thua =this->Gil_thua;   // gán qua rồi thì cho Gil_thua =0;
    this->Gil_thua=0;
    return thua;
}
bool BaseKnight::getTrungDoc(){return TrungDoc;}
void BaseKnight::setTrungDoc(bool trungdoc){ this->TrungDoc=trungdoc;}
// thêm vật phẩm vào đầu túi đồ khi gặp sk 112 113 114
bool BaseKnight::setBag(BaseItem *item){
    return bag->insertFirst(item);
}
bool BaseKnight::fight(BaseOpponent *opponent){
     if (this ->TrungDoc){
         this->bag->useItem(Antidoteitem);
         if (this->TrungDoc){
             this->TrungDoc=false;
             this->bag->Xoa3Item();
             this->sethp(this->hp-10);
         }
     }
     if (hp <=0 || hp <maxhp /4 || hp <maxhp /3 || hp<maxhp /2) this->bag->useItem(Phoenixdown);
     if (this->hp <=0 && this->gil >=100){
        this->hp=this->maxhp /2 ;
        this->gil -=100;
     }
     //cout <<hp;
     return this->hp >0;
}
BaseKnight::~BaseKnight(){
    delete bag;
}


// PALADIN
PaladinKnight::PaladinKnight(){
    this ->knightType=PALADIN;
}
int PaladinKnight::damageUltimecia(){
    return this ->hp * this->level * 0.06;
}
bool PaladinKnight::fight(BaseOpponent *opponent){
    if (opponent->Type()==MadBearType)        this ->setgil(this->getgil()+100);              // sự kiện 1
    else if (opponent->Type()==BanditType)    this ->setgil(this->getgil()+150);          // sự kiện 2
    else if (opponent->Type()==LordLupinType) this ->setgil(this->getgil()+450);       // sự kiện 3
    else if (opponent->Type()==ElfType)       this ->setgil(this->getgil()+750);             // sự kiện 4
    else if (opponent->Type()==TrollType)     this ->setgil(this->getgil()+800);           // sự kiện 5
    // sự kiện 7
    else if (opponent->Type()==QueenOfCardsType){
        int Gil_old= this->gil;
        opponent->Cap_Nhat_Knight(this);
        if (Gil_old >this->getgil()) this->gil=Gil_old;
    }
    //NinaDeRings
    else if (opponent->Type()==NinaDeRingsType){ if (hp < maxhp/3 )   this->sethp( hp+= maxhp/5);}
    else if (opponent->Type()==HadesType && this->level >=8)         BaseOpponent::WinHades=true;
    else opponent->Cap_Nhat_Knight(this);
    return BaseKnight::fight(opponent);
}
// LANCELOT
LancelotKnight::LancelotKnight(){
    this ->knightType=LANCELOT;
}
int LancelotKnight::damageUltimecia(){
    return this ->hp * this->level *0.05;
}
bool LancelotKnight::fight(BaseOpponent *opponent){
    if (opponent->Type()==MadBearType)            this ->setgil(this->getgil()+100);              // sự kiện 1
    else if (opponent->Type()==BanditType)        this ->setgil(this->getgil()+150);          // sự kiện 2
    else if (opponent->Type()==LordLupinType)     this ->setgil(this->getgil()+450);       // sự kiện 3
    else if (opponent->Type()==ElfType)           this ->setgil(this->getgil()+750);             // sự kiện 4
    else if (opponent->Type()==TrollType)         this ->setgil(this->getgil()+800);           // sự kiện 5
    else opponent->Cap_Nhat_Knight(this);
    return BaseKnight::fight(opponent);
}
// DRAGONKNIGHT
DragonKnight::DragonKnight(){
    this->knightType=DRAGON;
}
int DragonKnight::damageUltimecia(){ return this->hp * this->level * 0.075;}
bool DragonKnight::fight(BaseOpponent *opponent){
    if (opponent->Type()==OmegaWeaponType && BaseOpponent::WinOmegaWeapon==false){
        this->level=10;
        this->gil=999;
        BaseOpponent::WinOmegaWeapon=true;
    }
    else opponent->Cap_Nhat_Knight(this);
    this->TrungDoc=false;
    return BaseKnight::fight(opponent);
}
// NORMALKNIGHT
NormalKnight::NormalKnight(){ this->knightType=NORMAL;}
int NormalKnight::damageUltimecia(){ return 0*this->hp*this->level;}
bool NormalKnight::fight(BaseOpponent *opponent){
    if (opponent->Type()==OmegaWeaponType){
        if (BaseOpponent::WinOmegaWeapon) return true;
        else if (level==10 && maxhp==hp){
            gil=999;
            BaseOpponent::WinOmegaWeapon=true;
        }
        else this->sethp(0);
    }
    else opponent->Cap_Nhat_Knight(this);
    return BaseKnight::fight(opponent);
}
/* * * END implementation of class BaseKnight * * */




/* * * BEGIN implementation of class BaseOpponent * * */
BaseOpponent *BaseOpponent::createOpponent(int i,OpponentType opponenttype){
    BaseOpponent *opponent;
    switch (opponenttype) {
    case MadBearType: opponent = new MadBear(); break;
    case BanditType: opponent = new Bandit(); break;
    case LordLupinType: opponent = new LordLupin(); break;
    case ElfType: opponent = new Elf(); break;
    case TrollType: opponent = new Troll(); break;
    case TornberyType: opponent = new Tornbery(); break;
    case QueenOfCardsType: opponent = new QueenOfCards(); break;
    case NinaDeRingsType: opponent = new NinaDeRings(); break;
    case VuonSauRiengType: opponent = new VuonSauRieng(); break;
    case OmegaWeaponType: opponent = new OmegaWeapon(); break;
    case HadesType: opponent = new Hades(); break;
    default: return nullptr;
}
    opponent->i=i;
    return opponent;
}
// MADBEAR
OpponentType MadBear::Type(){ return MadBearType;}
void MadBear::Cap_Nhat_Knight(BaseKnight *knight_){
    if (knight_->getlevel() >= levelO(this->i,this->Type())) knight_->setgil(knight_->getgil()+100);
    else knight_->sethp(knight_->gethp()-10*(levelO(this->i,this->Type()-knight_->getlevel())));
}
// BANDIT
OpponentType Bandit::Type(){ return BanditType;}
void Bandit::Cap_Nhat_Knight(BaseKnight *knight_){
    if (knight_->getlevel() >= levelO(this->i,this->Type())) knight_->setgil(knight_->getgil()+150);
    else knight_->sethp(knight_->gethp()-15*(levelO(this->i,this->Type()-knight_->getlevel())));
}
// LORDLUPIN
OpponentType LordLupin::Type(){ return LordLupinType;}
void LordLupin::Cap_Nhat_Knight(BaseKnight *knight_){
    if (knight_->getlevel() >= levelO(this->i,this->Type())) knight_->setgil(knight_->getgil()+450);
    else knight_->sethp(knight_->gethp()-45*(levelO(this->i,this->Type()-knight_->getlevel())));
}
// ELF
OpponentType Elf::Type(){ return ElfType;}
void Elf::Cap_Nhat_Knight(BaseKnight *knight_){
    if (knight_->getlevel() >= levelO(this->i,this->Type())) knight_->setgil(knight_->getgil()+750);
    else knight_->sethp(knight_->gethp()-75*(levelO(this->i,this->Type()-knight_->getlevel())));
}
// TROLL
OpponentType Troll::Type(){ return TrollType;}
void Troll::Cap_Nhat_Knight(BaseKnight *knight_){
    if (knight_->getlevel() >= levelO(this->i,this->Type())) knight_->setgil(knight_->getgil()+800);
    else knight_->sethp(knight_->gethp()-95*(levelO(this->i,this->Type()-knight_->getlevel())));
}
// TORNBERY
OpponentType  Tornbery::Type(){ return TornberyType;}
void Tornbery::Cap_Nhat_Knight(BaseKnight *knight_){
    if (knight_->getlevel() >= levelO(this->i,this->Type())) knight_->setlevel(knight_->getlevel()+1);
    else if  (knight_->getlevel() < levelO(this->i,this->Type())) knight_->setTrungDoc(true);
    
}
// QUEEN OF CARDS
OpponentType QueenOfCards::Type(){ return QueenOfCardsType;}
void QueenOfCards::Cap_Nhat_Knight(BaseKnight *knight_){
    if (knight_->getlevel() >= levelO(this->i,this->Type())) knight_->setgil((knight_->getgil())*2);
    else knight_->setgil(knight_->getgil() /2);
}
// NINA DE RINGS
OpponentType NinaDeRings::Type(){ return NinaDeRingsType;}
void NinaDeRings::Cap_Nhat_Knight(BaseKnight *knight_){
    if( knight_->gethp() < knight_->getmaxhp() /3 && knight_->getgil() >=50){
        knight_->setgil(knight_->getgil()-50); // đưa cho nina 50 gil
        knight_->sethp(knight_->gethp() + knight_->getmaxhp() /5);
    }
}
//  VƯỜN SẦU RIÊNG 
OpponentType VuonSauRieng::Type(){ return VuonSauRiengType;}
void VuonSauRieng::Cap_Nhat_Knight(BaseKnight *knight_){
    knight_->sethp(knight_->getmaxhp());
}
//  OMEGA WEAPON
OpponentType OmegaWeapon::Type(){ return OmegaWeaponType;}
void OmegaWeapon::Cap_Nhat_Knight(BaseKnight *knight_){
    if (BaseOpponent::WinOmegaWeapon == true) return;
    else if (knight_->getlevel()==10 && knight_->gethp()==knight_->getmaxhp()){
        BaseOpponent::WinOmegaWeapon == true;
        knight_->setlevel(10);
        knight_->setgil(999);
    }
    else knight_->sethp(0);
}
// HADES
OpponentType Hades::Type(){ return HadesType;}
void Hades::Cap_Nhat_Knight(BaseKnight *knight_){
    if (BaseOpponent::WinHades==true) return;
    else if (knight_->getlevel()==10){
        BaseOpponent::WinHades=true;
        //cout<<"aaaaaaaaaaaa";
    }
    else knight_->sethp(0);
}
/* * * END implementation of class BaseOpponent * * */







/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
ArmyKnights::ArmyKnights(const string & file_armyknights){
    hasExcaliburSword_=hasGuinevereHair_=hasLancelotSpear_=hasPaladinShield_=false;
    ifstream inputt(file_armyknights);
    inputt>>size;
    Hiepsi = new BaseKnight *[size];
    int maxhppppppp,level,phoenixdownI,gil,antidote;
    for (int i=0;i<size;i++){
        inputt >>maxhppppppp>>level>>phoenixdownI>>gil>>antidote;
        Hiepsi[i]= BaseKnight::create(i + 1, maxhppppppp, level, gil,antidote, phoenixdownI);
    }
}
ArmyKnights::~ArmyKnights(){
    for(int i = 0; i < size; i++) delete Hiepsi[i];
    delete[] Hiepsi;
}
bool ArmyKnights::fight(BaseOpponent * opponent){
    // hiệp sĩ giao đấu 
    while(size){
        BaseKnight *llknight= lastKnight();
        if (llknight->fight(opponent)){
            // truyền gil thừa cho hiệp sĩ đứng trước
            for (int i=size-1;i>=0;i--){
                int gil_thua=Hiepsi[i]->getGil_thua();
                if (gil_thua==0 || i==0) break;
                Hiepsi[i-1]->setgil(gil_thua + Hiepsi[i-1]->getgil());
            }
            break;
        }
        size--;
        delete llknight;        // đánh thua thì xóa hiệp sĩ và bỏ qua sự kiện
        break;
    }
    delete opponent;
    return size;
}
bool ArmyKnights::adventure(Events * events){
    for (int i=0;i<events->count();i++){
        int event=events->get(i);
        //cout << "event: " << event << " i = " << i << " --- ";
        if (event>=1  && event <=11){
            this->fight(BaseOpponent::createOpponent(i,OpponentType(event)));
            if (BaseOpponent::WinHades==true){
                this->hasPaladinShield_=true;
            }
        }
        else if (event==95) this->hasPaladinShield_=true;
        else if (event ==96) this->hasLancelotSpear_=true;
        else if (event==97) this->hasGuinevereHair_=true;
        else if (event==98 && hasLancelotSpear_==true && hasPaladinShield_==true && hasGuinevereHair_==true)  this->hasExcaliburSword_=true;
        else if(event == 112 || event == 113 || event == 114){
            BaseItem* VatPham = nullptr;
            if(event == 112) VatPham = new PhoenixdownII();  
            else if(event == 113) VatPham = new PhoenixdownIII();
            else if(event == 114) VatPham = new PhoenixdownIV();
            bool success = false; //! xem thử đã thêm chưa
            for(int j = size - 1 ; j >= 0; j--) if(success = Hiepsi[j]->setBag(VatPham)) break; 
            if(!success) delete VatPham;
        }
        else if (event==99){
            if (hasExcaliburSword_==true){
                this->printInfo();
                return true;
            }
            if (hasGuinevereHair_==false || hasLancelotSpear_==false || hasPaladinShield_==false){
                for (int i=0;i<size;i++) {
                    delete Hiepsi[i];
                }
                delete [] Hiepsi;
                size=0;
            }
            else{
              int hpUltimecia=5000;
              BaseKnight *lastHiepSi=nullptr;
              int Hiep_si_normal =0;

              while (size >0){
                BaseKnight *knight=lastKnight();
                hpUltimecia -= knight->damageUltimecia();
                if (knight->damageUltimecia()==0) Hiep_si_normal++;
                if (knight->damageUltimecia()==0 && !lastHiepSi){
                    lastHiepSi==knight;
                    size--;
                    continue;
                }
                if (hpUltimecia <=0){
                    size += Hiep_si_normal;
                    if (lastHiepSi !=nullptr) Hiepsi[size-1]= lastHiepSi;
                    this->printInfo();
                    if (lastHiepSi !=nullptr) delete lastHiepSi;
                    size -= Hiep_si_normal;
                    return true;
                }
                delete knight;
                size --;
              } 
              if (lastHiepSi) delete lastHiepSi;                 
            }
            this->printInfo();
            return false;
        }
        this->printInfo();
        if (size==0) return false;       
    }
    return true;
}
int ArmyKnights::count() const{ return this->size;}
BaseKnight *ArmyKnights::lastKnight()const{
    return this->Hiepsi[size-1];
}
bool ArmyKnights::hasPaladinShield() const{ return hasPaladinShield_;}
bool ArmyKnights::hasLancelotSpear() const{ return hasLancelotSpear_;}
bool ArmyKnights::hasGuinevereHair() const{ return hasGuinevereHair_;}
bool ArmyKnights::hasExcaliburSword() const{ return hasExcaliburSword_;}


/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string & file){armyKnights = new ArmyKnights(file);}
void KnightAdventure::loadEvents(const string & file){events = new Events(file);}

void KnightAdventure::run(){
    BaseOpponent::WinOmegaWeapon = BaseOpponent::WinHades = false;
    bool end =armyKnights->adventure(events);
    armyKnights->printResult(end);
}
KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    delete events;
}

/* * * END implementation of class KnightAdventure * * */
/*                      BASEITEM
*/
// ANTIDOTE
bool Antidote::canUse( BaseKnight * knight ){
    if (knight->getTrungDoc()==true) return true;
    else return false;
}
void Antidote::use( BaseKnight * knight ){
    knight->setTrungDoc(false);
}
ItemType Antidote::Type(){ return Antidoteitem;
}
string Antidote::toString(){ return "Antidote";
}
// PHOENIXDOWN I
bool PhoenixdownI::canUse( BaseKnight * knight ){ return knight->gethp() <=0;
}
void PhoenixdownI::use( BaseKnight * knight ){  knight->sethp(knight->getmaxhp());
}
ItemType PhoenixdownI::Type(){ return PhoenixdownIitem;
}
string PhoenixdownI::toString(){  return "PhoenixI";
}
// PHOENIXDOWN II
bool PhoenixdownII::canUse( BaseKnight * knight ){ return knight->gethp() < (knight->getmaxhp()/4);
}
void PhoenixdownII::use( BaseKnight * knight ){  knight->sethp(knight->getmaxhp());
}
ItemType PhoenixdownII::Type(){ return PhoenixdownIIitem;
}
string PhoenixdownII::toString(){  return "PhoenixII";
}
// PHOENIXDOWN III
bool PhoenixdownIII::canUse( BaseKnight * knight ){ return knight->gethp() < (knight->getmaxhp())/3;
}
void PhoenixdownIII::use( BaseKnight * knight ){
    if (knight->gethp()<=0) knight->sethp((knight->getmaxhp())/3);
    else knight->sethp(knight->gethp()+(knight->getmaxhp())/4);
}
ItemType PhoenixdownIII::Type(){ return PhoenixdownIIIitem;
}
string PhoenixdownIII::toString(){  return "PhoenixIII";
}
// PHOENIXDOWN IV
bool PhoenixdownIV::canUse( BaseKnight * knight ){ return knight->gethp()< (knight->getmaxhp())/2;
}
void PhoenixdownIV::use( BaseKnight * knight ){
    if (knight->gethp()<=0) knight->sethp((knight->getmaxhp())/2);  
    else knight->sethp(knight->gethp()+(knight->getmaxhp())/5);
}
ItemType PhoenixdownIV::Type(){ return PhoenixdownIVitem;
}
string PhoenixdownIV::toString(){  return "PhoenixIV";
}