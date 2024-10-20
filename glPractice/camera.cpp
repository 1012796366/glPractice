#include "camera.h"

camera::camera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraTarget - cameraPosition);
	pitch = 0.0f;
	yaw = -90.0f;
	zoom = 90.0f;
	
	auto tempUp = glm::vec3(0.0f, 1.0f, 0.0f);			// ��ʱָ���������ϵ�����
	// ������˵�˳������Ӱ��ģ�a��b�պ÷�����b��a
	// ������������Ȼ��ֱ����������������;�������������ɵ�ƽ��
	cameraXaxis = glm::normalize(glm::cross(tempUp, cameraDirection));
	// �����x���뷽��������ˣ��õ���������ֱ��x���Լ�����������ɵ�ƽ�棬��Ϊ�����y��
	cameraYaxis = glm::cross(cameraDirection, cameraXaxis);
	// �����z�����������������������Ƿ���պ��෴(cameraDirection)
	// cameraZaxis = glm::normalize(cameraPosition - cameraTarget);			// �������
	view = glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraYaxis);
}

glm::mat4 getView(camera* cam)
{
	cam->view = glm::lookAt(cam->cameraPosition, cam->cameraPosition + cam->cameraDirection, cam->cameraYaxis);
	return cam->view;
}

camera defaultCamera;