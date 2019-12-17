	#include <QApplication>
	#include <QPushButton>
	#include <QWidget>

	int main(int argc, char **argv) {
	  QApplication a(argc, argv);
	  QWidget w;
	  QPushButton b("hideme", &w);
	  w.show();
	  QObject::connect(&b, &QPushButton::clicked,
	                   [&w]() { w.setWindowState(Qt::WindowMinimized); });
	  return a.exec();
	}
