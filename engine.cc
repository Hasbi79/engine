#include "gegevenClasses/easy_image.h"
#include "gegevenClasses/ini_configuration.h"

#include <fstream>
#include <iostream>

#include <limits>
#include "gegevenClasses/l_parser.h"

#include "dataStructures.h"
#include "algorithm"

#include <string>
#include "3D-lijntekening/Projection.h"

#include "LSystem2D/LSystem2D.h"
using namespace std;



//declaratie van de methodes
img::EasyImage draw2DLines(const Lines2D &lines, int size, const Color &backgroundColor);
Lines2D generate2DLines(const ini::Configuration &configuration);
Figures3D generate3DFigures(const ini::Configuration & configuration);



img::EasyImage generate_image(const ini::Configuration &configuration)
{
    int size = configuration ["General"]["size"];
    ini::DoubleTuple bg = configuration ["General"]["backgroundcolor"];
    std::string type = configuration["General"]["type"];


    Color backgroundColor;
    backgroundColor.red = bg[0];
    backgroundColor.green = bg[1];
    backgroundColor.blue = bg[2];


    if (type == "2DLSystem") {
        ini::DoubleTuple lc = configuration["2DLSystem"]["color"];
        Lines2D lines = generate2DLines(configuration);
        return draw2DLines(lines, size, backgroundColor);
    }
    else if (type == "Wireframe") {

        Figures3D figures = generate3DFigures(configuration);
        Lines2D lines = doProjection(figures);
        return draw2DLines(lines, size, backgroundColor);
    }

    return img::EasyImage(1,1);
}





int main(int argc, char const* argv[])
{
    int retVal = 0;
    try
    {
        std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
        if (args.empty()) {
            std::ifstream fileIn("filelist");
            std::string filelistName;
            while (std::getline(fileIn, filelistName)) {
                args.push_back(filelistName);
            }
        }
        for(std::string fileName : args)
        {
            ini::Configuration conf;
            try
            {
                std::ifstream fin(fileName);
                if (fin.peek() == std::istream::traits_type::eof()) {
                    std::cout << "Ini file appears empty. Does '" <<
                              fileName << "' exist?" << std::endl;
                    continue;
                }
                fin >> conf;
                fin.close();
            }
            catch(ini::ParseException& ex)
            {
                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                retVal = 1;
                continue;
            }

            img::EasyImage image = generate_image(conf);
            if(image.get_height() > 0 && image.get_width() > 0)
            {
                std::string::size_type pos = fileName.rfind('.');
                if(pos == std::string::npos)
                {
                    //filename does not contain a '.' --> append a '.bmp' suffix
                    fileName += ".bmp";
                }
                else
                {
                    fileName = fileName.substr(0,pos) + ".bmp";
                }
                try
                {
                    std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                    f_out << image;

                }
                catch(std::exception& ex)
                {
                    std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                    retVal = 1;
                }
            }
            else
            {
                std::cout << "Could not generate image for " << fileName << std::endl;
            }
        }
    }
    catch(const std::bad_alloc &exception)
    {
        //When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
        //Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
        //(Unless of course you are already consuming the maximum allowed amount of memory)
        //If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
        //mark the test as failed while in reality it just needed a bit more memory
        std::cerr << "Error: insufficient memory" << std::endl;
        retVal = 100;
    }
    return retVal;
}