#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //connect each number button with a function that will do the calculations and print them on a label
    connect(ui->Button_0,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_1,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_2,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_3,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_4,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_5,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_6,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_7,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_8,&QPushButton::clicked,this,&MainWindow::digit_pressed);
    connect(ui->Button_9,&QPushButton::clicked,this,&MainWindow::digit_pressed);

    connect(ui->comma, &QPushButton::clicked, this, &MainWindow::digit_pressed);

    connect(ui->add, &QPushButton::clicked, this, &MainWindow::binaryOp);
    connect(ui->subtract, &QPushButton::clicked, this, &MainWindow::binaryOp);
    connect(ui->divide, &QPushButton::clicked, this, &MainWindow::binaryOp);
    connect(ui->multiply, &QPushButton::clicked, this, &MainWindow::binaryOp);

    ui->label->setText("0");
}

void MainWindow::on_percentage_clicked()
{
    QString _name{};
    double _val{0.0};

    _val = ui->label->text().toDouble();
    _val *= .01;
    _name = QString::number(_val,'g',15);
    ui->label->setText(_name);
}

void MainWindow::on_equals_clicked()
{
    qDebug() << "Equals";

    //convert QStrings into doubles and do the calculations
    _dob1 = _num1.toDouble();
    _dob2 = _num2.toDouble();
    double _result{0.0};
    double _secondNum = ui->label->text().toDouble(); //catch the number entered after an operation button is pressed/clicked

    if(_add || _subtract || _multiply || _divide)
    {
        if(_add)
        {
            qDebug() << "add equation";
            _result = _dob1 + _secondNum;
            _add = false;
        }
        else if(_subtract)
        {
            qDebug() << "subtraction";
            _result = _dob1 - _secondNum;
            _subtract = false;
        }
        else if(_multiply)
        {
            qDebug() << "multiplication";
            _result = _dob1 * _secondNum;
            _multiply = false;
        }
        else if(_divide)
        {
            qDebug() << "division";
            if(_secondNum == 0.0){return;}

            _result = _dob1 / _secondNum;
            _divide = false;
        }
    }

    ui->label->setText(QString::number(_result));

    _num1 = QString::number(_result);
    _num2.clear();
}

void MainWindow::digit_pressed()
{
    qDebug() << "Digit";
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(button != nullptr);

    if(!_binaryOpClicked)
    {
        if(!_num1.contains('.') || button->text() != '.') //make sure that the first number consists of only one comma
        {
            qDebug() << "num 1";
            _num1.append(button->text());
            ui->label->setText(_num1);
        }
        else{return;}
    }
    else
    {
        if(!_num2.contains('.') || button->text() != '.') //make sure that the second number consists of only one comma
        {
            qDebug() << "num 2";
            _num2.append(button->text());
            ui->label->setText(_num2);
        }
        else{return;}
    }
}

void MainWindow::binaryOp()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(button != nullptr);
    _operator = button->text();
    _dob1 = ui->label->text().toDouble();

    //save the operator clicked and use it in onEqualsClicked method
    if(_operator == "+")        {_add = true;}
    else if(_operator == "-")   {_subtract = true;}
    else if(_operator == "x")   {_multiply = true;}
    else                        {_divide = true;}

    _binaryOpClicked = true;
}

//clear the screen and reset all variables
void MainWindow::on_Clear_clicked()
{
    ui->label->clear();
    _num1.clear();
    _num2.clear();
    _dob1 = .0;
    _dob2 = .0;
    _binaryOpClicked = false;
}

void MainWindow::on_changeSign_clicked()
{
    double _change = ui->label->text().toDouble();
    _change *= -1;
    ui->label->setText(QString::number(_change));
}

void MainWindow::on_backspace_clicked()
{
    QString _changeTxt = ui->label->text();
    _changeTxt.chop(1);
    _binaryOpClicked ? _num2 = _changeTxt : _num1 = _changeTxt;
    ui->label->setText(_changeTxt);
}

//method to type the numbers and operators directly from the keyboard
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_0:
        ui->Button_0->animateClick();
        break;
    case Qt::Key_1:
        ui->Button_1->animateClick();
        break;
    case Qt::Key_2:
        ui->Button_2->animateClick();
        break;
    case Qt::Key_3:
        ui->Button_3->animateClick();
        break;
    case Qt::Key_4:
        ui->Button_4->animateClick();
        break;
    case Qt::Key_5:
        ui->Button_5->animateClick();
        break;
    case Qt::Key_6:
        ui->Button_6->animateClick();
        break;
    case Qt::Key_7:
        ui->Button_7->animateClick();
        break;
    case Qt::Key_8:
        ui->Button_8->animateClick();
        break;
    case Qt::Key_9:
        ui->Button_9->animateClick();
        break;
    case Qt::Key_Comma: case Qt::Key_Period:
        ui->comma->animateClick();
        break;
    case Qt::Key_Plus:
        ui->add->animateClick();
        break;
    case Qt::Key_Minus:
        ui->subtract->animateClick();
        break;
    case Qt::Key_Asterisk:
        ui->multiply->animateClick();
        break;
    case Qt::Key_Slash:
        ui->divide->animateClick();
        break;
    case Qt::Key_Enter: case Qt::Key_Equal:
        ui->equals->animateClick();
        break;
    case Qt::Key_Backspace:
        ui->backspace->animateClick();
    default: break;
    }
}
