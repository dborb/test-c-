#include "figureDetector.h"

void FigureDetector::getFile(char* filename) {
    std::ifstream in(filename);
    if(!in.is_open())
        return;
    for(auto &itBuf : buffer){
        std::getline(in, itBuf);
        itBuf[buffer.size()] = '\0';
    }
}

int FigureDetector::detectFigure() {
    //ищем первые координаты 1 для определения фигуры
    std::pair<int, int> firstPos = getFirsTopLeftCoord();
    if(firstPos.first == -1){
        return 0;
    }
    //проверка на возможный круг
    if(buffer[firstPos.first + 1][firstPos.second - 1] == '1' || buffer[firstPos.first + 2][firstPos.second - 1] == '1'){
        int diam = firstPos.first;
        int topLen = 0;
        double radius;
        std::pair<double, double> centerCoord;

        //вычисляем диаметр круга
        for(; buffer[diam][firstPos.second] != '0'; ++diam);
        diam -= firstPos.first;
        if(diam < 5)
            return 0;
        //вычисляем длину верхнего отрезка для определения координат центра
        for(; buffer[firstPos.first][firstPos.second + topLen] != '0'; topLen++);

        //если диаметр четное число -- центр будет дробным
        //вычисляем координаты центра
        if(diam % 2 == 0){
            centerCoord.first = firstPos.first + (diam - 1.) / 2;
            centerCoord.second = firstPos.second + (topLen - 1.) / 2;
            radius = (diam - 1.) / 2;
        }
        else {
            centerCoord.first = firstPos.first + diam / 2;
            centerCoord.second = firstPos.second + topLen / 2;
            radius = diam / 2;
        }

        //проверка на наличие точек(единиц) на границе круга. взят алгоритм растеризации Брезенхема
        if(isCircle(centerCoord.first, centerCoord.second, radius)){
            figureParam.coord = centerCoord;
            figureParam.length = diam;
            return 2;
        }
    }
    //иначе проверка на квадрат
    else{
        //вычисляем длину квадрата
        int squareLength = firstPos.first;
        for(; buffer[squareLength][firstPos.second] != '0'; ++squareLength);
        squareLength -= firstPos.first;

        if(squareLength < 5)
            return 0;

        //проверяем является ли фигура квадратом
        if(isSquare(firstPos.first, firstPos.second, squareLength)){
            figureParam.coord = firstPos;
            figureParam.length = squareLength;
            return 1;
        }
    }
    return 0;
}

int FigureDetector::isSquare(int x, int y, int size) {
    for(int i = x; i < x + size; ++i){
        for(int j = y; j < y + size; ++j){
            if(buffer[i][j] == '0'){
                return 0;
            }
        }
    }
    return 1;
}

std::pair<int, int> FigureDetector::getFirsTopLeftCoord() {
    std::pair<int, int> firstPos(-1, -1);
    for(int i = 0; i < buffer.size(); i++){
        for(int j = 0; j < buffer[i].size(); j++){
            if(buffer[i][j] == '1'){
                firstPos.first = i;
                firstPos.second = j;
                return firstPos;
            }
        }
    }
    return firstPos;
}

int FigureDetector::isCircle(double x1, double y1, double r) {
    double x = (r - (int)r) > 0.1 ? 0.5 : 0;
    double y = r;
    double delta = 1 - 2 * r;
    double error;
    while (y >= 0) {
        //вместо симметричного раставления точек смотрим есть ли эти сами точки
        if(!isDotForCircle(x1, x, y1, y)){
            return 0;
        }
        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0)) {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0)) {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - --y);
    }
    return 1;
}

int FigureDetector::isDot(int x, int y) {
    return buffer[x][y] - '0';
}

int FigureDetector::isDotForCircle(double x1, double x, double y1, double y) {
    if(!isDot(x1 + x, y1 + y)){
        return 0;
    }
    if(!isDot(x1 + x, y1 - y)){
        return 0;
    }
    if(!isDot(x1 - x, y1 + y)){
        return 0;
    }
    if(!isDot(x1 - x, y1 - y)){
        return 0;
    }
    return 1;
}

figureP FigureDetector::getFigureParam() {
    return figureParam;
}


