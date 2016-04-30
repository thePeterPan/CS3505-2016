#include "mysqlwrapper.h"

MySQLWrapper::MySQLWrapper(QObject *parent)
    : QObject(parent), hostPath(""), port(3306),
      username(""), password(""), databaseName("")
{

}

MySQLWrapper::~MySQLWrapper()
{
    this->close();
}

void MySQLWrapper::setHost(QString _hostPath, int _port)
{
    hostPath = _hostPath;
    port = _port;
}

void MySQLWrapper::setUsername(QString _username)
{
    username = _username;
}

void MySQLWrapper::setPassword(QString _password)
{
    password = _password;
}

void MySQLWrapper::setDatabaseName(QString _name)
{
    databaseName = _name;
}

bool MySQLWrapper::open()
{
    if (hostPath == "" || username == "" || password == "")
        return false;

    try
    {
        // Create a connection:
        driver = get_driver_instance(); // Not threadsafe
        std::string completeHost = hostPath.toStdString() + ":"  + std::to_string(port);
        connection = driver->connect(completeHost, username.toStdString(), password.toStdString());
        connection->setSchema(databaseName.toStdString());
    }
    catch (sql::SQLException &e) {
//      qDebug() << "# ERR: SQLException in " << __FILE__;
//      qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__ ;
      qDebug() << "# ERR: " << e.what();
      qDebug() << " (MySQL error code: " << QString::number(e.getErrorCode());
//      qDebug() << ", SQLState: " << QObject::tr(e.getSQLState()) << " )";
        return false;
    }
}

bool MySQLWrapper::close()
{
    // Do not explicitly free driver, the connector object. Connector/C++ takes care of freeing that.
    resultSet->close();
    statement->close();
    connection->close();
    driver->threadEnd();

    delete resultSet;
    delete statement;
    delete connection;
    return true;
}

/**
 * @brief loginAvailable
 * @param login
 * @return True if no user has username login, false otherwise
 */
bool MySQLWrapper::usernameAvailable(QString login)
{
    QString sql = "SELECT count(*) AS count FROM user WHERE login = ?";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1, login.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        int count = resultSet->getInt("count");
        if(count != 0)
            return false;
    }
    return true;
}

/**
 * @brief loginCorrect
 * @param login
 * @param password
 * @return True if login and password combination are correct
 */
bool MySQLWrapper::loginCorrect(QString login, QString password)
{
    QString sql = "SELECT count(*) AS count FROM user WHERE login = ? AND password = ?";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    statement->setString(2,password.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        int count = resultSet->getInt("count");
        if(count == 1)
            return true;
    }
    return false;
}

/**
 * @brief isTeacher
 * @param login
 * @return True if user with username login is a teacher
 */
bool MySQLWrapper::isTeacher(QString login)
{
    QString sql = "SELECT is_teacher FROM user WHERE login = ?";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        return resultSet->getBoolean("is_teacher");
    }
    return false;
}

/**
 * @brief insertNewStudent Inserts new student into database
 * @param login
 * @param first
 * @param last
 * @param password
 * @param teacher
 */
void MySQLWrapper::insertNewStudent(QString login, QString first, QString last, QString password, QString teacher)
{
    QString sql = "INSERT INTO user (login, first, last, password, is_teacher) VALUES (?, ?, ?, ?, ?)";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    statement->setString(2,first.toStdString());
    statement->setString(3,last.toStdString());
    statement->setString(4,password.toStdString());
    statement->setBoolean(5,false);

    statement->executeUpdate();

    sql = "INSERT INTO class (student,teacher) VALUES (?, ?)";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    statement->setString(2,teacher.toStdString());

    statement->executeUpdate();

    sql = "INSERT INTO current_level (login,level,highscore) VALUES (?,?,?)";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    statement->setInt(2,1);
    statement->setInt(3,0);

    statement->executeUpdate();
}

/**
 * @brief insertNewTeacher Inserts new teacher into database
 * @param login
 * @param first
 * @param last
 * @param password
 */
