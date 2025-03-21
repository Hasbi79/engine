#include "gegevenClasses/easy_image.h"
#include "gegevenClasses/ini_configuration.h"


#include <fstream>
#include <iostream>


#include <limits>
#include "gegevenClasses/l_parser.h"

#include "dataStructures.h"
#include "algorithm"

#include "cmath"
#include "stack"

#include <string>
#include "Projection.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



img::EasyImage draw2DLines(const Lines2D & lines,  int size, const Color& backgroundColor) {

    double Xmax = std::numeric_limits<double>::lowest();
    double Xmin = std::numeric_limits<double>::max();
    double Ymax = std::numeric_limits<double>::lowest();
    double Ymin = std::numeric_limits<double>::max();



    for (auto &line : lines) {
        Xmin = std::min({Xmin, line.p1.x, line.p2.x});
        Xmax = std::max({Xmax, line.p1.x, line.p2.x});
        Ymax = std::max({Ymax, line.p1.y, line.p2.y});
        Ymin = std::min({Ymin, line.p1.y, line.p2.y});
    }

    //bereken de ranges
    double xrange  = Xmax - Xmin;
    double yrange = Ymax - Ymin;

    double Imagex = size * (xrange / std::max(xrange, yrange));
    double Imagey = size * (yrange / std::max(xrange, yrange));
    // schallfactor
    double d = 0.95 * (Imagex / xrange);


    //middelpunt afbeelding
    double DCx = (Xmin + Xmax) / 2 * d;
    double DCy = (Ymin + Ymax) / 2 * d;
    // verschuiving
    double dx  = (Imagex / 2) - DCx;
    double dy = (Imagey / 2) - DCy;

    img::EasyImage image(Imagex, Imagey, img::Color(
        backgroundColor.red * 255,
        backgroundColor.green * 255,
        backgroundColor.blue * 255
    ));


    for (const auto& line : lines) {
        double x1 = line.p1.x * d + dx;
        double y1 = line.p1.y * d + dy;
        double x2 = line.p2.x * d + dx;
        double y2 = line.p2.y * d + dy;

        // Use each line's own color
        img::Color lineImgColor(
            line.color.red * 255,
            line.color.green * 255,
            line.color.blue * 255
        );

        image.draw_line(x1, y1, x2, y2, lineImgColor);
    }

    return image;
}



Figures3D generate3DFigures(const ini::Configuration & configuration) {

    Figures3D figures;
    vector<double> eyeValues = configuration["General"]["eye"].as_double_tuple_or_die();
    Vector3D eye = Vector3D::point(eyeValues[0],eyeValues[1],eyeValues[2]);
      Figure figure;
    int nrFigures = configuration["General"]["nrFigures"].as_int_or_die();
    for (int i = 0; i < nrFigures; i++) {

        string figureName = "Figure" + to_string(i);

        double rotateX = configuration[figureName]["rotateX"].as_double_or_die();
        double rotateY = configuration[figureName]["rotateY"].as_double_or_die();
        double rotateZ = configuration[figureName]["rotateZ"].as_double_or_die();
        double scale = configuration[figureName]["scale"].as_double_or_die();

        vector<double> centerValues = configuration[figureName]["center"].as_double_tuple_or_die();
        Vector3D center = Vector3D::point(centerValues[0], centerValues[1], centerValues[2]);
        vector<double> colorValues = configuration[figureName]["color"].as_double_tuple_or_die();
        Color lineColor;
        lineColor.red = colorValues[0];
        lineColor.green = colorValues[1];
        lineColor.blue = colorValues[2];

        figure.color = lineColor;
        int nrPoints = configuration[figureName]["nrPoints"].as_int_or_die();
        for (int pointIndex = 0; pointIndex < nrPoints; pointIndex++) {

            string pointNumber = "point" + to_string(pointIndex);
            vector<double> pointValues = configuration[figureName][pointNumber].as_double_tuple_or_die();
            figure.points.push_back(Vector3D::point(pointValues[0], pointValues[1], pointValues[2]));

        }
        int nrLines = configuration[figureName]["nrLines"].as_int_or_die();
        for (int lineIndex = 0; lineIndex < nrLines; lineIndex++) {
            string lineName = "line" + to_string(lineIndex);
            vector<int> lineValues = configuration[figureName][lineName].as_int_tuple_or_die();

            // Create a Face object for each line
            Face lineFace;
            lineFace.point_indexes.push_back(lineValues[0]); // First point index
            lineFace.point_indexes.push_back(lineValues[1]); // Second point index

            // Add the face to the figure
            figure.faces.push_back(lineFace);

        }

        Matrix eyePointTrans = figure.eyePointTrans(eye);
        Matrix computedMatrix = figure.computeMatrix(scale,rotateX,rotateY,rotateZ,center,eyePointTrans);

        figure.applyTransformation(computedMatrix);

        figures.push_back(figure);

    }

    return figures;

}


Lines2D generate2DLines(const ini::Configuration &configuration) {
    // Load L-System config
    std::string filename = configuration["2DLSystem"]["inputfile"];
    LParser::LSystem2D l_system;


    ini::DoubleTuple color = configuration ["2DLSystem"]["color"];
    Color lineColor;
    lineColor.red = color[0];
    lineColor.green = color[1];
    lineColor.blue = color[2];


    std::ifstream input_stream(filename);
    if (!input_stream) {
        std::cerr << "Kan het bestand " << filename << " NIET openen\n";
        return {};
    }
    input_stream >> l_system;
    input_stream.close();

    // Generate the L-System string
    std::string lsystem_string = l_system.get_initiator();
    for (unsigned int i = 0; i < l_system.get_nr_iterations(); i++) {
        std::string next;
        for (char c : lsystem_string) {
            if (l_system.get_alphabet().count(c)) {
                next += l_system.get_replacement(c);
            } else {
                next += c;
            }
        }
        lsystem_string = next;
    }

    // Draw lines from the string
    Lines2D lines;
    double x = 0, y = 0;
    double currentAngle = l_system.get_starting_angle();

    std::stack<std::pair<double, double>> positionStack;
    std::stack<double> angleStack;

    for (char c : lsystem_string) {
        if (l_system.get_alphabet().count(c)) {
            double radians = currentAngle * M_PI / 180.0;
            double newX = x + std::cos(radians);
            double newY = y + std::sin(radians);

            if (l_system.draw(c)) {
                Line2D line;
                line.p1 = {x, y};
                line.p2 = {newX, newY};
                line.color = lineColor;
                lines.push_back(line);
            }

            x = newX;
            y = newY;
        } else if (c == '+') {
            currentAngle += l_system.get_angle();
        } else if (c == '-') {
            currentAngle -= l_system.get_angle();
        } else if (c == '(') {
            positionStack.push({x, y});
            angleStack.push(currentAngle);
        } else if (c == ')') {
            if (!positionStack.empty() && !angleStack.empty()) {
                x = positionStack.top().first;
                y = positionStack.top().second;
                currentAngle = angleStack.top();
                positionStack.pop();
                angleStack.pop();
            } else {
                std::cerr << "Stack is leeg bij ')'\n";
            }
        }
    }

    return lines;
}

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