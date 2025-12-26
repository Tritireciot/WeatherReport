#include <QtWidgets>
#include<QDialog>
#include <QSettings>
#include "MainWindow.h"
#include "AuthDialog.h"

static QString loadQss(const QString& resourcePath) {
    QFile f(resourcePath);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return {};
    return QString::fromUtf8(f.readAll());
}

void MainWindow::applyTheme(const QString& themeName) {
    QString path;
    if (themeName == "dark") path = ":/themes/dark.qss";
    else path = ":/themes/light.qss";

    const QString qss = loadQss(path);
    qApp->setStyleSheet(qss);

    QSettings s;
    s.setValue("ui/theme", themeName);
}

void MainWindow::createMenuBar(){
    QMenu* menuFile = new QMenu("Файл");

    menuFile->addAction(
        "О Программе",
        this,
        [this]{
            QMessageBox::about(this, "О Программе", "Монитор Погоды\nВерсия: 0.0.0\nАвтор: Вальчук К.В.\n");
        }
    );

    menuFile->addAction(
        "Выход",
        this,
        SLOT(close()),
        QKeySequence::Quit
    );

    QMenu* menuSettings = new QMenu("Настройка");

    menuSettings->addAction(
        "Авторизация",
        this,
        SLOT(authDialogSlot())
    );

    QMenu* menuTheme = new QMenu("Тема");

    QAction* lightTheme = new QAction("Светлая", this);
    lightTheme->setCheckable(true);
    connect(lightTheme, &QAction::triggered, this, [this] {
            applyTheme("light");
    });
    QAction* darkTheme = new QAction("Темная", this);
    darkTheme->setCheckable(true);
    connect(darkTheme, &QAction::triggered, this, [this] {
            applyTheme("dark");
    });

    QActionGroup* themeGroup = new QActionGroup(this);
    themeGroup->addAction(lightTheme);
    themeGroup->addAction(darkTheme);
    lightTheme->setChecked(true);

    QSettings s;
    const QString theme = s.value("ui/theme", "light").toString();
    if (theme == "dark") darkTheme->setChecked(true);
    else lightTheme->setChecked(true);

    applyTheme(theme);


    menuTheme->addAction(lightTheme);
    menuTheme->addAction(darkTheme);
    menuSettings->addMenu(menuTheme);

    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuSettings);

    loginLabel = new QLabel;
    lampIndicator = new LampIndicator;
    statusBar()->addPermanentWidget(loginLabel);
    statusBar()->addPermanentWidget(lampIndicator);

    weatherRequester = new WeatherRequester(this, lampIndicator);
    setCentralWidget(weatherRequester);
}

MainWindow::MainWindow(QWidget* pwgt): QMainWindow(pwgt){
    setWindowTitle("Weather Report");
    resize(900, 600);
    createMenuBar();
}

void MainWindow::authDialogSlot(){
    AuthDialog* pAuthDialog = new AuthDialog;
    if (pAuthDialog->exec() == QDialog::Accepted){
        loginLabel->setText(pAuthDialog->getLogin());
        weatherRequester->checkAuth(pAuthDialog->getPassword());
    }
    delete pAuthDialog;
}