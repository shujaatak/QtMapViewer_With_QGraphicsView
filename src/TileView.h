#ifndef TILE_VIEW
#define TILE_VIEW

#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QImage>
#include <QMenu>
#include <QGLWidget>
#include <QDebug>
#include <QHash>

class TileView : public QGraphicsView
{
    Q_OBJECT
    // QPropertyAnimation
    Q_PROPERTY(QPointF CurrentCenterPoint READ GetCenter WRITE SetCenter)

	public:
		TileView(QWidget* parent = NULL);
		
		// Tile methods
		void addTile(QImage loadedImage, int x, int y, int imgSize);

		// Marker methods
		void addMarker(int id, double x, double y, QImage image);
		void removeMarker(int id);
		void editMarker(int id, double x, double y);
		void clearAllMarker();

		// Scene methods
		void clearScene();
		void centerScene(const QPointF& centerPoint);
		void isZoomEnable(bool);

	signals:
		void visibleSceneChanged(QRectF visibleRect);
		void zoomUp();
		void zoomDown();

private:
		void initialize();

		QPointF GetCenter() { return CurrentCenterPoint; }
		void SetCenter(const QPointF& centerPoint);

		virtual void mousePressEvent(QMouseEvent* event);
		virtual void mouseReleaseEvent(QMouseEvent* event);
		virtual void mouseMoveEvent(QMouseEvent* event);
		virtual void wheelEvent(QWheelEvent* event);
		virtual void paintEvent(QPaintEvent* event);

		bool	zoomEnable;
		QHash<int, QGraphicsPixmapItem*>*	markerHashMap;

		QPointF CurrentCenterPoint; 
		QPoint  LastPanPoint;
		QGraphicsScene* scene;

		QPropertyAnimation*     animationScrolling;
		QPropertyAnimation*     animationScale;

		static const int MARKER_Z_LAYER;
		static const int TILE_Z_LAYER;
		static const int TILE_TEXT_Z_LAYER;
		static const int CROSSHAIR_Z_LAYER;
};

#endif
