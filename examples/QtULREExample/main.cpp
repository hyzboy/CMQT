// QtULREExample：Qt 窗口外壳（菜单）+ 内部运行 ULRE 引擎示例
//
// 演示窗口后端抽象：
//   QtWindow(hgl::Window 适配) → AppFramework::SetExternalWindow 注入
//   → ULRE Vulkan 渲染进 QWindow → QTimer 驱动 WorkManager::RunFrame
//
// 渲染内容：复用 example/Basic/DrawTriangle.cpp 的 TestApp（ECS 三角形）
// 换示例：改 #include 目标文件（需各自链接依赖与工作目录资源）

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>
#include <QWidget>

#include <hgl/qt/QtWindow.h>
#include <hgl/framework/WorkManager.h>
#include <hgl/framework/WorkObject.h>

// 复用 ULRE 示例的 WorkObject（与 RunFramework<TestApp> 相同的类）
#include <DrawTriangle.cpp>

using namespace hgl;

namespace
{
    QWidget *CreateVulkanContainer(QWindow *qwin, QWidget *parent)
    {
        QWidget *container = QWidget::createWindowContainer(qwin, parent);
        container->setMinimumSize(640, 480);
        return container;
    }
}

int main(int argc,char *argv[])
{
    QApplication qt_app(argc,argv);
    qt_app.setApplicationName(QStringLiteral("QtULREExample"));

    // ── 主窗口（Qt 外壳）──
    QMainWindow main_win;
    main_win.setWindowTitle(QStringLiteral("Qt ULRE - DrawTriangle"));
    main_win.resize(1280, 720);

    QMenuBar *bar=main_win.menuBar();

    QMenu *file_menu=bar->addMenu(QStringLiteral("File"));
    file_menu->addAction(QStringLiteral("Exit"),&main_win,[&main_win]{main_win.close();});

    QMenu *help_menu=bar->addMenu(QStringLiteral("Help"));
    help_menu->addAction(QStringLiteral("Qt Version"),&main_win,[]{
        QMessageBox::information(nullptr,QStringLiteral("Qt Version"),
            QStringLiteral("Qt %1\nULRE Vulkan inside Qt window").arg(QString::fromLatin1(qVersion())));
    });

    // ── Qt 窗口后端（hgl::Window 适配）──
    QtWindow qt_win(OS_TEXT("QtULREExample"));

    // ── ULRE 应用框架：注入外部窗口，不创建/不拥有 ──
    AppFramework app(OS_TEXT("QtULREExample"));

    if(!app.SetExternalWindow(&qt_win))
        return(-1);

    if(!app.Init(1280,720))
        return(-1);

    // 中央区域：Qt 窗口 → 容器（事件与渲染都走 qt_win）
    QWidget *container=CreateVulkanContainer(qt_win.GetQWindow(),&main_win);
    main_win.setCentralWidget(container);

    // ── ECS 世界 + WorkObject（同 RunFramework<TestApp> 初始化流程）──
    std::shared_ptr<ecs::ECSContext> world;
    if(app.GetECSContext())
        world=std::shared_ptr<ecs::ECSContext>(app.GetECSContext(),[](ecs::ECSContext *){});

    WorkManager wm(&app);

    auto *wo=new TestApp();
    wo->_InitializeWithECSContext_INTERNAL_DO_NOT_CALL(world);

    if(!wo->Init())
    {
        delete wo;
        return(-2);
    }

    // ── Qt 事件循环驱动 ULRE 帧循环（≈60 FPS）──
    QTimer frame_timer;
    frame_timer.setTimerType(Qt::PreciseTimer);
    frame_timer.setInterval(16);

    QObject::connect(&frame_timer,&QTimer::timeout,[&]{
        app.Tick();
        wm.RunFrame(wo);

        if(wo->IsDestroy())
            main_win.close();
    });

    main_win.show();
    qt_win.Show();
    frame_timer.start();

    const int result=qt_app.exec();

    frame_timer.stop();

    delete wo;

    return(result);
}
