#ifndef GRAF_H
#define GRAF_H

#include "function.h"
#include "par_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class graf;
}
QT_END_NAMESPACE

class graf : public QMainWindow
{
    Q_OBJECT

public:
    graf(QWidget *parent = nullptr);
    ~graf();

private slots:

    void on_create_pressed();

    void on_display_left_pressed();

    void on_display_right_pressed();

    void on_edit_pressed();

    void on_delete_2_pressed();

private:
    Ui::graf *ui;
    void create_view();
    void display_par();
    QString type2string(type_of_fun type);

    int open_par_window(function &in);

    std::list<function> function_list;
    int ammount=0;
    int curr=0;
    QChart *chart = nullptr;
    QChartView *view = nullptr;

    par_window *window;

};
#endif // GRAF_H
