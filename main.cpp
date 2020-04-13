#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Task: public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ get_id WRITE set_id NOTIFY id_changed)
    Q_PROPERTY(QString title READ get_title WRITE set_title NOTIFY title_changed)
public:
    Task(QObject* parent, int id, QString title):
        QObject(parent),
        m_id(id),
        m_title(title)
    {

    }

    int get_id() {
        return m_id;
    }
    void set_id(int id) {
        m_id = id;
        emit id_changed();
    }
    QString get_title() const {
        return m_title;
    }
    void set_title(const QString title) {
        m_title = title;
    }
signals:
    void id_changed();
    void title_changed();
private:
    int m_id;
    QString m_title;
};


class Database {
public:
    void init_db() {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(":memory:");
        if (!m_db.open()) qFatal("Could not open database.");
        QSqlQuery query;
        query.exec("create table tasks (id integer primary key, task text)");
        qDebug() << "Table tasks was created.";

        query.exec("insert into tasks values (1, 'Crete tasks table')");
//        qDebug() << query.lastError().isValid();
        query.exec("insert into tasks values (2, 'Insert task into table')");
        query.exec("insert into tasks values (3, 'Query task')");
        query.exec("insert into tasks values (4, 'Print task')");
        qDebug() << "4 tasks inserted.";

//        query.exec("select * from tasks");
//        QVector<Task> tasks;
//        while (query.next()) {
//            int task_id = query.value(0).toInt();
//            QString task_title = query.value(1).toString();
//            qDebug() << task_id << task_title;
//            Task task(nullptr, task_id, task_title);
//            tasks.append(t);
//        }

//        query.lastError();
//        if (query.lastError()) qFatal("DB Error: %s", query.lastError().databaseText());
    }

//    QVector<Task> fetch_tasks() {
//        QSqlQuery query;
//        QVector<Task> tasks;
//        while (query.next()) {
//            int task_id = query.value(0).toInt();
//            QString task_title = query.value(1).toString();
//            qDebug() << task_id << task_title;
//            Task task(nullptr, task_id, task_title);
//            tasks.append(task);
//        }
//        return tasks;
//    }

private:
    QSqlDatabase m_db;
};


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    Database db;
    db.init_db();

    return QGuiApplication::exec();
}

// https://stackoverflow.com/questions/3001615/qt-moc-with-implementations-inside-of-header-files
#include "main.moc"