void MySQLWrapper::insertNewTeacher(QString login, QString first, QString last, QString password)
{
    QString sql = "INSERT INTO user (login, first, last, password, is_teacher) VALUES (?, ?, ?, ?, ?)";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    statement->setString(2,first.toStdString());
    statement->setString(3,last.toStdString());
    statement->setString(4,password.toStdString());
    statement->setBoolean(5,true);

    statement->executeUpdate();
}

/**
 * @brief getTeacherWordsByLevel
 * @param teacher
 * @param level
 * @return QList of words for teacher at given level
 */
QList<QString> MySQLWrapper::getTeacherWordsByLevel(QString teacher, int level)
{
    QString sql = "SELECT word FROM words WHERE teacher = ? AND level = ?;";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,teacher.toStdString());
    statement->setInt(2,level);
    resultSet = statement->executeQuery();
    QList<QString> list;
    while(resultSet->next())
    {
        list.push_back(QString::fromUtf8(resultSet->getString("word").asStdString().c_str()));
    }
    return list;
}

/**
 * @brief getUserCurrentLevel Gets user's (student) current level
 * @param login
 * @return -1 if user is not a student or user does not exist
 */
int MySQLWrapper::getUserCurrentLevel(QString login)
{
    QString sql = "SELECT level FROM current_level WHERE login = ?";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        return resultSet->getInt("level");
    }
    return -1;
}

/**
 * @brief updateUserLevel Updates user's current level
 * @param login
 * @param level
 */
void MySQLWrapper::updateUserLevelAndScore(QString login, int level, int score)
{
    updateUserScore(login,score);
    updateUserLevel(login,level);
}

/**
 * @brief updateUserScore Updates user's high score in database.
 * @param login
 * @param score
 */
void MySQLWrapper::updateUserScore(QString login, int score)
{
    int currentScore = getUserScore(login);
    if(score > currentScore)
    {
        QString sql = "INSERT INTO current_level (login,highscore) VALUES(?,?) on duplicate key update login=?, highscore=?";
        statement = connection->prepareStatement(sql.toStdString());
        statement->setString(1,login.toStdString());
        statement->setInt(2,score);
        statement->setString(3,login.toStdString());
        statement->setInt(4,score);
        statement->executeUpdate();
    }
}
/**
 * @brief MySQLWrapper::updateUserLevel Updates the user's level
 * @param login
 * @param level
 */
void MySQLWrapper::updateUserLevel(QString login, int level)
{
    int currentLevel = getUserCurrentLevel(login);
    if(level > currentLevel)
    {
        QString sql = "INSERT INTO current_level (login,level) VALUES(?,?) on duplicate key update login=?, level =?;";
        statement = connection->prepareStatement(sql.toStdString());
        statement->setString(1,login.toStdString());
        statement->setInt(2,level);
        statement->setString(3,login.toStdString());
        statement->setInt(4,level);
        statement->executeUpdate();
    }
    currentLevel = getUserCurrentLevel(login);
    qDebug() << login << " " << currentLevel;
}

/**
 * @brief getUserScore
 * @param login
 * @return User's current high score
 */
int MySQLWrapper::getUserScore(QString login)
{
    QString sql = "SELECT highscore FROM current_level WHERE login = ?";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        return resultSet->getInt("highscore");
    }
    return -1;
}

/**
 * @brief addTeacherWordsByLevel Adds list of words to teacher's list at given level
 * @param words
 * @param login
 * @param level
 */
void MySQLWrapper::addTeacherWordsByLevel(QList<QString> words, QString teacher, int level)
{
    if(isTeacher(teacher))
    {
        foreach(QString word, words)
        {
            QString sql = "INSERT IGNORE INTO words (teacher, level, word) VALUES (?, ?, ?)";
            statement = connection->prepareStatement(sql.toStdString());
            statement->setString(1, teacher.toStdString());
            statement->setInt(2,level);
            statement->setString(3,word.toStdString());
            statement->executeUpdate();
        }
    }
}

/**
 * @brief MySQLWrapper::addNewTeacherWordByLevel Adds individual word to db by teacher and level
 * @param word
 * @param login
 * @param level
 */
