#pragma once

#include <QtWidgets>
#include "LampIndicator.h"
#include "WeatherRequester.h"

class MainWindow: public QMainWindow {
    Q_OBJECT

    private:
        QLabel* loginLabel;
        LampIndicator*  lampIndicator;
        WeatherRequester* weatherRequester;
        void createMenuBar();
        void applyTheme(const QString& themeName);

    public:
        MainWindow(QWidget* pwgt = nullptr);
    
    public slots:
        void authDialogSlot();
    
};