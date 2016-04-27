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

    delete resultSet;
    delete statement;
    delete connection;
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
        list.push_back(resultSet->getString("word"));
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

}

/**
 * @brief updateUserLevel Updates user's current level
 * @param login
 * @param level
 */
void MySQLWrapper::updateUserLevel(QString login, int level)
{

}

/**
 * @brief updateUserScore Updates user's high score in database.
 * @param login
 * @param score
 */
void MySQLWrapper::updateUserScore(QString login, int score)
{

}

/**
 * @brief getUserScore
 * @param login
 * @return User's current high score
 */
int MySQLWrapper::getUserScore(QString login)
{

}

/**
 * @brief addTeacherWordsByLevel Adds list of words to teacher's list at given level
 * @param words
 * @param login
 * @param level
 */
void MySQLWrapper::addTeacherWordsByLevel(QList<QString> words, QString login, int level)
{

}
