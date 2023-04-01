#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void newFile();
    void open();
    void quit();
    bool save();
    bool saveAs();

    void zoomIn();
    void zoomOut();
    void rectangleSelect(bool);
    void paintBucket(bool);
    void pinceau(bool);
    void droite(bool);
    void chooseForm(bool);

    void chooseBrushColor();
    void chooseBrushSize();
    void pixelGrid(bool);

    void resizeImage();
    void resizeCanvas();
    void flipHorizontally();
    void flipVertically();
    void rotateRight();
    void rotateLeft();
    void rotateBehind();

private:
    void createActions();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    int brushSize;
    QColor brushColor;

    QPoint lastPoint;
    QPixmap pixmap;
    QPainter painter;
    QString currentFile;
    QAction *pixelGridAction;
    QPixmap gridPixmap;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *rectangleSelectAction;
    QRect selectionRect;
    bool isSelectingRect;

    QAction *paintBucketAction;
    QAction *pinceauAction;
    QAction *droiteAction;
    QAction *formAction;
    QPoint startPoint;
    QPoint endPoint;
    QPixmap previewPixmap;
};

#endif