#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <boost/chrono.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(NULL));

    ui->setupUi(this);

    // header
    _simulator = new simulator(this);

    ui->matrixSizeSlider->setTickInterval(1);
    ui->matrixSizeSlider->setMaximum(10);
    connect(ui->matrixSizeSlider, SIGNAL (valueChanged(int)), ui->matrixSizeNumber, SLOT (display(int)));

    ui->threadSizeSlider->setMaximum(200);
    connect(ui->threadSizeSlider, SIGNAL (valueChanged(int)), ui->threadSizeNumber, SLOT (display(int)));

    connect(ui->matrixSizeSetButton, SIGNAL (clicked()), this, SLOT (setMatrixSize()));
    connect(ui->threadSizeSetButton, SIGNAL (clicked()), this, SLOT (setThreadSize()));

    ui->matrixAView->setShowGrid(false);
    ui->matrixAView->verticalHeader()->setVisible(false);
    ui->matrixAView->horizontalHeader()->setVisible(false);
    ui->matrixBView->setShowGrid(false);
    ui->matrixBView->verticalHeader()->setVisible(false);
    ui->matrixBView->horizontalHeader()->setVisible(false);
    ui->matrixCView->setShowGrid(false);
    ui->matrixCView->verticalHeader()->setVisible(false);
    ui->matrixCView->horizontalHeader()->setVisible(false);
    //

    //about matrix
    connect(ui->matrixAResetButton, SIGNAL (clicked()), this, SLOT (resetA()));
    connect(ui->matrixBResetButton, SIGNAL (clicked()), this, SLOT (resetB()));
    connect(ui->matrixCCalculateButton, SIGNAL (clicked()), this, SLOT (calculateMatrix()));
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMatrixSize()
{
    _simulator->setMatrixSize(ui->matrixSizeSlider->value());
    ui->logText->append("matrx size is changed\n");
}

void MainWindow::setThreadSize()
{
    _simulator->setThreadSize(ui->threadSizeSlider->value());
    ui->logText->append("thread number is changed\n");
}

void MainWindow::showMatrix(const matrix* mat, int idx) // idx 0 : A, idx 1 : B, idx 2 : C
{
    QTableWidget *cur;
    if(idx == 0)    cur = ui->matrixAView;
    if(idx == 1)    cur = ui->matrixBView;
    if(idx == 2)    cur = ui->matrixCView;

    if(mat->size() <= (1<<5))
    {
        cur->setRowCount(mat->size());
        cur->setColumnCount(mat->size());
        for(int i = 0; i < mat->size(); i++)
            for(int j = 0; j < mat->size(); j++)
            {
                QTableWidgetItem* ccur = new QTableWidgetItem();
                ccur->setText(QString::number(mat->getArr(i, j)));
                ccur->setTextAlignment(Qt::AlignCenter);
                cur->setItem(i, j, ccur);
            }
    }
    else
    {
        cur->setRowCount((1<<5)+1);
        cur->setColumnCount((1<<5)+1);
        for(int i = 0; i < (1<<5); i++)
        {
            for(int j = 0; j < (1<<5); j++)
            {
                QTableWidgetItem* ccur = new QTableWidgetItem();
                ccur->setText(QString::number(mat->getArr(i, j)));
                ccur->setTextAlignment(Qt::AlignCenter);
                cur->setItem(i, j, ccur);
            }
            QTableWidgetItem* ccur = new QTableWidgetItem();
            ccur->setText("...");
            ccur->setTextAlignment(Qt::AlignCenter);
            cur->setItem(i, (1<<5), ccur);
        }
        for(int j = 0; j <= (1<<5); j++)
        {
            QTableWidgetItem* ccur = new QTableWidgetItem();
            ccur->setText("...");
            ccur->setTextAlignment(Qt::AlignCenter);
            cur->setItem((1<<5), j, ccur);
        }
    }

    cur->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::resetA()
{
    _simulator->resetA();
    ui->logText->append("matrx A reset\n");
}

void MainWindow::resetB()
{
    _simulator->resetB();
    ui->logText->append("matrx B reset\n");
}

void MainWindow::calculateMatrix()
{
    boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
    _simulator->calculate();

    boost::chrono::duration<double> t = boost::chrono::system_clock::now() - start;

    ui->logText->append("matrix size : " + QString::number(_simulator->getMatrixSize()) +
                        ", additional thread number : " + QString::number(_simulator->getThreadSize()) +
                        ", result : " + QString::number(t.count()) + "(s)\n");
}
