#include "dialog.h"
#include "serail_app.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    SerailApp *serailPort = new SerailApp();


}

Dialog::~Dialog()
{

}
