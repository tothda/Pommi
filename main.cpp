#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#include <QTimer>
#include <QFileSystemModel>
#include <QQmlContext>

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

struct Task2 {
    int id;
    QString title;
    bool is_done;
};

class TaskListModel: public QAbstractListModel {
public:
    explicit TaskListModel(QObject* parent):
        QAbstractListModel(parent),
        task_list(new QVector<Task2>)
    {
        for (int i=0; i < 100; i++) {
            task_list->append(Task2{1, QString("Task %1").arg(i), false});
        }
    }


    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        int row = index.row();
        auto task = task_list->at(row);
        switch (role) {
            case Roles::ID:
                return QVariant(task.id);
            case Roles::TITLE:
                return QVariant(task.title);
            case Roles::IS_DONE:
                return QVariant(task.is_done);
            default:
                return QVariant();
        }
    }

    QModelIndex parent(const QModelIndex &child) const override {
        return {};
    }

    int rowCount(const QModelIndex &parent) const override {
        return task_list->size();
    }

    int columnCount(const QModelIndex &parent) const override {
        return 1;
    }

    enum Roles {
        ID = Qt::UserRole,
        TITLE,
        IS_DONE
    };

    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> roles;
        roles[Roles::ID] = "id";
        roles[Roles::TITLE] = "title";
        roles[Roles::IS_DONE] = "is_done";
        return roles;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override {
        qDebug() << "Data changed" <<index.row() << value.toString();
        int row = index.row();
        auto task = task_list->at(row);

        switch (role) {
            case Roles::TITLE:
                task.title = value.toString();
                break;
            case Roles::IS_DONE:
                task.is_done = value.toBool();
                break;
            default:
                return false;
        }
        task_list->replace(row, task);
        emit dataChanged(index, index, {role});
        return true;
    }

private:
    QVector<Task2>* task_list;
};


QSystemTrayIcon* create_system_tray_icon(QObject* parent) {
    qDebug() << "System Tray available : " << QSystemTrayIcon::isSystemTrayAvailable();
    qDebug() << "System Tray supports messages: " << QSystemTrayIcon::supportsMessages();
    auto system_tray_icon = new QSystemTrayIcon(parent);
    QIcon icon(":/tray_icon.png");
    system_tray_icon->setToolTip("This is a very funny tooltip :)");
//    qDebug() << "Icon size: " << icon.actualSize(QSize(32,32));
    system_tray_icon->setIcon(icon);

    // Create menu
    auto menu = new QMenu();
    auto action = new QAction();
    action->setText("Hello");
    menu->addAction(action);
    system_tray_icon->setContextMenu(menu);
    system_tray_icon->show();
    system_tray_icon->showMessage("Hello","Hallo");
    return system_tray_icon;
}

void set_up_timed_messages(QSystemTrayIcon* tray_icon) {
    auto timer = new QTimer(tray_icon);
    bool visible = true;
    QObject::connect(timer, &QTimer::timeout, [=](){
        qDebug() << "Timer triggered!" << tray_icon;
        tray_icon->showMessage("Message from timer!","Time to relax!",
                QSystemTrayIcon::MessageIcon::Warning, 10000);
        // Show/hide tray icon. Works!
        // tray_icon->setVisible(!tray_icon->isVisible());
    });
    timer->start(2000);
}

void test_model_view_architecture() {
    auto model = new QFileSystemModel;
    QObject::connect(model, &QFileSystemModel::directoryLoaded, [model](const QString &directory) {
        QModelIndex parentDirIndex = model->index(directory);
        int numRows = model->rowCount(parentDirIndex);
        int numColumns = model->columnCount(parentDirIndex);
        auto roles = model->roleNames();
        qDebug() << "numRows" << numRows << ", numColumns" << numColumns;
        qDebug() << "Roles:";

        for (int i = 0; i < roles.size(); i++) {
            auto name = roles.value(i);
            qDebug() << " - " << name;
        }

        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numColumns; col++) {
                QModelIndex childIndex = model->index(row, col, parentDirIndex);
                QString text = model->data(childIndex, Qt::DisplayRole).toString();
                qDebug() << row << "," << col << "=" << text;
            }

            // QModelIndex childIndex = model->index(row, 0, parentDirIndex);
            // QString text = model->data(childIndex, Qt::DisplayRole).toString();
            // QVariant d = model->data(childIndex, roles.key("fileIcon"));
            // qDebug() << row << text << d;
        }
    });
    model->setRootPath(QDir::currentPath());
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QSystemTrayIcon* tray_icon = create_system_tray_icon(&app);

    // This does not work for some reason...
    //set_up_timed_messages(tray_icon);

    test_model_view_architecture();
    TaskListModel task_list_model(&app);
    engine.rootContext()->setContextProperty("task_list", &task_list_model);

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
