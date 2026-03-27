#include <iostream> 
#include <string>
#include <ios>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <array>
#include <vector>
    constexpr unsigned short int Perm_Move {1<<0}; // 0x1
    constexpr unsigned short int Perm_Attact {1<<1};//0x2
    constexpr unsigned short int Perm_Use{1<<2}; // 0x4;
    constexpr unsigned short int Perm_Chat{1<<3}; // 0x8
    constexpr unsigned short int Perm_Admin{1<<4}; //0x10;
        
struct PermissionInfo 
    {
        unsigned int flag;
        std::string name;
    };
 class  Character 
    {
    private:
        unsigned short int Permission;
        const std::vector<PermissionInfo> PermissionList
        {
            {Perm_Move,"移动权限"},
            {Perm_Attact,"攻击权限"},
            {Perm_Use,"使用权限"},
            {Perm_Chat,"通信权限"},
            {Perm_Admin,"管理权限"},
    
        };
    public:
        Character():Permission{0}{};
        void GrantPermission(unsigned short int Prom)
        {
            Permission|=Prom;
            std::cout<<std::setw(20)<<"给所有权限:"<<std::bitset<sizeof(unsigned short int)*8>(Permission)<<std::endl;
             std::cout<<std::setw(20)<<"给所有权限:"<<std::dec<<Permission<<std::endl;
        }
        void RemovePermission (unsigned short int prom)
        {
            Permission &=(~prom);
            std::cout<<std::setw(20)<<"移除权限:"<<std::bitset<sizeof(unsigned short int)*8>(Permission)<<std::endl;
            std::cout<<std::setw(20)<<"给所有权限:"<<std::dec<<Permission<<std::endl;
        }
        bool HasPermission(unsigned int perm) const 
        {
          return (Permission & perm) != 0;
        }
        void GetStatue()
        {
            if (!Permission)
            {
                std::cout<<std::setw(20)<<"当前权限全关"<<std::endl;
            }else 
            {
                for (const auto& Perm : PermissionList)
                {
                     if (HasPermission(Perm.flag))
                     {
                       std::cout<< Perm.name<<":[开启]"<<std::endl;
                     } else {std::cout<< Perm.name<<":[关闭]"<<std::endl;}
                     
                }
                      
            }
            std::cout<<std::setw(20)<<"当前权限:"<<std::bitset<sizeof(unsigned short int)*8>(Permission)<<std::endl;
        }
    };
    
int main()
{
    // std::cout<<std::setfill('*');
    // int intget{1};
    // std::string StringName{"Name"}; 
    // std::cout << std::setw(20) << StringName << std::endl;
    // std::cout<<sizeof(intget)<<std::endl;
    // int PowFunc{};
    // PowFunc= std::pow(10,2);
    // std::left;
    // std::cout<<std::setw(20)<<PowFunc<<std::endl;
    // //std::cout<<std::setw(20)<<std::hex<<PowFunc<<std::endl;
    // //加减乘除余
    // std::cout<<std::setfill('-');
    // int a {17};int b {5};
    // std::cout<<std::setw(5)<<a+b<<std::endl;
    // std::cout<<std::setw(5)<<a-b<<std::endl;
    // std::cout<<std::setw(5)<<a*b<<std::endl;
    // std::cout<<std::setw(5)<<a/b<<std::endl;
    // std::cout<<std::setw(5)<<a%b<<std::endl;

    // int n{255};
    // std::cout<<std::dec<<n<<std::endl;
    // std::cout<<std::hex<<n<<std::endl;
    // std::cout<<std::oct<<n<<std::endl;
    // std::cout<<std::uppercase<<std::hex<<n<<std::endl;
    
    // std::cout<<std::setfill('-')<<std::setw(20)<<std::endl;
    
    // std::cout<<std::dec<<++n<<std::endl;
    // std::cout<<std::dec<<n<<std::endl;
    // std::cout <<std::setw(10) <<"Name" <<std::setw(10) << "Age" <<  std::endl;
    // std::cout <<std::setw(10) <<"Tom"<< std::setw(10) << 25 <<  std::endl;
    // std::cout <<std::setw(10) <<"Jerry"<< std::setw(10) << 30 <<  std::endl;

    // unsigned char x{60u};
    // int y{100U};
    
    int a = 0x11;      // 十六进制 -> 十进制 ?
    int b = 0b011;    // 二进制   -> 十进制 ?
    int c = 011;      // 八进制   -> 十进制 ?
    int d = 0x1A + 26;
    std::cout<<std::setw(5)<<a<<std::endl;
    std::cout<<std::setw(5)<<b<<std::endl;
    std::cout<<std::setw(5)<<c<<std::endl;
    std::cout<<std::setw(5)<<d<<std::endl;
    //const constexpr /running / 编译时
    // int p {1};
    // const int x = p;
    // constexpr int y = x;
    constexpr int y {30+60};
    int f = y;
    std::cout<<std::setw(5)<<f<<std::endl;

    std::cout<<std::setfill('-');
    std::cout <<std::setw(20) <<"-"<< std::setw(10)<<  std::endl;
    constexpr double Tdoubel{3.13};
    std::cout <<std::setw(20) <<"-"<< static_cast<int>(Tdoubel)<<std::endl;
    char Tchar{'a'};
    unsigned short int TSint{127u};
    std::cout <<std::setw(20) <<"-"<< Tchar <<  std::endl;
    std::cout <<std::setw(20) <<"-"<< static_cast<int>(Tchar)<<std::endl;
    std::cout <<std::setw(20) <<"-"<< static_cast<char>(TSint)<<std::endl;
    std::cout<<"******************************"<<std::endl;
    unsigned short int TUsint{15};
    std::cout <<std::setw(20) <<sizeof(TSint)*8<<std::endl;
    std::cout <<std::setw(20) <<std::showbase<<std::bitset<sizeof(TSint)*8>(TUsint)<<std::endl;
    std::cout <<std::setw(20) <<std::showbase<<std::oct<<TUsint<<std::endl;
    std::cout <<std::setw(20) <<std::showbase<<std::dec<<TUsint<<std::endl;
    std::cout <<std::setw(20) <<std::showbase<<std::hex<<TUsint<<std::endl;
    
    TUsint = TUsint>>2;
    std::cout <<std::setw(20) <<std::showbase<<std::bitset<sizeof(TSint)*8>(TUsint)<<std::endl;
    std::cout <<std::setw(20) <<std::showbase<<std::oct<<TUsint<<std::endl;
    std::cout <<std::setw(20) <<std::showbase<<std::dec<<TUsint<<std::endl;
    std::cout <<std::setw(20) <<std::showbase<<std::hex<<TUsint<<std::endl;
    
    std::cout <<std::setw(20) <<std::showbase<<std::log10(100)<<std::endl;
    
   
    Character Player_00;
    std::cout<<std::right;
    Player_00.GetStatue();
    Player_00.GrantPermission(Perm_Use|Perm_Attact|Perm_Chat|Perm_Move|Perm_Admin);
    Player_00.GetStatue();
    Player_00.RemovePermission(Perm_Use|Perm_Attact|Perm_Chat|Perm_Move|Perm_Admin);

    Player_00.GetStatue();


    

    return 0;
    
}