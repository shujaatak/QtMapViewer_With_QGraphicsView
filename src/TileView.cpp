#include "TileView.h"
#include <QGraphicsPixmapItem>

const int TileView::MARKER_Z_LAYER = 10;
const int TileView::TILE_Z_LAYER = 0;
const int TileView::TILE_TEXT_Z_LAYER = 1;
const int TileView::CROSSHAIR_Z_LAYER = 5;

TileView::TileView(QWidget* parent) : QGraphicsView(parent)
{
    this->setParent(parent);
	this->initialize();
}

void TileView::initialize()
{
	this->setupViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	this->update();

	this->scene = new QGraphicsScene(this);
	this->setScene(scene);
	this->setBackgroundBrush(QBrush(QColor(20,20,20), Qt::SolidPattern));

	this->setCursor(Qt::OpenHandCursor);

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	this->setFrameStyle(QFrame::Box);
	this->setMouseTracking(true);

	this->markerHashMap = new QHash<int, QGraphicsPixmapItem*>();
	this->zoomEnable = false;

	this->animationScrolling = new QPropertyAnimation(this,"CurrentCenterPoint");
	this->animationScrolling->setDuration(600);
	this->animationScrolling->setEasingCurve(QEasingCurve::OutQuad);
}

void TileView::addTile(QImage loadedImage, int x, int y, int imgSize)
{	
	// Convert from QImage to QPixmap
	QPixmap displayedImage = QPixmap::fromImage(loadedImage);

	// Add tile
  //  QGraphicsPixmapItem* displayedItem = new QGraphicsPixmapItem(displayedImage, scene);
    QGraphicsPixmapItem* displayedItem = new QGraphicsPixmapItem(displayedImage);
    scene->addItem(displayedItem);
	displayedItem->setPos(x*imgSize,y*imgSize);
	displayedItem->setZValue(TILE_Z_LAYER);

	QRectF bound = scene->itemsBoundingRect();
	QRectF enlargedBound = QRectF(bound.x() - 100, bound.y() - 100, bound.width() + 200, bound.height() + 200);

    setSceneRect(enlargedBound);
}

void TileView::addMarker(int id, double x, double y, QImage image)
{
	if (!markerHashMap->contains(id))
	{
		// Convert from QImage to QPixmap
		QPixmap pixmap = QPixmap::fromImage(image);
		// Add Pixmap to the Scene
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        scene->addItem(item);
		item->setPos(x,y);
		item->setZValue(1);
		item->setTransformationMode(Qt::SmoothTransformation);

		markerHashMap->insert(id, item);
	}
}

void TileView::removeMarker(int id)
{
	if(markerHashMap->contains(id))
	{
		QGraphicsPixmapItem* item = markerHashMap->value(id);
		scene->removeItem(item);
		delete item;
		markerHashMap->remove(id);
	}
}

void TileView::editMarker(int id, double x, double y)
{
	if(markerHashMap->contains(id))
	{
		QGraphicsPixmapItem* item = markerHashMap->value(id);
		item->setPos(x,y);
	}
}

void TileView::clearAllMarker()
{
	QHash<int, QGraphicsPixmapItem*>::const_iterator i;
	for (i = markerHashMap->constBegin(); i != markerHashMap->constEnd(); ++i)
	{
		QGraphicsPixmapItem* item = markerHashMap->value(i.key());
		scene->removeItem(item);
		delete item;
	}
	markerHashMap->clear();
}

void TileView::SetCenter(const QPointF& centerPoint)
{
	CurrentCenterPoint = centerPoint;
    centerOn(CurrentCenterPoint);

	QPointF topLeft = mapToScene (0, 0);
    QPointF bottomRight = mapToScene(this->width(), this->height());

    QRectF rectangle(topLeft, bottomRight);
	emit visibleSceneChanged(rectangle);
}

void TileView::mousePressEvent(QMouseEvent* event)
{
    //For panning the view
    LastPanPoint = event->pos();
    setCursor(Qt::ClosedHandCursor);

    // stop the inertial animation
    animationScrolling->stop();
    animationScrolling->setEndValue(GetCenter());
}

