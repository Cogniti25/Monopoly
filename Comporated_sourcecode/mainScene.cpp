#include "mainScene.h"
#include "cellitem.h"
#include <QPainter>
#include <QGraphicsPixmapItem>

MainScene::MainScene(QObject *parent) : QGraphicsScene(parent)
{

}

void MainScene::setupMainScene()
{
    //Load Board image. Stick it to mainScene
    QImage imageBoard("Image/Board.jpg");
    if (imageBoard.isNull()) qDebug() << "Error: Not found Board image!\n";
    board = this->addPixmap( QPixmap::fromImage(imageBoard) );

    //Load Dice image and change position/size. Stick it to mainScene
    diceImage[0] = new QGraphicsPixmapItem;
    diceImage[1] = new QGraphicsPixmapItem;
    setDiceImage(6, 0);
    setDiceImage(4, 1);

    //Load Cell area control
    setupCell();

    //Test set piece
    QImage imagePiece("Image/car.png");
    piece = this->addPixmap( QPixmap::fromImage(imagePiece) );
    piece->setScale(0.04);

    setPiece(piece, 1);
}

void MainScene::setupCell()
{
    int tmp = 134;

    //Cells at bottom
    for (int i = 10; i >= 2; i--)
    {
        cellItem[i] = new CellItem( QPointF(tmp,890), 84, 133, i, this);
        this->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(tmp, 890) );
        tmp += 84;
    }

    //Cells at top
    tmp = 134;
    for (int i = 22; i <= 30; i++)
    {
        cellItem[i] = new CellItem( QPointF(tmp, 0), 84, 133, i, this);
        this->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(tmp, 0) );
        tmp += 84;
    }

    //Cells on left
    tmp = 134;
    for (int i = 20; i >= 12; i--)
    {
        cellItem[i] = new CellItem( QPointF(0, tmp), 133, 84, i, this);
        this->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(0, tmp) );
        tmp += 84;
    }

    //Cells on right
    tmp = 134;
    for (int i = 32; i <= 40; i++)
    {
        cellItem[i] = new CellItem( QPointF(890, tmp), 133, 84, i, this);
        this->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(890, tmp) );
        tmp += 84;
    }

    cellItem[1] = new CellItem( QPointF(890, 890), 134, 134, 1, this);
    this->addItem( cellItem[1] );
    cellItem[1]->setPos( QPointF(890, 890) );

    cellItem[11] = new CellItem( QPointF(0, 890), 134, 134, 11, this);
    this->addItem( cellItem[11] );
    cellItem[11]->setPos( QPointF(0, 890) );

    cellItem[21] = new CellItem( QPointF(0, 0), 134, 134, 21, this);
    this->addItem( cellItem[21] );
    cellItem[21]->setPos( QPointF(0, 0) );

    cellItem[31] = new CellItem( QPointF(890, 0), 134, 134, 31, this);
    this->addItem( cellItem[31] );
    cellItem[31]->setPos( QPointF(890, 0) );

    //Due to modulo property, numId 40 will become 0 after modulo with 40
    cellItem[0] = cellItem[40];
}

//Load image of dice to the mainScene
//+ number: number of dice need loading
//+ idDice: first or second dice, used for positioning image of dice
void MainScene::setDiceImage(int number, int idDice)
{
    this->removeItem(diceImage[idDice]);
    delete diceImage[idDice];

    //Name of dice has format: "dice" + number of dice
    QString imageName = "Image/dice";
    imageName = imageName + QString::number(number) + ".png";

    QImage imageDice(imageName);
    if (imageDice.isNull()) qDebug() << "Error: Not found Dice image!\n";
    diceImage[idDice] = this->addPixmap( QPixmap::fromImage(imageDice) );
    diceImage[idDice]->setScale(0.2);
    //Put the first dice above the second dice
    if (idDice == 0) diceImage[idDice]->setPos(1030, 0); else diceImage[idDice]->setPos(1030, 70);
}

//Load image of piece to the right cell
void MainScene::setPiece(QGraphicsPixmapItem *&piece, int idCell)
{
    piece->setParentItem( cellItem[idCell] );
    //piece->setPos( cellItem[idCell]->getWidth() / 4,  cellItem[idCell]->getHeight() / 4 );
    piece->setPos(0, 0);
}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    qDebug() << point.x() << ' ' << point.y() << '\n';
    QGraphicsScene::mousePressEvent(event);
}

MainScene::~MainScene()
{
    delete board;
    delete diceImage[0];
    delete diceImage[1];
    for (int i = 1; i <= 40; i++) delete cellItem[i];
}
