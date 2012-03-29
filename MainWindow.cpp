#include "MainWindow.h"
#include <QDebug>
#include <QPixmap>
#include <map>

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
    (*m_camera) >> frame;
    QImage i((uchar*)frame.datastart, frame.size().width, frame.size().height, m_formats[std::pair<int, int>(frame.depth(), frame.channels())]);
    m_imgLabel->setPixmap(QPixmap::fromImage(i));
}

void MainWindow::takeScreenshot() {
    qDebug() << "saving: " << m_imgLabel->pixmap()->save("image.png");
}
