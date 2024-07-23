#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

class BaseKnight;
class NormalKnight;
class DragonKnight;
class LancelotKnight;
class PaladinKnight;
class BaseItem;
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
bool isPrime(int num);
int levelO(int i, int eventid);
//#define DEBUG


enum ItemType {
Antidoteitem=0,PhoenixdownIitem,PhoenixdownIIitem,PhoenixdownIIIitem,PhoenixdownIVitem,Phoenixdown
};

                        class BaseBag // Túi đồ Hiệp sĩ
{
protected:
    class node{
    public:
        BaseItem *data=nullptr;
        node *pNext=nullptr;
    };
protected:
    node *pHead=nullptr;
    BaseKnight *knight_;  // biểu diễn hiệp sĩ đang sở hữu túi đồ này
    int size=0,maxsize=0; // size là kích thước hiện tại của 1 túi, max là không gian tối đa của một túi
public:
    BaseBag(BaseKnight *knight_);
    virtual bool useItem(ItemType itemType);
    virtual BaseItem *checkPhoenixdown();
    virtual void XoaItem(); // xóa node
    virtual void Xoa3Item();
    virtual bool insertFirst(BaseItem * item); // trả về true nếu vật phẩm có thể thêm vào túi đồ
    virtual BaseItem * get(ItemType itemType); // trả về con trỏ đến 1 vật phẩm trong túi đồ
    virtual string toString() const;  // trả về chuỗi string biểu diễn thông tin cho đối tượng BaseIteam
    ~BaseBag();
};
class BagPaladin : public BaseBag{
public:
    BagPaladin(BaseKnight *knight_);
};
class BagLancelot : public BaseBag{
public:
    BagLancelot(BaseKnight *knight_);
};
class BagNormalKnight : public BaseBag{
public:
    BagNormalKnight(BaseKnight *knight_);
};
class BagDragon : public BaseBag{
public:
    BagDragon(BaseKnight *knight_);
    bool insertFirst (BaseItem * item); 
};






enum OpponentType{
    MadBearType=1,BanditType,LordLupinType,ElfType,TrollType,TornberyType,QueenOfCardsType,
    NinaDeRingsType,VuonSauRiengType,OmegaWeaponType,HadesType,
};
            class BaseOpponent // Đối thủ
{
public:
    // 2 biến static để xác định đã giết được 2 con quái vật OmegaWeapon và Hades hay chưa
    static bool WinOmegaWeapon;
    static bool WinHades;
protected:
    int i;  // thứ tự của sự kiện

public:
    static BaseOpponent* createOpponent(int i,OpponentType opponenttype);  // như baseknight
    virtual void Cap_Nhat_Knight(BaseKnight * knight_)=0;   // chiến đấu
    virtual OpponentType Type()=0;
};
class MadBear: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class Bandit: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class LordLupin: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class Elf: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class Troll: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
}; 
class Tornbery: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class QueenOfCards: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class NinaDeRings: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class VuonSauRieng: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class OmegaWeapon: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};
class Hades: public BaseOpponent{
    public:
    void Cap_Nhat_Knight(BaseKnight * knight_);
    OpponentType Type();
};



enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
                    class BaseKnight // Biểu diễn thông tin Hiệp sĩ
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType; // biểu diễn loại hiệp sĩ có 4 loại
    bool TrungDoc=0;        // kiểm tra xem có bị trúng độc hay không
    int Gil_thua=0;         // số vàng dư khi gil >999
public:
    void sethp(int hp);
    int gethp();
    int getmaxhp();
    void setlevel(int level);
    int getlevel();
    int getgil();
    void setgil(int gil);
    bool getTrungDoc();
    void setTrungDoc(bool Poisoned);
    int getGil_thua();
    bool setBag(BaseItem *item);