void TileView::mouseReleaseEvent(QMouseEvent* event)
{
    setCursor(Qt::OpenHandCursor);

    if(!LastPanPoint.isNull()) 
	{
        //Get how much we panned
        QPointF delta = mapToScene(LastPanPoint) - mapToScene(event->pos());
        LastPanPoint = event->pos();
    }
    LastPanPoint = QPoint();
}

void TileView::mouseMoveEvent(QMouseEvent* event)
{
    float latOffset = 0;
    float lonOffset = 0;

    if(!LastPanPoint.isNull()) 
	{
        // Get how much we panned
        QPointF delta = mapToScene(LastPanPoint) - mapToScene(event->pos());
        LastPanPoint = event->pos();

		setSceneRect(sceneRect().x() + delta.x(), sceneRect().y() + delta.y(), sceneRect().width(), sceneRect().height());

        // Update the center ie. do the pan
        SetCenter(GetCenter() + delta);

        // Set animation properties
        animationScrolling->setDuration(200 + delta.manhattanLength() * 3);
        if (animationScrolling->duration() > 1000)
		{
            animationScrolling->setDuration(1000);
        }

        // Set animation end
        animationScrolling->setEndValue(GetCenter()+delta*14);
    }
}

void TileView::wheelEvent(QWheelEvent* event)
{
	int delta = event->delta();
	if (delta > 0)
	{
		emit zoomDown();
	} 
	else if (delta < 0)
	{
		emit zoomUp();
	}

	if (zoomEnable)
	{
		static float totalScale = 1;
		animationScrolling->stop();
		animationScrolling->setEndValue(GetCenter());

		//Get the position of the mouse before scaling, in scene coords
		QPointF pointBeforeScale(mapToScene(event->pos()));

		//Get the original screen centerpoint
		QPointF screenCenter = GetCenter();

		//Get the rectangle of the visible area in scene coords
		QRectF visibleArea = mapToScene(rect()).boundingRect();

		//Get the scene area
		QRectF sceneBounds = sceneRect();
		
		if(event->orientation() == 1)
		{
			delta = 0;
		}

		double scaleFactor;
		if(delta > 0)
		{
			scaleFactor = 1 + (delta / 2500.0);
		}			
		else
		{
			scaleFactor = 1 + (delta / 3000.0);
		}
			
		if(scaleFactor < 0)
		{
			scaleFactor = 1;
		}

		int heightFactor = visibleArea.height()/scene->itemsBoundingRect().height();
		int widthFactor  = visibleArea.width() /scene->itemsBoundingRect().width();

		if( ((visibleArea.height() < scene->itemsBoundingRect().height() || visibleArea.width() < scene->itemsBoundingRect().width()))
			&& delta < 0)
		{
			scale(scaleFactor, scaleFactor);
		}        
		else if(visibleArea.height() > 100 && delta > 0)
		{
			scale(scaleFactor, scaleFactor);
		}
		else
		{
			scale(scaleFactor, scaleFactor);
		}

		QPointF pointAfterScale(mapToScene(event->pos()));
		QPointF offset = pointBeforeScale - pointAfterScale;
		QPointF newCenter = screenCenter + offset;
		SetCenter(newCenter);
		update();
	}
}

void TileView::clearScene()
{
	clearAllMarker();
	scene->clear();
}

void TileView::centerScene(const QPointF& centerPoint)
{
    centerOn(centerPoint);

    // Invisible crosshair... can be used for debug if we draw diff color
    QGraphicsLineItem* item1 = new QGraphicsLineItem(0, centerPoint.y(), INT_MAX, centerPoint.y());
    item1->setPen(QPen(QColor(0, 0, 0, 0)));
    item1->setZValue(10);

    QGraphicsLineItem* item2 = new QGraphicsLineItem(centerPoint.x(), 0, centerPoint.x(), INT_MAX);
    item2->setPen(QPen(QColor(0, 0, 0, 0)));
    item2->setZValue(10);

    scene->addItem(item1);
    scene->addItem(item2);

    CurrentCenterPoint = centerPoint;
	SetCenter(centerPoint);
}

void TileView::paintEvent(QPaintEvent* event)
{
    // let base implementation draw child widgets
    QGraphicsView::paintEvent(event);
}

void TileView::isZoomEnable(bool)
{
	zoomEnable = true;
}
