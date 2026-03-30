#include <iostream> 
#include <string>
#include <ios>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <array>
#include <vector>
#include <memory>
#include <cstddef>
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

    unsigned short int GetNumber(unsigned short int Array[],int InRow,int Incol)
    {
        return Array[((InRow-1)*Incol)+(Incol-1)];
    }

class Canvas

{
private:
    int row; //行数  元素行数表示 y 
    int cols; //列数 元素列数表示 x
    std::vector<char> Pixels;
public:
    Canvas(int Inrow,int incols):row(Inrow),cols(incols)
    {
        Pixels.resize(row*cols,'.');
    };
    //显示所有
    void FillPixels()
    {
        for (size_t i{0}; i < row; ++i) // 行
        {
            for (size_t j{0}; j < cols; ++j) // 列
            {
                std::cout<<Pixels.at(i*cols+j)<<' ';
            }
            std::cout<<std::endl;
        } 
    }

    //填充对应位置
    void FillPixelDir(int y,int x,char Pixel)
    {
        if (y<row&&x<cols&&y>=0&&x>=0)
        {
            Pixels.at(y*x+x) = Pixel;
        }
    }

    //填充行
    void FillPixelRow(int Inrow,char Pixel)
    {
        if (Inrow>=0&&Inrow<row)
        {
            for (size_t i {0}; i < cols; i++)
            {
                Pixels.at(Inrow*cols+i) = Pixel;
            }

            FillPixels();
        }
        
    }
    //填充列

    void FillPixelColsCols(int InCols,char Pixel)
    {
        if (InCols>=0&&InCols<cols)
        {
            for (size_t i {0}; i < row; i++)
            {
                Pixels.at(i*cols+InCols) = Pixel;
            }

            FillPixels();
        }
        
    }
};

class Canvas3D

{
private:
    int x;
    int y;
    int z;
    std::vector<char> matrix3D;
    
public:
    Canvas3D(int Inz ,int Iny,int Inx):x(Inx),y(Iny),z(Inz) // 3,4,5 // 三页, 四行 ,
    {
        matrix3D.resize(z*y*x,'.');
    };

    //创建一个魔方的三个面
    void FillPlan()
    {
        for (size_t i{0}; i < z; i++) // 页
        {
            for (size_t j{0}; j < y; j++) // 行
            {
                for (size_t k{0}; k < x; k++) // 列
                {
                    std::cout<< matrix3D.at(i*y*x+j*x+k);
                }
                std::cout<<'\n';
            }
            
            std::cout<<'\n';
        }
        
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


    //数组的大小编译编译时是固定的,无法动态改变除非使用动态数组
    constexpr unsigned short int row{3},cols{4};
    unsigned short int  Array [row*cols]{};
    //填充数组
    for (size_t i{0}; i < row*cols; ++i)
    {
        Array[i] = i+1;
    }

    for (size_t j {0}; j < row; ++j)
    {
        
        for (size_t k{0}; k <cols ; ++k)
        {
            std::cout<<Array[j*cols+k]<<',';
        }
       std::cout<<std::endl;
    }    
    
    std::cout << GetNumber(Array,1,2)<<std::endl;
    std::cout << GetNumber(Array,3,4)<<std::endl;

    
    auto CanvasPtr {std::make_shared<Canvas>(1,9)};
    //CanvasPtr->FillPixels();
    // Canvas NewCanvas{3,5};
    // NewCanvas.FillPixels();
    // NewCanvas.FillPixelDir(0,0,'*');
    // std::cout<<std::endl;
    // NewCanvas.FillPixels();
    // std::cout<<'\n';
    // NewCanvas.FillPixelRow(1,'&');
    // std::cout<<'\n';
    // NewCanvas.FillPixelColsCols(2,'$');
    //CanvasPtr->FillPixelRow(4,'0');
    CanvasPtr->FillPixelColsCols(5,'$');

    auto Canvas3DPtr{std::make_shared<Canvas3D>(3,4,5)};

    Canvas3DPtr->FillPlan();
    //Canvas3DPtr->FillPlan();

    //int* Pter = new(std::nothrow)int(2);
    int* PtrA{nullptr};
    int ArrayN[]{1,2,2,3,3};
    PtrA = ArrayN;
    int Number{10};
    int* Ptr = &Number;
    int* PtrArray{new int[5]{1,2,3,4,5}};
    
    for (size_t i = 0; i < 5; i++)
    {
        std::cout<<*(PtrA+i)<<std::endl;
    }

    //std::cout<<std::size(Ptr);   
    
    return 0;
}