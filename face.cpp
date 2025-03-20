//
// Created by Hassane Balde on 18/03/2025.
//

#include "face.h"


face::face(const std::vector<int>& indices) : point_indexes(indices) {
    point_indexes = indices;
}

const std::vector<int>& face::getPointIndexes() const {
    return point_indexes;
}
