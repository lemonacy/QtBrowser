#ifndef JXBRIDGE_H
#define JXBRIDGE_H
#include <QObject>

class JXBridge : QObject
{
    Q_OBJECT
public:
    static JXBridge * instance();

public slots:
    void sayHi(QString name);

private:
    JXBridge();
};

#endif // JXBRIDGE_H
