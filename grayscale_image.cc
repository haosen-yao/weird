#include "grayscale_image.hpp"
#include <iostream>
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset): width_{dataset.Width()}, height_{dataset.Height()} {
    for (unsigned int i = 0; i < dataset.Height(); ++i) {
        std::vector<Color> tempc;
        for (unsigned int j = 0; j < dataset.Width(); ++j) {
            const int kKmagic = 255;
            if (dataset.MinEle() == dataset.MaxEle()) {
                Color tempw = {0, 0, 0};
                tempc.push_back(tempw);
                continue;
            }
            int y = dataset.DatumAt(i, j) - dataset.MinEle();
            int h = dataset.MaxEle() - dataset.MinEle();
            double s = (double)y / h;
            double s1 = s * kKmagic;
            int temp = round(s1);
            if (temp > kKmagic || temp < 0) {
                throw std::runtime_error("not work");
            }
            Color basic = {temp, temp, temp};
            tempc.push_back(basic);
        }
        image_.push_back(tempc);
    }
}
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height): width_{width}, height_{height} {
    ElevationDataset a(filename, width, height);
    ElevationDataset* ptr = &a;
    GrayscaleImage b(*ptr);
}
size_t GrayscaleImage::Width() const {
    return width_;
}
size_t GrayscaleImage::Height() const {
    return height_;
}
unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}
const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_.at(row).at(col);
}
const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const {
    return image_;
}
std::ostream& operator<<(std::ostream& os, const GrayscaleImage& a) {
    os << "P3" << '\n';
    os << a.Width() << ' ' << a.Height() << '\n';
    os << a.MaxColorValue() << '\n';
    for (unsigned int i = 0; i < a.GetImage().size(); ++i) {
        for (unsigned int j = 0; j < a.GetImage().at(i).size(); ++j) {
            if (j == a.GetImage().at(i).size() - 1) {
                os << a.GetImage().at(i).at(j).Red() << ' ' << a.GetImage().at(i).at(j).Red() << ' ' << a.GetImage().at(i).at(j).Red() << '\n';
            } else {
                os << a.GetImage().at(i).at(j).Red() << ' ' << a.GetImage().at(i).at(j).Red() << ' ' << a.GetImage().at(i).at(j).Red() << ' ';
            }
        }
    }
    return os; 
}
void GrayscaleImage::ToPpm( const std::string& name ) const {
    std::ofstream ofs{name};
    ofs << *this;
}