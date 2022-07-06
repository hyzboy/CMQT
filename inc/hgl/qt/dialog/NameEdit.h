#pragma once

#include<QDialog>
#include<QLabel>
#include<QLineEdit>

namespace hgl
{
    namespace qt
    {
        namespace dialog
        {
            class NameEdit:public QDialog
            {
                Q_OBJECT

            protected:

                QLineEdit *name_edit;

                QLabel *hint_label;

                void OnCancelClicked();

            protected:

                virtual bool OnNameCheck(QString &)=0;

            public:

                NameEdit(const QString &,const QString &);
                virtual ~NameEdit()=default;

                virtual void OnOKClicked();
            };//class NameEdit:public QDialog
        }//namespace dialog
    }//namespace qt
}//namespace hgl
