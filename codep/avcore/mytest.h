#pragma once

#include <QWidget>
#include <QPushButton>
class mytest:public QWidget
{
	Q_OBJECT
		QPushButton  m_btnSplit;
	QPushButton  m_btnComb;
public:
	mytest(void);
	~mytest(void);
	public Q_SLOTS:
		void Split();
		void combination();
};
 