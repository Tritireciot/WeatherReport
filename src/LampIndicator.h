#pragma once
#include <QtWidgets>

const QColor RED = QColor(231, 76, 60);
const QColor GREEN = QColor(46, 204, 113);
const QColor GRAY = QColor(160, 160, 160);

class LampIndicator: public QWidget {
    Q_OBJECT

    public:
        enum class State { ON, OFF, DISABLED };

        LampIndicator(QWidget* pwgt = nullptr);

        State state() const;

        void setState(bool success);
    
    private:
        State state_;

    protected:
        void paintEvent(QPaintEvent*) override;
    
};

