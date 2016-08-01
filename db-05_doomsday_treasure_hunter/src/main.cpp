#include <allegro.h>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>

#include "game.hpp"
#include "exception.hpp"
#include "guichan.hpp"

int main(int argc, char **argv)
{
	try
	{						
		Game game;
		game.run();
	}
	catch (Exception e)
    {
        std::string str;
        std::ostringstream os(str);
    
        os << "A game exception occured: \"" << e.getMessage() << "\" "
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
    
        os << "A guichan exception occured: \"" << e.getMessage() << "\" "
           << "in function " << e.getFunction()
		   << " at line " << e.getLine()<< ".";

        std::cerr << os.str() << std::endl;

        allegro_message(os.str().c_str());
        return 1;
    }
	catch (std::exception e)
	{
        std::string str;
        std::ostringstream os(str);
    
		os << "An STD exception occured: \"" << e.what() << "\".";

        std::cerr << os.str() << std::endl;

        allegro_message(os.str().c_str());
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
