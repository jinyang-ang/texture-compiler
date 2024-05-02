#include "t_com.h"
#include <iostream>


int main(int argc, const char* argv[])
{
    //parse from command line
    Tex_compiler::descriptor object;
    //invalid number of arguments 
    if (argc != 3)
    {
        std::cout << "invalid number of arguments! " << std::endl;
        return 1;

    }
   /* if (argc == 2 && argv[1] == std::string("-help"))
    {
        std::cout << "How to use texture_compiler " << std::endl;
        std::cout << "execute the command with the following flags and their respective arguments  " << std::endl;
        std::cout << "-target indicates to the compiler what platforms is the resource meant to be build for.  " << std::endl;
        std::cout << "-desc indicates that is the descriptor file path.  " << std::endl;
        std::cout << "-rscpath indicates the path where the resource will be saved.  " << std::endl;
        std::cout << "use texture_compiler.exe -target PC -desc  \"assets/descriptor.json\" - rscpath  \"output.txt\" " << std::endl;
        return 0;
    }*/
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-target" && i + 1 < argc) {

            object.p_object.target = argv[++i];
        }

        else if (arg == "-desc" && i + 1 < argc) {

            object.p_object.desc_path = argv[++i];
            object.p_object.desc_path.erase(std::remove(object.p_object.desc_path.begin(), object.p_object.desc_path.end(), '\"'), object.p_object.desc_path.end());


        }
        else if (arg == "-rscpath" && i + 1 < argc) {

            object.p_object.rsc_path = argv[++i];
            object.p_object.rsc_path.erase(std::remove(object.p_object.rsc_path.begin(), object.p_object.rsc_path.end(), '\"'), object.p_object.rsc_path.end());

        }
    }


    //load from descriptor file 
    object.load();

    return 0;

}