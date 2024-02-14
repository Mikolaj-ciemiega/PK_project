#ifndef PAR_WINDOW_H
#define PAR_WINDOW_H

#include <QDialog>
#include "function.h"

namespace Ui {
class par_window;
}

struct out_data
{
    parameters par_selcted; type_of_fun type_selected; axis ax;
};

class par_window : public QDialog
{
    Q_OBJECT

public:
    explicit par_window(function &out_data, QWidget *parent = nullptr);
    explicit par_window(QWidget *parent = nullptr);
    ~par_window();

private slots:
    void on_push_line_pressed();

    void on_push_para_pressed();

    void on_push_root_pressed();

    void on_push_log_pressed();

    void on_push_sin_pressed();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_par_b_valueChanged(double arg1);

private:
    Ui::par_window *ui;
    void get_para();


    parameters para;
    type_of_fun type;
    function *out_data;
};

#endif // PAR_WINDOW_H
