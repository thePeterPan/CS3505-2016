#include "gamelogic.h"

GameLogic::GameLogic(QObject *parent, int windowWidth, int windowHeight, float scale) :
    QObject(parent), windowWidth(windowWidth), windowHeight(windowHeight), SCALE(scale)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(updateTimer()));
    sprites = QList<TemporarySprite>();

    //assuming that there will never be more than 20 letters in a word.
    for(int i = 0; i < 20; i++)
    {
        sprites.append(TemporarySprite());
    }
    setUpBox2D();
    SCALE = 100.0f;
    xScale = SCALE;
    yScale = SCALE;
    currentLevel = 1;
    previousWord = "";
    fromFile = false;
}

GameLogic::~GameLogic()
{
    delete World;
    delete timer;
}

// ===== Public Methods ===== //


int GameLogic::getCurrentLevel()
{
    return currentLevel;
}

void GameLogic::sendScoreToDB()
{
    int newLevel = (this->startingLevel > this->currentLevel) ? this->startingLevel : currentLevel;
    int newScore = (this->highScore > this->score) ? this->highScore : this->score;
    emit sendScore(username, newLevel, newScore);
}

void GameLogic::addWordsToQueue(int level)
{
    words.clear();

    if(!fromFile)
    {
        words.append(fromDB);
    }
    else
    {
        int numWords = wordsList.size();
        int start = (level - 1) * 10;
        if(start >= numWords)
        {
            timer->stop();
            emit levelCompleted(currentLevel - 1, score);
            return;
        }
        int end = ((start + 10) > numWords) ? numWords : start + 10;
        for(int i = start; i < end; i++)
        {
            words.append(wordsList[i]);
        }
        //wordsList.clear();
    }

    if(words.size()>0){
        currentWord = words.first();
        currentWordIndex = 0;
        words.removeFirst();
        qDebug() << currentWord;

        addWordToWorld();
    }
    else
    {
        timer->stop();
        if(!fromFile)
            sendScoreToDB();
        emit levelCompleted(currentLevel - 1, score);
        return;
    }

    /*
     *
     * Have a signal that tells this that it is loading from file.
     * Have file set up so that each level is divided (or 15 words, whatever is first)
     * Here, it either uses the test words, words from file, or, hopefully, words from a db
     *
     * */
}

void GameLogic::paintWorld(QPainter *painter)
{
    World->Step(1.0f/60.0f, 8, 3);

    for(int i = 0; i < currentWord.length(); i++)
    {
        (currentWordIndex > i) ? painter->setPen(Qt::red) : painter->setPen(Qt::cyan);

        sprites[i].draw(painter, xScale, yScale, windowHeight2);
    }
}

// ===== Private Methods ===== //


// ---------- BOX2D ---------- //


void GameLogic::setUpBox2D()
{
    /** Prepare the world */
    b2Vec2 gravity = b2Vec2(0.0f, -9.8f);

    World = new b2World(gravity);

    CreateGround(0.0f, 0.0f,windowWidth * 2, 1.0f);
    CreateGround(0.0f,0.0f,1.0f,windowHeight * 2);
    CreateGround(800.0f,0.0f,1.0f,windowHeight * 2);
    CreateGround(0.0f,windowHeight,windowWidth * 2,1.0f);

    createRoughGround();
}


/**
 * @brief gameLogic::CreateGround
 * @param x
 * @param y
 * @param width
 * @param height
 */
