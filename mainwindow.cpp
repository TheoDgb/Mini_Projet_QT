#include <QtWidgets>
#include "mainwindow.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent) {
    // taille de la fenetre
    resize(720, 720);

    // Initialise le pixmap et le painter
    pixmap = QPixmap(400, 400);
    pixmap.fill(Qt::white);

    setCursor(Qt::CrossCursor);
    // Initialise le pinceau
    brushSize = 1;
    brushColor = Qt::black;

    // Créer un menu avec des actions
    createActions();
    // Afficher le menu
    setMenuBar(menuBar());
}

void MainWindow::newFile() {
    if (!pixmap.toImage().isNull()) {
        // Demander une confirmation à l'utilisateur avant de créer un nouveau fichier
        QMessageBox::StandardButton reply = QMessageBox::question(
                this, tr("Unsaved changes"), tr("Are you sure you want to create a new drawing file ?\nAll unsaved content will be lost."),
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Save);
        if (reply == QMessageBox::Save) {
            saveAs();
        } else if (reply == QMessageBox::Yes) {
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty()) {
        QPixmap image;
        if (image.load(fileName)) {
            painter.end(); // End the painting on the old pixmap
            pixmap = image;
            painter.begin(&pixmap); // Begin painting on the new pixmap
            update();
            setCurrentFile(fileName);
        } else {
            QMessageBox::warning(this, tr("Application"), tr("Cannot load %1.").arg(fileName));
        }
    }
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

//void MainWindow::zoomIn(bool checked) {
//    zoomInAction->setChecked(checked);
//    if (checked) {
//        // connect to mouse press event to enable zoom-in on left mouse click
//        connect(this, &MainWindow::mousePressEvent, this, &MainWindow::handleZoomIn);
//    } else {
//        // disconnect from mouse press event to disable zoom-in
//        disconnect(this, &MainWindow::mousePressEvent, this, &MainWindow::handleZoomIn);
//    }
//}
//
//void MainWindow::handleZoomIn(QMouseEvent *event) {
//    // position de la souris
//    QPoint clickPos = event->pos();
//
//    painter.end();
//    QPixmap newPixmap = pixmap.scaled(pixmap.width()*1.2, pixmap.height()*1.2);
//    pixmap = newPixmap;
//    update();
//    painter.begin(&pixmap);
//}
// in mousepressevent Check if zoom in or zoom out is checked
//    if (zoomInAction->isChecked()) {
//        handleZoomIn(event);
//    } else if (zoomOutAction->isChecked()) {
//        handleZoomOut(event);
//    }
//void zoomIn(bool);
//void zoomOut(bool);
//void handleZoomIn(QMouseEvent *event);
//void handleZoomOut(QMouseEvent *event);

void MainWindow::zoomIn() {
    if (pinceauAction->isChecked()) {
        painter.end();

        QPixmap newPixmap = pixmap.scaled(pixmap.width()*1.2, pixmap.height()*1.2);
        pixmap = newPixmap;
        update();

        painter.begin(&pixmap);
        painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        QPixmap newPixmap = pixmap.scaled(pixmap.width()*1.2, pixmap.height()*1.2);
        pixmap = newPixmap;
        update();
    }
}
void MainWindow::zoomOut() {
    if (pinceauAction->isChecked()) {
        painter.end();

        QPixmap newPixmap = pixmap.scaled(pixmap.width() * 0.8, pixmap.height() * 0.8);
        pixmap = newPixmap;
        update();

        painter.begin(&pixmap);
        painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        QPixmap newPixmap = pixmap.scaled(pixmap.width()*0.8, pixmap.height()*0.8);
        pixmap = newPixmap;
        update();
    }
}
void MainWindow::rectangleSelect(bool) {
    if (rectangleSelectAction->isChecked()) {
        pinceauAction->setChecked(false);
        droiteAction->setChecked(false);
        // Activer le mode de sélection de rectangle
        selectionRect = QRect(); // Initialiser la sélection à un rectangle vide
        isSelectingRect = true;
        setCursor(Qt::CrossCursor); // Changer le curseur pour indiquer le mode de sélection
    } else {
        // Désactiver le mode de sélection de rectangle
        painter.begin(&pixmap);
        isSelectingRect = false;
        setCursor(Qt::ArrowCursor); // Changer le curseur pour indiquer que le mode de sélection est désactivé

        if (selectionRect.width() > 0 && selectionRect.height() > 0) {
            // Si un rectangle de sélection valide a été créé, copier son contenu dans le presse-papiers
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setPixmap(pixmap.copy(selectionRect));
        }

        // Réinitialiser la sélection de rectangle
        selectionRect = QRect();
        update(); // Mettre à jour l'affichage pour effacer la sélection de rectangle
        painter.end();
    }
}
//a faire :
//Si checked alors :
//- on active le mode de sélection de rectangle
//- si on fait un clic simple alors on enlève le rectangle de selection actuel
//
//Si pas checked alors :
//- Désactive le mode de sélection de rectangle
//- mais si un rectangle de sélection est en cours alors le garder
void MainWindow::paintBucket(bool) {

}
void MainWindow::pinceau(bool) {
    if (pinceauAction->isChecked()) {
        rectangleSelectAction->setChecked(false);
        droiteAction->setChecked(false);
        painter.begin(&pixmap);
        painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter.end();
    }
}
void MainWindow::droite(bool)
{
    if (droiteAction->isChecked()) {
        rectangleSelectAction->setChecked(false);
        pinceauAction->setChecked(false);
    }
}
void MainWindow::chooseForm(bool)
{
    // choisir une forme
}

// Menu Brush
void MainWindow::chooseBrushColor() {
    if (pinceauAction->isChecked()) {
        QColor color = QColorDialog::getColor(brushColor, this, tr("Choose brush color"));
        if (color.isValid()) {
            brushColor = color;
            painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
    } else {
        painter.begin(&pixmap);
        QColor color = QColorDialog::getColor(brushColor, this, tr("Choose brush color"));
        if (color.isValid()) {
            brushColor = color;
            painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        painter.end();
    }
}
void MainWindow::chooseBrushSize() {
    if (pinceauAction->isChecked()) {
        int size = QInputDialog::getInt(this, tr("Brush size"), tr("Select a brush size :"), brushSize, 1, 50, 1);
        brushSize = size;
        painter.setPen(QPen(painter.pen().color(), brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter.begin(&pixmap);
        int size = QInputDialog::getInt(this, tr("Brush size"), tr("Select a brush size :"), brushSize, 1, 50, 1);
        brushSize = size;
        painter.setPen(QPen(painter.pen().color(), brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.end();
    }
}

// Menu Affichage
void MainWindow::pixelGrid(bool checked) {

    // il faudrait créer un calque pour la grille de pixels

    pixelGridAction->setChecked(checked);

    if (checked) {
        painter.end();

        // Créer une nouvelle pixmap gridPixmap par dessus la pixmap de dessin
        gridPixmap = QPixmap(pixmap.size());
        gridPixmap.fill(Qt::transparent);

        // Initialiser le painter pour dessiner sur la gridPixmap
        QPainter gridPainter(&gridPixmap);

        // Dessiner une grille de pixels sur la gridPixmap
        QPen pen(Qt::gray, 1, Qt::DotLine);
        gridPainter.setPen(pen);

        int gridSize = 10;  // taille des pixels de la grille
        for (int i = gridSize; i < gridPixmap.width(); i += gridSize) {
            gridPainter.drawLine(i, 0, i, gridPixmap.height());
        }
        for (int j = gridSize; j < gridPixmap.height(); j += gridSize) {
            gridPainter.drawLine(0, j, gridPixmap.width(), j);
        }

        // Arrêter de dessiner sur la gridPixmap
        gridPainter.end();

        // Initialiser le painter pour dessiner sur la pixmap de dessin
        painter.begin(&pixmap);

        // Dessiner la pixmap de dessin sans la gridPixmap
        painter.drawPixmap(0, 0, pixmap);
        // Dessiner la gridPixmap sur la pixmap de dessin
        painter.drawPixmap(0, 0, gridPixmap);
        update();
    } else {
        // Supprimer la gridPixmap
        gridPixmap = QPixmap();

        // Afficher seulement la pixmap de dessin
        painter.end();
        painter.begin(&pixmap);
        painter.drawPixmap(0, 0, pixmap);
        update();
    }
}

// Menu Image
void MainWindow::resizeImage() {
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Resize Image"));
    // Demande nouvelle largeur
    QSpinBox *widthSpinBox = new QSpinBox(&dialog);
    widthSpinBox->setRange(1, 10000);
    widthSpinBox->setValue(pixmap.width());
    QLabel *widthLabel = new QLabel(tr("New width:"), &dialog);
    widthLabel->setBuddy(widthSpinBox);
    // Demande nouvelle hauteur
    QSpinBox *heightSpinBox = new QSpinBox(&dialog);
    heightSpinBox->setRange(1, 10000);
    heightSpinBox->setValue(pixmap.height());
    QLabel *heightLabel = new QLabel(tr("New height:"), &dialog);
    heightLabel->setBuddy(heightSpinBox);
    // Checkbox ré-échantillonnage proche voisin
    QCheckBox *nearestNeighborCheckBox = new QCheckBox(tr("Use nearest-neighbor resampling"), &dialog);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    // Créer la VBox et on lui associe les widgets précédents
    QVBoxLayout layout(&dialog);
    layout.addWidget(widthLabel);
    layout.addWidget(widthSpinBox);
    layout.addWidget(heightLabel);
    layout.addWidget(heightSpinBox);
    layout.addWidget(nearestNeighborCheckBox);
    layout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
        return;

    int newWidth = widthSpinBox->value();
    int newHeight = heightSpinBox->value();
    bool useNearestNeighbor = nearestNeighborCheckBox->isChecked();

    painter.end(); // End the painting on the old pixmap

    // Resize the pixmap
    QPixmap newPixmap(newWidth, newHeight);
    newPixmap.fill(Qt::white);
    QPainter newPainter(&newPixmap);

    if (useNearestNeighbor) { // ré-échantillonnage proche voisin
        newPainter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        newPainter.drawPixmap(0, 0, newWidth, newHeight, pixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation));
    } else { // ré-échantillonnage meilleure qualité
        newPainter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        newPainter.drawPixmap(QPoint(0, 0), pixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

    pixmap = newPixmap;
    painter.begin(&pixmap); // Begin painting on the new pixmap

    // Update the display
    update();
}

void MainWindow::resizeCanvas() {
    // Ouvrir une boite de dialogue pour demander une nouvelle taille pour la zone de dessin
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Nouvelle largeur"), tr("Entrer la nouvelle largeur :"), pixmap.width(), 100, 1000, 1, &ok);
    if (!ok) return; // Annuler

    int newHeight = QInputDialog::getInt(this, tr("Nouvelle hauteur"), tr("Entrer la nouvelle hauteur :"), pixmap.height(), 100, 1000, 1, &ok);
    if (!ok) return; // Annuler

    // Sauvegarder la taille et la couleur de la brosse
    int oldBrushSize = painter.pen().width();
    QColor oldBrushColor = painter.pen().color();

    // Arrêter de dessiner
    painter.end();

    // Copier le dessin actuel
    QPixmap oldPixmap = pixmap;

    // Mettre à jour la taille de la zone de dessin
    pixmap = QPixmap(newWidth, newHeight);
    pixmap.fill(Qt::white);

    // Ajouter du blanc pour agrandir la zone de dessin
    painter.begin(&pixmap);
    painter.drawPixmap(0, 0, oldPixmap);

    // Restaurer la taille et la couleur de la brosse
    painter.setPen(QPen(oldBrushColor, oldBrushSize, Qt::SolidLine));

    update();
}
void MainWindow::flipHorizontally() {
    int oldBrushSize = painter.pen().width();
    QColor oldBrushColor = painter.pen().color();

    painter.end();

    // Flip horizontalement la pixmap
    QPixmap flippedPixmap = pixmap.transformed(QTransform().scale(-1, 1));
    pixmap = flippedPixmap;

    painter.begin(&pixmap);
    painter.setPen(QPen(oldBrushColor, oldBrushSize, Qt::SolidLine));

    update();
}
void MainWindow::flipVertically() {
    int oldBrushSize = painter.pen().width();
    QColor oldBrushColor = painter.pen().color();

    painter.end();

    // Flip verticalement la pixmap
    QPixmap flippedPixmap = pixmap.transformed(QTransform().scale(1, -1));
    pixmap = flippedPixmap;

    painter.begin(&pixmap);
    painter.setPen(QPen(oldBrushColor, oldBrushSize, Qt::SolidLine));

    update();
}
void MainWindow::rotateRight() {
    int oldBrushSize = painter.pen().width();
    QColor oldBrushColor = painter.pen().color();

    painter.end();

    // Pivote de 90° vers la droite la pixmap
    QPixmap rotatedPixmap = pixmap.transformed(QTransform().rotate(90));
    pixmap = rotatedPixmap;

    painter.begin(&pixmap);
    painter.setPen(QPen(oldBrushColor, oldBrushSize, Qt::SolidLine));

    update();
}
void MainWindow::rotateLeft() {
    int oldBrushSize = painter.pen().width();
    QColor oldBrushColor = painter.pen().color();

    painter.end();

    // Pivote de 90° vers la gauche la pixmap
    QPixmap rotatedPixmap = pixmap.transformed(QTransform().rotate(-90));
    pixmap = rotatedPixmap;

    painter.begin(&pixmap);
    painter.setPen(QPen(oldBrushColor, oldBrushSize, Qt::SolidLine));

    update();
}
void MainWindow::rotateBehind() {
    int oldBrushSize = painter.pen().width();
    QColor oldBrushColor = painter.pen().color();

    painter.end();

    // Pivote de 180°
    QPixmap rotatedPixmap = pixmap.transformed(QTransform().rotate(180));
    pixmap = rotatedPixmap;

    painter.begin(&pixmap);
    painter.setPen(QPen(oldBrushColor, oldBrushSize, Qt::SolidLine));

    update();
}

void MainWindow::createActions() {
    // Crée un menu "Fichier" dans la barre de menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    // Crée une toolbar
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->setStyleSheet("background-color: #00D6FF;");

    // Création d'une action "Nouveau"
    QAction *newAction = new QAction(QIcon::fromTheme("document-new", QIcon(":/images/new.png")), tr("&New"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAction);
    //ajout à la toolbar
    fileToolBar->addAction(newAction);

    // Action ouvrir une image
    QAction *openAction = new QAction(QIcon::fromTheme("document-open", QIcon(":/images/open.png")), tr("&Open"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAction);
    fileToolBar->addAction(openAction);

    // Action enregistrer une image
    QAction *saveAction = new QAction(QIcon::fromTheme("document-save", QIcon(":/images/save.png")), tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Open);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAction);
    fileToolBar->addAction(saveAction);

    // Action enregistrer sous une image
    QAction *saveAsAction = new QAction(QIcon::fromTheme("document-save-as"), tr("&Save as"), this);
    saveAsAction->setShortcuts(QKeySequence::Open);
//    saveAsAction->setStatusTip(tr("Save file"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);
    fileMenu->addAction(saveAsAction);
//    fileToolBar->addAction(saveAsAction);

    // Ajout d'une séparation entre les actions "Ouvrir" et "Quitter"
    fileMenu->addSeparator();

    // Création d'une action "Quitter"
    QAction *exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::quit);
    fileMenu->addAction(exitAction);

    // Créer un menu "Tools" dans la barre de menu
    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    // Créer une toolbar "Tools"
    QToolBar *toolsToolBar = addToolBar(tr("Tools"));
    toolsToolBar->setStyleSheet("background-color: orange;");

    // Action zoom in
    zoomInAction = new QAction(QIcon("./images/zoomIn.png"), tr("Zoom in"), this);
    zoomInAction->setShortcut(tr("Ctrl++"));
    zoomInAction->setStatusTip(tr("Zoom in"));
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    toolsMenu->addAction(zoomInAction);
    toolsToolBar->addAction(zoomInAction);

    // Action zoom out
    zoomOutAction = new QAction(QIcon("./images/zoomOut.png"), tr("Zoom out"), this);
    zoomOutAction->setShortcut(tr("Ctrl+-"));
    zoomOutAction->setStatusTip(tr("Zoom out"));
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    toolsMenu->addAction(zoomOutAction);
    toolsToolBar->addAction(zoomOutAction);

    // Action rectangle de sélection
    rectangleSelectAction = new QAction(QIcon("./images/rectangleSelect.png"), tr("Rectangle select"), this);
    rectangleSelectAction->setShortcut(QKeySequence::New);
    rectangleSelectAction->setStatusTip(tr("Rectangle select"));
    rectangleSelectAction->setCheckable(true);
    connect(rectangleSelectAction, &QAction::toggled, this, &MainWindow::rectangleSelect);
    toolsMenu->addAction(rectangleSelectAction);
    toolsToolBar->addAction(rectangleSelectAction);

    // Action paint bucket
    paintBucketAction = new QAction(QIcon("./images/paintBucket.png"), tr("Paint Bucket"), this);
    paintBucketAction->setShortcut(QKeySequence::New);
    paintBucketAction->setStatusTip(tr("Paint Bucket"));
    paintBucketAction->setCheckable(true);
    connect(pinceauAction, &QAction::toggled, this, &MainWindow::paintBucket);
    toolsMenu->addAction(paintBucketAction);
    toolsToolBar->addAction(paintBucketAction);

    // Action pinceau
    pinceauAction = new QAction(QIcon("./images/pinceau.png"), tr("Pinceau"), this);
    pinceauAction->setShortcut(QKeySequence::New);
    pinceauAction->setStatusTip(tr("Pinceau"));
    pinceauAction->setCheckable(true);
    connect(pinceauAction, &QAction::toggled, this, &MainWindow::pinceau);
    toolsMenu->addAction(pinceauAction);
    toolsToolBar->addAction(pinceauAction);

    // Action droite
    droiteAction = new QAction(QIcon("./images/droite.png"), tr("Droite"), this);
    droiteAction->setShortcut(QKeySequence::New);
    droiteAction->setStatusTip(tr("Droite"));
    droiteAction->setCheckable(true);
    connect(droiteAction, &QAction::toggled, this, &MainWindow::droite);
    toolsMenu->addAction(droiteAction);
    toolsToolBar->addAction(droiteAction);

    // Action choisir une forme (cercle/trait/rectangle)
    formAction = new QAction(QIcon("./images/form.png"),tr("&Choose Form"), this);
    formAction->setShortcut(QKeySequence::New);
    formAction->setStatusTip(tr("Choose a form"));
    formAction->setCheckable(true);
    connect(formAction, &QAction::triggered, this, &MainWindow::chooseForm);
    toolsMenu->addAction(formAction);
    toolsToolBar->addAction(formAction);













    // Créer un menu "Brush" dans la barre de menu
    QMenu *brushMenu = menuBar()->addMenu(tr("&Brush"));
    // Créer une toolbar "Brush"
    QToolBar *brushToolBar = addToolBar(tr("Brush"));
    brushToolBar->setStyleSheet("background-color: #9A9A9A;");

    // Action choisir la couleur de la brush
    QAction *colorAction = new QAction(QIcon::fromTheme("color-picker", QIcon(":/images/color.png")), tr("Choose Color"), this);
    colorAction->setShortcut(QKeySequence::New);
    colorAction->setStatusTip(tr("Choose a color for the brush"));
    connect(colorAction, &QAction::triggered, this, &MainWindow::chooseBrushColor);
    brushMenu->addAction(colorAction);
    brushToolBar->addAction(colorAction);

    // Action choisir la taille de la brush
    QAction *sizeAction = new QAction(QIcon("./images/size.png"),tr("&Choose Size"), this);
    sizeAction->setShortcut(QKeySequence::New);
    sizeAction->setStatusTip(tr("Choose a size for the brush"));
    connect(sizeAction, &QAction::triggered, this, &MainWindow::chooseBrushSize);
    brushMenu->addAction(sizeAction);
    brushToolBar->addAction(sizeAction);

    // Créer un menu "Affichage" dans la barre de menu
    QMenu *displayMenu = menuBar()->addMenu(tr("&Display"));

    // Créer une toolbar "Display"
    QToolBar *displayToolBar = addToolBar(tr("Display"));
    displayToolBar->setStyleSheet("background-color: yellow;");

    // Action afficher une grille des pixels
    pixelGridAction = new QAction(QIcon("./images/pixelGrid.png"), tr("Pixel grid"), this);
    pixelGridAction->setShortcut(QKeySequence::New);
    pixelGridAction->setStatusTip(tr("Pixel grid"));
    pixelGridAction->setCheckable(true);
    connect(pixelGridAction, &QAction::toggled, this, &MainWindow::pixelGrid);
    displayMenu->addAction(pixelGridAction);
    displayToolBar->addAction(pixelGridAction);

    // Créer un menu "Image" dans la barre de menu
    QMenu *imageMenu = menuBar()->addMenu(tr("&Image"));

    // Action redimensionner l'image
    QAction *resizeImageAction = new QAction(QIcon("./images/resize.png"), tr("Resize image"), this);
    resizeImageAction->setShortcut(QKeySequence::New);
    resizeImageAction->setStatusTip(tr("Resize the image"));
    connect(resizeImageAction, &QAction::triggered, this, &MainWindow::resizeImage);
    imageMenu->addAction(resizeImageAction);

    // Action modifier la taille de la zone de dessin
    QAction *resizeCanvasAction = new QAction(QIcon("./images/resizeCanvas.png"), tr("Resize canvas"), this);
    resizeCanvasAction->setShortcut(QKeySequence::New);
    resizeCanvasAction->setStatusTip(tr("Resize the canvas"));
    connect(resizeCanvasAction, &QAction::triggered, this, &MainWindow::resizeCanvas);
    imageMenu->addAction(resizeCanvasAction);

    // Action retourner horizontalement le dessin
    QAction *flipHorizontallyAction = new QAction(QIcon("./images/flipHorizontally.png"), tr("Flip horizontally"), this);
    flipHorizontallyAction->setShortcut(QKeySequence::New);
    flipHorizontallyAction->setStatusTip(tr("Flip horizontally the image"));
    connect(flipHorizontallyAction, &QAction::triggered, this, &MainWindow::flipHorizontally);
    imageMenu->addAction(flipHorizontallyAction);

    // Action retourner verticalement le dessin
    QAction *flipVerticallyAction = new QAction(QIcon("./images/flipVertically.png"), tr("Flip vertically"), this);
    flipVerticallyAction->setShortcut(QKeySequence::New);
    flipVerticallyAction->setStatusTip(tr("Flip Vertically the image"));
    connect(flipVerticallyAction, &QAction::triggered, this, &MainWindow::flipVertically);
    imageMenu->addAction(flipVerticallyAction);

    // Action pivoter de 90° le dessin vers la droite
    QAction *rotateRightAction = new QAction(QIcon("./images/rotateRight.png"), tr("Rotate 90° to the right"), this);
    rotateRightAction->setShortcut(QKeySequence::New);
    rotateRightAction->setStatusTip(tr("Rotate the image 90° to the right"));
    connect(rotateRightAction, &QAction::triggered, this, &MainWindow::rotateRight);
    imageMenu->addAction(rotateRightAction);

    // Action pivoter de 90° le dessin vers la gauche
    QAction *rotateLeftAction = new QAction(QIcon("./images/rotateLeft.png"), tr("Rotate 90° to the left"), this);
    rotateLeftAction->setShortcut(QKeySequence::New);
    rotateLeftAction->setStatusTip(tr("Rotate the image 90° to the left"));
    connect(rotateLeftAction, &QAction::triggered, this, &MainWindow::rotateLeft);
    imageMenu->addAction(rotateLeftAction);

    // Action pivoter de 180° le dessin
    QAction *rotateBehindAction = new QAction(QIcon("./images/rotateBehind.png"), tr("Rotate 180°"), this);
    rotateBehindAction->setShortcut(QKeySequence::New);
    rotateBehindAction->setStatusTip(tr("Rotate the image 180°"));
    connect(rotateBehindAction, &QAction::triggered, this, &MainWindow::rotateBehind);
    imageMenu->addAction(rotateBehindAction);

//    A FAIRE : COMME POUR RESIZE CANVAS ENREGISTRER PINCEAU ET COULEUR POUR OPEN d'images
//    A FAIRE : brush size : se rappeller de la taille quand on veut la changer car là ca remet a 1 la selection
//    ??????? : quand on change de couleur, le pinceau devient des cubes ???
//    A FAIRE : resizecanva : 1 boite de dialog
//    A FAIRE : setStatusTip marche pas

    // Menu affichage :
    // une règle des pixels sur les cotés gauche et haut
    // grille de pixels

    // Menu Outils :
    // rectangle de selection
    // déplacer les pixels sélectionnés
    // selctionner au lasso
    // déplacer la sélection
    // baguette magique
    // pot de peinture
    // texte
    // formes

    // Menu calque

    // Menu effet
    pinceauAction->setChecked(true);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Enregistre la position actuelle de la souris
        lastPoint = startPoint = event->pos();
    }
    if (droiteAction->isChecked()) {
        if (event->button() == Qt::LeftButton) {
            // Capturez la position de départ du point a
            startPoint = event->pos();
            // Créez une pixmap temporaire pour dessiner la droite en temps réel
            previewPixmap = pixmap;
        }
    }

    if (isSelectingRect) {
        // Commencer la sélection de rectangle à partir du point d'origine
        selectionRect.setTopLeft(event->pos());
        selectionRect.setWidth(0);
        selectionRect.setHeight(0);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (pinceauAction->isChecked()) {
            // Dessine une ligne entre la dernière position de la souris et la nouvelle position
            painter.drawLine(lastPoint, event->pos());
        }
        if (droiteAction->isChecked()) {
            if (event->buttons() & Qt::LeftButton) {
                // Pixmap temporaire sinon plein de droites se créent
                QPainter painter(&previewPixmap);
                painter.drawLine(startPoint, event->pos());
                update();
            }
        }
        // Enregistre la nouvelle position de la souris comme la dernière position
        lastPoint = event->pos();

        update();
    }

    if (isSelectingRect) {
        // Mettre à jour la taille de la sélection de rectangle en fonction de la position actuelle de la souris
        selectionRect.setBottomRight(event->pos());
        update(); // Mettre à jour l'affichage pour dessiner la sélection de rectangle
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (droiteAction->isChecked()) {
        if (event->button() == Qt::LeftButton) {
            // Droite finale
            QPainter painter(&pixmap);
            painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(startPoint, event->pos());
            update();
            // Réinitialiser la pixmap temporaire
            previewPixmap = QPixmap();
        }
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    // pinceau par défaut
    if (!rectangleSelectAction->isChecked() && !pinceauAction->isChecked() && !droiteAction->isChecked()) {
        pinceauAction->setChecked(true);
    }
    // Dessine le pixmap sur la fenêtre
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);

    if (isSelectingRect) {
        // Dessiner la sélection de rectangle en pointillés
        QPen pen(Qt::DashLine);
        pen.setWidth(2);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(selectionRect);
    }
}