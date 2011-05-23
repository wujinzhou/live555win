#include "mytest.h"
#include "AvCore.h"
#include <QBoxLayout>
mytest::mytest(void)
:m_btnSplit("split",this)
,m_btnComb("combination",this)
{
	QObject::connect(&m_btnSplit,SIGNAL(clicked()),this,SLOT(Split()));
	QObject::connect(&m_btnComb,SIGNAL(clicked()),this,SLOT(combination()));
	QBoxLayout*  layout = new QBoxLayout(QBoxLayout::LeftToRight,this);
	layout->addWidget(&m_btnSplit);
	layout->addWidget(&m_btnComb);
	
}

mytest::~mytest(void)
{
}

AvCore  core;
void mytest::Split()
{

	char* argv[] = {"d:\\test2.flv" , "d:\\t1.flv" , "d:\\t2.flv"};

	core.encoder("d:\\1.mp4" , "d:\\ÁªÏët1.flv" ,0,90,"720x480",700000,"d:\\ffpresets\\libx264-fast.ffpreset",3);
}
void mytest::combination()
{

	char* argv[] = {"d:\\test2.flv" , "d:\\t1.flv" , "d:\\t2.flv"};

	core.combination(2,argv+1,argv[0],"d:\\testout.flv");
}