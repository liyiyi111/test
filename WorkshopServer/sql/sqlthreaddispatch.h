#ifndef SQLTHREADDISPATCH_H
#define SQLTHREADDISPATCH_H

#include <QObject>

class SqlExec;
class QSemaphore;

/**
 * @brief 数据库连接池调度类
 */
class SqlThreadDispatch : public QObject
{
    Q_OBJECT
protected:
    explicit SqlThreadDispatch(QObject *parent = nullptr);

public:
    static SqlThreadDispatch* getObject();

    /**
     * @brief 获取数据库操作对象
     * @return 操作对象
     */
    SqlExec *getExec();
    /**
     * @brief 释放操作对象
     * @param exec 操作对象
     */
    void freeExec(SqlExec *exec);
    /**
     * @brief 获取当前状态的文本信息
     * @return
     */
    QString getStateText();

protected:
    void initDispatch();

    static SqlThreadDispatch *obj;
    QList <SqlExec *> sqlDispatchList;
    QSemaphore *semaphore;

};

#endif // SQLTHREADDISPATCH_H
