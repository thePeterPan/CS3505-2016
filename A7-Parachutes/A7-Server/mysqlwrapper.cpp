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
    connection->close();
    resultSet->close();
    statement->close();

    delete resultSet;
    delete statement;
    delete connection;
}


bool MySQLWrapper::loginAvailable(QString login)
{
    QString sql = "select count(*) as count from user where login = ?";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        int count = resultSet->getInt("count");
        if(count != 0)
            return false;
    }
    return true;
}

bool MySQLWrapper::isTeacher(QString login)
{
    QString sql = "select is_teacher from user where login = ?";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    resultSet = statement->executeQuery();
    while(resultSet->next())
    {
        return resultSet->getBoolean("is_teacher");
    }
    return false;
}

void MySQLWrapper::insertNewStudent(QString login, QString first, QString last, QString password, QString teacher)
{
    QString sql = "insert into user (login, first, last, password, is_teacher) values (?, ?, ?, ?, ?)";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    statement->setString(2,first.toStdString());
    statement->setString(3,last.toStdString());
    statement->setString(4,password.toStdString());
    statement->setBoolean(5,false);

    statement->executeUpdate();

    sql = "insert into class (student,teacher) values (?, ?)";
    statement = connection->prepareStatement(sql.toStdString());
    statement->setString(1,login.toStdString());
    statement->setString(2,teacher.toStdString());

    statement->executeUpdate();


}

void MySQLWrapper::insertNewTeacher(QString login, QString first, QString last, QString password)
{

}
