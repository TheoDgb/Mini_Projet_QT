//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H
//
//#include <QMainWindow>
//
//QT_BEGIN_NAMESPACE
//class QAction;
//class QMenu;
//class QPlainTextEdit;
//class QSessionManager;
//QT_END_NAMESPACE
//
//class MainWindow : public QMainWindow
//{
//    Q_OBJECT
//
//public:
//    MainWindow();
//
//    void loadFile(const QString &fileName);
//
//protected:
//    void closeEvent(QCloseEvent *event) override;
//
//private slots:
//    void newFile();
//    void open();
//    bool save();
//    bool saveAs();
//    void about();
//    void documentWasModified();
//#ifndef QT_NO_SESSIONMANAGER
//    void commitData(QSessionManager &);
//#endif
//
//private:
//    void createActions();
//    void createStatusBar();
//    void readSettings();
//    void writeSettings();
//    bool maybeSave();
//    bool saveFile(const QString &fileName);
//    void setCurrentFile(const QString &fileName);
//    QString strippedName(const QString &fullFileName);
//
//    QPlainTextEdit *textEdit;
//    QString curFile;
//};
//
//#endif



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

private:
    void createActions();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    QPoint lastPoint;
    QPixmap pixmap;
    QPainter painter;
    QString currentFile;
};

#endif