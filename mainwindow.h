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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void newFile();
    void open();
    void quit();
    bool save();
    bool saveAs();
    void chooseBrushColor();
    void chooseBrushSize();
    void chooseForm();
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

    QPoint lastPoint;
    QPixmap pixmap;
    QPainter painter;
    QString currentFile;
    QAction *pixelGridAction;
};

#endif