#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "CommonUtil.h"
#include "D3DRender.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::ImageProcessUI),
	m_imgData(NULL),
	m_dataWidth(0),
	m_dataHeight(0),
	m_videoProcess(NULL)
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_ui;
	if (m_videoProcess)
	{
		delete []m_videoProcess;
		m_videoProcess = NULL;
	}

	if (m_imgData)
	{
		delete []m_imgData;
		m_imgData = NULL;
	}
}

void MainWindow::on_pushButton_open_clicked(void)
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image Files (*.png *.jpg *.bmp)"));

	if (fileName.isEmpty())
	{
		MessageBox(0, 0, "fileName is NULL!", 0);
	}

	bool bLoad = m_imgLoad.load(fileName);

	if(!bLoad)
	{
		MessageBox(0, 0, "m_imgLoad load fail", 0);
	}

	m_ui->label_origin->setPixmap(QPixmap::fromImage(m_imgLoad));

	int imageWidth  = m_imgLoad.width();
	int imageHeight = m_imgLoad.height();
	if (!m_imgData || imageWidth != m_dataWidth || imageHeight != m_dataHeight)
	{
		m_dataWidth  = imageWidth;
		m_dataHeight = imageHeight;

		if (m_imgData)
		{
			delete []m_imgData;
			m_imgData = NULL;
		}

		m_imgData = new char[m_dataWidth * m_dataHeight * 4];
	}

	//加载处理图片时，也初始化D3D
	m_videoProcess = new D3DVideoRender();
	m_videoProcess->Init(NULL,m_dataWidth,m_dataHeight);
}

void MainWindow::on_pushButton_save_clicked(void)
{
	
}

void MainWindow::on_horizontalSliderSoftSkin_valueChanged(int value)
{
	m_videoProcess->setSoftSkin(value);
	processing();
}
void MainWindow::on_horizontalSliderWhite_valueChanged(int value)
{
	m_videoProcess->setWhiteValue(value);
	processing();
}
void MainWindow::on_horizontalSliderSharp_valueChanged(int value)
{
	m_videoProcess->setSharp(value);
	processing();
}

void MainWindow::on_horizontalSliderThin_valueChanged(int value)
{
	m_videoProcess->setThin(value);
	processing();
}

void MainWindow::processing()
{
	if (!m_videoProcess)
	{
		m_videoProcess = new D3DVideoRender();
		m_videoProcess->Init(NULL,m_dataWidth,m_dataHeight);
	}
	
	m_videoProcess->RenderToTexture((LPBYTE)m_imgLoad.bits(),(LPBYTE)m_imgData,m_dataWidth,m_dataHeight,m_dataWidth * 4);
	QImage image((unsigned char*)m_imgData,m_dataWidth,m_dataHeight,QImage::Format_ARGB32);
	m_ui->label_process->setPixmap(QPixmap::fromImage(image));
}
