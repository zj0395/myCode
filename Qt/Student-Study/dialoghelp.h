#ifndef DIALOGHELP_H
#define DIALOGHELP_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

#define INFORMATION( title, word )\
{\
    QMessageBox::information( this, title, word );\
}

#define CHECK_EMPTY( userName, info )\
{\
    if( userName.isEmpty() )\
    {\
        INFORMATION( tr("提示"), tr("%1为空").arg(info) );\
        return;\
    }\
}

#endif // DIALOGHELP_H
