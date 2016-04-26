#ifndef MYSQLWRAPPER_H
#define MYSQLWRAPPER_H

#include <QObject>
#include <QDebug>
#include <QList>
//MySQL Connector libraries
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

//Name=neverland-db
//Server=us-cdbr-azure-west-c.cloudapp.net
//Login=b485a4f4f7fcea
//Password=fd0282b9

//Database Schema: user(login,first,last,password,is_teacher)
//login is PK
//current_level(login,level)
//login is PK
//class(student,teacher)
//student is PK
//list(level,teacher)
//level,teacher is superkey
//words(teacher,level,word)
//teacher,level,word is superkey

class MySQLWrapper : public QObject
{
    Q_OBJECT
public:
    explicit MySQLWrapper(QObject *parent = 0);
    ~MySQLWrapper();
    void setHost(QString _hostPath, int _port = 3306);
    void setUsername(QString _username);
    void setPassword(QString _password);
    void setDatabaseName(QString _name);

    /**
     * @brief getTeacherWordsByLevel
     * @param teacher
     * @param level
     * @return QList of words for teacher at given level
     */
    QList<QString> getTeacherWordsByLevel(QString teacher, int level);
    /**
     * @brief loginAvailable
     * @param login
     * @return True if no user has username login, false otherwise
     */
    bool loginAvailable(QString login);
    /**
     * @brief loginCorrect
     * @param login
     * @param password
     * @return True if login and password combination are correct
     */
    bool loginCorrect(QString login, QString password);
    /**
     * @brief isTeacher
     * @param login
     * @return True if user with username login is a teacher
     */
    bool isTeacher(QString login);

    /**
     * @brief insertNewStudent Inserts new student into database
     * @param login
     * @param first
     * @param last
     * @param password
     * @param teacher
     */
    void insertNewStudent(QString login, QString first, QString last, QString password, QString teacher);
    /**
     * @brief insertNewTeacher Inserts new teacher into database
     * @param login
     * @param first
     * @param last
     * @param password
     */
    void insertNewTeacher(QString login, QString first, QString last, QString password);
    /**
     * @brief getUserCurrentLevel Gets user's (student) current level
     * @param login
     * @return -1 if user is not a student or user does not exist
     */
    int getUserCurrentLevel(QString login);

    /**
     * @brief updateUserScore Updates user's high score in database.
     * @param login
     * @param score
     */
    void updateUserScore(QString login, int score);
    /**
     * @brief getUserScore
     * @param login
     * @return User's current high score
     */
    int getUserScore(QString login);
    /**
     * @brief updateUserLevel Updates user's current level
     * @param login
     * @param level
     */
    void updateUserLevel(QString login, int level);
    /**
     * @brief addTeacherWordsByLevel Adds list of words to teacher's list at given level
     * @param words
     * @param login
     * @param level
     */
    void addTeacherWordsByLevel(QList<QString> words, QString login, int level);

    bool open();
    bool close();

signals:

public slots:


private:
    QString hostPath;
    int port;
    QString username;
    QString password;
    QString databaseName;

    // Do these need to be deleted?
    sql::Driver *driver;
    sql::Connection *connection;
    sql::PreparedStatement *statement;
    sql::ResultSet *resultSet;
};

#endif // MYSQLWRAPPER_H
