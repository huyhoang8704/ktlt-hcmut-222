#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);
int levelO(int i);  // tinh level doi thu
int min(int &HP, int &maxHP);  // tim so nho nhat cua 2 so
int minn(int a);
int minHP(int &HP, int &maxHP);
int min_level(int &level);
bool isPrime(int n);     //kiem tra xem n co phai so nguyen to khong
int findPrimeNum(int n);// Nhập vào số nguyên n và trả về số nguyên tố > n và gần n nhất
int s1(int n);         // tong n chu so le lon nhat co 2 chu so
int fibonacci_closest(int x); //tra mau ve so fibo gan nhat
bool checkArthur(int &HP);
bool check13(int num);    // check sk13
void openfile(string &file_input,int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,
 string &line2,string &mushghost,string &asclepius,string &merlin); // mo file
void mushGhost1(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr[],int n2,int maxHP);
void mushGhost2(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr[],int n2,int maxHP);
void mushGhost3(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr3[],int n2,int maxHP);
void mushGhost4(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,int arr4[],int n2,int maxHP);
void mushGhost(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string eventcode,string mushGhostpatch,int maxHP);
bool checkmerlin(string line);
void sk18(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string merlinpatch,int maxHP);
void sk19(int &HP, int &level, int &remedy, int &maidenkiss,int &phoenixdown,int &rescue,string asclepiusPatch,int maxHP);
#endif // __KNIGHT_H__