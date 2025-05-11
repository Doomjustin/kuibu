# FLTK basics
本章将教你使用FLTK的基础知识

## 编写你的第一个FLTK程序
在1.3.x及更早的版本中，所有的FLTK程序都要求将<FL/Fl.h>作为首个include的头文件。<br/>
从1.4.0起，这个要求已放宽，仅当使用Fl class或者枚举等功能时才需要包含<FL/Fl.h>。本文档中的示例代码可能任然会处处包含它，虽然这并不是必须的。<br/>
此外，程序必须include其使用的每一个FLTK class的头文件，代码清单1展示了一个使用FLTK的简单Hello,World窗口程序。

```c++
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char* argv[])
{
    auto *window = new Fl_Window{ 340, 180 };
    auto *box = new Fl_Box{ 20, 40, 300, 100, "Hello, World!" };
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();

    window->show(argc, argv);
    return Fl::run();
}
```

在include必要的头文件之后，程序会创建一个window。之后所有的Widget都会自动成为这个window的子部件。

```c++
auto *window = new Fl_Window{ 340, 180 };
```

接着创建一个box，其label为"Hello, World!"。FLTK会自动将这个box添加到当前的group Widget: window中。

```c++
auto *box = new Fl_Box{ 20, 40, 300, 100, "Hello, World!" };
```

然后，设置box的类型和label的字体，大小和样式。

```c++
box->box(FL_UP_BOX);
box->labelfont(FL_BOLD+FL_ITALIC);
box->labelsize(36);
box->labeltype(FL_SHADOW_LABEL);
```

告知FLTK将不再向window添加更多Widget。

```c++
window->end();
```

最后，显示关闭window并进入FLTK事件循环。

```c++
window->show(argc, argv);
return Fl::run();
```

最终程序将显示"Hello, World!"窗口。你可以通过关闭文件或者ESC键来推出程序。

## 创建Widget
Widget是通过c++的new来创建的。大多数的Widget的构造函数包括：

```c++
Fl_Widget(x, y, width, height, label)
```

x和y决定了Widget或者window在屏幕上的位置。在FLTK中，窗口或者屏幕的左上角为坐标原点（即x=0，y=0）。<br/>
width和height决定了Widget或window的尺寸。Widget的最大尺寸通常受底层窗口系统或硬件限制。<br/>
《What Units Do FLTK Functions Use?》一文描述了FLTK为x，y，width，height以及所有图形量采用的计量单位。<br/>
label是指用于标注Widget的字符串指针或者nullptr。若未指定，标签默认显示为NULL。label字符串必须存储在静态内存中（如字符串常量），因为FLTK不会复制该字符串-仅直接使用指针。

## 创建Widget层级结构
Widget通常按功能分组，这些组(Group)可以再次组合，从而形成Widget的层析结构。FLTK通过自动添加在MyGroup->begin()和MyGroup->end()之间创建的所有Widget，简化了Group的填充过程。在此例中，MyGroup是当前组。<br/>
新创建的Group及其派生的Widget会在构造函数中隐身调用begin()，从而有效地将所有随后创建的Widget添加到自身，知道调用end()为止。<br/>
在一个Group上调用end()会将当前组转移到该Widget的父级。在顶级Group上调用end()会将当前组设置为nullptr。<br/>
将当前组设置为nullptr将停止自动层级结构。然后可以使用Fl_Group::add(...)和Fl_Group::insert(...)来手动添加新的Widget。

## get/set方法
box->box(FL_UP_BOX)设置Fl_Box绘制的框的类型，将其从默认的FL_NO_BOX（表示不绘制任何框）更改为其他类型。在"Hello, World!"示例中，使用FL_UP_BOX，表示将在Widget周围绘制一个凸起的按钮边框。更多细节请参阅Box Types部分。<br/>
你可以通过box-box()来检查框类型。FLTK使用方法名重载来为get/set方法创建简短的名称。set始终采用void name(type)的形式，而get始终采用type name() const的形式

## 属性变化后的重绘(redraw)
几乎所有的get/set都是非常快速，简短的内联函数，因此效率极高。然而，set不会自动调用redraw() - 需要自行调用。这大大减少了代码量和执行时间。唯一常见的例外是value()会在必要时调用redraw()，以及label()会在必要时调用redraw_label()。

## Labels
所有的Widget都支持label。对于窗口而言，label会显示在标题栏上。示例程序调用了labelfont()，labelsize()，labeltype()方法。<br/>
lablefont()用于设置label的字体和样式。实例中使用的FL_BOLD和FL_ITALIC。<br/>
labelsize()以FLTK单位设置字体高度。<br/>
labeltyoe()设置标签类型。FLTK内部支持normal，embossed(浮雕)和shadowed(阴影)标签，还可以根据需要添加更多类型。<br/>
所有标签选项的完整列表在Labels and Labels Types章节

## 显示窗口
show()用于显示Widget或Window。对于Window，还可以提供命令行参数，允许用户自定义窗口的外观，大小和位置。

## 主事件循环
所有的FLTK应用程序（以及大多数GUI程序）都基于一个简单的事件处理模型。用户操作如鼠标移动，按钮点击和键盘活动会生成时间并发送到应用程序。