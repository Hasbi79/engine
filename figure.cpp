//
// Created by Hassane Balde on 18/03/2025.
//

#include "figure.h"



// Constructor: Maak een lege figuur
figure::figure() = default;

// Methode om een punt toe te voegen
void figure::addPoint(const Vector3D& point) {
    points.push_back(point);
}

// Methode om een vlak toe te voegen
void figuref::addFace(const std::vector<int>& indices) {
    faces.emplace_back(indices);
}