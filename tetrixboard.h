#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>

#include "tetrixpiece.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

/*Класс TetrixBoard наследует от QFrame и содержит логику игры и функции отображения*/
class TetrixBoard : public QFrame
{
    Q_OBJECT

public:
/*В конструкторе настраиваем виджет, ввод с клавиатуры будет получен виджетом с помощью Qt:: StrongFocus и инициализируем состояние игры: */
    TetrixBoard(QWidget *parent = 0);


    void setNextPieceLabel(QLabel *label);
/*Предоставляем подсказку предполагаемого размера и подсказку минимального размера для доски,
 * исходя из размера пространства для каждого блока в игровой зоне:*/
/*Используя подсказку минимального размера, мы указываем макету в Родительском виджете (игровое окно),
 * что label не должен уменьшаться ниже минимального размера.*/
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
/*реагирует на нажатие кнопки "старт".
 * Запускается новая игра: сбрасывается состояние игры, счет игрока и уровень и очищает доску*/
    void start();

/*pause() используется для временной остановки текущей игры
 * Реализуется с помощью остановки внутреннего таймера*/
    void pause();

/*сигналы нужны для того, чтобы сообщать другим компонентам программы о статусе игры*/
signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemoved(int numLines);

protected:
/*прорисовка фигур (первой и последующих), пауза*/
    void paintEvent(QPaintEvent *event) override;

/*вызывается каждый раз, когда игрок нажимает клавишу,
 * в то время как виджет TetrixBoard имеет ждёт сообщения от клавиатуры, а не от мыши*/
    void keyPressEvent(QKeyEvent *event) override;
/*Таймер игры, позволяющий управлять скоростью спуска фигуры*/
    void timerEvent(QTimerEvent *event) override;


private:
    enum { BoardWidth = 10, BoardHeight = 20 };

    TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime() { return 1000 / (1 + level); }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
/*очистка поля*/
    void clearBoard();
/*спуск фигуры*/
    void dropDown();
/*спуск всей конструкции вниз на одну линию*/
    void oneLineDown();
/*начисление очков игроку за позиционирование текущей фигуры,
 * проверку полных строк на доске и, если линии не были удалены,
 * создание новой фигуры для замены текущей в виджете следующей фигуры*/
    void pieceDropped(int dropHeight);
/*ищет пустые места в линиях*/
    void removeFullLines();
/*Функция new Piece() помещает следующую доступную фигуру в верхнюю часть доски
 * и создает новую фигуру со случайной формой*/
    void newPiece();
/*обновляет фигуру в виджете, показывающем следующую фигуру*/
    void showNextPiece();
/*проверка на "занятость" следующей ячейки. Делается, чтобы фигуры друг на друга не заскакивали*/
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);

/* Рисует блок - 1/4 фигуры*/
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);

/* QBasicTimer управляет скоростью, с которой тетрамины падают вниз*/

    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    TetrixPiece curPiece;
    TetrixPiece nextPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int level;
    TetrixShape board[BoardWidth * BoardHeight];
};

#endif
