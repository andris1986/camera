#include "MainWindow.h"
#include <QDebug>
#include <QPixmap>
#include <map>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    m_formats[std::pair<int, int>(CV_8U, 3)] = QImage::Format_RGB888;
    m_formats[std::pair<int, int>(CV_8S, 3)] = QImage::Format_RGB888;
    m_formats[std::pair<int, int>(CV_16U, 3)] = QImage::Format_RGB16;
    m_formats[std::pair<int, int>(CV_16S, 3)] = QImage::Format_RGB16;
    m_formats[std::pair<int, int>(CV_32S, 3)] = QImage::Format_RGB32;
    m_formats[std::pair<int, int>(CV_32F, 3)] = QImage::Format_RGB32;
    m_formats[std::pair<int, int>(CV_32S, 4)] = QImage::Format_ARGB32;

    m_camera = new cv::VideoCapture(0);

    m_imgLabel = new QLabel(this);
    m_saveButton = new QPushButton("Capture", this);
    m_layout = new QVBoxLayout();

    m_layout->addWidget(m_imgLabel);
    m_layout->addWidget(m_saveButton);

    this->setCentralWidget(new QWidget(this));
    this->centralWidget()->setLayout(m_layout);

    if(m_camera->isOpened()) {
        qDebug() << "Camera opened";
        connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateImage()));
        connect(m_saveButton, SIGNAL(clicked()), this, SLOT(takeScreenshot()));
        m_timer.setInterval(100);
        m_timer.start();
    }
    else {
        qDebug() << "Camera not opened";
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateImage() {
    cv::Mat frame;
    cv::Mat rgbFrame;
    (*m_camera) >> frame;

    cv::cvtColor(frame, rgbFrame, CV_BGR2RGB);

    QImage i(rgbFrame.ptr(), rgbFrame.size().width, rgbFrame.size().height, m_formats[std::pair<int, int>(rgbFrame.depth(), rgbFrame.channels())]);
    m_imgLabel->setPixmap(QPixmap::fromImage(i));
}

void MainWindow::takeScreenshot() {
    qDebug() << "saving: " << m_imgLabel->pixmap()->save("image.png");
}
