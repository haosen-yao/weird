#include "path_image.hpp"
#include <iostream>
int Min(int a, int b, int c, int d) {
    int tempone = 0;
    if (b >= a) {
        tempone = b - a;
    } else {
        tempone = a - b;
    }
    int temptwo = 0;
    if (c >= a) {
        temptwo = c - a;
    } else {
        temptwo = a - c;
    }
    int tempthree = 0;
    if (d >= a) {
        tempthree = d - a;
    } else {
        tempthree = a - d;
    }
    if (tempone < temptwo && tempone < tempthree) {
        return b;
    }
    if (tempone < tempthree && tempone == temptwo) {
        return c;
    }
    if (temptwo < tempthree && temptwo < tempone) {
        return c;
    }
    return d;
}
int Min(int a, int b, int c) {
    int tempone = 0;
    if (b >= a) {
        tempone = b - a;
    } else {
        tempone = a - b;
    }
    int temptwo = 0;
    if (c >= a) {
        temptwo = c - a;
    } else {
        temptwo = a - c;
    }
    if (tempone < temptwo) {
        return b;
    }
    return c;
}
Path Pathhelper(Path a, size_t b, size_t c, int i, int j) {
    Path x = std::move(a);
    x.SetLoc(b, c);
    if (i > j) {
        int value = i - j;
        x.IncEleChange(value);
    } else {
        int value = j - i;
        x.IncEleChange(value);
    }
    return x;
}
Path Pathadjust(Path a, const ElevationDataset &dataset, size_t length, size_t row) {
    Path b = std::move(a);
    if (length == 0 || length == 1) {
        return b;
    }
    const ElevationDataset* ptr = &dataset;
    if (row == 0) {
        int helper = Min(dataset.DatumAt(row, dataset.Width() - length),dataset.DatumAt(row, dataset.Width() - length + 1), dataset.DatumAt(row + 1, dataset.Width() - length + 1));
        if (helper == dataset.DatumAt(row, dataset.Width() - length + 1)) {
            b = Pathhelper(b, dataset.Width() - length + 1, row, dataset.DatumAt(row, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length));
        } else {
            b = Pathhelper(b, dataset.Width() - length + 1, row + 1, dataset.DatumAt(row + 1, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length));
            row += 1;
        }
        length--;
        return Pathadjust(b, *ptr, length, row);
    } 
    if (row == dataset.Height() - 1) {
        int helper = Min(dataset.DatumAt(row, dataset.Width() - length),dataset.DatumAt(row - 1, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length + 1));
        if (helper == dataset.DatumAt(row, dataset.Width() - length + 1)) {
            b = Pathhelper(b, dataset.Width() - length + 1, row, dataset.DatumAt(row, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length));
        } else {
            b = Pathhelper(b, dataset.Width() - length + 1, row - 1, dataset.DatumAt(row - 1, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length));
            row -= 1;
        }
        length--;
        return Pathadjust(b, *ptr, length, row);
    }
    int helper = Min(dataset.DatumAt(row, dataset.Width() - length), dataset.DatumAt(row - 1, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length + 1), dataset.DatumAt(row + 1, dataset.Width() - length + 1));
    if (helper == dataset.DatumAt(row, dataset.Width() - length + 1)) {
        b = Pathhelper(b, dataset.Width() - length + 1, row, dataset.DatumAt(row, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length));
    } else if (helper == dataset.DatumAt(row + 1, dataset.Width() - length + 1)) {
        b = Pathhelper(b, dataset.Width() - length + 1, row + 1, dataset.DatumAt(row + 1, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length));
        row += 1;
    } else {
        b = Pathhelper(b, dataset.Width() - length + 1, row - 1, dataset.DatumAt(row - 1, dataset.Width() - length + 1), dataset.DatumAt(row, dataset.Width() - length));
        row -= 1;
    }
    length--;
    return Pathadjust(b, *ptr, length, row);
}
PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset):width_{dataset.Width()}, height_{dataset.Height()} {
    path_image_ = image.GetImage();
    dataset.GetData();
    for (unsigned int i = 0; i < dataset.Height(); ++i) {
        Path a(width_, i);
        a = Pathadjust(a, dataset, width_, i);
        paths_.push_back(a);
    }
    for(unsigned int k = 0; k < paths_.size(); ++k) {
        for(unsigned int y = 0; y < paths_.at(k).GetPath().size(); ++y) {
            const int kKmagicred = 252;
            const int kKmagicg = 25;
            const int kKmagicb = 63;
            Color red = {kKmagicred, kKmagicg, kKmagicb};
            path_image_.at(paths_.at(k).GetPath().at(y)).at(y) = red;
        }
    }  
    Path test = paths_.at(0);
    size_t use = 0;
    for (unsigned int k = 0; k < paths_.size(); ++k) {
        if (test.EleChange() > paths_.at(k).EleChange()) {
            test = paths_.at(k);
            use = k;
        }
    }
    for (unsigned int k = 0; k < paths_.size(); ++k) {
        if (test.EleChange() == paths_.at(k).EleChange()) {
            if (k < use) {
                test = paths_.at(k);
            }
        }
    }
    const int kKmagicred = 31;
    const int kKmagicg = 253;
    const int kKmagicb = 13;
    Color green = {kKmagicred, kKmagicg, kKmagicb};
    for (unsigned int h = 0; h < test.GetPath().size(); h++) {
        path_image_.at(test.GetPath().at(h)).at(h) = green;
    }
}
size_t PathImage::Width() const {
    return width_;
}
size_t PathImage::Height() const {
    return height_;
}
unsigned int PathImage::MaxColorValue() const {
    return kMaxColorValue;
}
const std::vector<Path>& PathImage::Paths() const {
    return paths_;
}
const std::vector<std::vector<Color> >& PathImage::GetPathImage() const {
    return path_image_;
}
std::ostream& operator<<(std::ostream& os, const PathImage& a) {
    os << "P3" << '\n';
    os << a.Width() << ' ' << a.Height() << '\n';
    os << a.MaxColorValue() << '\n';
    for (unsigned int i = 0; i < a.GetPathImage().size(); ++i) {
        for (unsigned int j = 0; j < a.GetPathImage().at(i).size(); ++j) {
            if (j == a.GetPathImage().at(i).size() - 1) {
                os << a.GetPathImage().at(i).at(j).Red() << ' ' << a.GetPathImage().at(i).at(j).Green() << ' ' << a.GetPathImage().at(i).at(j).Blue() << '\n';
            } else {
                os << a.GetPathImage().at(i).at(j).Red() << ' ' << a.GetPathImage().at(i).at(j).Green() << ' ' << a.GetPathImage().at(i).at(j).Blue() << ' ';
            }
        }
    }
    return os; 
}
void PathImage::ToPpm(const std::string& name) const {
    std::ofstream ofs{name};
    ofs << *this;
}