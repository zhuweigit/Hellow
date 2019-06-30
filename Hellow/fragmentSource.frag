#version 330 core 

in vec3 FragPos;  //����
in vec3 Normal;   //������
in vec2 TexCoord;  //uv ����

struct Material
{
vec3 ambient;        //vec3��ɫ     sampler2D ��ͼɫ
sampler2D diffuse;
sampler2D specuar;
float shininess;
};
   
struct LightPoint      // ���� ����!!!!!
{
float constant; 
float linear;   
float quadratic;
};

struct LightSpot
{
 // float cosPhy;
  float cosPhyInner;  
 float cosPhyOutter ; 
};

uniform LightSpot lightS; 
uniform LightPoint lightP;    //�������������
uniform vec3 lightDirUniform;   //�ƹ�����
uniform Material material;  //�Ѷ��󴫽�����������������������11111     //�Ѿ���ʵ�����������ݿ�����������material.diffuse�ýṹ��������������)��
uniform vec3 ambientColor;     //������ɫ
uniform vec3 objColor;         //�������ɫ
uniform vec3 lightPos;         
uniform vec3 lightColor;
uniform vec3 CammeraPos;   //�ӽ�����  �ӵ㣨������㣩

 out vec4 FragColor;  
void main() 
{    
 
  float dist=length(lightPos-FragPos);
  float attenuation= 1.0f/(lightP.constant +lightP.linear*dist+ lightP.quadratic*(dist*dist));  //���Դ��˥��ֵ
 
 vec3 lightDir=normalize(lightPos-FragPos);    //lightDir��������
   vec3 reflectVec=reflect(-lightDir,Normal); 
   vec3 cammeraVec=normalize(CammeraPos-FragPos);  
  
  //specular 
   float specularAmount=pow(max(dot(reflectVec,cammeraVec),0),32);   //pow�η��� ˥���� 
   vec3 specular =texture(material.specuar,TexCoord).rgb*specularAmount*lightColor;                 //��Ӧ�нǵ�ֵ�����������ӳ���淴�����
     //diffuse	
   vec3 diffuse=texture(material.diffuse,TexCoord).rgb*max(dot(lightDir,Normal),0)*lightColor;   //����UV����ȥͼƬ��ȡ��Ӧ��ͼƬ��ɫ
	
   vec3 ambient=texture(material.diffuse,TexCoord).rgb*ambientColor;  

   float cosTheta = dot(normalize(FragPos-lightPos),  -1 * lightDirUniform);    
  
  float spotRatio;
 if(cosTheta>lightS.cosPhyInner)
 {//inside
   spotRatio=1.0f;
 }
 else if(cosTheta>lightS.cosPhyOutter)
 {//middle
    spotRatio=1.0f-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOutter-lightS.cosPhyInner);
 }
 else{//outsider
 spotRatio=0;
 }
  FragColor=vec4(  (ambient+ (diffuse+specular)*spotRatio)*objColor ,1.0);


 //  if(cosTheta > lightS.cosPhy)          //??????????????????????????????????????????????????????????????
//   {
//   //inside
//   FragColor=vec4(  (ambient+ (diffuse+specular))*objColor ,1.0);   //���������  *attenuation //Ϊʲô������˥��ֵ56���к��߼��ϻ���ʱ����ʱû��        
//
//   }
//   else  //outside
//   {
//    FragColor=vec4( ambient *objColor ,1.0);   //���������	
//
//   }
//

 } 