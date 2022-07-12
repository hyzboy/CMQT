#include<hgl/qt/QtVulkanWindow.h>

namespace hgl
{
    bool QtVulkanWindow::event(QEvent* e)
    {
        switch(e->type())
        {
            case QEvent::UpdateRequest:
    //            render();
                break;

            case QEvent::PlatformSurface:
                break;


            default: break;
        }
    }

    void QtVulkanWindow::exposeEvent(QExposeEvent*){}
    void QtVulkanWindow::hideEvent(QHideEvent* ev){}

    void QtVulkanWindow::keyPressEvent(QKeyEvent*){}
    void QtVulkanWindow::keyReleaseEvent(QKeyEvent*){}
    void QtVulkanWindow::mouseMoveEvent(QMouseEvent*){}
    void QtVulkanWindow::mousePressEvent(QMouseEvent*){}
    void QtVulkanWindow::mouseReleaseEvent(QMouseEvent*){}
    void QtVulkanWindow::resizeEvent(QResizeEvent*){}
    void QtVulkanWindow::moveEvent(QMoveEvent*){}
    void QtVulkanWindow::wheelEvent(QWheelEvent*){}
}//namespace hgl
