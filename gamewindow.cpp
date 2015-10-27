#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QLabel>
#include <QDebug>

int GameWindow::WIDTH = 1024;
int GameWindow::HEIGHT = 768;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setFixedSize(WIDTH, HEIGHT);

    if(!model.loadLevels()) {
        qDebug() << "Couldn't load the levels!";
        deleteLater();
    } else {
         QPixmap blockPic(":/images/block.png");
         auto blocks = model.getCurrentLevel()->getBlocks();
         for(int y = 0; y < blocks.size(); y++) {
             for(int x = 0; x < blocks[y].size(); x++) {
                 if(blocks[y][x] != nullptr) {
                       Block* b = blocks[y][x];
                       QLabel* lbl = new QLabel(this);
                       lbl->setGeometry(b->getX(), b->getY(), b->getWidth(), b->getHeight());
                       lbl->setPixmap(blockPic);
                       lbl->setScaledContents(true);
                       b->setBuddy(lbl);
                       lbl->show();
                 }
             }
         }

         Player* p = model.getCurrentLevel()->getPlayer();
         QLabel* plbl = new QLabel(this);
         plbl->setGeometry(p->getRect());
         QPixmap playerPic(":/images/player.png");
         plbl->setPixmap(playerPic);
         plbl->setScaledContents(true);
         p->setBuddy(plbl);
         plbl->show();

         Exit* e = model.getCurrentLevel()->getExit();
         QLabel* elbl = new QLabel(this);
         elbl->setGeometry(e->getRect());
         QPixmap exitPic(":/images/exit.png");
         elbl->setPixmap(exitPic);
         elbl->setScaledContents(true);
         e->setBuddy(elbl);
         elbl->show();

         QTimer *timer = new QTimer(this);
         timer->setInterval(1000 / fps);
         connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
         timer->start();
    }
}

void GameWindow::timerHit() {
    model.update();
}

GameWindow::~GameWindow()
{
    delete ui;
}
