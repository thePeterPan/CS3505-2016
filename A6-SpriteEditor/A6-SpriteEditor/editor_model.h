#ifndef EDITOR_MODEL_H
#define EDITOR_MODEL_H

#include <QObject>
#include <QWidget>

#include <QColor>

#include "sprite.h"

class editor_model : public QObject
{
    Q_OBJECT
public:
    explicit editor_model(QObject *parent = 0);

signals:

public slots:
};

#endif // EDITOR_MODEL_H
