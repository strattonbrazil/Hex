#ifndef CANVAS_H
#define CANVAS_H

#include <QGLWidget>
#include <QSharedPointer>
#include <QTimer>
#include <QElapsedTimer>

#include "hexgrid.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
signals:

public slots:
    void advance();
private:
    QRect getHexTarget(int row, int column);
    QRect getHexOverlayTarget(int row, int column, float yScale=1.0);
    void renderGrid(QPainter &painter);
    void updateLogic();
    bool hasPulseUpdate();

    QSharedPointer<HexGrid> _grid;
    Hex* _targetHex;
    Hex* _hoverHex;

    QElapsedTimer _elapsed;
    QTimer _timer;
    qint64 _lastUpdate;

    QPoint _pieP;
    QPoint _ogreP;
    QPoint _playerP;
};

#endif // CANVAS_H
