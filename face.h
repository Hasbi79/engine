//
// Created by Hassane Balde on 18/03/2025.
//

#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H

#include "iostream"
#include "vector"


class face {
public:
    std::vector<int> point_indexes;

    face(const std::vector<int>& indices);


    const std::vector<int>& getPointIndexes() const ;


};


#endif //ENGINE_FACE_H
