#ifndef GRAF_H
#define GRAF_H

#include "function.h"
#include "par_window.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

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
