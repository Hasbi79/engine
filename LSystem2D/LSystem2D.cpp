//
// Created by hassa on 26/03/2025.
//

#include "LSystem2D.h"




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
