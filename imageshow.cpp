#include "imageshow.h"
#include "ui_imageshow.h"
#include <QTextCodec>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QFile>
#include <QTextStream>
#include <QDebug>

ImageShow::ImageShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageShow)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
    ui->setupUi(this);

    this->set_title(QObject::tr("ͼƬ����ת������"));
    this->other_operation();
    this->init_connector();
}

void ImageShow::other_operation()
{
    ui->radioButtonHex->setChecked(true);

    ui->btnImageToData->setEnabled(false);
    ui->btnTextToImage->setEnabled(false);
}

void ImageShow::set_title(const QString &text)
{
    this->setWindowTitle(text);
}

void ImageShow::init_connector()
{
    QObject::connect(ui->btnImage, SIGNAL(clicked()), this, SLOT(do_get_image_name()));
    QObject::connect(ui->btnText, SIGNAL(clicked()), this, SLOT(do_get_txt_name()));
    QObject::connect(ui->lineEditImage, SIGNAL(textChanged(QString)), this, SLOT(do_btn_enable(QString)));
    QObject::connect(ui->lineEditText, SIGNAL(textChanged(QString)), this, SLOT(do_btn_enable(QString)));

    QObject::connect(ui->btnImageToData, SIGNAL(clicked()), this, SLOT(do_image_to_text()));
}

// ��ȡͼƬ����
void ImageShow::image_to_data(QString image_name, QString data_name, QString my_format)
{
    qDebug() << image_name;
    qDebug() << data_name;
    qDebug() << my_format;
    QImage img(image_name);
    QByteArray ba;
    QBuffer buffer(&ba);
    img.save(&buffer, "JPG");   //����JPG���뱣������
    QByteArray ca = qCompress(ba, 1);

    QByteArray da;
    if ("Hex" == my_format)
    {
        da = ca.toHex();    // ת��Ϊ16����
    }
    else if ("Base64" == my_format)
    {
        da = ca.toBase64();
    }
//    for (int i = 0; i != ca.size(); ++i)
//    {
//        qDebug() << ca.at(i);
//    }

    // ��ͼ������ת��Ϊ�ַ���
    QString txt_str(da);
    QFile txt_out_file(data_name);
    if (txt_out_file.open(QIODevice::WriteOnly))
    {
        txt_out_file.write(txt_str.toLatin1());
        txt_out_file.close();
        QMessageBox::information(this, QObject::tr("��ʾ"),
                                 QObject::tr("ͼ���Ѿ�ת�����"));
    }
}

ImageShow::~ImageShow()
{
    delete ui;
}

void ImageShow::do_get_image_name()
{
    ui->lineEditImage->clear();

    QString file_name = QFileDialog::getOpenFileName(this,
                                                     QObject::tr("��ͼƬ"),
                                                     QDir::currentPath(),
                                                     QString("*.*;;*.jpg;;*.png;;*.gif"));
    if (!file_name.isEmpty())
    {
        ui->lineEditImage->setText(file_name);
    }
    else
    {
        QMessageBox::warning(this, QObject::tr("����"),
                             QObject::tr("����û��Ϊ�˳���ѡ��һ��ͼ���ļ�"));
    }
}

void ImageShow::do_get_txt_name()
{
    ui->lineEditText->clear();

    QString file_name = QFileDialog::getOpenFileName(this,
                                                     QObject::tr("��ȡ�ı��ļ�"),
                                                     QDir::currentPath(),
                                                     QString("*.*;;*.h;;*.c;;*.cpp;;*.asm"));
    if (!file_name.isEmpty())
    {
        ui->lineEditText->setText(file_name);
    }
    else
    {
        QMessageBox::warning(this, QObject::tr("����"),
                             QObject::tr("����û��Ϊ�˳���ѡ��һ���ļ�"));
    }
}

void ImageShow::do_image_enabel()
{
    if (!ui->lineEditImage->text().isEmpty())
    {
        ui->btnImageToData->setEnabled(true);
    }
}

void ImageShow::do_txt_enable()
{
    if (!ui->lineEditText->text().isEmpty())
    {
        ui->btnTextToImage->setEnabled(true);
    }
}

void ImageShow::do_btn_enable(const QString &text)
{
    //
    if (!ui->lineEditImage->text().isEmpty())
    {
        ui->btnImageToData->setEnabled(true);
    }

    if (!ui->lineEditText->text().isEmpty())
    {
        ui->btnTextToImage->setEnabled(true);
    }
}

void ImageShow::do_image_to_text()
{
    QString image_name = ui->lineEditImage->text();
    QString text_name = ui->lineEditText->text();
    QString format_name("");
    if (ui->radioButtonHex->isChecked())
    {
        format_name.append("Hex");
    }
    else if(ui->radioButtonBase->isChecked())
    {
        format_name.append("Base64");
    }

    this->image_to_data(image_name, text_name, format_name);
}
