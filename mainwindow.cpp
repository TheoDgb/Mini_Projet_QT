#include <QtWidgets>
#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QColorDialog>

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
    // ouvrir une image
}

void MainWindow::quit() {
    QApplication::quit();
}

bool MainWindow::save()
{
    if (currentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(currentFile);
    }
}
bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    setWindowModified(false);

    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = "untitled.png";
    setWindowFilePath(shownName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly)) {
        pixmap.save(&file, "PNG"); // sauvegarde de la pixmap en tant qu'image PNG
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                    .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }
    setCurrentFile(fileName); // appel de la fonction setCurrentFile
    statusBar()->showMessage(tr("Image saved"), 2000);
    return true;
}

void MainWindow::chooseBrushColor() {
    QColor color = QColorDialog::getColor(painter.pen().color(), this, tr("Choisir une couleur"));
    if (color.isValid()) {
        painter.setPen(color);
    }
}

void MainWindow::chooseBrushSize() {
    bool ok;
    int size = QInputDialog::getInt(this, tr("Taille du pinceau"), tr("Entrez une taille pour le pinceau :"), 1, 1, 50, 1, &ok);
    if (ok) {
        painter.setPen(QPen(painter.pen().color(), size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
}

void MainWindow::createActions() {
    // Crée un menu "Fichier" dans la barre de menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));
    // Crée une toolbar
    QToolBar *fileToolBar = addToolBar(tr("Fichier"));

    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    // Création d'une action "Nouveau"
    QAction *newAction = new QAction(tr("&Nouveau"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAction);
    //ajout à la toolbar
    fileToolBar->addAction(newAction);

    // Action ouvrir une image
    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAction = new QAction(openIcon, tr("&Ouvrir"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAction);
    fileToolBar->addAction(openAction);

    // Action enregistrer une image
    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
    QAction *saveAction = new QAction(saveIcon, tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Open);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAction);
    fileToolBar->addAction(saveAction);

    // Action enregistrer sous une image
    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveAsAction = new QAction(saveAsIcon, tr("&Save as"), this);
    saveAsAction->setShortcuts(QKeySequence::Open);
//    saveAsAction->setStatusTip(tr("Save file"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
    fileMenu->addAction(saveAsAction);
//    fileToolBar->addAction(saveAsAction);

    // Ajout d'une séparation entre les actions "Ouvrir" et "Quitter"
    fileMenu->addSeparator();

    // Création d'une action "Quitter"
    QAction *quitAction = new QAction(tr("&Quitter"), this);
    quitAction->setShortcut(QKeySequence::Quit);
    connect(quitAction, &QAction::triggered, this, &MainWindow::quit);
    fileMenu->addAction(quitAction);

    // Créer un menu "Brush" dans la barre de menu
    QMenu *brushMenu = menuBar()->addMenu(tr("&Brush"));
    // Créer une toolbar "Brush"
    QToolBar *brushToolBar = addToolBar(tr("Brush"));

    // Action choisir la couleur de la brush
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    QAction *colorAction = new QAction(cutIcon, tr("Choose Color"), this);
    colorAction->setShortcut(QKeySequence::New);
    colorAction->setStatusTip(tr("Choose a color for the brush"));
    connect(colorAction, &QAction::triggered, this, &MainWindow::chooseBrushColor);
    brushMenu->addAction(colorAction);
    brushToolBar->addAction(colorAction);

    // Action choisir la taille de la brush
    const QIcon sizeIcon = QIcon("./images/size.png");
    QAction *sizeAction = new QAction(sizeIcon,tr("&Choose Size"), this);
    sizeAction->setShortcut(QKeySequence::New);
    sizeAction->setStatusTip(tr("Choose a size for the brush"));
    connect(sizeAction, &QAction::triggered, this, &MainWindow::chooseBrushSize);
    brushMenu->addAction(sizeAction);
    brushToolBar->addAction(sizeAction);

    // Action choisir une forme (cercle/trait/rectangle)

    // Action

    // Menu effet

    // Image (redimentionner)

    // calques
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