#include <allegro.h>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>

#include "exception.hpp"
#include "game.hpp"
#include "guichan.hpp"


int main(int argc, char **argv)
{
	try
	{
		nmc::Game game;
		game.run();
	}
    catch (nmc::Exception e)
    {
        std::string str;
        std::ostringstream os(str);
    
        os << "A NMC exception occured: \'" << e.getMessage() << "\' "
           << "in function " << e.getFunction()
           << " at line " << e.getLine()<< ".";

        std::cerr << os.str() << std::endl;

        allegro_message(os.str().c_str());
        return 1;   
    }
    catch (gcn::Exception e)
    {
        std::string str;
        std::ostringstream os(str);

        os << "A Guichan exception occured: \'" << e.getMessage() << "\' "
           << "in function " << e.getFunction()
           << " at line " << e.getLine() << ".";

        std::cerr << os.str() << std::endl;

        allegro_message(os.str().c_str());
        return 1;   
    }
	catch (std::exception e)
	{
        std::string error = std::string("A STD exception occured: \'")
            + e.what() + "\'.";
        
        std::cerr << error << std::endl;
        allegro_message(error.c_str());
		return 1;
	}
    catch (...)
	{
        std::string error = "An unknown exception occured (this is generally very bad).";
        
        std::cerr << error << std::endl;
        allegro_message(error.c_str());
		return 1;
	}
	return 0;
}
END_OF_MAIN()