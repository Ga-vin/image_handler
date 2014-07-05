#ifndef IMAGESHOW_H
#define IMAGESHOW_H

#include <QDialog>

namespace Ui {
class ImageShow;
}

class ImageShow : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageShow(QWidget *parent = 0);
    void other_operation();
    void set_title(const QString &text);
    void init_connector();
    void image_to_data(QString image_name, QString data_name, QString my_format);
    ~ImageShow();
    
private slots:
    void do_get_image_name();
    void do_get_txt_name();
    void do_image_enabel();
    void do_txt_enable();
    void do_btn_enable(const QString &text);
    void do_image_to_text();
private:
    Ui::ImageShow *ui;
};

#endif // IMAGESHOW_H
