#include<QWindow>
#include<QVulkanInstance>

namespace hgl
{
    class Window;

    namespace
    {
        QVulkanInstance *qt_vulkan_instance=nullptr;
    }

    VkSurfaceKHR CreateVulkanSurface(VkInstance vk_inst,Window *w)
    {
        if(vk_inst==VK_NULL_HANDLE)return(VK_NULL_HANDLE);
        if(!w)return(VK_NULL_HANDLE);

        QWindow *qwin=(QWindow *)w;

        qt_vulkan_instance=new QVulkanInstance();
        qt_vulkan_instance->setVkInstance(vk_inst);

        if(qt_vulkan_instance->create())
        {
            QVulkanInstance::surfaceForWindow(qwin);
        }
        else
        {
            delete qt_vulkan_instance;
            qt_vulkan_instance=nullptr;
        }
    }
}