#include "generatevideo.h"
#include "qmessagebox.h"
GenerateVideo::GenerateVideo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GenerateVideo::~GenerateVideo()
{

}

void GenerateVideo::on_generatePushButton_clicked()
{
	QString profileId = ui.profileId_lineEdit->text();

	QMessageBox Msgbox;
	Msgbox.setText("The Profile ID : "+profileId);
	Msgbox.exec();
}