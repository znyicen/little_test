// ģ��Ƭ����ɫ��
#version 330 core
out vec4 color;           // Ƭ����ɫ�����������ɫ

in vec3 FragPos;          // ��ǰƬ�Σ������أ�λ��
in vec3 Normal;           // ������
  
uniform vec3 lightPos;    // �ƹ�����
uniform vec3 viewPos;     // �۲�������
uniform vec3 lightColor;  // �ƹ���ɫ
uniform vec3 objectColor; // �������ɫ

void main()
{
	// �ڱ�׼������ɫ����ϵ��0.0f-1.0f��

    // Ambient ����ɫ����������ȫ�ڰ��ĳ�����
    float ambientStrength = 0.1f;                  // ������ǿ��
    vec3 ambient = ambientStrength * lightColor;   // �������Ӽ���
  	
    // Diffuse ������
    vec3 norm = normalize(Normal);                 // ��׼������
    vec3 lightDir = normalize(lightPos - FragPos); // ����ƹⷽ��
    float diff = max(dot(norm, lightDir), 0.0);    // ����ɢ���ǿ��  
    vec3 diffuse = diff * lightColor;              // �õ�ɢ������
    
    // Specular �߹�
    float specularStrength = 0.5f;                 // �߹�ǿ��
    vec3 viewDir = normalize(viewPos - FragPos);   // �������߷���
    vec3 reflectDir = reflect(-lightDir, norm);    // ���㷴������
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // ����߹ⷶΧ
    vec3 specular = specularStrength * spec * lightColor;     // �߹�����
        
    vec3 result = (ambient + diffuse + specular) * objectColor; // ���������յ�Ƭ����ɫ���
    color = vec4(result, 1.0f);
} 