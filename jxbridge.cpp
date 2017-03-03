#include "jxbridge.h"
#include <QMessageBox>

JXBridge * JXBridge::instance()
{
    static JXBridge s_obj;
    return &s_obj;
}

JXBridge::JXBridge()
{
}

void JXBridge::sayHi(QString name)
{
    QMessageBox::information(NULL, tr("Information"), tr("Hi, ") + name, QMessageBox::Yes);
}
