#include "elevation_dataset.hpp"
ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height): width_{width}, height_{height} {
    std::ifstream ifs{filename};
    if (!(ifs.is_open())) {
        throw std::runtime_error("not work");
    }
    std::vector<int> ans;
    std::vector<std::vector<int>> data;
    int value = 0;
    size_t size = 0;
    while (ifs.good()) {
        ifs >> value;
        if (ifs.fail()) {
            ifs.clear();
            ifs.ignore(1, ' ');
            continue;
        }
        ans.push_back(value);
        size++;
        if (ans.size() == width) {
            data.push_back(ans);
            ans.clear();
        }
    }
    if (size != width_ * height_) {
        throw std::runtime_error("too much or less");
    }
    data_ = data;
    min_ele_ = data_.at(0).at(0);
    max_ele_ = data_.at(0).at(0);
    for (unsigned int i = 0; i < data_.size(); ++i) {
        for (unsigned int j = 0; j < data_.at(i).size(); ++j) {
            if (data_.at(i).at(j) > max_ele_) {
                max_ele_ = data.at(i).at(j);
            }
            if (data_.at(i).at(j) < min_ele_) {
                min_ele_ = data.at(i).at(j);
            }
        }
    }
}
size_t ElevationDataset::Width() const {
    return width_;
}
size_t ElevationDataset::Height() const {
    return height_;
}
int ElevationDataset::MaxEle() const {
    return max_ele_;
}
int ElevationDataset::MinEle() const {
    return min_ele_;
}
int ElevationDataset::DatumAt(size_t row, size_t col) const {
    if (row >= height_ || col >= width_ || row < 0 || col < 0) {
        throw std::invalid_argument("no use");
    }
    return data_.at(row).at(col);
}
const std::vector<std::vector<int> >& ElevationDataset::GetData() const {
    return data_;
}
