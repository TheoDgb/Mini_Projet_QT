//#include <QtWidgets>
//#include "mainwindow.h"
//
//MainWindow::MainWindow()
//    : textEdit(new QPlainTextEdit)
//{
//    setCentralWidget(textEdit);
//
//    createActions();
//    createStatusBar();
//
//    readSettings();
//
//    connect(textEdit->document(), &QTextDocument::contentsChanged,
//            this, &MainWindow::documentWasModified);
//
//#ifndef QT_NO_SESSIONMANAGER
//    connect(qApp, &QGuiApplication::commitDataRequest,
//            this, &MainWindow::commitData);
//#endif
//
//    setCurrentFile(QString());
//    setUnifiedTitleAndToolBarOnMac(true);
//}
//
//void MainWindow::closeEvent(QCloseEvent *event)
//{
//    if (maybeSave()) {
//        writeSettings();
//        event->accept();
//    } else {
//        event->ignore();
//    }
//}
//
//void MainWindow::newFile()
//{
//    if (maybeSave()) {
//        textEdit->clear();
//        setCurrentFile(QString());
//    }
//}
//
//void MainWindow::open()
//{
//    if (maybeSave()) {
//        QString fileName = QFileDialog::getOpenFileName(this);
//        if (!fileName.isEmpty())
//            loadFile(fileName);
//    }
//}
//
//bool MainWindow::save()
//{
//    if (curFile.isEmpty()) {
//        return saveAs();
//    } else {
//        return saveFile(curFile);
//    }
//}
//bool MainWindow::saveAs()
//{
//    QFileDialog dialog(this);
//    dialog.setWindowModality(Qt::WindowModal);
//    dialog.setAcceptMode(QFileDialog::AcceptSave);
//    if (dialog.exec() != QDialog::Accepted)
//        return false;
//    return saveFile(dialog.selectedFiles().first());
//}
//void MainWindow::about() {
//   QMessageBox::about(this, tr("About Application"),
//                      tr("It's a <b>drawing</b> app project created to learn QT."));
//}
//
//void MainWindow::documentWasModified() {
//    setWindowModified(textEdit->document()->isModified());
//}
//
//void MainWindow::createActions() {
//
//    // actions files
//    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
//    QToolBar *fileToolBar = addToolBar(tr("File"));
//    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
//    QAction *newAct = new QAction(newIcon, tr("&New"), this);
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip(tr("Create a new drawing"));
//    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
//    fileMenu->addAction(newAct);
//    fileToolBar->addAction(newAct);
//
//    // actions documents
//    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
//    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
//    openAct->setShortcuts(QKeySequence::Open);
//    openAct->setStatusTip(tr("Open an existing file"));
//    connect(openAct, &QAction::triggered, this, &MainWindow::open);
//    fileMenu->addAction(openAct);
//    fileToolBar->addAction(openAct);
//
//    // action save
//    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
//    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
//    saveAct->setShortcuts(QKeySequence::Save);
//    saveAct->setStatusTip(tr("Save the document to disk"));
//    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
//    fileMenu->addAction(saveAct);
//    fileToolBar->addAction(saveAct);
//    // action save as
//    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
//    QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
//    saveAsAct->setShortcuts(QKeySequence::SaveAs);
//    saveAsAct->setStatusTip(tr("Save the document under a new name"));
//
//    fileMenu->addSeparator();
//
//    const QIcon exitIcon = QIcon::fromTheme("application-exit");
//    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
//    exitAct->setShortcuts(QKeySequence::Quit);
//    exitAct->setStatusTip(tr("Exit the application"));
//
//    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
//    QToolBar *editToolBar = addToolBar(tr("Edit"));
//
//#ifndef QT_NO_CLIPBOARD
//    // a supp
//    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
//    QAction *cutAct = new QAction(cutIcon, tr("Cu&t"), this);
//    cutAct->setShortcuts(QKeySequence::Cut);
//    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
//                            "clipboard"));
//    connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
//    editMenu->addAction(cutAct);
//    editToolBar->addAction(cutAct);
//
//    // a faire : action select couleur
//
//    // action copier text => image
//    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
//    QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
//    copyAct->setShortcuts(QKeySequence::Copy);
//    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
//                             "clipboard"));
//    connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy);
//    editMenu->addAction(copyAct);
//    editToolBar->addAction(copyAct);
//
//    // action paste text => image
//    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
//    QAction *pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
//    pasteAct->setShortcuts(QKeySequence::Paste);
//    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
//                              "selection"));
//    connect(pasteAct, &QAction::triggered, textEdit, &QPlainTextEdit::paste);
//    editMenu->addAction(pasteAct);
//    editToolBar->addAction(pasteAct);
//
//    menuBar()->addSeparator();
//
//
//
//
//
//
//
//
//
//
//
//
//#endif // !QT_NO_CLIPBOARD
//
//
//
//    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
//    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
//    aboutAct->setStatusTip(tr("Show the application's About box"));
//
//    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
//    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
//
//#ifndef QT_NO_CLIPBOARD
//    cutAct->setEnabled(false);
//    copyAct->setEnabled(false);
//    connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
//    connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
//#endif // !QT_NO_CLIPBOARD
//}
//void MainWindow::createStatusBar()
//{
//    statusBar()->showMessage(tr("Ready"));
//}
//void MainWindow::readSettings()
//{
//    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
//    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
//    if (geometry.isEmpty()) {
//        const QRect availableGeometry = screen()->availableGeometry();
//        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
//        move((availableGeometry.width() - width()) / 2,
//             (availableGeometry.height() - height()) / 2);
//    } else {
//        restoreGeometry(geometry);
//    }
//}
//void MainWindow::writeSettings()
//{
//    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
//    settings.setValue("geometry", saveGeometry());
//}
//bool MainWindow::maybeSave()
//{
//    if (!textEdit->document()->isModified())
//        return true;
//    const QMessageBox::StandardButton ret
//        = QMessageBox::warning(this, tr("Application"),
//                               tr("The document has been modified.\n"
//                                  "Do you want to save your changes?"),
//                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//    switch (ret) {
//    case QMessageBox::Save:
//        return save();
//    case QMessageBox::Cancel:
//        return false;
//    default:
//        break;
//    }
//    return true;
//}
//void MainWindow::loadFile(const QString &fileName)
//{
//    QFile file(fileName);
//    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, tr("Application"),
//                             tr("Cannot read file %1:\n%2.")
//                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
//        return;
//    }
//
//    QTextStream in(&file);
//#ifndef QT_NO_CURSOR
//    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
//#endif
//    textEdit->setPlainText(in.readAll());
//#ifndef QT_NO_CURSOR
//    QGuiApplication::restoreOverrideCursor();
//#endif
//
//    setCurrentFile(fileName);
//    statusBar()->showMessage(tr("File loaded"), 2000);
//}
//bool MainWindow::saveFile(const QString &fileName)
//{
//    QString errorMessage;
//
//    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
//    QSaveFile file(fileName);
//    if (file.open(QFile::WriteOnly | QFile::Text)) {
//        QTextStream out(&file);
//        out << textEdit->toPlainText();
//        if (!file.commit()) {
//            errorMessage = tr("Cannot write file %1:\n%2.")
//                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
//        }
//    } else {
//        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
//                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
//    }
//    QGuiApplication::restoreOverrideCursor();
//
//    if (!errorMessage.isEmpty()) {
//        QMessageBox::warning(this, tr("Application"), errorMessage);
//        return false;
//    }
//
//    setCurrentFile(fileName);
//    statusBar()->showMessage(tr("File saved"), 2000);
//    return true;
//}
//void MainWindow::setCurrentFile(const QString &fileName)
//{
//    curFile = fileName;
//    textEdit->document()->setModified(false);
//    setWindowModified(false);
//
//    QString shownName = curFile;
//    if (curFile.isEmpty())
//        shownName = "untitled.txt";
//    setWindowFilePath(shownName);
//}
//QString MainWindow::strippedName(const QString &fullFileName)
//{
//    return QFileInfo(fullFileName).fileName();
//}
//#ifndef QT_NO_SESSIONMANAGER
//void MainWindow::commitData(QSessionManager &manager)
//{
//    if (manager.allowsInteraction()) {
//        if (!maybeSave())
//            manager.cancel();
//    } else {
//        // Non-interactive: save without asking
//        if (textEdit->document()->isModified())
//            save();
//    }
//}
//#endif










