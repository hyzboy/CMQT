#include<hgl/qt/widgets/TipMenu.h>
#include<QToolTip>
#include<QHelpEvent>

namespace hgl
{
    namespace qt
    {
        bool TipMenu::event(QEvent *e)
        {
            if(e->type()==QEvent::ToolTip)
            {
                QHelpEvent *helpEvent=static_cast<QHelpEvent *>(e);
                QAction *action=actionAt(helpEvent->pos());
                if(action)
                {
                    QToolTip::showText(helpEvent->globalPos(),action->toolTip());
                    return true;
                }
            }

            return QMenu::event(e);
        }
    }//namespace qt
}//namespace hgl
