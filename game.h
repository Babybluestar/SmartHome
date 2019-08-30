#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
class Game: public QGraphicsView{
    Q_OBJECT
public:
    explicit Game(QWidget* parent = 0);
    ~Game();
    void displayWinning();
    void displayLosing();

    void decreaseEnemiesAmount();
    int getEnemiesAmount();

    void closeEvent(QCloseEvent *event);

    void createBlockCol(double x, size_t amount);
    void createBlockGrid();

    QGraphicsScene * scene;
    QMediaPlayer *music;
public slots:
    void start();
    void displayMainMenu();


private:
    int _enemiesAmount;

};

#endif // GAME_H
