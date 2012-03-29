#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>

#include <opencv/cv.h>
#include <opencv/highgui.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QLabel * m_imgLabel;
    QPushButton * m_saveButton;
    QVBoxLayout * m_layout;
    QTimer m_timer;

    cv::VideoCapture * m_camera;

    std::map<std::pair<int, int>, QImage::Format> m_formats;

private slots:
    void updateImage();
    void takeScreenshot();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
