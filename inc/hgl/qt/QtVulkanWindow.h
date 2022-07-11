#pragma once

#include<QWindow>

namespace hgl
{
    class QtVulkanWindow:public QWindow
    {
    public:

        bool event(QEvent* e) override;

        void exposeEvent(QExposeEvent*) override;
        void hideEvent(QHideEvent* ev) override;

        void keyPressEvent(QKeyEvent*) override;
        void keyReleaseEvent(QKeyEvent*) override;
        void mouseMoveEvent(QMouseEvent*) override;
        void mousePressEvent(QMouseEvent*) override;
        void mouseReleaseEvent(QMouseEvent*) override;
        void resizeEvent(QResizeEvent*) override;
        void moveEvent(QMoveEvent*) override;
        void wheelEvent(QWheelEvent*) override;
    };//public QtVulkanWindow
}//namespace hgl
