#include "MainWindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	//Create Main Layout
    QVBoxLayout* vBoxLayout = new QVBoxLayout();    
	QWidget* centralWidget = new QWidget(this);
	
	imageView = new TileView(centralWidget);
	vBoxLayout->addWidget(imageView);
	setCentralWidget(centralWidget);
	centralWidget->setLayout(vBoxLayout);
	this->resize(800,600);

	standardButton = new QPushButton("Standard");
	standardButton->setParent(imageView);
	standardButton->move(10, 20);
	QObject::connect
	(
		standardButton,		SIGNAL(pressed()), 
		this,				SLOT(standardButtonPressed())
	);
	
	cycleButton = new QPushButton("Cycle");
	cycleButton->setParent(imageView);
	cycleButton->move(10, 50);
	QObject::connect
	(
		cycleButton,		SIGNAL(pressed()), 
		this,				SLOT(cycleButtonPressed())
	);

	cycleTransportButton = new QPushButton("Cycle Transport");
	cycleTransportButton->setParent(imageView);
	cycleTransportButton->move(10, 80);
	QObject::connect
	(
		cycleTransportButton,	SIGNAL(pressed()), 
		this,					SLOT(cycleTransportButtonPressed())
	);

	zoomUpButton = new QPushButton("Zoom Up");
	zoomUpButton->setParent(imageView);
	zoomUpButton->move(10, 110);
	QObject::connect
	(
		zoomUpButton,			SIGNAL(pressed()), 
		this,					SLOT(zoomUpButtonPressed())
	);

	zoomDownButton = new QPushButton("Zoom Down");
	zoomDownButton->setParent(imageView);
	zoomDownButton->move(10, 140);
	QObject::connect
	(
		zoomDownButton,			SIGNAL(pressed()), 
		this,					SLOT(zoomDownButtonPressed())
	);

	// Create the tile manager
    tileManager = new TileManager(imageView);

    double latitude1 = 45.713851;
    double longitude1 = -74.07692;
    double latitude2 = 45.420624;
    double longitude2 = -73.427353;
	int zoomFactor = 6;

	tileManager->fovChanged(latitude1, longitude1, latitude2, longitude2, zoomFactor, true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::standardButtonPressed()
{
	tileManager->changeTileType(STANDARD);
}

void MainWindow::cycleButtonPressed()
{
	tileManager->changeTileType(CYCLE);
}

void MainWindow::cycleTransportButtonPressed()
{
	tileManager->changeTileType(CYCLE_TRANSPORT);
}

void MainWindow::zoomUpButtonPressed()
{
	tileManager->zoomUp();
}

void MainWindow::zoomDownButtonPressed()
{
	tileManager->zoomDown();
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
	int delta = event->delta();

	if (delta > 0)
	{
		tileManager->zoomDown();
	}
	else if (delta < 0)
	{
		tileManager->zoomDown();
	}
}