public:
    BaseKnight();
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    virtual bool fight(BaseOpponent *opponent);  // mô tả quá trình Hiệp sĩ đấu với đối thủ nếu thua trả về false thắng ngược l
    virtual int damageUltimecia()=0; // tính số dameage cho boss cuối cùng đọc sự kiện 99
    ~BaseKnight();
};
class PaladinKnight: public BaseKnight{
public:
    PaladinKnight();
    int damageUltimecia();
    bool fight(BaseOpponent *opponent);
};
class LancelotKnight: public BaseKnight{
public:
    LancelotKnight();
    int damageUltimecia();
    bool fight(BaseOpponent *opponent);
};
class DragonKnight: public BaseKnight{
public:
    DragonKnight();
    int damageUltimecia();
    bool fight(BaseOpponent *opponent);
};
class NormalKnight: public BaseKnight{
public:
    NormalKnight();
    int damageUltimecia();
    bool fight(BaseOpponent *opponent);
};
                    class ArmyKnights  // Đội quân Hiệp sĩ
{
private:
    int size; // số lượng hiệp sĩ
    BaseKnight **Hiepsi;
    bool hasPaladinShield_,hasLancelotSpear_,hasGuinevereHair_,hasExcaliburSword_;
public:
    ArmyKnights (const string & file_armyknights);  // file chứa thông tin hiệp sĩ
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);  // mô tả quá trình đội quân hiệp sĩ giao đấu với đối thủ
    bool adventure (Events * events);  // class chứa sự kiện trong hành trình
    int count() const;  // đếm số lượng Hiệp sĩ hiện tại
    BaseKnight * lastKnight() const; // trả về Hiệp sĩ cuối cùng , nếu không còn thì trả về NULL
    bool hasPaladinShield() const; // khiên của Paladin
    bool hasLancelotSpear() const; // Ngọn giáo của LAncelot
    bool hasGuinevereHair() const; // Sợi tóc của công chúa
    bool hasExcaliburSword() const;// Gươm 
    void printInfo() const;
    void printResult(bool win) const;
};

                class BaseItem // Biểu diễn thông tin cho 1 vật phẩm
{ 
public:
    virtual bool canUse ( BaseKnight * knight ) = 0; // trả về true nếu dùng được vật phẩm này
    virtual void use ( BaseKnight * knight ) = 0; //thực hiện tác động lên Hiệp sĩ biểu diễn bởi knight nhằm thay đổi các thông số của Hiệp sĩ cho phù hợp với tác dụng của vật phẩm
    virtual ItemType Type()=0;                    // trả về kiểu dữ liệu
    virtual string toString()=0;                  // return về chuỗi theo kiểu enum vd "Antidote"
};
// Biểu diễn các vật phẩm bởi class
class Antidote :public BaseItem{
public:
    bool canUse( BaseKnight * knight );
    void use ( BaseKnight * knight );
    ItemType Type();
    string toString();
};
class PhoenixdownI :public BaseItem{
public:
    bool canUse( BaseKnight * knight );
    void use ( BaseKnight * knight );
    ItemType Type();
    string toString();
};
class PhoenixdownII :public BaseItem{
public:
    bool canUse( BaseKnight * knight );
    void use ( BaseKnight * knight );
    ItemType Type();
    string toString();
};
class PhoenixdownIII :public BaseItem{
public:
    bool canUse( BaseKnight * knight );
    void use ( BaseKnight * knight );
    ItemType Type();
    string toString();
};
class PhoenixdownIV :public BaseItem{
public:
    bool canUse( BaseKnight * knight );
    void use ( BaseKnight * knight );
    ItemType Type();
    string toString();
};
            class Events // sự kiện của hành trình                                                              
{
private:
    int e;           // biến đếm số sự kiện
    int *event;          // chưa delete , sự kiện
public:
    Events(const string &file_events);
    ~Events();
    int count() const;          // trả về số lượng sự kiện
    int get(int i) const;       // trả về mã sự kiện ở vị trí i vd: 5 6 7 get(2)=7
};
            class KnightAdventure { 
private:
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:
    void loadArmyKnights(const string &); // truyền dữ liệu vào
    void loadEvents(const string &);
    void run();
};
#endif // __KNIGHT2_H__