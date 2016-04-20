#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QQueue>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);

signals:
    void newWord(QString word);
    void newLevel(int level);
    void failed();
    void victory();

public slots:
    void newLetterTyped(char letter);

private:
    QString currentWord;
    int currentWordIndex;
    QQueue<QString> words;
};

#endif // GAME_H
