/******************************************************************************

Copy elision demonstrated: note the _no_difference_ between C++11(14) and C++17
Note that when the move constructor is defined, will be used anywhere
and when not, the copy constructor is used by d efault. This is copy elision.

*******************************************************************************/
#include <iostream>

#define I_LIKE_TO_MOVE_IT
#undef  I_LIKE_TO_MOVE_IT // comment/ uncomment this line, compile and run:

class CAnimal
{
    static int call_cnt;
public:
    CAnimal() = default;
    CAnimal(const CAnimal&){std::cout<<++call_cnt<<"\tcopied\n";}
#ifdef I_LIKE_TO_MOVE_IT    
    CAnimal(CAnimal&&){std::cout<<++call_cnt<<"\tmoved\n";};
#endif
};

int CAnimal::call_cnt = 0;

CAnimal getAnimal()
{
    CAnimal ani;
    auto ani2 = (CAnimal){std::forward<CAnimal&&>(ani)};
    auto ani3 = std::move(ani2);
    auto pani = &ani3;
    return std::forward<CAnimal&&>(*pani);
}


int main()
{
    getAnimal();
    std::cout<<"Game Over!\n";
    return 0;
}