void MySQLWrapper::addNewTeacherWordByLevel(QString word, QString login, int level)
{
    if(isTeacher(login))
    {
        QString sql = "INSERT IGNORE INTO words (teacher, level, word) VALUES (?, ?, ?)";
        statement = connection->prepareStatement(sql.toStdString());
        statement->setString(1, login.toStdString());
        statement->setInt(2,level);
        statement->setString(3,word.toStdString());
        statement->executeUpdate();
    }
}

/**
 * @brief MySQLWrapper::deleteTeacherWordsByLevel Deletes all words with that teacher and level
 * @param login
 * @param level
 */
void MySQLWrapper::deleteTeacherWordsByLevel(QString login, int level)
{
    if(isTeacher(login))
    {
        QList<QString> wordsToDelete = getTeacherWordsByLevel(login, level);
        foreach(QString word, wordsToDelete)
        {
            QString sql = "DELETE FROM words WHERE teacher=? AND level=? AND word=?";
            statement = connection->prepareStatement(sql.toStdString());
            statement->setString(1, login.toStdString());
            statement->setInt(2, level);
            statement->setString(3, word.toStdString());
            statement->executeUpdate();
        }
    }
}

/**
 * @brief MySQLWrapper::deleteTeacherWordByLevel deletes individual word by the teacher, word and level
 * @param word
 * @param login
 * @param level
 */
void MySQLWrapper::deleteTeacherWordByLevel(QString word, QString login, int level)
{
    if(isTeacher(login))
    {
        QString sql = "DELETE FROM words WHERE teacher=? AND level=? AND word=?";
        statement = connection->prepareStatement(sql.toStdString());
        statement->setString(1, login.toStdString());
        statement->setInt(2, level);
        statement->setString(3, word.toStdString());
        statement->executeUpdate();
    }
}

/**
 * @brief MySQLWrapper::getTeacher
 * @param student
 * @return Name of student's teacher. Empty string if non-existent student
 */
QString MySQLWrapper::getTeacher(QString student)
{
    QString sql = "SELECT teacher FROM class WHERE student = ?;";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,student.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        return (QString::fromUtf8(resultSet->getString("teacher").asStdString().c_str()));
    }
    return "";
}

/**
 * @brief Get a list of students that belong to the teacher.
 * @param teacher
 * @return
 */
QList<QString> MySQLWrapper::getStudents(QString teacher)
{
    QString sql = "SELECT student FROM class WHERE teacher = ?;";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,teacher.toStdString());
    QList<QString> result;
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        result.push_back(QString::fromUtf8(resultSet->getString("student").asStdString().c_str()));
    }
    return result;
}


/**
 * @brief MySQLWrapper::getTeacherStats
 * @param teacher
 * @return QList of QList<QString> with stats
 * Each list is formatted as follows:
 * Student Name (string)
 * Student Level (as a string)
 * Student High Score (as a string)
 */
QList<QList<QString>> MySQLWrapper::getTeacherStats(QString teacher)
{
    QString sql = "SELECT c.student, l.level, l.highscore FROM class c, current_level l WHERE c.student = l.login AND c.teacher = ?;";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,teacher.toStdString());
    QList<QList<QString>> result;
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        QList<QString> user;
        user.push_back(QString::fromUtf8(resultSet->getString("student").asStdString().c_str()));
        user.push_back(QString::number(resultSet->getInt("level")));
        user.push_back(QString::number(resultSet->getInt("highscore")));
        result.push_back(user);
    }
    return result;
}

/**
 * @brief Increases the user level by one.
 * @param login
 */
void MySQLWrapper::incrementUserLevel(QString login)
{
    int level = getUserCurrentLevel(login);
    level++;
    updateUserLevel(login,level);
}

QList<QString> MySQLWrapper::getFirstAndLastName(QString login)
{
    QString sql = "SELECT first, last FROM user WHERE login = ?;";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1, login.toStdString());
    QList<QString> result;
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        result.push_back(QString::fromUtf8(resultSet->getString("first").asStdString().c_str()));
        result.push_back(QString::fromUtf8(resultSet->getString("last").asStdString().c_str()));
    }

    return result;
}
