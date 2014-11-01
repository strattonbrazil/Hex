#include "canvas.h"

#include <QPainter>
#include <QMouseEvent>

const int HEX_WIDTH = 60;
const int HEX_HEIGHT = 50;
const int HALF_HEX_HEIGHT = HEX_HEIGHT / 2;
const int OVERLAP = 14;
const int PULSE_INTERVAL = 2000;

#include <iostream>
using namespace std;

Canvas::Canvas(QWidget *parent) :
    QWidget(parent), _hoverHex(0)
{
    _grid = QSharedPointer<HexGrid>(new HexGrid(10,10));

    QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(advance()));
    _timer.start(1000 / 33);
    _elapsed.start();
    _lastUpdate = 0;
    _targetHex = 0;

    _pieP = QPoint(0, 4);
    _ogreP = QPoint(1, 4);
    _playerP = QPoint(9, 4);

    setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    QColor backgroundColor(24,24,24);
    painter.fillRect(0, 0, width(), height(), QBrush(backgroundColor));

    renderGrid(painter);

    // draw the pie
    QImage pieImage(":/resource/assets/pie.png");
    painter.drawImage(getHexOverlayTarget(_pieP.x(), _pieP.y()), pieImage);

    // draw the ogre
    QImage ogreImage(":/resource/assets/ogre.png");
    painter.drawImage(getHexOverlayTarget(_ogreP.x(), _ogreP.y(), 1.3f), ogreImage);

    // draw the player
    QImage playerImage(":/resource/assets/knight.png");
    painter.drawImage(getHexOverlayTarget(_playerP.x(), _playerP.y()), playerImage);


    // draw the player destination
    if (_targetHex && (_targetHex->row() != _playerP.x() || _targetHex->column() != _playerP.y())) {
        QImage playerTargetImage(":/resource/assets/knight_transparent.png");
        painter.drawImage(getHexOverlayTarget(_targetHex->row(), _targetHex->column()), playerTargetImage);
    }

    //painter.drawText(20, height() - 100, "Timer: ");

    // draw countdown
    float countup = (_elapsed.elapsed() - (float)_lastUpdate) / PULSE_INTERVAL;
    painter.fillRect(0, height()-20, width()*countup, 20, QBrush(QColor(0,0,255)));
}

void Canvas::renderGrid(QPainter &painter)
{
    QImage hexImage(":/resource/assets/hex.png");
    QImage greenHexImage(":/resource/assets/hex_green_border.png");


    for (int row = 0; row < _grid->height(); row++) {
        for (int column = 0; column < _grid->width(); column++) {
            Hex* hex = _grid->hex(row, column);
            QRect target = getHexTarget(row, column);
            if (hex == _hoverHex)
                painter.drawImage(target, greenHexImage);
            else
                painter.drawImage(target, hexImage);


            painter.setPen(QColor(255,255,255));
            painter.setBrush(QBrush(QColor(255,255,255)));
            QString f;
            f.setNum(hex->distance());
            painter.drawText(target.x() + 0.5*target.width(), target.y() + 0.5*target.height(), f);
        }
    }
}

QRect Canvas::getHexTarget(int row, int column)
{
    int lowered = column % 2 == 1;
    const int x = HEX_WIDTH * column - OVERLAP * column;
    const int y = HEX_HEIGHT * row + HALF_HEX_HEIGHT * lowered;
    return QRect(x, y, HEX_WIDTH, HEX_HEIGHT);
}

QRect Canvas::getHexOverlayTarget(int row, int column, float yScale)
{
    QRect target = getHexTarget(row, column);
    int newHeight = target.height() * yScale;
    target.setY(target.y() - (newHeight-target.height()));
    target.setHeight(newHeight);

    return target;
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    _targetHex = _hoverHex;
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QPoint cursorP = event->pos();

    //if (cursorP.x() < OVERLAP)
      //  cout << "first column" << endl;

    // check both columns, should be in one or the other
    // either in this column or column+1
    Hex* closestHex = 0;
    float closestD;
    int column = (cursorP.x() - OVERLAP) / (HEX_WIDTH - OVERLAP);
    for (int checkColumn = column; checkColumn <= column+1; checkColumn++) {
        int lowered = checkColumn % 2 == 1;
        int row = (cursorP.y() - lowered*HALF_HEX_HEIGHT) / HEX_HEIGHT;

        if (row < _grid->height() && checkColumn < _grid->width()) {
            QRect cellBounds = getHexTarget(row, checkColumn);
            if (cellBounds.contains(cursorP)) {
                Hex* hex = _grid->hex(row, checkColumn);
                // using manhattan length, need real sqrt?
                float cursorD = (cellBounds.center() - cursorP).manhattanLength();
                if (!closestHex) {
                    closestHex = hex;
                    closestD = cursorD;
                } else if (cursorD < closestD) {
                    closestHex = hex;
                    closestD = cursorD;
                }
            }
        }
    }
    _hoverHex = closestHex;

    update();
}

void Canvas::advance()
{
    updateLogic();
    update();
}

void Canvas::updateLogic()
{
    if (hasPulseUpdate()) {
        // move ogre
        QLinkedList<Hex*> ogrePath = _grid->findPath(_ogreP, _playerP);
        _ogreP.setX(ogrePath.first()->row());
        _ogreP.setY(ogrePath.first()->column());

        // move player
        if (_targetHex) {
            QPoint targetP(_targetHex->row(), _targetHex->column());
            QLinkedList<Hex*> playerPath = _grid->findPath(_playerP, targetP);

            if (playerPath.size() >= 2)
                playerPath.pop_front();

            if (playerPath.size() > 0) {
                _playerP.setX(playerPath.first()->row());
                _playerP.setY(playerPath.first()->column());
            }

        }
    }
}

bool Canvas::hasPulseUpdate()
{
    qint64 current = _elapsed.elapsed();
    if (current - _lastUpdate > PULSE_INTERVAL) {
        _lastUpdate = current;
        return true;
    }
    return false;
}
