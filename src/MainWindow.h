#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QMainWindow>

#include "TileView.h"
#include "TileManager.h"
#include "MapMarker.h"
#include <QPushButton>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
        MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void standardButtonPressed();
		void cycleButtonPressed();
		void cycleTransportButtonPressed();

		void zoomUpButtonPressed();
		void zoomDownButtonPressed();

	private:
		MapMarker planeMarker;

		TileManager* tileManager;
		TileView* imageView;

		QPushButton* standardButton;
		QPushButton* cycleButton;
		QPushButton* cycleTransportButton;

		QPushButton* zoomUpButton;
		QPushButton* zoomDownButton;

    private:
		virtual void wheelEvent(QWheelEvent* event);

};

#endif
