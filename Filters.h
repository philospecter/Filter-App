#pragma once
#include "Image_Class.h"
#include <string>

namespace ImageFilters {
    void apply(Image& image, int filterNumber, int p1 = 0, int p2 = 0, int p3 = 0, int p4 = 0, double d1 = 0.0, const std::string& extraFile = "");
}
