#include "path.hpp"
#include <iostream>

Path::Path(size_t length, size_t starting_row): length_{length}, starting_row_{starting_row} {
    for (unsigned int i = 0; i < length_; ++i) {
        path_.push_back(starting_row);
    }
}
size_t Path::Length() const {
    return length_;
}
size_t Path::StartingRow() const {
    return starting_row_;
}
unsigned int Path::EleChange() const {
    return ele_change_;
}
void Path::IncEleChange(unsigned int value) {
    ele_change_ += value;
} // value must be positive; ????
const std::vector<size_t>& Path::GetPath() const {
    return path_;
}
void Path::SetLoc( size_t col, size_t row ) {
    if (col >= length_ || row < 0 || col < 0) {
        throw std::invalid_argument("no use");
    }
    path_.at(col) = row;
}