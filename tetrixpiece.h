#ifndef TETRIXPIECE_H
#define TETRIXPIECE_H

enum TetrixShape { NoShape, ZShape, SShape, LineShape, TShape, SquareShape,
                   LShape, MirroredLShape };

/*
 * Класс TetrixPiece содержит информацию о фигуре в игровой зоне игры, включая ее форму,
 * положение и диапазон позиций, которые она может занимать на доске
*/
class TetrixPiece
{
public:
    /*изначально создаётся "пустая" фигура*/
    TetrixPiece() { setShape(NoShape); }

/*выбирает случайную форму из перечисления TetrixShape и вызывает функцию setShape() */
    void setRandomShape();

/*Функция setShape использует таблицу поиска фигур, чтобы связать каждую фигуру с массивом позиций блоков*/
    void setShape(TetrixShape shape);


    TetrixShape shape() const { return pieceShape; }
    int x(int index) const { return coords[index][0]; }
    int y(int index) const { return coords[index][1]; }

/*
 * Функции minX () и maxX () возвращают минимальные и максимальные горизонтальные координаты,
 * занятые блоками, составляющими фигуру
*/
    int minX() const;
    int maxX() const;

/*minY() и maxY() возвращают минимальные и максимальные вертикальные координаты, занятые блоками*/
    int minY() const;
    int maxY() const;

/*Функция rotatedLeft () возвращает новый элемент той же формы, что и существующий,
 * но повернутый против часовой стрелки на 90 градусов*/
    TetrixPiece rotatedLeft() const;

/*функция rotatedRight () возвращает новый элемент той же формы,
 * что и существующий, но повернутый по часовой стрелке на 90 градусов*/
    TetrixPiece rotatedRight() const;

private:
    void setX(int index, int x) { coords[index][0] = x; }
    void setY(int index, int y) { coords[index][1] = y; }
/*Каждая фигура содержит четыре блока, которые определяются переменной coords*/
    TetrixShape pieceShape;
    int coords[4][2];
};

#endif
