#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QChar>
#include <QKeyEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();
    void keyPressEvent(QKeyEvent* event); //reimplementation of the default function

private slots:
    void digit_pressed();
    void binaryOp();
    void on_percentage_clicked();
    void on_equals_clicked();
    void on_Clear_clicked();
    void on_changeSign_clicked();
    void on_backspace_clicked();

private:
    Ui::MainWindow *ui;

    double _dob1{.0};
    double _dob2{.0};
    QString _num1{};
    QString _num2{};
    QString _operator{};

    //status
    bool _binaryOpClicked{false};
    bool _divide{false};
    bool _add{false};
    bool _subtract{false};
    bool _multiply{false};
    bool _checked{false};

};
#endif // MAINWINDOW_H
