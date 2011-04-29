#include "AvCore.h"
#include <Windows.h>
#include <QApplication>
#include "mytest.h"
int main(int argc,char* argv[])
{
	QApplication  app(argc,argv);

	mytest  test;
	test.show();
	return app.exec();

}