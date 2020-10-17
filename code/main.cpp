#include <iostream>
#include "figureDetector.h"

int N = 15;

int main(int argc, char** argv) {
    FigureDetector figureDetector(N);
    figureDetector.getFile(argv[1]);
    figureP figureParam;
    switch (figureDetector.detectFigure()) {
        case UNKNOWN_FIGURE:
            std::cout << "неизвестная фигура";
            break;
        case SQUARE:
            figureParam = figureDetector.getFigureParam();
            std::cout << "квадрат, длина ребра: " << figureParam.length;
            std::cout<<", левый верхний угол: (" << figureParam.coord.first << ", " << figureParam.coord.second << ")";
            break;
        case CIRCLE:
            figureParam = figureDetector.getFigureParam();
            std::cout << "круг, диаметр: " << figureParam.length;
            std::cout << ", координаты центра: (" << figureParam.coord.first << ", " << figureParam.coord.second << ")";
            break;
        default:
            break;
    }

    return 0;
}
