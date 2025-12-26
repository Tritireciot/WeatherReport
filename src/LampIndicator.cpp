#include "LampIndicator.h"
#include <QPainter>
#include <QPaintEvent>

LampIndicator::LampIndicator(QWidget* pwgt): QWidget(pwgt){
    setFixedSize(28, 28);
    state_ = State::DISABLED;
}

LampIndicator::State LampIndicator::state() const {
    return state_;
}

void LampIndicator::setState(bool success){
    state_ = success ? State::ON : State::OFF;
    update();
}

void LampIndicator::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(QColor(60, 60, 60), 1));

    QRectF r = rect().adjusted(2, 2, -2, -2);

    QColor fill;
    switch (state_) {
        case State::OFF:
            fill = RED;  
            break;
        case State::ON: 
            fill = GREEN; 
            break;
        case State::DISABLED:  
            fill = GRAY; 
            break;
    }

    p.setBrush(fill);
    p.drawEllipse(r);
}

