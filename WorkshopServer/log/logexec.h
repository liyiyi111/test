#ifndef LOGEXEC_H
#define LOGEXEC_H

#include <QObject>

class LogExec : public QObject
{
    Q_OBJECT
protected:
    explicit LogExec(QObject *parent = nullptr);

public:
    static LogExec *getObject();
    /**
     * @brief 输出一条日志
     * @param msg
     */
    void OutPutMsg(QString msg);
    /**
     * @brief 输出一条警告日志
     * @param msg
     */
    void OutPutWarningMsg(QString msg);
    /**
     * @brief 输出一条错误日志
     * @param msg
     */
    void OutPutErrorMsg(QString msg);

protected:
    static LogExec *obj;

};

#endif // LOGEXEC_H
