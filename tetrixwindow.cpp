#include <QtWidgets>

#include "tetrixboard.h"
#include "tetrixwindow.h"


/*Конструктор настраивает элементы пользовательского интерфейса для игры*/
TetrixWindow::TetrixWindow()
{
    board = new TetrixBoard;

    nextPieceLabel = new QLabel;
    nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    board->setNextPieceLabel(nextPieceLabel);
/*Объекты QLCDNumber используются для отображения оценки, количества жизней и удаленных строк.
 * Они изначально показывают значения по умолчанию (0) и будут заполнены в начале игры*/
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Старт"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Выход"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Пауза"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

/*Кнопки "старт", "выход" и "пауза" не получают сигналов с клавиатуры. Клавиатура используется только экземпляром TetrixBoard.
 * NB: кнопки реагируют на специальные сочетания клавишь Alt+ Ctrl+ */
    connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
/*обновление счета, количества жизней и линий, удаленных из игровой зоны.*/
    connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
    connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
    connect(board, SIGNAL(linesRemoved(int)),
            linesLcd, SLOT(display(int)));

/*помещаем виджеты и board в QGridLayout вместе с некоторыми ярлыками, которые мы создаем с помощью функции createLabel*/
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("Следующий элемент")), 0, 0);
    layout->addWidget(nextPieceLabel, 1, 0);
    layout->addWidget(createLabel(tr("Уровень")), 2, 0);
    layout->addWidget(levelLcd, 3, 0);
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(board, 0, 1, 6, 1);
    layout->addWidget(createLabel(tr("Очки")), 0, 2);
    layout->addWidget(scoreLcd, 1, 2);
    layout->addWidget(createLabel(tr("Количество убранных линий")), 2, 2);
    layout->addWidget(linesLcd, 3, 2);
    layout->addWidget(quitButton, 4, 2);
    layout->addWidget(pauseButton, 5, 2);
    setLayout(layout);

    setWindowTitle(tr("Game Tetrix"));
    resize(550, 370);
}

/*устанавливаем макет сетки на виджете, даем окну заголовок и изменяем его размер до соответствующего размера.*/
QLabel *TetrixWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}

/*Поскольку каждая метка будет использоваться в макете виджета,
 * она станет дочерним элементом виджета TetrixWindow и в результате будет удалена при удалении окна.
*/
