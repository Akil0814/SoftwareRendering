#include <iostream>
#include <Windows.h>

#include <cmath>

#include "application/application.h"
#include "gpu/gpu.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup" )//更改main入口

void draw_circle(int cx, int cy, int radius)
{
	const int steps = 360; // 越大越圆

	for (int i = 0; i < steps; i++)
	{
		float theta = 2.0f * PI * i / steps;

		int x = static_cast<int>(cx + radius * std::cos(theta));
		int y = static_cast<int>(cy + radius * std::sin(theta));

		sgl->draw_point(x, y, Color::Blue);
	}
}

void on_render()
{
	sgl->clear();

	for (uint32_t i = 0; i < App->get_width(); ++i)
	{
		sgl->draw_point(i,100,Color::Red);
	}

	draw_circle(250, 250, 50);
}


int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance, //本应用程序实例句柄，唯一指代当前程序
	_In_opt_ HINSTANCE hPrevInstance, //本程序前一个实例，一般是null
	_In_ LPWSTR lpCmdLine, //应用程序运行参数
	_In_ int nCmdShow) //窗口如何显示（最大化、最小化、隐藏），不需理会
{
	if (!App->init(hInstance, 800, 600))
		return -1;

	//将bmp指向的内存配置到sgl当中
	sgl->init_surface(App->get_width(), App->get_height(),App->get_canvas());

	bool active = true;
	while (active)
	{
		active = App->peek_message();
		on_render();
		App->show();
	}

	return 0;
}