#define QT_DEBUG_PLUGINS 1
#include <QApplication>
#include <unistd.h>
#include <pthread.h>
#include <iostream>

int main(int argc, char * argv[]) {
	pthread_attr_t attr;
	std::cout<<"sizeof(attr):"<<sizeof(attr)<<"\n";
    {
        QApplication app(argc, argv);
        sleep(1);
        QCoreApplication::quit();
    }
    sleep(1);
    return 0;
}
