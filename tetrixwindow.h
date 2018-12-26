#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class TetrixBoard;

/*Класс TetrixWindow используется для отображения
 * информации об игре и содержит игровую область*/
class TetrixWindow : public QWidget
{
    Q_OBJECT

public:
    TetrixWindow();

/* @ param *board - игровое поле
 * @ param *nextPieceLabel - виджет для показа следующей тетрамины
 * @ param *scoreLcd - виджет для показа очков
 * @ param *levelLcd - виджет для показа номера уровня
 * @ param *linesLcd - виджет для показа количества удалённых линий
 * @ param *startButton - кнопка "старт"
 * @ param *pauseButton - кнопка "пауза"
 * @ param *quitButton - кнопка "выход"
*/

private:
    QLabel *createLabel(const QString &text);

    TetrixBoard *board;
    QLabel *nextPieceLabel;
    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *quitButton;
};
#endif
