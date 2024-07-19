#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVTKOpenGLNativeWidget.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <chrono>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , position(0.0)
    , direction(true)
    , frameCount(0)
    , cameraAngle(0.0)
    , sphereRadius(0.07)
{
    ui->setupUi(this);

    // renderer and window
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    ui->qvtkWidget->setRenderWindow(renderWindow);

    // sphere
    sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(64);
    sphereSource->SetPhiResolution(64);
    sphereSource->SetRadius(sphereRadius);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    sphereActor = vtkSmartPointer<vtkActor>::New();
    sphereActor->SetMapper(mapper);

    renderer->AddActor(sphereActor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    // camera
    camera = vtkSmartPointer<vtkCamera>::New();
    renderer->SetActiveCamera(camera);
    renderer->ResetCamera();

    // floor
    vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<vtkPlaneSource>::New();
    planeSource->SetXResolution(10);
    planeSource->SetYResolution(10);
    vtkSmartPointer<vtkPolyDataMapper> planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    planeMapper->SetInputConnection(planeSource->GetOutputPort());

    floorActor = vtkSmartPointer<vtkActor>::New();
    floorActor->SetMapper(planeMapper);
    floorActor->GetProperty()->SetColor(0.8, 0.8, 0.8);
    floorActor->GetProperty()->SetRepresentationToWireframe();
    renderer->AddActor(floorActor);

    // Setup orientation marker
    axesActor = vtkSmartPointer<vtkAxesActor>::New();
    orientationMarkerWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    orientationMarkerWidget->SetOrientationMarker(axesActor);
    orientationMarkerWidget->SetInteractor(renderWindow->GetInteractor());
    orientationMarkerWidget->SetViewport(0.0, 0.0, 0.2, 0.2);
    orientationMarkerWidget->SetEnabled(1);
    orientationMarkerWidget->InteractiveOff();

    // Setup timers and FPS
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePosition);
    timer->start(16); // Approximately 60 FPS

    fpsTimer = new QTimer(this);
    connect(fpsTimer, &QTimer::timeout, this, &MainWindow::updateFPS);
    fpsTimer->start(1000); // Update FPS

    // Setup FPS label
    fpsLabel = new QLabel(this);
    ui->statusbar->addPermanentWidget(fpsLabel);

    lastTime = std::chrono::steady_clock::now();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePosition()
{
    // Update the position of the sphere
    if (direction)
    {
        position += 0.01;
        if (position > 1.0)
            direction = false;
    }
    else
    {
        position -= 0.01;
        if (position < -1.0)
            direction = true;
    }

    sphereActor->SetPosition(position, 0, 0.2);

    // Move the camera around the sphere
    // cameraAngle += 0.01;
    // double radius = 5.0;
    // double camX = radius * cos(cameraAngle);
    // double camY = radius * sin(cameraAngle);
    // camera->SetPosition(camX, camY, 2.0);
    // camera->SetFocalPoint(0.0, 0.0, 0.0);
    // camera->SetViewUp(0.0, 0.0, 1.0);

    ui->qvtkWidget->renderWindow()->Render();

    frameCount++;
}

void MainWindow::updateFPS()
{
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - lastTime;
    double fps = frameCount / elapsed_seconds.count();

    fpsLabel->setText(QString("FPS: %1").arg(fps, 0, 'f', 2));

    frameCount = 0;
    lastTime = now;
}
