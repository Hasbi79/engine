#include "gegevenClasses/easy_image.h"
#include "gegevenClasses/ini_configuration.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "gegevenClasses/l_parser.h"
#include "algorithm"

#include "gegevenClasses/vector3d.h"
#include "stack"

#include "figure.h"

struct Line2D {
    double x1, y1,x2,y2;
};

img::EasyImage draw2DLines(std::vector<Line2D> lines, const int size,
                           const std::vector<double>& bgCcolor,
                           const std::vector<double>& lineColor )
{


    if (lines.empty()) {
        std::cout << "er zijn geen lijnen " << "\n";
        return img::EasyImage();
    }
    // bereken max en min van alle punten
    double xmax = std::numeric_limits<double>::lowest();
    double xmin = std::numeric_limits<double>::max();
    double ymax = std::numeric_limits<double>::lowest();
    double ymin = std::numeric_limits<double>::max();

    for (auto &line : lines) {
        xmax = std::max({xmax, line.x1, line.x2});
        xmin = std::min({xmin, line.x1, line.x2});
        ymax = std::max({ymax, line.y1, line.y2});
        ymin = std::min({ymin, line.y1, line.y2});
    }
    //bereken de ranges
    double xrange  = xmax - xmin;
    double yrange = ymax - ymin;

    double imagex = size * (xrange/ std::max(xrange,yrange));
    double imagey = size * (yrange/ std::max(xrange,yrange));
    // schallfactor
    double d = 0.95 * ( imagex /xrange );

    for(auto & line : lines ){
        line.x1 *= d;
        line.x2 *= d;
        line.y1 *= d;
        line.y2 *= d;
    }
    //middelpunt afbeelding
    double DCx = (xmin + xmax) / 2 * d;
    double DCy = (ymin + ymax) / 2 * d;
    // verschuiving
    double dx  = (imagex / 2 ) - DCx;
    double dy = (imagey / 2 ) - DCy;

    for(auto & line : lines ){
        line.x1 += dx;
        line.x2 += dx;
        line.y1 += dy;
        line.y2 += dy;
        // rond de coordinaten van punten af
        line.x1 = std::round(line.x1);
        line.x2 = std::round(line.x2);
        line.y1 = std::round(line.y1);
        line.y2 = std::round(line.y2);
    }
    img::EasyImage image(imagex,imagey);
    // achtergrond kleur toepassen
    image.clear(img::Color(bgCcolor[0] * 255, bgCcolor[1] * 255, bgCcolor[2] * 255));

    for (const auto& line : lines) {
        image.draw_line(
                static_cast<int>(line.x1), static_cast<int>(line.y1),
                static_cast<int>(line.x2), static_cast<int>(line.y2),
                img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255)
        );
    }
    return image;
}



img::EasyImage readl2Dlines(const std::string filename, int size,
                            const std::vector<double> &bgColor,
                            const std::vector<double> & lineColor){

    LParser::LSystem2D l_system;

    // Open het L2D-bestand en laad de L-Systeem parameters
    std::ifstream input_stream(filename);
    if(!input_stream){
        std::cerr<< "kan het bestand" << filename << "NIET OPENEN " << "\n";
    }
    input_stream >> l_system;
    input_stream.close();


//    krijg het begin string
    std::string lsystem_string = l_system.get_initiator();

    for(unsigned int i = 0; i < l_system.get_nr_iterations() ; i++){
        std::string nextString;
        for(char c  : lsystem_string){
//            kijk of het in het alfabet is want + en - mogen niet veranderen en die zitten dr niet in
            if(l_system.get_alphabet().count(c)){
//                vervang de string door de replacement string bij to te voegen
                nextString +=  l_system.get_replacement(c);
            } else{
                // stel het karakter moet niet vervangen worden voeg het gewoon toe
                // behoud dus tekens als + en -
                nextString += c;
            }
        }
//        pas de volgende lsytsem aan naar de niuwe string
        lsystem_string = nextString;
    }


//    een vector waar de lijn coordinaten worden opgeslagen
    std::vector<Line2D> lines;

//    de startposisites we beginnen in oorsprong (0,0)
    double x = 0; double y = 0;
//    starthoek
    double startingAngle =  l_system.get_starting_angle();

//     ga door elke character van lsystem string die gemaakt is hierboven
//    currentangle zodat je bij draaien van hoeken niet startingangle aanpast
    double currentAngle = startingAngle;
    // maak een stack met waar je huidige positie en richting opslaat
    std::stack<std::pair<double,double>> stackPositie; //positie x en y
    std::stack<double> stackHuidigerichting;

    for(char c : lsystem_string) {

        if (l_system.get_alphabet().count(c)) {
            double angleInradialen = currentAngle * (M_PI / 180.0);

            double newX = x + std::cos(angleInradialen);
            double newY = y + std::sin(angleInradialen);

            if (l_system.draw(c)) {
                lines.push_back({x, y, newX, newY});
            }

            x = newX;
            y = newY;
        } else if (c == '+') {
//            als je + tegenkomt in de systemstrings dan vermeerdert de starangle met get angle dat 25 graden is
            currentAngle += l_system.get_angle();
        } else if (c == '-') {
//            met de klok draaien
            currentAngle -= l_system.get_angle();
        } else if (c == '('){
            stackPositie.push({x, y});
            stackHuidigerichting.push(currentAngle);
        } else if ( c == ')'){
            if(stackHuidigerichting.empty()|| stackPositie.empty()){
                std::cerr << "stack is leeg"<< "\n";
            }
            std::pair<double,double> prevPosition = stackPositie.top();
            x = prevPosition.first;
            y = prevPosition.second;
            stackPositie.pop();

            currentAngle = stackHuidigerichting.top();
            stackHuidigerichting.pop();

        }

    }

    return draw2DLines(lines, size,bgColor,lineColor);

}


img::EasyImage generate_image(const ini::Configuration &configuration)
{
    std::string filename = configuration["2DLSystem"]["inputfile"].as_string_or_die();
    int size = configuration["General"]["size"].as_int_or_default(500);

    std::string type = configuration["General"]["type"].as_string_or_die();
    std::vector<double> bgColor = configuration["General"]["backgroundcolor"].as_double_tuple_or_default({255,255,255});
    std::vector<double> lineColor = configuration["2DLSystem"]["color"].as_double_tuple_or_default({0,0,0});

    if(type == "2DLSystem"){
        return readl2Dlines(filename,size,bgColor,lineColor);
    }
//    if(type == "line_drawings"){
//
//    }

    return img::EasyImage();
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