#include <QtWidgets>
#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    // taille de la fenetre <=
    setFixedSize(500, 500);

    // Initialise le pixmap et le painter
    pixmap = QPixmap(500, 500);
    pixmap.fill(Qt::white);
    painter.begin(&pixmap);

    // Créer un menu avec des actions
    createActions();
    // Afficher le menu
    setMenuBar(menuBar());
}

MainWindow::~MainWindow()
{
}

void MainWindow::newFile() {
    if (!pixmap.toImage().isNull()) {
        // Demander une confirmation à l'utilisateur avant de créer un nouveau fichier
        QMessageBox::StandardButton reply = QMessageBox::question(
                this, tr("Confirmation"), tr("Êtes-vous sûr de vouloir créer un nouveau fichier de dessin ?\nTout le contenu non enregistré sera perdu."),
                QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::No) {
            // Création d'un nouveau fichier de dessin
            // Remplissage du pixmap avec de la couleur blanche
            pixmap.fill(Qt::white);
            // Réinitialisation du painter pour dessiner sur le nouveau pixmap
            painter.end();
            painter.begin(&pixmap);
            // Actualisation de la fenêtre
            update();
        }
    }
}

void MainWindow::open() {

}

void MainWindow::quit() {
    QApplication::quit();
}

void MainWindow::createActions() {
    // Crée un menu "Fichier" dans la barre de menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));

    // Création d'une action "Nouveau"
    QAction *newAction = new QAction(tr("&Nouveau"), this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAction);

    // Création d'une action "Ouvrir"
    QAction *openAction = new QAction(tr("&Ouvrir"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAction);

    // Ajout d'une séparation entre les actions "Ouvrir" et "Quitter"
    fileMenu->addSeparator();

    // Création d'une action "Quitter"
    QAction *quitAction = new QAction(tr("&Quitter"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &MainWindow::quit);
    fileMenu->addAction(quitAction);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Enregistre la position actuelle de la souris
        lastPoint = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // Dessine une ligne entre la dernière position de la souris et la nouvelle position
        painter.drawLine(lastPoint, event->pos());

        // Enregistre la nouvelle position de la souris comme la dernière position
        lastPoint = event->pos();

        // Met à jour la fenêtre
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    // Dessine le pixmap sur la fenêtre
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}