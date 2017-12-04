#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ImageProcessUI;
}

class D3DVideoRender;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
	void on_pushButton_open_clicked(void);
	void on_pushButton_save_clicked(void);
	void on_horizontalSliderSoftSkin_valueChanged(int value);
	void on_horizontalSliderWhite_valueChanged(int value);
	void on_horizontalSliderSharp_valueChanged(int value);
	void on_horizontalSliderThin_valueChanged(int value);

private:
	void processing();

private:
    Ui::ImageProcessUI* m_ui;
	QImage              m_imgLoad;
	char*				m_imgData;
	int					m_dataWidth;
	int					m_dataHeight;
	D3DVideoRender*	m_videoProcess;
};

#endif // MAINWINDOW_H
