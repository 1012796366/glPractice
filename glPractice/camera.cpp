#include "camera.h"

camera::camera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraTarget - cameraPosition);
	pitch = 0.0f;
	yaw = -90.0f;
	zoom = 90.0f;
	
	auto tempUp = glm::vec3(0.0f, 1.0f, 0.0f);			// 暂时指定绝对向上的向量
	// 向量叉乘的顺序是有影响的，a×b刚好反向于b×a
	// 摄像机右手轴必然垂直于摄像机方向向量和绝对向上向量组成的平面
	cameraXaxis = glm::normalize(glm::cross(tempUp, cameraDirection));
	// 摄像机x轴与方向向量相乘，得到的向量垂直于x轴以及方向向量组成的平面，即为摄像机y轴
	cameraYaxis = glm::cross(cameraDirection, cameraXaxis);
	// 摄像机z轴就是摄像机方向向量，但是方向刚好相反(cameraDirection)
	// cameraZaxis = glm::normalize(cameraPosition - cameraTarget);			// 多余操作
	view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraYaxis);
}

glm::mat4 getView(camera* cam)
{
	cam->view = glm::lookAt(cam->cameraPosition, cam->cameraPosition + cam->cameraDirection, cam->cameraYaxis);
	return cam->view;
}

camera defaultCamera;