void GameLogic::CreateGround(float x, float y, float width, float height)
{

    b2BodyDef groundDef;
    groundDef.position.Set(x/SCALE, y/SCALE);
    //bodyDef.type = b2_staticBody; // Static by default
    b2Body* ground = World->CreateBody(&groundDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox((width/2.0f)/SCALE, (height/2.0f)/SCALE); // Creates a box shape. Divide your desired width and height by 2.
    ground->CreateFixture(&groundBox,10.0f); // Apply the fixture definition
}

/**
 * Creates random shapes for the ground
 * @brief gameLogic::createRoughGround
 */
void GameLogic::createRoughGround()
{
    float size = 5;
    for(float i = 0; i < size; i++)
    {
        b2BodyDef boxDef;
        //boxDef.type = b2_dynamicBody;
        boxDef.position.Set(i+ i * 0.1f, 0.21f);
        b2Body* box = World->CreateBody(&boxDef);

        b2PolygonShape shape;
        shape.SetAsBox(0.1f,0.1f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 150.0f;
        fixtureDef.friction = 0.05f;
        fixtureDef.restitution = 1.0f;
        box->CreateFixture(&fixtureDef);
    }
}

// ---------- Sprites ---------- //


void GameLogic::addWordToWorld()
{
    for(int i = 0; i < previousWord.length(); i++)
    {
        World->DestroyBody(sprites[i].getBody());
    }
    previousWord = currentWord;

    float itemWidth = 80.0f;
    int spacing = windowWidth / currentWord.length();
    for(int i = 0; i < currentWord.length(); i++)
    {
        sprites[i].setBody(CreateBox(""+currentWord[i],i*spacing, windowHeight-itemWidth/2 + (rand() % 30),itemWidth,itemWidth, 0.1f,1.0f));
        sprites[i].setLetter(""+currentWord[i]);
    }
    if(readyToPlay)
        startNewTimer();
}

/**
 * NOTE: Box2D can only reliably simulate objects with size dimensions less than 10m.
 * Therefore, a large scaling number is needed in order to scale down or up from pixel size.
 * @brief gameLogic::CreateBox
 * @param letter
 * @param x
 * @param y
 * @param width
 * @param height
 * @param friction
 * @param restitution
 * @param density
 */
b2Body * GameLogic::CreateBox(QString letter, float x, float y, float width, float height, float friction, float restitution, float density)
{
    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(x/SCALE, y/SCALE);
    b2Body* box = World->CreateBody(&boxDef);

    b2PolygonShape shape;
    shape.SetAsBox((width/2.0f)/SCALE,(height/2.0f)/SCALE);//2mx2m box
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    box->CreateFixture(&fixtureDef);

    return box;
}

// ---------- Game Play ---------- //

void GameLogic::scoreChanged(int score)
{
    emit updateScore(QString("Score: ").append(QString::number(score)));
}

void GameLogic::startNewTimer()
{
    //qDebug() << "starting timer";
    timerSeconds = timerFactor - currentLevel;
    timerSeconds = (timerSeconds > 3) ? timerSeconds : 3;
    QString timerText = "Time:";
    if(timerSeconds < 10)
        timerText.append("0");
    timerText.append(QString::number(timerSeconds));
    emit updateActionTimer(timerText);
    timer->start(1000);
}


// ===== SLOTS ===== //

// ---------- Start, Pause, Play ---------- //

void GameLogic::startGame()
{
    readyToPlay = true;

    // Give them some starting points, else they lose if they type
    // something wrong at the very beginning.
    score = 100;
    scoreChanged(score);

//    if(!fromFile)
//    {
//        emit requestWordList(currentLevel, teacher);
//    }
    addWordsToQueue(currentLevel);
    startNewTimer();
}

void GameLogic::pause()
{
    this->timer->stop();
    //qDebug() << "Pause!";
}

void GameLogic::unPause()
{
    this->timer->start(1000);
    //qDebug() << "Go again!";
}

// --------- Keyboard Input ---------- //

void GameLogic::newLetterTyped(QChar letter)
{
    if(letter == currentWord.at(currentWordIndex).toUpper())
    {
        //qDebug() << letter << " was correct";
        if(currentWordIndex == currentWord.length() - 1)
        {
            score += completeWordReward * timerSeconds;
            scoreChanged(score);
            if(words.isEmpty())
            {
                addWordsToQueue(++currentLevel);
                emit newLevel(currentLevel);
            }
            else
            {
                currentWord = words.first();
                currentWordIndex = 0;
                words.removeFirst();
                qDebug() << "new word: " << currentWord;
                addWordToWorld();

            }
            // If there is one word left, ask the DB for another list //
            if(words.size() == 1)
            {
                qDebug() << "Words requested for level: " << currentLevel + 1;
                emit requestWordList(currentLevel + 1, this->teacher);
            }
        }
        else
        {
            currentWordIndex++;
        }
    }
    else
    {
        if (score > 0) {
            score -= missTypePenalty;
            scoreChanged(score);
        }
        else
        {
            sendScoreToDB();
            emit gameOver(currentLevel - 1,score);
        }
        emit failed();
    }
    // If the new letter is incorrect || the position of the lowest sprite on GUI is bad:
    //      emit failed();
    // If that's the end of the word, but the QQueue is not empty:
    //      emit newWord on the next word
    // If that's the end of the word and the QQueue is empty;
    //      emit newLevel to update GUI and Database
    //      If any levels left:
    //          get next words from database
    //          send first word to gui
    //      otherwise
    //          you won, game over.
    // Otherwise,
    //      Word isn't over, do nothing and wait for next letter typed

}

// ---------- Timer ---------- //

void GameLogic::updateTimer()
{
    timerSeconds--;
    QString timerText = "Time:";
    if(timerSeconds < 10)
        timerText.append("0");
    timerText.append(QString::number(timerSeconds));
    emit updateActionTimer(timerText);
    if(timerSeconds <= 0)
    {
        timer->stop();
        emit failed();
        sendScoreToDB();
        emit gameOver(currentLevel - 1, score);
        emit requestWordList(currentLevel, this->teacher);
        qDebug() << "time's up!";
    }
}

// ----------   ---------- //


void GameLogic::addWordsFromFile(QStringList list)
{
    wordsList = list;
    fromFile = true;
}

void GameLogic::changeSize(int newWidth, int newHeight)
{
    windowHeight2 = newHeight;
    yScale = 100 * windowHeight2 / windowHeight;
    xScale = 100 * newWidth / windowWidth;
}


void GameLogic::receivedWordList(QList<QString> list)
{
    qDebug() << "List received from server: " << list;
    fromDB = list;
}


void GameLogic::receiveUserInfo(QString username, QString first, QString last, QString teacher, int level, int highScore)
{
    this->username = username;
    this->firstName = first;
    this->lastName = last;
    this->teacher = teacher;
    this->highScore = highScore;
    this->currentLevel = level;
    this->startingLevel = level;

    emit requestWordList(currentLevel, teacher);

}
