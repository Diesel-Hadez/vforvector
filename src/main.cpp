#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "Vector.h"
#include "Question.h"

int main(int argc, char **argv)
{
	try
	{
        /*
         //Should probably have did this in a unit test...
        Vector a;
        a.X = 2;
        a.Y = 2;
        a.Z = 2;
        Vector b;
        b.X = 3;
        b.Y = 3;
        b.Z = 5;
        std::cout << (b-a).AsString() << std::endl;
        std::cout << "Angle: " << Vector::Angle(a,b) << std::endl;
        std::string temp = "NO";
        if (Vector::IsParallel(a,b))
            temp = "YES";
        std::cout << "Parallel? : " << temp << std::endl;
        std::cout << "Distance? : " << Vector::Distance(a,b) << std::endl;
        std::cout << "Dot Product: " << Vector::DotProduct(a,b) << std::endl;
        std::cout << "Magnitude of (2,2,2): " << a.Magnitude() << std::endl;
        std::cout << "Unit Vector of (2,2,2): " << a.UnitVector().AsString() << std::endl;
        std::cout << "Unit Vector of (3,3,3): " << b.UnitVector().AsString() << std::endl;
        return 0;*/
		Game::GetInstance().Run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "FATAL UNKNOWN ERROR HAS OCCURED" << "\n";
	}
	return 0;
}
