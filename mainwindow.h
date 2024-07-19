#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPlaneSource.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <chrono>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updatePosition();
    void updateFPS();

private:
    Ui::MainWindow *ui;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkSphereSource> sphereSource;
    vtkSmartPointer<vtkActor> sphereActor;
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkActor> floorActor;
    vtkSmartPointer<vtkAxesActor> axesActor;
    vtkSmartPointer<vtkOrientationMarkerWidget> orientationMarkerWidget;
    QTimer *timer;
    QTimer *fpsTimer;
    QLabel *fpsLabel;
    double position;
    bool direction;
    int frameCount;
    std::chrono::time_point<std::chrono::steady_clock> lastTime;
    double cameraAngle;
    double sphereRadius;
};

#endif // MAINWINDOW_H
