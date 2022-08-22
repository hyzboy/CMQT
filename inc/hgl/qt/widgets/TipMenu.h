#ifndef HGL_QT_TIP_MENU_INCLUDE
#define HGL_QT_TIP_MENU_INCLUDE

#include<QMenuBar>

namespace hgl
{
    namespace qt
    {
        class TipMenu:public QMenu
        {
            Q_OBJECT

        public:

            using QMenu::QMenu;

            bool event(QEvent *)override;
        };//class TipMenu:public QMenu
    }//namespace qt
}//namespace hgl
#endif//HGL_QT_TIP_MENU_INCLUDE
