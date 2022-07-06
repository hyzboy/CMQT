#include<hgl/qt/dialog/NameEdit.h>
#include<QVBoxLayout>
#include<QPushButton>

namespace hgl
{
    namespace qt
    {
        namespace dialog
        {
            NameEdit::NameEdit(const QString &hint_text,const QString &str)
            {
                setModal(true);

                QVBoxLayout *layout=new QVBoxLayout(this);

                {
                    QLabel *lab=new QLabel(hint_text,this);

                    lab->setAlignment(Qt::AlignLeft);

                    layout->addWidget(lab);
                }

                {
                    name_edit=new QLineEdit(str,this);

                    name_edit->setAlignment(Qt::AlignCenter);

                    name_edit->setCursorPosition(0);

                    layout->addWidget(name_edit);
                }

                {
                    hint_label=new QLabel(this);

                    hint_label->setAlignment(Qt::AlignCenter);

                    layout->addWidget(hint_label);
                }
    
                //按钮区
                {
                    QWidget *button_widget=new QWidget(this);
                    QHBoxLayout *button_layout=new QHBoxLayout(button_widget);

                    //确定、取消按钮
                    {
                        QPushButton *ok_button=new QPushButton(button_widget);
                        ok_button->setText(tr("OK"));
                        connect(ok_button,&QPushButton::clicked,this,&NameEdit::OnOKClicked);

                        button_layout->addWidget(ok_button,0,Qt::AlignRight);

                        QPushButton *cancel_button=new QPushButton(button_widget);
                        cancel_button->setText(tr("Cancel"));
                        connect(cancel_button,&QPushButton::clicked,this,&NameEdit::OnCancelClicked);
            
                        button_layout->addWidget(cancel_button,0,Qt::AlignLeft);
                    }

                    layout->addWidget(button_widget);
                }

                resize(layout->sizeHint());
            }

            void NameEdit::OnCancelClicked()
            {
                close();
            }

            void NameEdit::OnOKClicked()
            {
                QString err_text;

                if(OnNameCheck(err_text))
                    close();

                QPalette palette=hint_label->palette();
                palette.setColor(hint_label->foregroundRole(),Qt::GlobalColor::red);

                hint_label->setPalette(palette);
                hint_label->setText(err_text);
            }
        }//namespace dialog
    }//namespace qt
}//namespace hgl
