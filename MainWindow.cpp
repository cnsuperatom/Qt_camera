#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_camera(new EloamCamera)
{
    ui->setupUi(this);

    // Init Widget Font type and size
    initWidgetFont();

    // Init Widget Style
    initWidgetStyle();

    m_camera->init();

    // Set Window Title
    this->setWindowTitle(tr("Eloam Camera Control"));

    // Set Menu Bar Version Info
    ui->menuVersion->addAction("V0.1 2020-Nov-11");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_camera;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    qDebug() << "MainWindow::resizeEvent ui->centralWidget->size()=" << ui->centralWidget->size();
    m_camera->resize(ui->centralWidget->size());
}

void MainWindow::initWidgetFont()
{
}

void MainWindow::initWidgetStyle()
{
    m_camera->setParent(ui->centralWidget);
}
