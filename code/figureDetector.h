#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#ifndef DETECTOR_FIGUREDETECTOR_H
#define DETECTOR_FIGUREDETECTOR_H
typedef struct {
    std::pair<double, double> coord;
    int length = 0;
} figureP;

enum figure{
    UNKNOWN_FIGURE,
    SQUARE,
    CIRCLE
};

class FigureDetector {
private:
    std::vector<std::string> buffer;
    figureP figureParam;
    int isSquare(int x, int y, int n);
    int isCircle(double x, double y, double r);
    int isDot(int x, int y);
    int isDotForCircle(double x1, double x, double y1, double y);
    std::pair<int, int> getFirsTopLeftCoord();
public:
    explicit FigureDetector(int n){ buffer.resize(n);};
    ~FigureDetector(){
        for (auto &i : buffer) {
            i.clear();
        }
        buffer.clear();
    }
    void getFile(char* filename);
    int detectFigure();
    figureP getFigureParam();

};
#endif //DETECTOR_FIGUREDETECTOR_H
